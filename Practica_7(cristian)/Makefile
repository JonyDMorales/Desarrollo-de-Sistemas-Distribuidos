all:
	g++ PaqueteDatagrama.cpp -c
	g++ SocketDatagrama.cpp -c
	gcc gfxModified.c -c
	g++ Servidor.cpp PaqueteDatagrama.o SocketDatagrama.o gfxModified.o -o Servidor -lX11 -lm
	g++ Cliente.cpp PaqueteDatagrama.o SocketDatagrama.o gfxModified.o -o Cliente -lX11 -lm