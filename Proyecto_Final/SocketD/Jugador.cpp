#include "Jugador.h"
#include "Coordenada.h"
#include "Coordenada.cpp"

Jugador::Jugador(char* nickname, int idu, int level){
	NickName = new char[strlen(nickname)];
	memcpy(NickName,nickname, strlen(nickname));
	id = idu;
	nivel = level;
}

void Jugador :: cargaCoordenadas(Coordenada c1){
	V_Coordenada.push_back(c1);
}


bool Jugador :: buscaCoordenada(Coordenada Ataque){
	bool flag = false;
	for(int i = 0; i < V_Coordenada.size(); i++)
		if( (V_Coordenada[i].obtenerX() == Ataque.obtenerX()) && (V_Coordenada[i].obtenerY() ==  Ataque.obtenerY())){
			V_Coordenada.erase(V_Coordenada.begin() + i);
			flag = true;
		} 
	return flag;
}

void Jugador :: setNivel(int level){ nivel = level; }

char* Jugador :: getNickName(){ return NickName; }

int Jugador :: getNivel(){ return nivel;}

int Jugador :: getId(){ return id; }

bool Jugador :: getMuerte(){
	bool flag = true;
	for(int i = 0; i < V_Coordenada.size(); i++)
		if( (V_Coordenada[i].obtenerX() != 0) && (V_Coordenada[i].obtenerY() != 0)) 
			flag = false;
	return flag;
}
