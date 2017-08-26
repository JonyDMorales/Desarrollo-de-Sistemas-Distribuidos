/*
SocketDatagrama.h
Es donde se encuentran los metodos y variables del socket
*/
#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <string>
#include <list>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <strings.h>
using namespace std;

class SocketDatagrama{
	public:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s;
		struct timeval tiempo, t1, t, tr;;
		bool timeout;
	
	public:
		SocketDatagrama();
		SocketDatagrama(int);
		~SocketDatagrama();
		int recibe(PaqueteDatagrama & p);
		int envia(PaqueteDatagrama & p);
		void unsetTimeout();
   		void setTimeout(time_t segundos, suseconds_t microsegundos);
   		int recibeTimeout(PaqueteDatagrama &p);
   		void setBroadcast();
		void unsetBroadcast(); 
};

#endif