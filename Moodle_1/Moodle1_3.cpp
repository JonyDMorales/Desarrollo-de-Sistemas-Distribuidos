#include <iostream>
using namespace std;

int main( ) {
	long int tiempo;
	int horas;
	int minutos;
	int segundos;

	cout << "tiempo.\n";
	cout << "Introduce el tiempo en segundos: \n";
	cin  >> tiempo;

	horas 	= tiempo/3600;
	tiempo	= tiempo - (horas*3600);
	cout << tiempo << endl;
	minutos	= tiempo/60;
	segundos	= tiempo - (minutos*60);	 

	cout << "horas: " << horas << endl;
	cout << "minutos: " << minutos << endl;
	cout << "segundos: " << segundos << endl;

	return 0;
}