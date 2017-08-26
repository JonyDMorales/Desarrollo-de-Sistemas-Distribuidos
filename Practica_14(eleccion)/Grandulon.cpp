#include "SocketD/SocketDatagrama.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	vector<int> vec;
	int pto = 9000; 
	int count = atoi(argv[1]);
	char* ip;
	char ips[count][3]; //Todas las ip del anillo
	SocketDatagrama sock = SocketDatagrama(7200);
	sock.setTimeout(1,0);
	int tiempo = 0;
	int elec = 100;

	for (int i = 2, j = 0; i < (count + 2); i++, j++){
		ip = argv[i];
		strcpy(ips[j], ip);
		vec.push_back(atoi(ip));
		cout << vec[j] << " y " << ips[j] << endl;
	}

	PaqueteDatagrama eleccion = PaqueteDatagrama((char *)elec, sizeof(int), "192.168.0.255", pto);
	sock.envia(eleccion);

	while(true){
		//pintaenProceso();
		PaqueteDatagrama solicitud = PaqueteDatagrama(sizeof(int));
		sock.recibe(solicitud);
		int* aux = (int *)solicitud.obtieneDatos();
		if(aux[0] == 100){
			ip = solicitud.obtieneDireccion();
			int num = ((ip[11]*100) + (ip[12]*10) + (ip[13]));
			if(vec[0] > num){

			}else{

			}

		}else{
			continue;
		}

		/*
		PaqueteDatagrama paquet_recu = PaqueteDatagrama(sizeof(vector<int>));
		tiempo = sock.recibe(paquet_recu);

		if (tiempo != -1){
			PaqueteDatagrama eleccion = PaqueteDatagrama(&vec, sizeof(vec), ips[1], pto);
			sock.envia(eleccion);
        }else{
          cout << "Entro" << endl;
          continue;
        }*/
	}

return 0;
}

//./Anillo 9000 1 "192.168.0.105" "192.168.0.113"