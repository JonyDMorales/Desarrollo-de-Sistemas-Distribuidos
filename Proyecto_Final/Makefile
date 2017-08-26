all:
	g++ SocketD/Funciones.cpp -c
	g++ SocketD/Grafica.h -c
	g++ SocketD/Grafica.cpp -c
	g++ SocketD/Coordenada.h -c
	g++ SocketD/Coordenada.cpp -c
	g++ SocketD/PaqueteDatagrama.cpp -c
	g++ SocketD/SocketDatagrama.cpp -c
	g++ SocketD/Jugador.cpp -c
	
	g++  `pkg-config --libs --cflags gtk+-3.0` -w Game.cpp `pkg-config --libs gtk+-3.0` SocketDatagrama.o PaqueteDatagrama.o Funciones.o Grafica.o  -pthread -o Game -lX11 -lm