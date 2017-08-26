#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "gfxModified.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <vector>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <math.h>
using namespace std;
#define PUERTO 9001
#define PI 3.14159265

void borrar(int x,int y);
void pintar(int x,int y);

PaqueteDatagrama *datosPinta;
SocketDatagrama *s;
int main()
{
    char* coord;

    int x=0,y=0;

    int n=1;
    srand (time(NULL));
    char* res;

    s = new SocketDatagrama(PUERTO);

   
    gfx_open(800, 600, "Ejemplo Micro Juego GFX");
    gfx_color(25,25,25);
    gfx_line(0,300,800,300);
    gfx_color(25,25,25);
    gfx_line(400,0,400,600);
    while(1){
        
        datosPinta = new PaqueteDatagrama(10);
        s->recibe(*datosPinta);
        cout<< datosPinta->obtieneDatos()<<endl;
        res = strchr(datosPinta->obtieneDatos(),',');
        if(res != NULL){
            coord = strtok(datosPinta->obtieneDatos(),",");
            x=atoi(coord);
            coord = strtok(NULL,",");
            y=atoi(coord);
            coord = strtok(NULL,",");
            pintar(x,y);
        }else{
            coord = strtok(datosPinta->obtieneDatos(),";");
            x=atoi(coord);
            coord = strtok(NULL,";");
            y=atoi(coord);
            coord = strtok(NULL,";");
            borrar(x,y);
        }


        gfx_flush();
        //usleep(180);
    }
}

void borrar(int x,int y){
    gfx_color(0,0,0);
    gfx_point(x,-y+300);
}

void pintar(int x,int y){
    gfx_color(100,100,255);
    gfx_point(x,-y+300);
}