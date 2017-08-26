#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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
	cout << "La fecha es(dia-mes-año): " << dia << "-" << mes << "-" << anio << endl;
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

int Fecha::masVieja_ReferenciaC(Fecha *fecha1, Fecha *fecha2){
	if (fecha1->anio < fecha2->anio)
		return -1;
	if ((fecha1->anio == fecha2->anio)&&(fecha1->mes < fecha2->mes))
		return -1;
	if ((fecha1->anio == fecha2->anio)&&(fecha1->mes == fecha2->mes)&&(fecha1->dia < fecha2->dia))
		return -1;
	if ((fecha1->anio == fecha2->anio)&&(fecha1->mes == fecha2->mes)&&(fecha1->dia == fecha2->dia))
		return 0;
return 1;	
}

int Fecha::masVieja_Valor(Fecha fecha1, Fecha fecha2){
	if (fecha1.anio < fecha2.anio)
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes < fecha2.mes))
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes == fecha2.mes)&&(fecha1.dia < fecha2.dia))
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes == fecha2.mes)&&(fecha1.dia == fecha2.dia))
		return 0;
return 1;	
}

int Fecha::masVieja_Referencia(Fecha &fecha1, Fecha &fecha2){
	if (fecha1.anio < fecha2.anio)
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes < fecha2.mes))
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes == fecha2.mes)&&(fecha1.dia < fecha2.dia))
		return -1;
	if ((fecha1.anio == fecha2.anio)&&(fecha1.mes == fecha2.mes)&&(fecha1.dia == fecha2.dia))
		return 0;
return 1;	
}

int main(){
	Fecha a, b, c(21, 9, 1973);

	//cout <<"valor: " << sizeof(a);
	for (int i = 0; i < 500000; i++){
		a.inicializaFecha((int)(rand() % 31 + 1), (int)(rand() % 12 + 1), (int)(rand () % 2017 + 0));
		b.inicializaFecha((int)(rand() % 31 + 1), (int)(rand() % 12 + 1), (int)(rand () % 2017 + 0));
		
		//Por valor
		c.masVieja_Valor(a, b);

		//Por referencia en C++
		//c.masVieja_Referencia(a, b);
		
		//Por referencia en C
		//c.masVieja_ReferenciaC(&a, &b);

	}
} 