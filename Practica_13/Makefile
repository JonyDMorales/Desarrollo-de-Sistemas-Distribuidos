all:
	g++ SocketD/PaqueteDatagrama.cpp -c
	g++ SocketD/SocketMulticast.cpp -c
	g++ Cliente.cpp SocketMulticast.o PaqueteDatagrama.o -o Cliente
	g++ Servidor.cpp SocketMulticast.o PaqueteDatagrama.o -o Servidor