#include <ESP8266WiFi.h>
//#include <WiFi.h>
//#include <WiFiUdp.h>
#include <DHT.h>
#include <SDS011.h>
#include <MQ135.h>
#include <ArduinoOTA.h>   // pour MaJ/debug Over The Air
#include <RemoteDebug.h>
#include <coap-simple.h>

#define DHTTYPE               DHT11
#define SDS011_RXPin          3
#define SDS011_TXPin          1
#define DHTPIN                2
#define MQ135PIN              A0
#define LED_ALERTE_IMMEDIATE  16
#define LED_ALERTE_ANNUELLE   5
#define LED_DONNEE_FIABLE     4

DHT dht(DHTPIN, DHTTYPE);
SDS011 PMSensor;
MQ135 gasSensor = MQ135(MQ135PIN);

float rzero;
float temperature = 0;
float humidity = 0;
float ppm = 0;
float rzero2 = 0;
float p25 = 0;
float p10 = 0;

/*String host = "192.168.1.12";
int port = 80;
String http_url = "http://"+host+":"+port+"/";*/
int periode_transmission = 5000;

RemoteDebug Debug;

WiFiUDP udp;
Coap coap(udp);

// Callback pour la découverte des URIs accessibles
void callback_discovery(CoapPacket &packet, IPAddress ip, int port) {
  coap.sendResponse(ip, port, packet.messageid, "/sensors");
}

// Callback pour renvoyer l'état des capteurs
void callback_sensors(CoapPacket &packet, IPAddress ip, int port) {
  Debug.println("Entrée dans callback_sensors");
  char out[50]; // TODO gérer plus finement
  sprintf(out, "%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f", rzero, p25, p10, ppm, temperature, humidity, rzero2);
  coap.sendResponse(ip, port, packet.messageid, out);
}

void setup() {
  pinMode(LED_ALERTE_IMMEDIATE, OUTPUT);
  pinMode(LED_ALERTE_ANNUELLE, OUTPUT);
  pinMode(LED_DONNEE_FIABLE, OUTPUT);
  pinMode(DHTPIN, INPUT);

  Serial.begin(115200);
  Serial.println();

  dht.begin();
  PMSensor.begin(SDS011_RXPin, SDS011_TXPin);

  // Recuperation du R0 pour la calibration
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  rzero = gasSensor.getCorrectedRZero(temperature, humidity);
  Serial.println(rzero);  // valeur à reporter dans mq135.h RZERO
  // TODO pourquoi j'ai "nan"?

  WiFi.mode(WIFI_STA);  // pour retirer le mode "access-point"
  WiFi.begin("SSID", "PASSWORD");  // Connexion au Wifi
  // TODO securite SSL

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Debug.begin("AirQuality");
  
  ArduinoOTA.setHostname("AirQuality");
  //ArduinoOTA.setPassword("unmotdepasse"); // TODO pour eviter les MaJ OTA par n'importe qui...
  ArduinoOTA.begin();
  
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Initialisation du serveur CoAP et ses URIs
  coap.server(callback_discovery, ".well-known/core");  // Peut mieux faire?
  coap.server(callback_sensors, "sensors");
  coap.start();
  
  digitalWrite(LED_ALERTE_IMMEDIATE, LOW);
  digitalWrite(LED_ALERTE_ANNUELLE, LOW);
  digitalWrite(LED_DONNEE_FIABLE, HIGH);
}

void loop() {
  // MaJ eventuelle Over The Air (wifi)
  ArduinoOTA.handle();
  Debug.handle();

  // TODO : gérer un mode "idle" : pour le SDS, pour le ESP... économie de batterie
  
  delay(periode_transmission);

  /** BLOC MESURES **/
  bool erreur_donnees = false;
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  // alerte : si humidite > 70 ; alors SDS11 non fiable
  if (isnan(temperature) || isnan(humidity) || (humidity > 70)) {
    erreur_donnees = true;
    Debug.println("Erreur de lecture temperature/humidite");
    Debug.println("hum="+String(humidity)+";temp="+String(temperature));
  }
  
  ppm = gasSensor.getCorrectedPPM(temperature, humidity);
  rzero2 = gasSensor.getCorrectedRZero(temperature, humidity);
  
  if (PMSensor.read(&p25, &p10) == 0) {
    // Test des valeurs seuil OMS annuelles et à 3 jours
    if ((p25>25) || (p10>50)) {
      digitalWrite(LED_ALERTE_IMMEDIATE, HIGH);
      digitalWrite(LED_ALERTE_ANNUELLE, LOW);
    } else {
      digitalWrite(LED_ALERTE_IMMEDIATE, LOW);
      if ((p25>10) || (p10>20)) {
        digitalWrite(LED_ALERTE_ANNUELLE, HIGH);
      } else {
        digitalWrite(LED_ALERTE_ANNUELLE, LOW);
      }
    }
  } else {
    erreur_donnees = true;
    Debug.println("Erreur de lecture SDS011");
    Debug.println("Pin RX : " + String(analogRead(SDS011_RXPin)) + "; Pin TX : " + String(analogRead(SDS011_TXPin)));
    p25 = 0;
    p10 = 0;
  }

  Debug.println(String(p10)+"ppm10/20;"+String(p25)+"ppm25/10");

  // Signaler la fiabilite des donnees
  if (erreur_donnees) {
    digitalWrite(LED_DONNEE_FIABLE, LOW);
  } else {
    digitalWrite(LED_DONNEE_FIABLE, HIGH);
  }
  /** FIN BLOC MESURES **/

  coap.loop();
}
