all:
	g++ SocketD/PaqueteDatagrama.cpp -c
	g++ SocketD/SocketDatagrama.cpp -c
	g++ Cliente.cpp SocketDatagrama.o PaqueteDatagrama.o -pthread -o Cliente
	g++ Cliente1.cpp SocketDatagrama.o PaqueteDatagrama.o -pthread -o Cliente1