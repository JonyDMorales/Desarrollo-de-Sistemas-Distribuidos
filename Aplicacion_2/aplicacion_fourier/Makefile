fourier:  fourier.cpp gfxModified.o SocketDatagrama.o PaqueteDatagrama.o
	g++ fourier.cpp gfxModified.o SocketDatagrama.o PaqueteDatagrama.o -o fourier -lX11 -lm
gfxModified.o: gfxModified.c gfxModified.h
	gcc gfxModified.c -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h SocketDatagrama.o
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c