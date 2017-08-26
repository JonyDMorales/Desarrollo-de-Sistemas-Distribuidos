#ifndef FECHA_H_
#define FECHA_H_

class Fecha{
	private:
		int dia;
		int mes;
		int anio;
		int conv;
		bool bis;
		char otro [980];
	public:
		Fecha(int = 3, int = 4, int = 2014);
		void inicializaFecha(int, int, int);
		void muestraFecha();
		void convierte();
		void leapyr();
		int masVieja_Valor(Fecha fecha1, Fecha fecha2);
		int masVieja_Referencia(Fecha &fecha1, Fecha &fecha2);
		int masVieja_ReferenciaC(Fecha *fecha1, Fecha *fecha2);
};

#endif