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

int main(int argn,char* args[]){
	char* ip = args[1];
	int pto = atoi(args[2]);
	cout << "Esperando cliente" << endl;
	SocketMulticast sock = SocketMulticast(pto);
	PaqueteDatagrama peticion = PaqueteDatagrama(sizeof(string));
	sock.recibe(peticion, ip);
	char* msg = peticion.obtieneDatos();
	char* ip1 = peticion.obtieneDireccion();
	cout << "Se recibio mensaje: " << msg << endl;
	cout << "Ip: " << ip1 << endl;
return 0;
}