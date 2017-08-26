#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include <iostream>
using namespace std;

int main(){
	int aux = 1;
	SocketDatagrama sock_client = SocketDatagrama(7000);
	PaqueteDatagrama solicitud = PaqueteDatagrama(&aux,sizeof(int),"127.0.0.1",5000);
	sock_client.envia(solicitud);
	PaqueteDatagrama paquet_recu = PaqueteDatagrama(sizeof(struct timeval));
	sock_client.recibe(paquet_recu);
return 0;
}