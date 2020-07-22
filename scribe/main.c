#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <coap2/coap.h>

#include "common.h"

#define COAP_RUN_BLOCK    0
#define COAP_RUN_NONBLOCK 1
#define STRING_SIZE 10

// TODO fichier de conf
/* Parametrage SQL */
char* sql_host = "localhost";
char* sql_user = "XXX";
char* sql_pwd = "XXX";
char* sql_db = "air_quality";
/* Parametrage réseau */
char* coap_ip = "AirQuality";
char* coap_port = "5683";

const char* delimiters = ";"; // pour le strtok, plus tard https://codingboost.com/parsing-csv-files-in-c

static u_int8_t response_payload[50];
static size_t response_length;

static void capture_payload(struct coap_context_t *ctx,
                coap_session_t *session,
                coap_pdu_t *sent,
                coap_pdu_t *received,
                const coap_tid_t id)
{
    printf("capture_payload : handler OK!\n");
    size_t payload_length = received->used_size-(received->data-received->token);
    strncpy(response_payload, received->data, payload_length);
    response_length = payload_length;
    printf("received : %s (%d) \n", response_payload, payload_length);
}

int main (void)
{
    coap_context_t  *ctx = NULL;
    coap_session_t *session = NULL;
    coap_address_t dst;
    coap_pdu_t *pdu = NULL;
    
    // Connection à la BDD
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) 
    {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, sql_host, sql_user, sql_pwd, sql_db, 0, NULL, 0) == NULL) 
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    coap_startup();  
    
    /* resolve destination address where server should be sent */
    if (resolve_address(coap_ip, coap_port, &dst) < 0)
    {
        coap_log(LOG_CRIT, "failed to resolve address\n");
        goto finish;
    }
    
    /* create CoAP context and a client session */
    ctx = coap_new_context(NULL);

    if (!ctx || !(session = coap_new_client_session(ctx, NULL, &dst,
                                                    COAP_PROTO_UDP)))
    {
        coap_log(LOG_EMERG, "cannot create client session\n");
        goto finish;
    }
    
    coap_register_response_handler(ctx, capture_payload);

    // Une aide utile (à ranger qq part) : https://dev.mysql.com/doc/refman/8.0/en/mysql-stmt-execute.html
    // Exemple complet : https://docs.oracle.com/cd/E17952_01/mysql-5.1-en/mysql-stmt-execute.html
    MYSQL_STMT *coucou_stmt = mysql_stmt_init(con);

    const char* query_stmt = "INSERT INTO data_v1(RZERO, P25, P10, PPM_CO2, TEMPERATURE, HUMIDITY, RZERO2) VALUES (?, ?, ?, ?, ?, ?, ?)";
    if (mysql_stmt_prepare(coucou_stmt, query_stmt, strlen(query_stmt)))
    {
        // traitement d'erreur
        printf("ERREUR SQL : %d\n", mysql_stmt_error(coucou_stmt)[0]);
        goto finish;
    }

    MYSQL_BIND bind[7];
    float          float_data[7];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type= MYSQL_TYPE_FLOAT;
    bind[0].buffer= (void *)&float_data[0];
    bind[0].is_null= 0;

    bind[1].buffer_type= MYSQL_TYPE_FLOAT;
    bind[1].buffer= (void *)&float_data[1];
    bind[1].is_null= 0;

    bind[2].buffer_type= MYSQL_TYPE_FLOAT;
    bind[2].buffer= (void *)&float_data[2];
    bind[2].is_null= 0;

    bind[3].buffer_type= MYSQL_TYPE_FLOAT;
    bind[3].buffer= (void *)&float_data[3];
    bind[3].is_null= 0;

    bind[4].buffer_type= MYSQL_TYPE_FLOAT;
    bind[4].buffer= (void *)&float_data[4];
    bind[4].is_null= 0;

    bind[5].buffer_type= MYSQL_TYPE_FLOAT;
    bind[5].buffer= (void *)&float_data[5];
    bind[5].is_null= 0;

    bind[6].buffer_type= MYSQL_TYPE_FLOAT;
    bind[6].buffer= (void *)&float_data[6];
    bind[6].is_null= 0;


    while(1)
    {
        /* construct CoAP message */
        pdu = coap_pdu_init(COAP_MESSAGE_CON,
                        COAP_REQUEST_GET,
                        0 /* message id */,
                        coap_session_max_pdu_size(session));
        if (!pdu)
        {
            coap_log( LOG_EMERG, "cannot create PDU\n" );
            goto finish;
        }

        /* add a Uri-Path option */
        const char *uri = "sensors";
        coap_add_option(pdu, COAP_OPTION_URI_PATH, strlen(uri), (unsigned char*)uri);

        //interroger le nodeMCU
        coap_send(session, pdu);
        printf("ECOUTE CONTEXTE COAP : attention si pas de réponse (détecteur hors tension...) on reste figé ici TODO\n");
        coap_run_once(ctx, COAP_RUN_BLOCK);
        /* TODO reprendre la doc https://libcoap.net/doc/reference/4.2.1/man_coap_io.html 
        et https://libcoap.net/doc/reference/4.1.1/net_8c.html#a7d530e6812093b447402018b5fada462
        il y a un truc que j'ai pas compris, pourquoi faut-il utiliser les deux fonctions? */

        // parser le payload
        float_data[0] = atof(strtok(response_payload, delimiters));
        for (int i = 1; i < 7; i++)
        {
            float_data[i] = atof(strtok(NULL, delimiters));
        }
        
        if (mysql_stmt_bind_param(coucou_stmt, bind))
        {
            printf("ERREUR BIND\n");
            goto finish;
        }

        //écrire le résultat dans la BDD, avec mysql stmt
        if (mysql_stmt_execute(coucou_stmt))
        {
            printf("ERREUR EXEC REQUETE : code %d\n", mysql_stmt_errno(coucou_stmt)); //https://mariadb.com/kb/en/mariadb-error-codes/
            printf("ERREUR EXEC REQUETE : %s\n", mysql_error(con));
        }
    }
        
    mysql_stmt_close(coucou_stmt);

    
finish:
    coap_session_release(session);
    coap_free_context(ctx);
    coap_cleanup();
    mysql_close(con);

    return 0;
}
