#ifndef JUGADOR_H_
#define JUGADOR_H_

#include "Coordenada.h"
#include <vector>
#include <string.h>

class Jugador{

private:
	char* NickName;
	int id;
	int nivel;
	std::vector<Coordenada> V_Coordenada;

public:
	Jugador(char*, int, int);
	bool 	buscaCoordenada(Coordenada);
	void 	setNivel(int);
	void 	cargaCoordenadas(Coordenada);
	char* 	getNickName();
	int 	getNivel();
	int 	getId();
	bool 	getMuerte();

};
#endif