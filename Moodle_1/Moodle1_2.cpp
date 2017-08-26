#include <iostream>
#include <math.h>
#define g 9.81
using namespace std;

int main( ) {
	double tiempo;
 	double distancia;

	cout << "Altura de un Edificio.\n";
	cout << "Introduce el tiempo que tardo en caer la pelota: \n";
	cin  >> tiempo;

	//formula de distancia para caida libre
	distancia = (pow(tiempo,2)*g)/2;  

	cout << "La altura es: " << distancia << "  es:\n"; 
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);

	cout << distancia << endl;
	
	return 0;
}