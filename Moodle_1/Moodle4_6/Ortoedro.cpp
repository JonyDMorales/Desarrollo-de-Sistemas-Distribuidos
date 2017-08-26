#include "Coordenada.h"
#include "Rectangulo.h"
#include "Ortoedro.h"
#include <iostream>
using namespace std;

Ortoedro::Ortoedro() : rectangulo1(Coordenada(0,0,0),Coordenada(0,0,0)),
					   rectangulo2(Coordenada(0,0,0),Coordenada(0,0,0)),
					   rectangulo3(Coordenada(0,0,0),Coordenada(0,0,0)),
					   rectangulo4(Coordenada(0,0,0),Coordenada(0,0,0)),
					   rectangulo5(Coordenada(0,0,0),Coordenada(0,0,0)),
					   rectangulo6(Coordenada(0,0,0),Coordenada(0,0,0)) { }

Ortoedro::Ortoedro(Rectangulo uno,
				   Rectangulo dos,
				   Rectangulo tres,
				   Rectangulo cuatro,
				   Rectangulo cinco,
				   Rectangulo seis): rectangulo1(uno),
					   				 rectangulo2(dos),
					   				 rectangulo3(tres),
					   				 rectangulo4(cuatro),
					   				 rectangulo5(cinco),
					   				 rectangulo6(seis) { }

void Ortoedro::obtieneVertices(){
	cout << "Vertice 1: " << endl;
	cout << "x = " << rectangulo1.obtieneSupIzq().obtenerX() << " y = " << rectangulo1.obtieneSupIzq().obtenerY() << " z = " << rectangulo1.obtieneSupIzq().obtenerZ() << endl;
	cout << "Vertice 2: " << endl;
	cout << "x = " << rectangulo1.obtieneInfDer().obtenerX() << " y = " << rectangulo1.obtieneInfDer().obtenerY() << " z = " << rectangulo1.obtieneInfDer().obtenerZ() << endl;

	cout << "Vertice 3: " << endl;
	cout << "x = " << rectangulo2.obtieneSupIzq().obtenerX() << " y = " << rectangulo2.obtieneSupIzq().obtenerY() << " z = " << rectangulo2.obtieneSupIzq().obtenerZ() << endl;
	cout << "Vertice 4: " << endl;
	cout << "x = " << rectangulo2.obtieneInfDer().obtenerX() << " y = " << rectangulo2.obtieneInfDer().obtenerY() << " z = " << rectangulo2.obtieneInfDer().obtenerZ() << endl;

	cout << "Vertice 5: " << endl;
	cout << "x = " << rectangulo3.obtieneSupIzq().obtenerX() << " y = " << rectangulo3.obtieneSupIzq().obtenerY() << " z = " << rectangulo3.obtieneSupIzq().obtenerZ() << endl;
	cout << "Vertice 6: " << endl;
	cout << "x = " << rectangulo3.obtieneInfDer().obtenerX() << " y = " << rectangulo3.obtieneInfDer().obtenerY() << " z = " << rectangulo3.obtieneInfDer().obtenerZ() << endl;

	cout << "Vertice 7: " << endl;
	cout << "x = " << rectangulo4.obtieneSupIzq().obtenerX() << " y = " << rectangulo4.obtieneSupIzq().obtenerY() << " z = " << rectangulo4.obtieneSupIzq().obtenerZ() << endl;
	cout << "Vertice 8: " << endl;
	cout << "x = " << rectangulo4.obtieneInfDer().obtenerX() << " y = " << rectangulo4.obtieneInfDer().obtenerY() << " z = " << rectangulo4.obtieneInfDer().obtenerZ() << endl;

}

double Ortoedro::obtieneArea(){
	double largo = rectangulo2.obtieneSupIzq().obtenerY() - rectangulo1.obtieneInfDer().obtenerY();
	double ancho = rectangulo1.obtieneInfDer().obtenerX() - rectangulo4.obtieneInfDer().obtenerX();
	double profundidad = rectangulo2.obtieneInfDer().obtenerZ() - rectangulo4.obtieneInfDer().obtenerZ();
return ((2*ancho*profundidad)+(2*profundidad*largo)+(2*largo*ancho));
}

double Ortoedro::obtieneVolumen(){
	double largo = rectangulo2.obtieneSupIzq().obtenerY() - rectangulo1.obtieneInfDer().obtenerY();
	double ancho = rectangulo1.obtieneInfDer().obtenerX() - rectangulo4.obtieneInfDer().obtenerX();
	double profundidad = rectangulo2.obtieneInfDer().obtenerZ() - rectangulo4.obtieneInfDer().obtenerZ();
return (largo * ancho * profundidad);
}