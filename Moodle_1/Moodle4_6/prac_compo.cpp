#include "Coordenada.h"
#include "Rectangulo.h"
#include "Ortoedro.h"
#include <iostream>
using namespace std;

int main( ){

	cout << "Ortoedro" << endl;
	Rectangulo rec1(Coordenada(0,10,0),Coordenada(10,0,0));
	Rectangulo rec2(Coordenada(10,10,0),Coordenada(10,0,20));
	Rectangulo rec3(Coordenada(10,10,20),Coordenada(0,0,20));
	Rectangulo rec4(Coordenada(0,10,20),Coordenada(0,0,0));
	Rectangulo rec5(Coordenada(0,10,0),Coordenada(10,10,20));
	Rectangulo rec6(Coordenada(10,0,0),Coordenada(0,0,20));
	
	Ortoedro Or(rec1,rec2,rec3,rec4,rec5,rec6);

	Or.obtieneVertices();
	cout << "\nEl área es = " << Or.obtieneArea() << endl;
	cout << "El volumen es = " << Or.obtieneVolumen() << endl;

return 0;
}