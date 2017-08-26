uvideojuego:  uvideojuego.o gfxModified.o
	g++ uvideojuego.o gfxModified.o -o uvideojuego -lX11 -lm
uvideojuego.o: uvideojuego.cpp gfxModified.o
	g++ uvideojuego.cpp -c
gfxModified.o: gfxModified.c gfxModified.h
	gcc gfxModified.c -c