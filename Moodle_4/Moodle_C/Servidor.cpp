/*
Servidor.cpp
Es la clase principal del servidor
se ejecuta: ./Servidor RUTA RUTA
*/
#include "SocketD/SocketDatagrama.h"
#include "SocketD/header.h"
#include "SocketD/Archivo.cpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

char* KAZAA;
char* TRASH;
string ips[33];
string archivos[30];
int k;
SocketDatagrama sock  = SocketDatagrama(9000);
SocketDatagrama sock1 = SocketDatagrama(9100);
SocketDatagrama sock2 = SocketDatagrama(9200);
SocketDatagrama sock3 = SocketDatagrama(9300);
SocketDatagrama sock4 = SocketDatagrama(9400);

void error(const char *s){
  perror (s);
  exit(EXIT_FAILURE);
}

bool Se_encuentra(char *archivo){
    DIR *dir;
    struct dirent *ent;
    /* Empezaremos a leer en el directorio */
    dir = opendir (KAZAA);
    /* Miramos que no haya error */
    if (dir == NULL) 
        error("No puedo abrir el directorio");
    /* Leyendo uno a uno todos los archivos que hay */
    while ((ent = readdir (dir)) != NULL) {
        if ((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0)){
            string aux = ent->d_name;
            if( aux == archivo){
                return false;
            }
        }
    }
    closedir (dir);
    return true;
}

void* Envia_Borrar(void *){
    DIR *dir;
    struct dirent *ent;
    struct messageCS peticion;
    peticion.opcode = DELETE;
    peticion.count  = 0;
    peticion.offset = 0;
    while(true){
        dir = opendir (TRASH);
        if (dir == NULL) 
            error("No puedo abrir el directorio");
        while ((ent = readdir (dir)) != NULL) {
            if ((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0)){
                strcpy(peticion.name, ent->d_name);
                for (int i = 0; i < k; i++){
                    PaqueteDatagrama msj = PaqueteDatagrama((char *)&peticion, sizeof(peticion), ips[i].c_str(), 9400);
                    sock2.envia(msj);
                }
            }
        }
        closedir (dir);
        sleep(2);
    }
}

void* Responde_Archivo(void *){
    struct messageCS peticion;
    struct messageSC respuesta;
    while(true){
        PaqueteDatagrama datos = PaqueteDatagrama(sizeof(struct messageCS));
        sock4.recibe(datos);
        memcpy((char *)&peticion, datos.obtieneDatos(), sizeof(peticion));
        char* ip = datos.obtieneDireccion();
        string path;
        path = "" + (string)KAZAA;
        path = path + peticion.name;

        switch(peticion.opcode){

            case DELETE:
                if (!Se_encuentra(peticion.name)){
                    cout << "Se elimino: " << peticion.name << endl;
                    int aux = unlink (path.c_str());
                }
            break;

            case READ:
                if (!Se_encuentra(peticion.name)){
                    Archivo archivo = Archivo(path.c_str());
                    respuesta.count = archivo.lee(peticion.offset);
                    //strcpy(respuesta.data, archivo.get_contenido());
                    memcpy((char *)respuesta.data, archivo.get_contenido(), respuesta.count);
                    //respuesta.data = archivo.get_contenido();
                    archivo.cerrar();
                    respuesta.result = OK;
                    PaqueteDatagrama msj = PaqueteDatagrama((char *)&respuesta, sizeof(struct messageSC), ip, 9300);
                    sock4.envia(msj);
                }
            break;
        }   
    }
}

