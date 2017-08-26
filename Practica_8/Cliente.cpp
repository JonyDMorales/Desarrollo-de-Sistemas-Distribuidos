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

int main(int args, char *argv[]) {

    SocketDatagrama sock_client = SocketDatagrama(7200);
    sock_client.setTimeout(1,0);
    int arreglo[2]={1,2};
    int espera= -1;
    for (int i = 100; i < 151; ++i){
        char ip[16];
        sprintf(ip, "192.168.0.%d", i);
        PaqueteDatagrama pack = PaqueteDatagrama((char *)&arreglo, 2*sizeof(int), ip, 7200);
        sock_client.envia(pack);

        PaqueteDatagrama paquet_recu = PaqueteDatagrama(sizeof(int));
        espera=sock_client.recibeTimeout(paquet_recu);

        if (espera < 1)
            cout << endl;
            //cout << "no hay respuesta de la ip:" << ip << endl;
        else{
            int* mensaje = (int *) paquet_recu.obtieneDatos();
            cout << "\nla ip:" << ip << " y la respuesta fue: " << mensaje[0] << endl;
        }
    }

return 0;
}