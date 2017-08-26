/*
SocketDatagrama.cpp
Es donde se encuentran los metodos del socket
*/
#include "SocketDatagrama.h" 
#include "PaqueteDatagrama.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <math.h>

using namespace std;

SocketDatagrama::SocketDatagrama(int pto) {
	s = socket(AF_INET, SOCK_DGRAM,0);
	bzero((char *)&direccionLocal,sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr=INADDR_ANY;
	direccionLocal.sin_port = htons(pto);
	bind(s,(struct sockaddr *)&direccionLocal,
	sizeof(direccionLocal));
}

SocketDatagrama::SocketDatagrama() {
	s = socket(AF_INET, SOCK_DGRAM,0);
	bzero((char *)&direccionLocal,sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr=INADDR_ANY;
	direccionLocal.sin_port = htons(0);
	bind(s,(struct sockaddr *)&direccionLocal,
	sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama(){
	close(s);
}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
	socklen_t lon = sizeof(direccionForanea);
	unsigned char x[ 4 ]; 
	char ip[16];
   	int aux = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &lon);
	memcpy( x, (char *)&direccionForanea.sin_addr.s_addr, 4 );
	sprintf( ip, "%d%c%d%c%d%c%d", (int)x[ 0 ], '.', (int)x[ 1 ], '.', (int)x[ 2 ], '.', (int)x[ 3 ] );
	p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(htons(direccionForanea.sin_port));
return aux;
}


int SocketDatagrama::envia(PaqueteDatagrama &p) {
	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   	direccionForanea.sin_family = AF_INET;
   	direccionForanea.sin_port = htons(p.obtienePuerto());
   	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	int aux = sendto(s,(char *)p.obtieneDatos(), p.obtieneLongitud(), 0,
	(struct sockaddr *)&direccionForanea,sizeof(direccionForanea));
return aux;
}

void SocketDatagrama::unsetTimeout(){
	timeout = false;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, 0, 0);
}

void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos){
	tiempo.tv_sec = segundos;
	tiempo.tv_usec = microsegundos;
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&tiempo, sizeof(tiempo));
	timeout = true;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p){
	struct timeval t1, t2, tr;

	int retorno;
	socklen_t clilen;
	clilen = sizeof(direccionForanea);
	gettimeofday(&t1, NULL);
	retorno = recvfrom(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);
	gettimeofday(&t2, NULL);
	if(retorno < 0){
		std :: cout << "Tiempo Excedido" << std :: endl;
		if(errno == EWOULDBLOCK)
			retorno = retorno;
		else
			std :: cout << "Error en recvfrom" << std :: endl;
	}
	if(retorno > 0){
		unsetTimeout();
		timersub(&t2, &t1, &tr);
		std :: cout << "Tiempo de recepcion" << std :: endl;
		std :: cout << "Segundos: " << tr.tv_sec << std :: endl;
		std :: cout << "Microsegundos: " << tr.tv_usec << std :: endl;
		p.inicializaPuerto(ntohs(direccionForanea.sin_port));
		inet_ntop(AF_INET, &(direccionForanea.sin_addr), p.obtieneDireccion(), INET_ADDRSTRLEN);
	}
	
	return retorno;
}