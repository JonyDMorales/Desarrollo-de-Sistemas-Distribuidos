#ifndef FECHA_H_
#define FECHA_H_

class Fecha{
	private:
		int dia;
		int mes;
		int anio;
		int conv;
		bool bis;
	public:
		Fecha(int = 3, int = 4, int = 2014);
		void inicializaFecha(int, int, int);
		void muestraFecha();
		void convierte();
		void leapyr();
};

#endif