void* Solicito_Archivo(void*){
    while(true){
        PaqueteDatagrama datos = PaqueteDatagrama(sizeof(string));
        sock2.recibe(datos);
        char* nombre = datos.obtieneDatos();
        char* ip = datos.obtieneDireccion();
        /*No va negado*/
        if (Se_encuentra(nombre)){
            cout << nombre << endl;
            struct messageCS peticion;
            struct messageSC respuesta;

            peticion.opcode = READ;
            peticion.count  = 0;
            peticion.offset = 0;
            strcpy(peticion.name, nombre);
            PaqueteDatagrama msj = PaqueteDatagrama((char *)&peticion, sizeof(peticion), ip, 9400);
            PaqueteDatagrama res = PaqueteDatagrama(sizeof(struct messageSC));
        
            string path;
            path = "" + (string)KAZAA;
            path = path + peticion.name;

            Archivo archivo = Archivo(path.c_str(), S_IRWXU);
            //Archivo archivo = Archivo(peticion.name, S_IRWXU);
            sock3.setTimeout(1,000);
            bool finished = false;
            int offset = 0;
            int aux = 0;
            do {
                peticion.offset += offset;
                msj.inicializaDatos((char *)&peticion);
                sock3.envia(msj);
                int pktBytes = sock3.recibeTimeout(res);
                if(pktBytes != -1) {
                    memcpy((char *)&respuesta, res.obtieneDatos(), sizeof(respuesta));
                    if(respuesta.result == OK) {
                        offset = archivo.escribe(respuesta.data, respuesta.count);
                        if (respuesta.count != 1000){
                            finished = true;
                            cout << "Se recibio: " << nombre << " de " << ip << endl;
                            archivo.cerrar();
                        }    
                    }else {
                        cout << "Error en: " << nombre << endl;
                        exit(-1);
                    }
                }else{
                    offset = 0;
                    aux++;
                    if (aux > 3)
                        break;
                }
            }while(!finished);
        }
    }
}

void* Envia_Archivos(void *){
    DIR *dir;
    struct dirent *ent;
    string nombre_archivo;
    sleep(3);
    while(true){
        dir = opendir (KAZAA);
        if (dir == NULL) 
            error("No puedo abrir el directorio");
        while ((ent = readdir (dir)) != NULL) {
            if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
                nombre_archivo = ent->d_name;
                //cout << nombre_archivo << endl;
                for (int i = 0; i < k; i++){
                    PaqueteDatagrama str_nombre = PaqueteDatagrama((char *)nombre_archivo.c_str(), sizeof(string), ips[i].c_str(), 9200);   
                    sock2.envia(str_nombre);
                    sleep(2);
                }
            }
        }
        closedir (dir);
    }
}

void* Responder_Peticion(void *){
    PaqueteDatagrama peticion = PaqueteDatagrama(2*sizeof(int));
    int* arr;
    char* ip;
    int res;
    while(true){
        sock1.recibe(peticion);
        arr = (int *) peticion.obtieneDatos();
        ip = peticion.obtieneDireccion();
        res = arr[0] + arr[1];
        PaqueteDatagrama respuesta = PaqueteDatagrama((char *)&res, sizeof(int), ip, 9000);
        sock1.envia(respuesta);
    }
}

void* Registrar_Ip(void *){
    bool esta;
    k = 0;
    sleep(1);
    while(true){
        esta = true;
        PaqueteDatagrama respuesta = PaqueteDatagrama(sizeof(int));
        sock.recibe(respuesta);
        string ip = respuesta.obtieneDireccion();
        int* resul = (int *)respuesta.obtieneDatos();
        for (int j = 0; j < (k+1); j++){
            if ((ips[j] == ip) || (resul[0] != 5)){
                esta = false;
            }
        }
        if (esta){
            ips[k] = ip;
            cout << "Se agrego: " << ips[k] << endl;
            k++; 
        }
    }
}

void* Enviar_Peticion(void *){
    int arreglo[2] = {2,3};
    while(true){
        sock.setBroadcast();
        PaqueteDatagrama peticion = PaqueteDatagrama((char *)&arreglo, sizeof(arreglo), "192.168.0.255"/*"127.0.0.1"*/, 9100);
        sock.envia(peticion);
        sleep(10);
    }
}

int main(int args, char *argv[]) {
    KAZAA = argv[1];
    TRASH = argv[2];
    pthread_t th1, th2, th3, th4, th5, th6, th7;
    pthread_create(&th1, NULL, Registrar_Ip, NULL); 
    pthread_create(&th2, NULL, Responder_Peticion, NULL); 
    pthread_create(&th3, NULL, Enviar_Peticion, NULL);
    pthread_create(&th4, NULL, Envia_Archivos, NULL);
    pthread_create(&th5, NULL, Solicito_Archivo, NULL); 
    pthread_create(&th6, NULL, Responde_Archivo, NULL); 
    pthread_create(&th7, NULL, Envia_Borrar, NULL); 
    
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);
    pthread_join(th6,NULL);
    pthread_join(th7,NULL);
return 0;
}

/*
"/home/jonyd/Escritorio/Desarrollo de Sistemas Distribuidos/Practicas/Moodle_4/Moodle_C/KAZAA/"
"/home/jonyd/Escritorio/Desarrollo de Sistemas Distribuidos/Practicas/Moodle_4/Moodle_C/TRASH/"
*/