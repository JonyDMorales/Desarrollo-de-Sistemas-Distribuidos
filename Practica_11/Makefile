all:
	g++ SocketD/PaqueteDatagrama.cpp -c
	g++ SocketD/SocketDatagrama.cpp -c
	g++ Cliente.cpp SocketDatagrama.o PaqueteDatagrama.o -o Cliente
	g++ Servidor.cpp SocketDatagrama.o PaqueteDatagrama.o -o Servidor