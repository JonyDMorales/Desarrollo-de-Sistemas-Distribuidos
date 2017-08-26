#include <iostream>
#include <algorithm>
#include "Moodle2_5.h"
using namespace std;

Fraccion::Fraccion(int num, int den){
	numerador = num;
	denominador = den;
}

void Fraccion::inicializa_Fraccion(int num, int den){
	numerador = num;
	denominador = den;
return;
}

double Fraccion::resolver_Fraccion(){
	double res;
	res = numerador / denominador;
return res;
}

int Fraccion::mcd(int num1, int num2) {
    int mcd = 0;
    int a = std::max(num1, num2);
    int b = std::min(num1, num2);
    do {
        mcd = b;
        b = a%b;
        a = mcd;
    } while(b!=0);
    return mcd;
}


int Fraccion::mcm (int num, int den){ 
	Fraccion f;
	int mcm = 0;
    int a = std::max(num, den);
    int b = std::min(num, den);
    mcm = (a/f.mcd(a,b));
    return mcm;
}

void Fraccion::reducir_Fraccion(){
	Fraccion f;
	int mcm = f.mcd(numerador,denominador);
	//cout << "mcd: " << mcm << endl;
	numerador = numerador / mcm;
	denominador = denominador / mcm;
return;
}

void Fraccion::muestra_Fraccion(){
	cout << "Fraccion: " << numerador << " / " << denominador << endl;
return;
}

int main(){
	Fraccion f;
	int op, num, den;

	do{
		cout << "\n1. Introducir Fraccion:" << endl;
		cout << "2. Reducir Fraccion:" << endl;
		cout << "3. Mostrar Fraccion:" << endl;
		cout << "4. salir" << endl;
		cin  >> op;
		
		switch(op){
			case 1:
				cout << "Introduce numerador:" << endl;
				cin  >> num;
				cout << "Introduce denominador:" << endl;
				cin  >> den;
				f.inicializa_Fraccion(num, den);
			break;
			case 2:
				f.reducir_Fraccion();
				f.muestra_Fraccion();
			break;
			case 3:
				f.muestra_Fraccion();
			break;
		}
	}while(op < 4);
	return 0;
}