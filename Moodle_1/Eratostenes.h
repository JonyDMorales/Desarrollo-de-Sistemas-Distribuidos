#ifndef ERATOSTENES_H_
#define ERATOSTENES_H_

class Eratostenes{
	private:
		std::vector<int> naturales;
		std::vector<bool> es;

	public:
		Eratostenes();
		void insertar(int, bool);
		void mostrar();
		void Algoritmo();
};

#endif