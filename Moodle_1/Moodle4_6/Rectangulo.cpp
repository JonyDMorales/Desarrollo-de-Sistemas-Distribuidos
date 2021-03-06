#include "Coordenada.h"
#include "Rectangulo.h"
#include <iostream>
using namespace std;

Rectangulo::Rectangulo() : superiorIzq(0,0,0), inferiorDer(0,0,0){ }

//Rectangulo::Rectangulo(double xSupIzq, double ySupIzq, double xInfDer, double
//yInfDer):superiorIzq(xSupIzq, ySupIzq), inferiorDer(xInfDer, yInfDer){ }

Rectangulo::Rectangulo(Coordenada uno, Coordenada dos): superiorIzq(uno), inferiorDer(dos){ }

void Rectangulo::imprimeEsq(){
	cout << "Para la esquina superior izquierda.\n";
	cout << "x = " << superiorIzq.obtenerX() << " y = " << superiorIzq.obtenerY() << " z = " << superiorIzq.obtenerZ() << endl;
	cout << "Para la esquina inferior derecha.\n";
	cout << "x = " << inferiorDer.obtenerX() << " y = " << inferiorDer.obtenerY() << " z = " << inferiorDer.obtenerZ() << endl;
}

Coordenada Rectangulo::obtieneSupIzq(){
return superiorIzq;
}

Coordenada Rectangulo::obtieneInfDer(){
return inferiorDer;
}

double Rectangulo::obtieneArea(){
	double largo = inferiorDer.obtenerX() - superiorIzq.obtenerX();
	double ancho = superiorIzq.obtenerY() - inferiorDer.obtenerY();
return (largo * ancho);
}