/*
Servidor.cpp
Es la clase principal del servidor donde se reciben y crean los parqueten que se recibiran y se enviaran
se ejecuta: ./Servidor
*/
#include "SocketD/SocketDatagrama.h"
#include "Serializacion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#define PATH "./Archivos/"
using namespace std;

void error(const char *s){
  perror (s);
  exit(EXIT_FAILURE);
}

string Busca_en_Archivo(char *archivo, char * palabra){
  	FILE *fich;
  	unsigned ftam;
  	char * aux = (char *) malloc(1 + strlen(archivo)+ strlen(PATH));
  	string datos;
  	string respuesta = string(archivo);
  	unsigned offset = 0;
  	stringstream stream;

  	respuesta += " ";
    strcpy(aux, PATH);
    strcat(aux, archivo);
  	ifstream file;
  	file.open(aux , ios::in);
  	if (!file){
   		cout << "No se pudo abrir: " << archivo << endl; 
    }else{
      	
     	while (! file.eof() ) {
            getline (file,datos, ' ');
            if (datos == palabra){
            	offset++;
            	//cout << "1: " << datos << "  2: " << palabra << " valor: " << offset << endl;
            	stream << offset; 
            	respuesta += stream.str() + ", ";
            	stream.str(std::string());
            	offset += datos.size(); 
            }else{
            	offset += datos.size() + 1;
            }
        }
     	file.close();
    }
    return respuesta;
}

int main(int args, char *argv[]) {
	int PUERTO = 9000;
	SocketDatagrama socket(PUERTO);
	char *respuesta = NULL;
 	DIR *dir;
  	struct dirent *ent;
  	struct messageCS *solicitud;
  	string aux = "";
	
	while (true) {
		cout << "\n\nEsperando Clientes...\n" << endl;
		PaqueteDatagrama info = PaqueteDatagrama(sizeof(struct messageCS));
		socket.recibe(info);
		/*Se recibe peticion*/
		solicitud = (struct messageCS *) info.obtieneDatos();
		char *ip = info.obtieneDireccion();
    int port  = info.obtienePuerto();
		cout << "Se recibio peticion de: " << ip << endl;
		
		int opcode = 0;
		int count = 0;
		int offset= 0;

		opcode = solicitud->opcode;
		count = solicitud->count;
		offset= solicitud->offset;
		char palabra[count];
    strcpy(palabra, solicitud->name); 
		cout << "Opcode: " 	<< opcode  << endl;
		cout << "Count: " 	<< count   << endl;
		cout << "Offset: " 	<< offset  << endl;
		cout << "Name: " 	<< palabra << endl;
		switch(opcode){

            case READ:
            	/* Empezaremos a leer en el directorio */
  				dir = opendir (PATH);
				/* Miramos que no haya error */
  				if (dir == NULL) 
    				error("No puedo abrir el directorio");
  				/* Leyendo uno a uno todos los archivos que hay */
  				while ((ent = readdir (dir)) != NULL) {
      				if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
      					/* Una vez tenemos el archivo, lo pasamos a una función para procesarlo. */
      					aux += Busca_en_Archivo(ent->d_name, palabra);
    				}
    			}
  				closedir (dir);
  				/*Se envia respuesta*/
  				struct messageSC msj;
  				msj.count = aux.size();
				msj.result  = OK;
				msj.offset = 0;
				strcpy(msj.data, aux.c_str());
        		PaqueteDatagrama res = PaqueteDatagrama((char *)&msj, sizeof(msj), ip, port);
        		socket.envia(res);
        		cout << "\n\n\nSe envio: " << endl;
				cout << "Count: " 	<< msj.count  << endl;
				cout << "Result: " 	<< msj.result << endl;
				cout << "Offset: " 	<< msj.offset << endl;
				cout << "Data: " 	<< msj.data   << endl;
        		aux = "";
        		respuesta = NULL;                     
            break;

		}
	}//while true
return 0;
}
