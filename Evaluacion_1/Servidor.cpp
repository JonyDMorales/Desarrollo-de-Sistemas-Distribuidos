#include "SocketD/SocketDatagrama.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <inttypes.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
using namespace std;

struct messageSC{
    float promedio; //Promedio del arreglo de 100 numeros
    char nombre[45]; //Nombre del alumno con fin de cadena incluido
};

int main(int args, char *argv[]) {
    SocketDatagrama socket = SocketDatagrama(7300);
    uint32_t* num;
    uint32_t aux1[100];
    struct messageSC respuesta;
    cout << "Esperando Clientes..." << endl;
    //strcpy(respuesta.nombre, "Jonatan Morales Torres\0");
    sprintf(respuesta.nombre, "Jonatan Morales Torres");
    while(true){
        PaqueteDatagrama peticion = PaqueteDatagrama(sizeof(aux1));
        socket.recibe(peticion);

        char *ip = peticion.obtieneDireccion();
        int port  = peticion.obtienePuerto();
        num = (uint32_t *) peticion.obtieneDatos();
        double aux = 0;

        for (int i = 0; i < 100; i++){
            aux += num[i];
        }

        respuesta.promedio = aux/100;
        
        cout << "La peticion es de: " << ip << endl;
        cout << "Por el puero:"       << port << endl;
        cout << "El promedio es: " << respuesta.promedio << endl;
        cout << "Nombre: " << respuesta.nombre << endl << endl;
        PaqueteDatagrama res = PaqueteDatagrama((char *)&respuesta,sizeof(struct messageSC),ip, port);
        socket.envia(res);
    }
return 0;
}
