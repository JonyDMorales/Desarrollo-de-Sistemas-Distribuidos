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
	char* nombre_archivo = argv[3];

	SocketDatagrama socket = SocketDatagrama(7200);
	struct messageCS peticion;
	struct messageSC *respuesta;

	peticion.opcode = READ;
	peticion.count = 0;
	peticion.offset = 0;
	strcpy(peticion.name, nombre_archivo);
	PaqueteDatagrama msj = PaqueteDatagrama((char *)&peticion, sizeof(peticion), ip, PUERTO);
	PaqueteDatagrama res = PaqueteDatagrama(sizeof(struct messageSC));
	
	int archivo;
    if((archivo = open(nombre_archivo, O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1) {
        //perror(args[3]);
        exit(-1);
    }

    socket.setTimeout(1,0);
	bool finished = false;
    int offset = 0;
    do {
     	peticion.offset += offset;
        msj.inicializaDatos((char *)&peticion);
        socket.envia(msj);
        int pktBytes = socket.recibeTimeout(res);
        if(pktBytes != -1) {
            respuesta = (struct messageSC*)res.obtieneDatos();   
            if(respuesta->result == OK) {
                int fileBytes = respuesta->count;
                cout << "Bytes: " << fileBytes << endl;
                int written = write(archivo, respuesta->data, fileBytes);
                offset = written;                   
                if (respuesta->count != 1000)    
                	finished = true;
            }else {
                printf("Error: %d\n", respuesta->result);
            }
        }else{
        	offset = 0;
        }
    }while(!finished);
	close(archivo);
	return 0;
}

/*
./Cliente "192.168.0.120" 7000 "psetup.xpm"
./Cliente "192.168.0.120" 7000 "umax.jpg"
./Cliente "192.168.0.120" 7000 "Linux.mp4"
*/