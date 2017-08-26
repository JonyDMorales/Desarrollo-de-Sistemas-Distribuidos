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

struct parametros{
    char ip[16];
    int arreglo[2];
};

void *Esta_Vivo(void * arg){
    int espera= -1;
    struct parametros *p;
    p =  ( struct parametros *) arg ; 
    PaqueteDatagrama pack = PaqueteDatagrama((char *)p->arreglo, 2*sizeof(int), p->ip, 7200);
    //cout << "Se envio a: " << p->ip << endl;
    sock_client.envia(pack);

    PaqueteDatagrama paquet_recu = PaqueteDatagrama(sizeof(int));
    espera = sock_client.recibeTimeout(paquet_recu);

    if (espera < 1){
        cout << endl;
    }else{
        int* mensaje = (int *) paquet_recu.obtieneDatos();
        char* ip = paquet_recu.obtieneDireccion();
        cout << "\nla ip:" << ip << " y la respuesta fue: " << mensaje[0] << endl;
    }
}

int main(int args, char *argv[]) {
    sock_client.setTimeout(2,0);
    pthread_t clientes[33];
    char ip[16];
    struct parametros param;
    param.arreglo[0] = 0;
    param.arreglo[1] = 4;
    strcpy(param.ip, "192.168.0.100");
    pthread_create(&clientes[0], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.101");
    pthread_create(&clientes[1], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.102");
    pthread_create(&clientes[2], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.103");
    pthread_create(&clientes[3], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.104");
    pthread_create(&clientes[4], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.105");
    pthread_create(&clientes[5], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.106");
    pthread_create(&clientes[6], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.107");
    pthread_create(&clientes[7], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.108");
    pthread_create(&clientes[8], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.109");
    pthread_create(&clientes[9], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.110");
    pthread_create(&clientes[10], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.111");
    pthread_create(&clientes[11], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.112");
    pthread_create(&clientes[12], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.113");
    pthread_create(&clientes[13], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.114");
    pthread_create(&clientes[14], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.115");
    pthread_create(&clientes[15], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.116");
    pthread_create(&clientes[16], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.117");
    pthread_create(&clientes[17], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.118");
    pthread_create(&clientes[18], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.119");
    pthread_create(&clientes[19], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.120");
    pthread_create(&clientes[20], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.121");
    pthread_create(&clientes[21], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.122");
    pthread_create(&clientes[22], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.123");
    pthread_create(&clientes[23], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.124");
    pthread_create(&clientes[24], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.125");
    pthread_create(&clientes[25], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.126");
    pthread_create(&clientes[26], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.127");
    pthread_create(&clientes[27], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.128");
    pthread_create(&clientes[28], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.129");
    pthread_create(&clientes[29], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.130");
    pthread_create(&clientes[30], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.131");
    pthread_create(&clientes[31], NULL, Esta_Vivo, (void*)&param);
    strcpy(param.ip, "192.168.0.132");
    pthread_create(&clientes[32], NULL, Esta_Vivo, (void*)&param);
     
    pthread_join(clientes[0],NULL);
    pthread_join(clientes[1],NULL);
    pthread_join(clientes[2],NULL);
    pthread_join(clientes[3],NULL);
    pthread_join(clientes[4],NULL);
    pthread_join(clientes[5],NULL);
    pthread_join(clientes[6],NULL);
    pthread_join(clientes[7],NULL);
    pthread_join(clientes[8],NULL);
    pthread_join(clientes[9],NULL);
    pthread_join(clientes[10],NULL);
    pthread_join(clientes[11],NULL);
    pthread_join(clientes[12],NULL);
    pthread_join(clientes[13],NULL);
    pthread_join(clientes[14],NULL);
    pthread_join(clientes[15],NULL);
    pthread_join(clientes[16],NULL);
    pthread_join(clientes[17],NULL);
    pthread_join(clientes[18],NULL);
    pthread_join(clientes[19],NULL);
    pthread_join(clientes[20],NULL);
    pthread_join(clientes[21],NULL);
    pthread_join(clientes[22],NULL);
    pthread_join(clientes[23],NULL);
    pthread_join(clientes[24],NULL);
    pthread_join(clientes[25],NULL);
    pthread_join(clientes[26],NULL);
    pthread_join(clientes[27],NULL);
    pthread_join(clientes[28],NULL);
    pthread_join(clientes[29],NULL);
    pthread_join(clientes[30],NULL);
    pthread_join(clientes[31],NULL);
    pthread_join(clientes[32],NULL);
return 0;
}