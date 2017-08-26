#include <vector>
#include "Eratostenes.h"
#include <iostream>
using namespace std;

int main( ) {
	Eratostenes e1;
	int N;

	cout << "Algoritmo de Eratostenes" << endl;
	cout << "Introduce hasta que numero natural parar: " << endl;
	cin >> N;

	for (int i = 0; i < N; i++){
		if(i == 0 || i == 1)
			e1.insertar(i, false);
		else
			e1.insertar(i, true);
	}

	e1.Algoritmo();
	e1.mostrar();
	return 0;
}