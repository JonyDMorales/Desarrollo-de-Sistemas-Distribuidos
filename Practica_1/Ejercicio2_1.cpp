#include <iostream>
using namespace std;

int main( ) {
	int numero_1;
	int numero_2;
	float resultado;

	cout << "Dividir Numeros.\n";
	cout << "Introduce un numero: ";
	cin >> numero_1;
	cout << "Introduce otro numero: ";
	cin >> numero_2;

	resultado= numero_1/numero_2;

		cout << "El resultado es: "<< resultado << endl;	
	return 0;
}