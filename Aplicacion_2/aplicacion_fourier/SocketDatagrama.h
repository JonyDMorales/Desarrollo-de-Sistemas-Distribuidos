#include <stdio.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include "PaqueteDatagrama.h"

#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

class SocketDatagrama {
	public:
		SocketDatagrama( int );
		~SocketDatagrama();
		int recibe( PaqueteDatagrama & );
		int envia( PaqueteDatagrama & );
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s; 
};
#endif