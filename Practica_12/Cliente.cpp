#include "SocketD/SocketDatagrama.h"
#include "SocketD/header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <fcntl.h>
using namespace std;

string ips[33];
SocketDatagrama sock = SocketDatagrama(9000); 
int k;
sem_t mutex1;
sem_t mutex2;

void* hilo_3(void *){
    while(true){
        PaqueteDatagrama peticion = PaqueteDatagrama(sizeof(int));
        char* ip;
        bool esta;
        k = 0;
        while(true){
            esta = true;
            sock.recibe(peticion);
            ip = peticion.obtieneDireccion();
            //cout << "Se obtuvo respuesta de: " << ip << endl;
            for (int j = 0; j < k; j++){
                if (ips[j] == ip){
                    //cout << "Entro" << endl;
                    esta = false;
                }
            }
            if (esta){
                ips[k] = std::string(ip);
                k++;
            }
        }
    }
} 

void* hilo_2(void *){
    while(true){
        sem_wait(&mutex2);
        for (int i = 0; i < k; i++){
            cout << "Ip: " << ips[i] << endl;
        }
        cout << endl << endl;
        sleep(3);
        sem_post(&mutex1);
    }
}

void* hilo_1(void *){
    while(true){
        sem_wait(&mutex1);
        int arr[2];
        arr[0] = 3;
        arr[1] = 5;
        sock.setBroadcast();
        PaqueteDatagrama peticion = PaqueteDatagrama((char *)&arr, sizeof(arr), "192.168.0.255", 7200);
        sock.envia(peticion);
        sem_post(&mutex2); 
    }
}

int main(int args, char *argv[]){
    pthread_t th1, th2, th3;
    
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 0);
    
    pthread_create(&th1, NULL, hilo_1, NULL); 
    pthread_create(&th2, NULL, hilo_2, NULL); 
    pthread_create(&th3, NULL, hilo_3, NULL); 

    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
	return 0;
}