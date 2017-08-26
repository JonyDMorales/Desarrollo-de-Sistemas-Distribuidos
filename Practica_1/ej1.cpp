#include <iostream>
#include <math.h>
using namespace std;


int main(){
	const double PI=3.1416;
	double r,area;
	cout << "Introduzca el valor del radio: \n";
	cin >> r;


	area=PI*(pow(r,2));
	cout << "El resultado es: " << area <<"\n";
}