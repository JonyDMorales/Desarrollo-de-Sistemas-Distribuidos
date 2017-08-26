#include "SocketD/SocketMulticast.h"
#include "SocketD/PaqueteDatagrama.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstdio>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <fcntl.h>
using namespace std;

int puerto = 7200;

int main(int argn,char* args[]){

	char *ip = args[1];
	int pto = atoi(args[2]);
	string msg = args[3];
	int ttl = atoi(args[4]);

	SocketMulticast sock = SocketMulticast(puerto);
	sock.setBroadcast();
	PaqueteDatagrama peticion = PaqueteDatagrama((char*)msg.c_str(), sizeof(msg), ip, pto);
	sock.envia(peticion, ttl);
	cout << "Se envio mensaje: " << msg << endl;
	cout << "Ip: " << ip << endl;
	cout << "Puerto: " << pto << endl;
	cout << "TTL: " << ttl << endl;
return 0;
}