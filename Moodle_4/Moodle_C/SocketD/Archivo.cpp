#include "Archivo.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

Archivo :: Archivo(const char *filename){
	fd = open(filename, O_RDONLY);
	nombreArchivo = filename;
	if(fd == -1){
        perror("No se puede abrir ");
        exit(-1);
    }
}

Archivo :: Archivo(const char *filename, mode_t modo){
	fd = open(filename, O_CREAT|O_RDWR, 0666);
	nombreArchivo = filename;
	if(fd == -1){
        perror("No se puede abrir ");
        exit(-1);
    }
}

Archivo :: ~Archivo(){}

size_t Archivo :: lee(size_t nbytes){
	int aux;
	char conte[1000];
	lseek(fd, nbytes, SEEK_SET);
	aux = read(fd, conte, BUF_SIZE);
	contenido = conte;
	//strcpy(contenido,conte);
	if(aux == -1){
        perror("No se puede leer");
        exit(-1);
    }
	return aux;
}

size_t Archivo :: escribe(const void *buffer, size_t nbytes){
	int aux = write(fd, buffer, nbytes); 
	if(aux == -1){
        perror("No se puede escribir");
        exit(-1);
    }
	return aux;
}

char* Archivo :: get_contenido(){
	return contenido;
}
 	
void Archivo :: cerrar(){
	close(fd);
	//cout << "Cerro" << endl;
}