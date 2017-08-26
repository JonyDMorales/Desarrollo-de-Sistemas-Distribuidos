all:
	g++ SocketD/PaqueteDatagrama.cpp -c
	g++ SocketD/SocketDatagrama.cpp -c
	g++ Servidor.cpp SocketDatagrama.o PaqueteDatagrama.o -o Servidor