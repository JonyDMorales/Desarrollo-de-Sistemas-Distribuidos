#include <iostream>
#include "Moodle2_4.h"
using namespace std;

Temperatura::Temperatura(float temp){
	tem_kelvin = temp;
}

void Temperatura::setTempKelvin(float temp){
	tem_kelvin = temp;
return;
}

void Temperatura::setTempFahrenheit(float temp){
	tem_kelvin = (temp-32)/1.8 + 273.15;
return;	
}

void Temperatura::setTempCelsius(float temp){
	tem_kelvin = temp + 273.15;
return;	
}

void Temperatura::muestra_Kelvin(){
	cout << "Temperatura en Kelvin: " << tem_kelvin << endl;
return;	
}

void Temperatura::muestra_Fahrenheit(){
	cout << "Temperatura en Fahrenheit: " << ((tem_kelvin - 273.15)* 1.8000 + 32.00) << endl;
return;	
}

void Temperatura::muestra_Celsius(){
	cout << "Temperatura en Fahrenheit: " << (tem_kelvin - 273.15) << endl;
return;	
}


int main(){
	float temp;
	Temperatura t;
	int op;

	do{
		cout << "\n1. Introducir en Kelvin:" << endl;
		cout << "2. Introducir en Fahrenheit:" << endl;
		cout << "3. Introducir en Celsius:" << endl;
		cout << "4. Mostrar en Kelvin:" << endl;
		cout << "5. Mostrar en Fahrenheit:" << endl;
		cout << "6. Mostrar en Celsius:" << endl;
		cout << "7. salir" << endl;
		cin  >> op;
		
		switch(op){
			case 1:
				cout << "Introduce la temperatura:" << endl;
				cin  >> temp;
				t.setTempKelvin(temp);
			break;
			case 2:
				cout << "Introduce la temperatura:" << endl;
				cin  >> temp;
				t.setTempFahrenheit(temp);
			break;
			case 3:
				cout << "Introduce la temperatura:" << endl;
				cin  >> temp;
				t.setTempCelsius(temp);
			break;
			case 4:
				t.muestra_Kelvin();
			break;
			case 5:
				t.muestra_Fahrenheit();
			break;
			case 6:
				t.muestra_Celsius();
			break;
			default:
				cout << "Opcion invalida" << endl;
			break;
		}
	}while(op < 7);
} 