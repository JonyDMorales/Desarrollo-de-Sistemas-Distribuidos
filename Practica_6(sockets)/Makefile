all:
	g++ PaqueteDatagrama.cpp -c
	g++ SocketDatagrama.cpp -c
	g++ Servidor.cpp PaqueteDatagrama.o SocketDatagrama.o -o Servidor
	g++ Cliente.cpp PaqueteDatagrama.o SocketDatagrama.o -o Cliente