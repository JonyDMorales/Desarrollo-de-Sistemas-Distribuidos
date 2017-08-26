#ifndef FRACCION_H_
#define TRACCION_H_

class Fraccion{
	private:
		int numerador;
		int denominador;

	public:
		Fraccion(int = 1, int = 1);
		void inicializa_Fraccion(int,int);
		double resolver_Fraccion();
		int mcd(int, int);
		int mcm(int, int);
		void reducir_Fraccion();
		void muestra_Fraccion();
};

#endif