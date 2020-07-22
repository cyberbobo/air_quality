MARIADB_INCLUDE = `mariadb_config --cflags`
COAP2_INCLUDE = -I/usr/include/coap2
INCLUDE = $(MARIADB_INCLUDE) $(COAP2_INCLUDE)

MARIADB_LIBS = `mariadb_config --libs`
COAP2_LIBS =  -L/usr/lib/arm-linux-gnueabihf/ -lcoap-2
LIBS = $(MARIADB_LIBS) $(COAP2_LIBS)

all: air_recorder

air_recorder: main.o
		gcc -o air_recorder $(INCLUDE) main.o common.o $(LIBS)

main.o: main.c
		gcc -o main.o $(INCLUDE) -c main.c $(LIBS) -Wall -O

common.o: common.c
		gcc -c common.c -Wall -O

clean:
		rm -rf *.o

mrproper: clean
		rm -rf air_recorder
