#include "PaqueteDatagrama.h"
#include <cstring>
PaqueteDatagrama::PaqueteDatagrama(char* data,unsigned int longi,char* ip,int puerto){
	inicializaPuerto(puerto);
	longitud=longi;
	datos=new char[longi];
	inicializaDatos(data);
	inicializaIp(ip);

}
PaqueteDatagrama::~PaqueteDatagrama(){
	delete[](datos);
}
PaqueteDatagrama::PaqueteDatagrama(unsigned int longi){
	longitud=longi;
	datos=new char[longitud];
}
char* PaqueteDatagrama::obtieneDireccion(){
	return ip;
}
unsigned int PaqueteDatagrama::obtieneLongitud(){
	return longitud;
}
int PaqueteDatagrama::obtienePuerto(){
	return puerto;
}
char* PaqueteDatagrama::obtieneDatos(){
	return datos;
}
void PaqueteDatagrama::inicializaPuerto(int p){
	puerto=p;
}
void PaqueteDatagrama::inicializaIp(char* Ip){
	memcpy(ip,Ip,16);
}
void PaqueteDatagrama::inicializaDatos(char* data){
	memcpy(datos,data,longitud);
}
