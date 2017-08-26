#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <string>
#include <list>


using namespace std;

class SocketDatagrama{
	public:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForanea;
		int s;

	public:
	SocketDatagrama();
	SocketDatagrama(int);
	~SocketDatagrama();
	int recibe(PaqueteDatagrama & p);
	int envia(PaqueteDatagrama & p);
};

#endif