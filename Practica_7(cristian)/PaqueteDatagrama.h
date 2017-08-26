#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

class PaqueteDatagrama{

	private :
		char *datos;
		char ip[16];
		unsigned longitud;
		int puerto;

	public :
 	PaqueteDatagrama(void *, unsigned , const char *, int);
	PaqueteDatagrama(unsigned );
	char *obtieneDireccion();
	unsigned obtieneLongitud();
	int obtienePuerto();
	char *obtieneDatos();
	void inicializaPuerto(int);
	void inicializaIP(char *);
	void inicializaDatos(char *);
};

#endif