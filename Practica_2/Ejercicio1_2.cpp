#include <iostream>
#include "Fecha.h"
using namespace std;

Fecha::Fecha(int dd, int mm, int aaaa) : dia(dd), mes(mm), anio(aaaa){
	if((dia < 1) || (dia > 31)){
		cout << "Valor ilegal para el dia!\n";
		exit(1);
	}
	if((mes < 1) || (mes > 12)){
		cout << "Valor ilegal para el mes!\n";
		exit(1);
	}
	if((anio < 0) || (anio > 2017)){
		cout << "Valor ilegal para el mes!\n";
		exit(1);
	}
}

void Fecha::inicializaFecha(int dd, int mm, int aaaa){
	anio = aaaa;
	mes = mm;
	dia = dd;
return;
}

void Fecha::muestraFecha(){
	cout << "La fecha es(dia-mes-año): " << dia << "-" << mes << "-" << anio <<" Conversion: "<< conv << " bisiesto: "<< bis<<  endl;
return;
}

void Fecha::convierte(){
	conv = (anio*10000)+(mes*100)+dia;
	return;
}

void Fecha::leapyr(){
	if ((anio%400)==0){
		bis = true;
		return;
	}
	if(((anio%4)==0)&&((anio%100)!=0)){
		bis = true;
		return;
	}
	else{
		bis = false;
		return;
	}
}

int main(){
	Fecha a, b, c(21, 9, 1973);

	b.inicializaFecha(17, 6 , 2000);
	a.convierte();
	a.leapyr();
	a.muestraFecha();
	b.convierte();
	b.leapyr();
	b.muestraFecha();
	c.convierte();
	c.leapyr();
	c.muestraFecha();

	//cout << dia <<endl;
	//cout << mes <<endl;
	//cout << anio <<endl;
} 