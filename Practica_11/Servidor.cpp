#include "SocketD/SocketDatagrama.h"
#include "SocketD/header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <fcntl.h>
using namespace std;

int main(int args, char *argv[]){

	SocketDatagrama socket = SocketDatagrama(9000);
    struct mensaje *peticion;
    int porcentaje = atoi(argv[1]); 
    PaqueteDatagrama res = PaqueteDatagrama(sizeof(struct mensaje));

    while(true){
        if(porcentaje >= (1 + rand() % (100 - 1))){
            cout << "Se perdio paquete" << endl;
            socket.recibe(res);
        }else{
            socket.recibe(res);
            peticion = (struct mensaje *) res.obtieneDatos();
            cout << "Se recibio solicitud" << endl;
            cout << "Intento numero: " << peticion->secuencia << endl;
            cout << "Numeros a sumar: " << peticion->solicitud[0] << " y " << peticion->solicitud[1] << endl;
            peticion->respuesta = peticion->solicitud[0] + peticion->solicitud[1];
            char* ip = res.obtieneDireccion();
            PaqueteDatagrama msj = PaqueteDatagrama((char *)peticion, sizeof(struct mensaje), ip, 7200);
            socket.envia(msj);
            cout << "Se envio respuesta: " << peticion->respuesta << endl << endl; 
        }  
    }
	return 0;
}