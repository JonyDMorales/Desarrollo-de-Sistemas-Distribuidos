#include "Coordenada.h"
#include <math.h>
#include <iostream>
using namespace std;

Coordenada::Coordenada(double xx, double yy) : r(xx), teta(yy){ }

/*
double Coordenada::obtenerX(){
return x;
}

double Coordenada::obtenerY(){
return y;
}*/


double Coordenada::obtenerX(){
return (r* cos(teta));
}

double Coordenada::obtenerY(){
return (r* sin(teta));
}