#include <vector>
#include "Eratostenes.h"
#include <iostream>
using namespace std;

Eratostenes::Eratostenes() { }

void Eratostenes::insertar(int aux, bool aux1){
	naturales.push_back(aux);
	es.push_back(aux1);
return;
}

void Eratostenes::mostrar(){
	for (int i = 0; i < naturales.size(); ++i)
		cout << naturales[i] << "  Es primo: " << es[i] << endl;
return;
}

void Eratostenes::Algoritmo(){
	for(int i = 2; i*i <= naturales.size(); ++i) {
        if(es[i]) {
            for(int h = 2; i*h <= naturales.size(); ++h)
                es[i*h] = false;
        }
    }
return;
}