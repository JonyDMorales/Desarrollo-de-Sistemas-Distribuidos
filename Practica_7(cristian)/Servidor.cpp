#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "gfxModified.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> 
#include <vector>
#include <math.h>
#include <sys/time.h>
#include <iostream>
using namespace std;

void pintaNum(int x, int y, int numero);
void borraNum(int x, int y, int numero);

int main() {
    gfx_open(1000, 300, "Ejemplo Micro Juego GFX");
    cout << "Servidor" << endl;
    SocketDatagrama socket = SocketDatagrama(9000);
    

    
        struct timeval tiempo;
        char buffer[30];
        time_t curtime;
        int x,milesimas;
        char mil[3];

        PaqueteDatagrama peticion = PaqueteDatagrama(sizeof(int));
        socket.recibe(peticion);
        char *ip = peticion.obtieneDireccion();
        int port  = peticion.obtienePuerto();
        cout << "Se recibio peticion de: " << ip << ":" << port << " -> " << atoi(peticion.obtieneDatos()) << endl;
   while (1) {    
        gettimeofday(&tiempo,NULL);   
        curtime = tiempo.tv_sec;
        milesimas = tiempo.tv_usec;
            
        sprintf(mil,"%d",milesimas);
        strftime(buffer,30,"%T:",localtime(&curtime));
        strcat( buffer,mil);
        PaqueteDatagrama hora_actual = PaqueteDatagrama((char *)&tiempo, sizeof(tiempo), ip, port);
        socket.envia(hora_actual);

        x=25;
        for(int i=0;i<10;i++,x+=100){
            pintaNum(x,25,(int)(buffer[i]-48));
        }   
        usleep(100);
        gfx_flush();
        x=25;
        for(int i=0;i<10;i++,x+=100){
            borraNum(x,25,(int)(buffer[i]-48));
        }   

    }
    return 0;
}

void pintaNum(int x, int y, int num){
    gfx_color(255,0,0);
    switch(num){
        case 0:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 1:
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 2:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup    
            break;
        case 3:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 4:
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 5:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 6:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 7:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 8:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 9:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        default:
            gfx_fill_rectangle(x+25,y+45,7,20);//der Sup
            gfx_fill_rectangle(x+25,y+75,7,20);//der Inf
            break;
    }
}

void borraNum(int x, int y, int num){
    gfx_color(0,0,0);
    switch(num){
        case 0:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 1:
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 2:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup    
            break;
        case 3:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 4:
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 5:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 6:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 7:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 8:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x-10,y+75,7,50);//izq Inf
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        case 9:
            gfx_fill_rectangle(x,y,50,7);//arriba
            gfx_fill_rectangle(x,y+130,50,7);//abajo
            gfx_fill_rectangle(x,y+65,50,7);//enmedio
            gfx_fill_rectangle(x-10,y+15,7,50);//izq Sup
            gfx_fill_rectangle(x+55,y+15,7,50);//der Sup
            gfx_fill_rectangle(x+55,y+75,7,50);//der Inf
            break;
        default:
            gfx_fill_rectangle(x+25,y+45,7,20);//der Sup
            gfx_fill_rectangle(x+25,y+75,7,20);//der Inf
            break;
    }
}


