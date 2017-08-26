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

SocketDatagrama sock_client = SocketDatagrama(7200);

void *Enviar(void *){
    char ip[16];
    int arreglo[2] = {2,3};
    for (int i = 100; i < 133; i++){
        sprintf(ip, "192.168.0.%d", i);
        cout << "Se envio a: " << ip << endl;
        PaqueteDatagrama pack = PaqueteDatagrama((char *)arreglo, 2*sizeof(int), ip, 7200);
        sock_client.envia(pack);    
    }
}

void *Recibe(void *){
    for (int i = 100; i < 133; i++){
        PaqueteDatagrama paquet_recu = PaqueteDatagrama(sizeof(int));
        sock_client.recibe(paquet_recu);
        int* mensaje = (int *) paquet_recu.obtieneDatos();
        char * ip = paquet_recu.obtieneDireccion();
        cout << "\nla ip:" << ip << " y la respuesta fue: " << mensaje[0] << endl;
    }
}

int main(int args, char *argv[]) {
    //sock_client.setTimeout(0,9);
    pthread_t th1,th2;
    pthread_create(&th1, NULL, Enviar, NULL);
    pthread_create(&th2, NULL, Recibe, NULL);
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
return 0;
}