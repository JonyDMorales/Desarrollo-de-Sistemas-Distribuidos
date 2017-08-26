#include <iostream>
using namespace std;

double algoritmo_babilonico (double x){
	double r = x;
	double t = 0;
	while (t != r){
		t = r;
		r = (x/r + r)/2; 
	} 
	return r;
}

int main( ) {
	double numero;
 	
	cout << "Algoritmo Babilonico.\n";
	cout << "Introduce un numero entero: \n";
	cin >> numero;

	numero = algoritmo_babilonico(numero);

	cout << "la raiz del numero: " << numero << "  es:\n"; 
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(4);

	cout << numero << endl;
	
	return 0;
}