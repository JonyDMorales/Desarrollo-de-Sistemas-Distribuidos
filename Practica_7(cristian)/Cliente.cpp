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

int main(){
	gfx_open(1000, 300, "Ejemplo Micro Juego GFX");
	char aux = '0';
	struct timeval *tiempo, taux, temps_nouveau;
	char buffer[30];
 	time_t curtime;
 	time_t milesimas, milesimasp;
 	int x,port;
 	char mil[3], datos [sizeof(tiempo)],*ip;
 	unsigned difference;


	SocketDatagrama sock_client = SocketDatagrama(9000);
	PaqueteDatagrama solicitud = PaqueteDatagrama(&aux,sizeof(aux),"192.168.0.113", 9000);
	sock_client.envia(solicitud);

	PaqueteDatagrama paquet_recu = PaqueteDatagrama(2*sizeof(tiempo));
	clock_t end, start;
	start = clock();
	sock_client.recibe(paquet_recu);
	end = clock();
	ip  = paquet_recu.obtieneDireccion();
    port  = paquet_recu.obtienePuerto();
    	
  
	tiempo = (struct timeval *) paquet_recu.obtieneDatos();

	curtime = tiempo->tv_sec;
  	milesimas = tiempo->tv_usec;
	cout << "Tiempo recibido es segundos -> " << curtime 
    <<"  usegundos -> "<< milesimas << endl; 

    /*Algortimo*/
  	difference = end - start;
  	cout << difference << endl;
	tiempo->tv_usec += difference;

	curtime = tiempo->tv_sec;
  	milesimas = tiempo->tv_usec;
	cout << "Tiempo recibido es segundos -> " << curtime 
    <<"  usegundos -> "<< milesimas << endl; 

	settimeofday(tiempo,NULL);

	while(true){
		gettimeofday(&taux,NULL);
		curtime = taux.tv_sec;
  		milesimas = taux.tv_usec;
		sprintf(mil,"%d",(int)milesimas);
		strftime(buffer,30,"%T:",localtime(&curtime));
		strcat( buffer,mil);
		x=25;
		if(milesimas > milesimasp){
			for(int i=0;i<10;i++,x+=100){
				pintaNum(x,25,(int)(buffer[i]-48));
			}	
			usleep(10);
			gfx_flush();
			x=25;
			for(int i=0;i<10;i++,x+=100){
				borraNum(x,25,(int)(buffer[i]-48));
			}
  		}
  		milesimasp = milesimas;
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

//timedatectl set-time "2017-04-07 17:10:11"