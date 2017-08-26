#include "SocketDatagrama.h"

SocketDatagrama::SocketDatagrama( int puerto ) {
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero( ( char * )&direccionLocal, sizeof( direccionLocal ) );
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons( puerto );
	bind( s, ( struct sockaddr * )&direccionLocal, sizeof( direccionLocal ) );
}


SocketDatagrama::~SocketDatagrama() { close( s ); }

int SocketDatagrama::recibe( PaqueteDatagrama &p ) {
	
	int y = recvfrom( s, p.obtieneDatos(), p.obtieneLongitud() * sizeof( char ), 0, ( struct sockaddr * ) &direccionForanea, ( socklen_t * ) sizeof(direccionForanea));
	
	return y;
}

int SocketDatagrama::envia( PaqueteDatagrama &p ) {
	bzero((char *)&direccionForanea, sizeof( direccionForanea ) );
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr( p.obtieneDireccion() );
	direccionForanea.sin_port = htons( p.obtienePuerto() );
	int len = sendto( s, ( char * )p.obtieneDatos(), p.obtieneLongitud() * sizeof( char ), 0, ( struct sockaddr * ) &direccionForanea, sizeof( direccionForanea ));
	return len;
}

