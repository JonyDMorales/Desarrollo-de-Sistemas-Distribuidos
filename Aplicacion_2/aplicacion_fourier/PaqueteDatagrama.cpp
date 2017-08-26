#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama( char * data, unsigned int tam, char * IP, int port ) {
	datos = new char[ tam ];
	longitud = tam;
	inicializaDatos( data);
	//inicializaIp( IP );
	memcpy( ip, IP, 16 * sizeof(char) );
	//inicializaPuerto( port );
	memcpy( (char*)datos, data, longitud);
}

PaqueteDatagrama::PaqueteDatagrama( unsigned int tam ) {
	longitud = tam;
	datos = new char[ tam ];
}

PaqueteDatagrama::~PaqueteDatagrama() { }

char * PaqueteDatagrama::obtieneDireccion() {
	return ip;
}

unsigned int PaqueteDatagrama::obtieneLongitud() {
	return longitud;
}

int PaqueteDatagrama::obtienePuerto() {
	return puerto;
}

char * PaqueteDatagrama::obtieneDatos() {
	return datos;
}

void PaqueteDatagrama::inicializaPuerto( int port ) {
	puerto = port;
}

void PaqueteDatagrama::inicializaIp( char * IP ) {
	memcpy( ip, IP, 16 * sizeof(char) );
}

void PaqueteDatagrama::inicializaDatos( char * data) {
	memcpy( (char*)datos, data, longitud);
}