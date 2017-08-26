/*
Servidor.cpp
Es la clase principal del servidor
se ejecuta: ./Servidor
*/
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

int main(int args, char *argv[]) {
    SocketDatagrama socket = SocketDatagrama(9000);
    int res, espera = -1;
    int* num;
    cout << "Esperando Clientes..." << endl;
    while(true){
        PaqueteDatagrama peticion = PaqueteDatagrama(2*sizeof(int));
        //socket.setTimeout(2,500);
        socket.recibe(peticion);
        //espera = socket.recibeTimeout(peticion);
        //if (espera < 1){
            //cout << endl;
        //}else{
            char *ip = peticion.obtieneDireccion();
            int port  = peticion.obtienePuerto();
            num = (int *)peticion.obtieneDatos();
            res = num[0] + num[1];
            cout << "La peticion es de: " << ip << endl;
            cout << "Por el puero:"       << port << endl;
            cout << "Los numeros son: "   << num[0] << " y " << num[1] << endl;
            cout << "La suma es:  "       << res << endl;
            PaqueteDatagrama respuesta = PaqueteDatagrama(&res,sizeof(int),ip, port);
            socket.envia(respuesta);
        //}
        
    }
return 0;
}
