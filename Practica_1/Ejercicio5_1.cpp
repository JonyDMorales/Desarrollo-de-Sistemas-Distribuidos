#include <iostream>
using namespace std;

int main( ) {
	int numero = 2;
 	
 	numero = numero+ (++numero);
	cout << "El problema del incremento o decremento.\n";
	cout << "n=2 el resultado es: "<< numero << endl;
	
	return 0;
}