#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <iostream>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

int main() {
    cout << "Servidor" << endl;
    SocketDatagrama socket = SocketDatagrama(5000);

    while (1) {
        PaqueteDatagrama peticion = PaqueteDatagrama(sizeof(int));
        socket.recibe(peticion);
        
        struct timeval tiempo;
        gettimeofday(&tiempo,NULL);
        
        char *dirip = peticion.obtieneDireccion();
        int port  = peticion.obtienePuerto();
        
        PaqueteDatagrama hora_actual = PaqueteDatagrama(&tiempo, sizeof(struct timeval), dirip, port);
        
        cout << dirip << ":" << port << endl;
        
        socket.envia(hora_actual);

        cout << "El tiempo es segundos-> " << tiempo.tv_sec 
            <<"usegundos -> "<<tiempo.tv_usec << endl;
    }
    return 0;
}



