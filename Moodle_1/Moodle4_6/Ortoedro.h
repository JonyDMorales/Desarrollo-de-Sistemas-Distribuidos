#ifndef ORTOEDRO_H_
#define ORTOEDRO_H_

class Ortoedro{
	private:
		Rectangulo rectangulo1;
		Rectangulo rectangulo2;
		Rectangulo rectangulo3;
		Rectangulo rectangulo4;
		Rectangulo rectangulo5;
		Rectangulo rectangulo6;

	public:
		Ortoedro();
		Ortoedro(Rectangulo uno,
				 Rectangulo dos,
				 Rectangulo tres,
				 Rectangulo cuatro,
				 Rectangulo cinco,
				 Rectangulo seis);

		double obtieneArea();
		double obtieneVolumen();
		void obtieneVertices();
};

#endif