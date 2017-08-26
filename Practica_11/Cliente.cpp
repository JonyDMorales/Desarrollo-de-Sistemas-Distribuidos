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
	char* ip = argv[1];
	int PUERTO = atoi(argv[2]);
	int num = atoi(argv[3]);
    int solicitudes = 0;
    int solicitudes_totales = 0;
    bool bandera = false;
    int tiempo = 0;
	SocketDatagrama socket = SocketDatagrama(7200);
	socket.setTimeout(1,0);

    struct mensaje peticion;
    struct mensaje *msj_res;

    PaqueteDatagrama res = PaqueteDatagrama(sizeof(struct mensaje));

    for (int k = 0; k < num; k++){
        bandera = false;
        peticion.solicitud[0] = 1 + rand() % (100 - 1);
        peticion.solicitud[1] = 1 + rand() % (100 - 1);
        for (int i = 0; i < 7; i++){
            peticion.secuencia = i+1;
            peticion.respuesta = 0;
            PaqueteDatagrama msj = PaqueteDatagrama((char *)&peticion, sizeof(peticion), ip, PUERTO);
            socket.envia(msj);
            tiempo = socket.recibeTimeout(res);
            if (tiempo != -1){
                bandera = true;
                solicitudes_totales++;
                break;
            }else if(i == 6){
                cout << "El servidor no se encuentra activo" << endl << endl;
                exit(0);
            }

        }
        cout << "Los numeros fueron: " << peticion.solicitud[0] << " y " << peticion.solicitud[1] << endl;

        if (bandera){
            msj_res = (struct mensaje *) res.obtieneDatos();
            cout << "Intento: " <<  peticion.secuencia << endl;
            solicitudes += peticion.secuencia;
            cout << "La respuesta fue: " << msj_res->respuesta << endl << endl;
        }else{
            cout << "El servidor no se encuentra activo" << endl << endl;
        }   
    }
    cout << "El numero de solicitudes distintas hechas al servidor: " << solicitudes << endl;
    cout << "El número de solicitudes totales hechas al servidor: " << solicitudes_totales << endl;
    cout << "Porcentaje de datagramas perdidos: " << 100-((solicitudes_totales*100)/solicitudes) << endl << endl;
	return 0;
}