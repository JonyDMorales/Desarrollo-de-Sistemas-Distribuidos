/*
PaqueteDatagrama.cpp
Es donde se encuentran los metodos para obtener informacion del paquete
*/
#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama(void *data, unsigned largo, const char * dirip, int pto) {
	datos = new char[largo];
    memcpy(datos,data,largo);
	strcpy(ip,dirip);
	longitud = largo;
	puerto = pto;
}

PaqueteDatagrama::PaqueteDatagrama(unsigned largo){
	datos = new char[largo];
	longitud = largo;
}

char *  PaqueteDatagrama::obtieneDireccion() {return ip;}

unsigned PaqueteDatagrama::obtieneLongitud() {return longitud;}

int PaqueteDatagrama::obtienePuerto() {return puerto;}

char * PaqueteDatagrama::obtieneDatos() {return datos;}

void PaqueteDatagrama::inicializaPuerto(int pto) {
	puerto = pto;
}

void PaqueteDatagrama::inicializaIP(char *dirip) {
    strcpy(ip,dirip);
}

void PaqueteDatagrama::inicializaDatos(char *data) {
    memcpy(datos,data,longitud);
}