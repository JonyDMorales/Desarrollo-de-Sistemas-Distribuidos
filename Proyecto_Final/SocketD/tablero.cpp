
// CÓDIGO GFXMODIFIED

//Resolución de la pantalla
#define ANCHURA 1000
#define ALTURA 980

#if defined(__cplusplus)
extern "C" {
#endif

#ifndef GFX_H
#define GFX_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include "gfxModified.h"


/* gfx_open creates several X11 objects, and stores them in these globals
   the globals are used by the other functions in the library.  */

static Display *gfx_display=0;
static Window  gfx_window;
static GC      gfx_gc;
static Colormap gfx_colormap;
static int      gfx_fast_color_mode = 0;

/* These values are saved by gfx_wait then retrieved later by gfx_xpos and gfx_ypos. */
static int saved_xpos = 0;
static int saved_ypos = 0;

	class Funciones
	{
		public:
		void gfx_open( int width, int height, const char *title );
		void gfx_flush();
		void gfx_color(int valor );
		void gfx_clear();
		void gfx_clear_color( int r, int g, int b );
		int gfx_event_waiting();
		int gfx_event_waiting2();
		char gfx_wait();
		int gfx_xpos();
		int gfx_ypos();
		int gfx_xsize();
		int gfx_ysize();
		void gfx_text( int x, int y , char *text );
		void gfx_point( int x, int y );
		void gfx_line( int x1, int y1, int x2, int y2 );
		void gfx_circle( int xCtr, int yCtr, int r );
		void gfx_ellipse( int xCtr, int yCtr, int r1, int r2 );
		void gfx_fill_ellipse( int xCtr, int yCtr, int r1, int r2 );
		void gfx_rectangle( int x, int y, int w, int h );
		void gfx_fill_rectangle( int x, int y, int w, int h );
		void gfx_fill_arc( int x, int y, unsigned int width, unsigned int height, int angle1, int angle2);
		void gfx_polygon( XPoint *pointsarr, int num_pts );
		void gfx_triangle( int x1, int y1, int x2, int y2, int x3, int y3 );
		bool gfx_keyPress(bool keys[6]);
	};


	/* Open a new graphics window. */
	void Funciones::gfx_open( int width, int height, const char *title )
	{
		gfx_display = XOpenDisplay(0);
		if(!gfx_display) {
			fprintf(stderr,"gfx_open: unable to open the graphics window.\n");
			exit(1);
		}

		Visual *visual = DefaultVisual(gfx_display,0);
		if(visual && visual->c_class ==TrueColor) {
			gfx_fast_color_mode = 1;
		} else {
			gfx_fast_color_mode = 0;
		}

		int blackColor = BlackPixel(gfx_display, DefaultScreen(gfx_display));
		int whiteColor = WhitePixel(gfx_display, DefaultScreen(gfx_display));

		gfx_window = XCreateSimpleWindow(gfx_display, DefaultRootWindow(gfx_display), 0, 0, width, height, 0, blackColor, blackColor);

		XSetWindowAttributes attr;
		attr.backing_store = Always;

		XChangeWindowAttributes(gfx_display,gfx_window,CWBackingStore,&attr);

		XStoreName(gfx_display,gfx_window,title);

		XSelectInput(gfx_display, gfx_window, StructureNotifyMask|KeyPressMask|ButtonPressMask | KeyReleaseMask);

		XMapWindow(gfx_display,gfx_window);

		gfx_gc = XCreateGC(gfx_display, gfx_window, 0, 0);
		//gfx_gc.font = 
		gfx_colormap = DefaultColormap(gfx_display,0);

		XSetForeground(gfx_display, gfx_gc, whiteColor);

		/* Wait for the MapNotify event */
		for(;;) {
			XEvent e;
			XNextEvent(gfx_display, &e);
			if (e.type == MapNotify)
				break;
		}
	}

	/* Flush all previous output to the window. */
	void Funciones::gfx_flush()
	{
		XFlush(gfx_display);
	}

	/* Change the current drawing color. */
	void Funciones::gfx_color(int val )
	{
        if(val == 1){
            //printf("ENTRE");
            XColor color;

		color.flags = DoRed | DoGreen | DoBlue;
        color.red = 0;
        color.blue = 58652;
        color.green = 0;
			XAllocColor(gfx_display,gfx_colormap,&color);

		XSetForeground(gfx_display, gfx_gc, color.pixel);
        }else if(val == 2){
           // printf("ENTRE 2");
            XColor color;

		color.flags = DoRed | DoGreen | DoBlue;
        color.red = 0;
        color.blue = 0;
        color.green = 33333;
			XAllocColor(gfx_display,gfx_colormap,&color);

		XSetForeground(gfx_display, gfx_gc, color.pixel);
        }else if(val == 3){
            XColor color;

		color.flags = DoRed | DoGreen | DoBlue;
        color.red = 65535;
        color.blue = 0;
        color.green = 0;
			XAllocColor(gfx_display,gfx_colormap,&color);

		XSetForeground(gfx_display, gfx_gc, color.pixel);
        }else{
			 XColor color;

		color.flags = DoRed | DoGreen | DoBlue;
        color.red = 65535;
        color.blue = 34640;
        color.green = 23451;
			XAllocColor(gfx_display,gfx_colormap,&color);

		XSetForeground(gfx_display, gfx_gc, color.pixel);
		}
		
	}

	/* Clear the graphics window to the background color. */
	void Funciones::gfx_clear()
	{
		XClearWindow(gfx_display,gfx_window);
	}

	/* Change the current background color. */
	void Funciones::gfx_clear_color( int r, int g, int b )
	{
		XColor color;
		color.pixel = 0;
		color.red = r<<8;
		color.green = g<<8;
		color.blue = b<<8;
		XAllocColor(gfx_display,gfx_colormap,&color);

		XSetWindowAttributes attr;
		attr.background_pixel = color.pixel;
		XChangeWindowAttributes(gfx_display,gfx_window,CWBackPixel,&attr);
	}

	/* See if an event has occurred */
	int Funciones::gfx_event_waiting()
	{
		XEvent event;

		gfx_flush();

		while (1) {
				if(XCheckMaskEvent(gfx_display,-1,&event)) {
						if(event.type==KeyPress) {
								XPutBackEvent(gfx_display,&event);
								return 1;
						} else if (event.type==ButtonPress) {
								XPutBackEvent(gfx_display,&event);
								return 1;
						} else {
								return 0;
						}
				} else {
						return 0;
				}
		}
	}

	int Funciones::gfx_event_waiting2()
	{
		XEvent event;

		gfx_flush();
		while (1) {
				if(XCheckMaskEvent(gfx_display,-1,&event)) {
						if(event.type==KeyPress) {
								XPutBackEvent(gfx_display,&event);
								return 1;
						} else if (event.type==ButtonPress) {
								XPutBackEvent(gfx_display,&event);
								return 1;
						} else if (event.type==KeyRelease) {

								XPutBackEvent(gfx_display,&event);
								return 1; 
				} 
					else {
								return 0;
						}
				} else {
						return 0;
				}
		}
	}



	/* Wait for the user to press a key or mouse button. */
	char Funciones::gfx_wait()
	{
		XEvent event;

		gfx_flush();
		while(1) {
			XNextEvent(gfx_display,&event);

			if(event.type==KeyPress) {
				saved_xpos = event.xkey.x;
				saved_ypos = event.xkey.y;
				return XLookupKeysym(&event.xkey,0);
			} else if(event.type==ButtonPress) {
				saved_xpos = event.xkey.x;
				saved_ypos = event.xkey.y;
				return event.xbutton.button;
			}
		}
	}

	/* Return the X coordinate of the last event. */
	int Funciones::gfx_xpos()
	{
		return saved_xpos;
	}

	/* Return the  Y coordinate of the last event. */
	int Funciones::gfx_ypos()
	{
		return saved_ypos;
	}

	/* get width and height of the screen */
	int Funciones::gfx_xsize()
	{
		return XDisplayWidth(gfx_display, 0);
	}

	int Funciones::gfx_ysize()
	{
		return XDisplayHeight(gfx_display, 0);
	}

	/* Draw a string at point (x,y) */
	void Funciones::gfx_text( int x, int y , char *text )	
	{	
		//Font font=XLoadFont(gfx_display,-bitstream-charter-medium-r-normal--12-120-75-75-p-68-iso8859-1[65 70 80_90]);
		//XTextItem stritem={text,50,5,};
		XDrawString(gfx_display, gfx_window, gfx_gc, x, y, text, strlen(text));
		//XDrawText(gfx_display, gfx_window, gfx_gc, x, y,stritem,1);
	}

	

	/* Draw a single point at (x,y) */
	void Funciones::gfx_point( int x, int y )
	{
		XDrawPoint(gfx_display, gfx_window, gfx_gc, x, y);
	}

	/* Draw a line from (x1,y1) to (x2,y2) */
	void Funciones::gfx_line( int x1, int y1, int x2, int y2 )
	{
		XDrawLine(gfx_display, gfx_window, gfx_gc, x1, y1, x2, y2);
	}

	/* Draw a circle; uses a version of Bresenham's circle algorithm */
	void Funciones::gfx_circle( int xCtr, int yCtr, int r )
	{
	int x, y;	/* vert. and horiz. distance from center */
	int p;	/* parameter to control changes in y */

	y = r;
	p = 3 - 2*r;

	for (x = 0; x <= y; x++)
	{
		gfx_point(xCtr + x, yCtr + y);
		gfx_point(xCtr + x, yCtr - y);
		gfx_point(xCtr - x, yCtr + y);
		gfx_point(xCtr - x, yCtr - y);
		gfx_point(xCtr + y, yCtr + x);
		gfx_point(xCtr + y, yCtr - x);
		gfx_point(xCtr - y, yCtr + x);
		gfx_point(xCtr - y, yCtr - x);

		if (p < 0)
		p = p + 4 * x + 6;
		else
		{
		p = p + 4 * (x - y) + 10;
		y--;
		}
	} 
	}

	/* Draw an ellipse; uses Xlib's native arc drawing function */
	void Funciones::gfx_ellipse( int xCtr, int yCtr, int r1, int r2 )
	{
		XDrawArc(gfx_display, gfx_window, gfx_gc, xCtr-r1, yCtr-r2, 2*r1, 2*r2, 0, 360*64);
	}

	void Funciones::gfx_fill_ellipse( int xCtr, int yCtr, int r1, int r2 )
	{
		XFillArc(gfx_display, gfx_window, gfx_gc, xCtr-r1, yCtr-r2, 2*r1, 2*r2, 0, 360*64);
	}

	/* Draw a rectangle, given its top left corner and its (positive) width and height */
	void Funciones::gfx_rectangle( int x, int y, int w, int h )
	{ 
		XDrawRectangle(gfx_display, gfx_window, gfx_gc, x, y, w, h);
	}

	/* Draw a filled rectangle; similar setup to gfx_rectangle, but "one pixel in" on all four sides */
	void Funciones::gfx_fill_rectangle( int x, int y, int w, int h )
	{ 
		XFillRectangle(gfx_display, gfx_window, gfx_gc, x, y, w, h);
	}

	/* Dibuja un arco lleno  donde x, y es la coordenada del angulo superior izquierdo que la contiene*/
	void Funciones::gfx_fill_arc( int x, int y, unsigned int width, unsigned int height, int angle1, int angle2)
	{
		//XFillArc(display, win, gc2, 50, 50, 300, 200, 0, 360*64);	

		XFillArc(gfx_display, gfx_window, gfx_gc, x, y, width, height, angle1, angle2);	
	}


	/* Draw a polygon; uses Xlib's XPoint struct; the num_pts points are in the pointsarr array */
	/* (if the last point is the same as the first point, the polygon will be a closed one) */
	void Funciones::gfx_polygon( XPoint *pointsarr, int num_pts )
	{
		XDrawLines(gfx_display, gfx_window, gfx_gc, pointsarr, num_pts, CoordModeOrigin);
	}

	/* Draw a triangle connecting (x1,y1), (x2,y2), and (x3,y3) */
	void Funciones::gfx_triangle( int x1, int y1, int x2, int y2, int x3, int y3 )
	{
		gfx_line(x1,y1,x2,y2);
		gfx_line(x2,y2,x3,y3);
		gfx_line(x3,y3,x1,y1);
	}


	bool Funciones::gfx_keyPress(bool keys[6]){
		XEvent report,pause;
		int i;
			XNextEvent (gfx_display, &report);
			switch (report.type)
			{
			case KeyPress:
				//  fprintf (stdout, "key #%ld was pressed.\n",
				//   (long) XLookupKeysym (&report.xkey, 0));

				switch((long) XLookupKeysym (&report.xkey, 0)){
				case 97:
					keys[0] = 1;
					break;
				case 119:
					keys[1] = 1;
					break;
				case 100:
					keys[2] = 1;
					break;
				case 65361:
					keys[3] = 1;
					break;
				case 65362:
					keys[4] = 1;
					break;
				case 65363:
					keys[5] = 1;
					break;
				case 65307:
					printf("escaped\n");
					return 1;
					break;
				case 112:
					printf("paused\n");
					while(1){
						//pause=XEvent(NULL);
						XNextEvent (gfx_display, &pause);
						if( (long) XLookupKeysym (&pause.xkey, 0) == 112)
							break;
						else
							printf("press p to continue\n");					
					}
					break;
				default:
					//printf("wrong key");
					break;
				}

				int counter;
				/*
				for(counter=0;counter<6;counter++)
					printf("%i ",keys[counter]);
				printf("\n\n");
				*/
				break;
			case KeyRelease:
				{
					unsigned short is_retriggered = 0;

					if (XEventsQueued(gfx_display, QueuedAfterReading))
					{
						XEvent nev;
						XPeekEvent(gfx_display, &nev);

						if (nev.type == KeyPress && nev.xkey.time == report.xkey.time &&
							nev.xkey.keycode == report.xkey.keycode)
						{

							// delete retriggered KeyPress event
							XNextEvent (gfx_display, &report);
							is_retriggered = 1;
						}
					}

					if (!is_retriggered){
						//   fprintf (stdout, "key #%ld was released.\n",
						// (long) XLookupKeysym (&report.xkey, 0));

						switch((long) XLookupKeysym (&report.xkey, 0)){
						case 97:
							keys[0] = 0;
							break;
						case 119:
							keys[1] = 0;
							break;
						case 100:
							keys[2] = 0;
							break;
						case 65361:
							keys[3] = 0;
							break;
						case 65362:
							keys[4] = 0;
							break;
						case 65363:
							keys[5] = 0;
							break;	
						default:
							//printf("wrong key");
							break;
						}
						int counter;
						/*
						for(counter=0;counter<6;counter++)
							printf("%i ",keys[counter]);
						printf("\n\n");
						*/
					}
				}
				break;
			}
		return 0;
	}

#endif

#if defined(__cplusplus)
}
#endif


// CÓDIGO Grafica

#include <iostream>
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

class Grafica{

  private:
    Funciones gfx_function;
    bool tecla[6];  //Arreglo para saber si una tecla de dirección se ha presionado
  public: 
    Grafica();
    int inicializaGrafica(int level);
    void print_time();
    int impresion();
	void tablero5x5();
    void tablero7x7();
    void tablero10x10();
    
    
	void Barcos_medianosG();
    void Barcos_grandesG();
	void Barcos_pequenosG();
    void Barcos_medianos();
    void Barcos_grandes();
	void Barcos_pequenos();
    void Barcos_medianos5();
    void Barcos_grandes5();
	void Barcos_pequenos5();
    void Numeros5x5();
    void Numeros7x7();
    void Numeros10x10();
	void barco_Bomba(int x, int y);
	void Posicionamiento5x5(int x, int y, int c, int m);
	//void dispSiete(char val_num);
	void gfx_clear();
};

int pos_x, pos_y;
int casilla_1 = 160;
int casilla_2 = 120;
int casilla_3 = 80;
int margen_1 = 10;
int offset = 50;
int barcos[5][4];
int coordenadas[9][3];
int level;

Grafica::Grafica() 
{ 
}

void Grafica::tablero5x5()
{
    gfx_function.gfx_fill_rectangle(50,50,10,860); 
    gfx_function.gfx_fill_rectangle(220,50,10,860); 
    gfx_function.gfx_fill_rectangle(390,50,10,860); 
    gfx_function.gfx_fill_rectangle(560,50,10,860); 
    gfx_function.gfx_fill_rectangle(730,50,10,860); 
    gfx_function.gfx_fill_rectangle(900,50,10,860); 
 

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,860,10); 
    gfx_function.gfx_fill_rectangle(50,220,860,10); 
    gfx_function.gfx_fill_rectangle(50,390,860,10); 
    gfx_function.gfx_fill_rectangle(50,560,860,10); 
    gfx_function.gfx_fill_rectangle(50,730,860,10); 
    gfx_function.gfx_fill_rectangle(50,900,860,10); 
    
  
   
}

void Grafica::tablero7x7()
{
    //char *a;
    //memcpy(&a,'A',sizeof(a));
    gfx_function.gfx_fill_rectangle(50,50,10,910); 
    gfx_function.gfx_fill_rectangle(180,50,10,910); 
    gfx_function.gfx_fill_rectangle(310,50,10,910); 
    gfx_function.gfx_fill_rectangle(440,50,10,910); 
    gfx_function.gfx_fill_rectangle(570,50,10,910); 
    gfx_function.gfx_fill_rectangle(700,50,10,910);
    gfx_function.gfx_fill_rectangle(830,50,10,910);
    gfx_function.gfx_fill_rectangle(960,50,10,910); 
    //gfx_function.gfx_text(25,64,a);

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,910,10); 
    gfx_function.gfx_fill_rectangle(50,180,910,10); 
    gfx_function.gfx_fill_rectangle(50,310,910,10); 
    gfx_function.gfx_fill_rectangle(50,440,910,10); 
    gfx_function.gfx_fill_rectangle(50,570,910,10); 
    gfx_function.gfx_fill_rectangle(50,700,910,10); 
    gfx_function.gfx_fill_rectangle(50,830,910,10); 
    gfx_function.gfx_fill_rectangle(50,960,910,10); 
    
  
   
}

void Grafica::tablero10x10()
{
    gfx_function.gfx_fill_rectangle(50,50,5,905); 
    gfx_function.gfx_fill_rectangle(140,50,5,905); 
    gfx_function.gfx_fill_rectangle(230,50,5,905); 
    gfx_function.gfx_fill_rectangle(320,50,5,905); 
    gfx_function.gfx_fill_rectangle(410,50,5,905); 
    gfx_function.gfx_fill_rectangle(500,50,5,905); 
    gfx_function.gfx_fill_rectangle(590,50,5,905); 
    gfx_function.gfx_fill_rectangle(680,50,5,905); 
    gfx_function.gfx_fill_rectangle(770,50,5,905); 
    gfx_function.gfx_fill_rectangle(860,50,5,905); 
    gfx_function.gfx_fill_rectangle(950,50,5,905); 
 

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,905,5); 
    gfx_function.gfx_fill_rectangle(50,140,905,5); 
    gfx_function.gfx_fill_rectangle(50,230,905,5);
	gfx_function.gfx_fill_rectangle(50,320,905,5); 
    gfx_function.gfx_fill_rectangle(50,410,905,5); 
    gfx_function.gfx_fill_rectangle(50,500,905,5); 
    gfx_function.gfx_fill_rectangle(50,590,905,5);
    gfx_function.gfx_fill_rectangle(50,680,905,5); 
    gfx_function.gfx_fill_rectangle(50,770,905,5); 
    gfx_function.gfx_fill_rectangle(50,860,905,5); 
    gfx_function.gfx_fill_rectangle(50,950,905,5); 
   
}

void Grafica::Posicionamiento5x5(int x, int y, int c, int m){
	if(x > 1){
		pos_x = (x - 1) * c + c/2 + (x * m);
	}else{
		pos_x = c/2 + m;
	}

	if(y > 1){
		pos_y = (y - 1) * c + c/2 + (y * m);
	}else{
		pos_y = c/2 + m;
	}
	pos_x = pos_x + offset;
	pos_y = pos_y + offset;

}

void Grafica::Barcos_pequenosG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 20, 20);
   // gfx_function.gfx_fill_ellipse(920, 905, 20, 30);
}

void Grafica::Barcos_medianosG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 45, 20, 45);
   // gfx_function.gfx_fill_ellipse(780, 500, 20, 80);
}

void Grafica::Barcos_grandesG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 90, 20, 90);
    
}

void Grafica::Barcos_pequenos(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 20, 30);
   // gfx_function.gfx_fill_ellipse(920, 905, 20, 30);
}

void Grafica::Barcos_medianos(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 65, 20, 65);
   // gfx_function.gfx_fill_ellipse(780, 500, 20, 80);
}

void Grafica::Barcos_grandes(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 130, 20, 130);
    
}

void Grafica::Barcos_pequenos5(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 60);
	//gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 60);	
}

void Grafica::Barcos_medianos5(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 85, 30, 85);
    //gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 120);
}

void Grafica::Barcos_grandes5(){
   gfx_function.gfx_fill_ellipse(pos_x, pos_y + 170, 30, 170);
    
}

void Grafica::Numeros5x5(){
    gfx_function.gfx_fill_rectangle(25,95,5,40); //1

    gfx_function.gfx_fill_rectangle(10,280,30,5); //2
    gfx_function.gfx_fill_rectangle(10,300,30,5); //2
    gfx_function.gfx_fill_rectangle(10,320,30,5); //2
    gfx_function.gfx_fill_rectangle(35,280,5,20); //2
    gfx_function.gfx_fill_rectangle(10,300,5,20); //2
	
    gfx_function.gfx_fill_rectangle(10,460,30,5); //2
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,500,30,5); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,480,5,20); //2

    gfx_function.gfx_fill_rectangle(10,660,30,5); //2
    gfx_function.gfx_fill_rectangle(10,640,5,20); //2
    gfx_function.gfx_fill_rectangle(35,640,5,20); //2
    gfx_function.gfx_fill_rectangle(35,660,5,20); //2

    gfx_function.gfx_fill_rectangle(10,860,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,30,5); //2
    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,5,20); //2
    gfx_function.gfx_fill_rectangle(35,840,5,20); //2  

}

void Grafica::Numeros7x7(){
    gfx_function.gfx_color(2);
    gfx_function.gfx_fill_rectangle(25,95,5,30); //1

    gfx_function.gfx_fill_rectangle(10,220,30,5); //2
    gfx_function.gfx_fill_rectangle(10,240,30,5); //2
    gfx_function.gfx_fill_rectangle(10,260,30,5); //2
    gfx_function.gfx_fill_rectangle(35,220,5,20); //2
    gfx_function.gfx_fill_rectangle(10,240,5,20); //2
	
    gfx_function.gfx_fill_rectangle(10,340,30,5); //2
    gfx_function.gfx_fill_rectangle(10,360,30,5); //2
    gfx_function.gfx_fill_rectangle(10,380,30,5); //2
    gfx_function.gfx_fill_rectangle(35,340,5,20); //2
    gfx_function.gfx_fill_rectangle(35,360,5,20); //2

    
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,480,5,20); //2


    gfx_function.gfx_fill_rectangle(10,600,30,5); //2
    gfx_function.gfx_fill_rectangle(10,620,30,5); //2
    gfx_function.gfx_fill_rectangle(10,640,30,5); //2
    gfx_function.gfx_fill_rectangle(10,600,5,20); //2
    gfx_function.gfx_fill_rectangle(35,620,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,720,30,5); //2
    gfx_function.gfx_fill_rectangle(10,740,30,5); //2
    gfx_function.gfx_fill_rectangle(10,760,30,5); //2
    gfx_function.gfx_fill_rectangle(10,720,5,20); //2
    gfx_function.gfx_fill_rectangle(10,740,5,20); //2
    gfx_function.gfx_fill_rectangle(35,740,5,20); //2

    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(35,840,5,20); //2
    gfx_function.gfx_fill_rectangle(35,860,5,20); //2
    

}

void Grafica::Numeros10x10(){
    gfx_function.gfx_color(3);
    gfx_function.gfx_fill_rectangle(25,75,5,30); //1

    gfx_function.gfx_fill_rectangle(10,160,30,5); //2
    gfx_function.gfx_fill_rectangle(10,180,30,5); //2
    gfx_function.gfx_fill_rectangle(10,200,30,5); //2
    gfx_function.gfx_fill_rectangle(35,160,5,20); //2
    gfx_function.gfx_fill_rectangle(10,180,5,20); //2
	
    gfx_function.gfx_fill_rectangle(10,245,30,5); //2
    gfx_function.gfx_fill_rectangle(10,265,30,5); //2
    gfx_function.gfx_fill_rectangle(10,285,30,5); //2
    gfx_function.gfx_fill_rectangle(35,245,5,20); //2
    gfx_function.gfx_fill_rectangle(35,265,5,20); //2

    gfx_function.gfx_fill_rectangle(10,370,30,5); //2
    gfx_function.gfx_fill_rectangle(10,350,5,20); //2
    gfx_function.gfx_fill_rectangle(35,350,5,20); //2
    gfx_function.gfx_fill_rectangle(35,370,5,20); //2

    gfx_function.gfx_fill_rectangle(10,440,30,5); //2
    gfx_function.gfx_fill_rectangle(10,460,30,5); //2
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,440,5,20); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,520,30,5); //2
    gfx_function.gfx_fill_rectangle(10,540,30,5); //2
    gfx_function.gfx_fill_rectangle(10,560,30,5); //2
    gfx_function.gfx_fill_rectangle(10,520,5,20); //2
    gfx_function.gfx_fill_rectangle(10,540,5,20); //2
    gfx_function.gfx_fill_rectangle(35,540,5,20); //2

    gfx_function.gfx_fill_rectangle(10,620,30,5); //2
    gfx_function.gfx_fill_rectangle(35,620,5,20); //2
    gfx_function.gfx_fill_rectangle(35,640,5,20); //2

    gfx_function.gfx_fill_rectangle(10,700,30,5); //2
    gfx_function.gfx_fill_rectangle(10,720,30,5); //2
    gfx_function.gfx_fill_rectangle(10,740,30,5); //2
    gfx_function.gfx_fill_rectangle(35,700,5,20); //2
    gfx_function.gfx_fill_rectangle(35,720,5,20); //2
    gfx_function.gfx_fill_rectangle(10,700,5,20); //2
    gfx_function.gfx_fill_rectangle(10,720,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,800,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,30,5); //2
    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(35,800,5,20); //2
    gfx_function.gfx_fill_rectangle(35,820,5,20); //2
    gfx_function.gfx_fill_rectangle(10,800,5,20); //2
    
    gfx_function.gfx_fill_rectangle(20,880,20,3); //2
    gfx_function.gfx_fill_rectangle(20,930,20,3); //2
    gfx_function.gfx_fill_rectangle(40,880,3,52); //2    
    gfx_function.gfx_fill_rectangle(20,880,3,50); //2
    gfx_function.gfx_fill_rectangle(10,880,3,50); //1

}

void Grafica::barco_Bomba(int x, int y){
	
	for(int i = 0; i < 9; i++){
		if(coordenadas[i][0] == x && coordenadas[i][1] == y && coordenadas[i][2]){
			if(level == 1){
				
					gfx_function.gfx_color(4);
					Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_1, margen_1);
					gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_1/2),coordenadas[i][0], coordenadas[i][1] + (casilla_1/2));
					coordenadas[i][2] = 0;
				
			}else if(level == 2){
				
					gfx_function.gfx_color(4);
					Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_2, margen_1);
					gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_2/2),coordenadas[i][0], coordenadas[i][1] + (casilla_2/2));
					coordenadas[i][2] = 0;
				
			}else{
					gfx_function.gfx_color(4);
					Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_3, margen_1);
					gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_3/2),coordenadas[i][0], coordenadas[i][1] + (casilla_3/2));
					coordenadas[i][2] = 0;
				
			}
			 
		}
	}
}

int Grafica::inicializaGrafica(int level)
{
    
    int i;
    int pos_x;
 
    Grafica reloj;

    //LETRAS
    
    
    gfx_function.gfx_open(ANCHURA, ALTURA, "Tablero Jueguito :)");
	    
	while(1){
        //Dibuja el tablero
       if(level == 1){
            gfx_function.gfx_color(1);
            reloj.tablero5x5();
			reloj.Numeros5x5();
            for(int i = 0 ; i < 5 ; i++){
				reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_1,margen_1);
				if(i == 0 || i == 1){
					reloj.Barcos_pequenos5();
				}else if(i == 2 || i == 3){
					reloj.Barcos_medianos5();
				}else{
					reloj.Barcos_grandes5();
				}
			}
			  
            gfx_function.gfx_flush();
            usleep(18000);
       }else if(level == 2) {
           gfx_function.gfx_color(2);
            reloj.tablero7x7();
			reloj.Numeros7x7();
            for(int i = 0 ; i < 5 ; i++){
				reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_2,margen_1);
				if(i == 0 || i == 1){
					reloj.Barcos_pequenos();
				}else if(i == 2 || i == 3){
					reloj.Barcos_medianos();
				}else{
					reloj.Barcos_grandes();
				}
			}
			  
            gfx_function.gfx_flush();
            usleep(18000);

       }else if(level == 3){
            gfx_function.gfx_color(3);
            reloj.tablero10x10();
			reloj.Numeros10x10();
            for(int i = 0 ; i < 5 ; i++){
				reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_3,margen_1);
				if(i == 0 || i == 1){
					reloj.Barcos_pequenosG();
				}else if(i == 2 || i == 3){
					reloj.Barcos_medianosG();
				}else{
					reloj.Barcos_grandesG();
				}
			}

            gfx_function.gfx_flush();
            usleep(18000);
        }else{
           cout << "No hay ese nivel, tonto" << endl;
       }
       
		
    }     
}


void Grafica::gfx_clear()
	{
		XClearWindow(gfx_display,gfx_window);
	}


int main(int argc, char *argv[])
{
    //int gettimeofday(struct timeval *tv, struct timezone *tz);
    //cout << gettimeofday() << endl;
    Grafica graph;
	int x,y;
    //graph.print_time();
    //while(1){
    cout << "Introduce nivel" << endl,
    cin >> level;
    cout << level << endl;
	
	int i;
	
	cout <<"Barco 1 (1 recuadro)"  << endl;
	cin >> barcos[0][0];
	cin >> barcos[0][1];
	barcos[0][2] = 0;
	coordenadas[0][0] = barcos[0][0];
	coordenadas[0][1] = barcos[0][1];
	coordenadas[0][2] = 1;

	cout <<"Barco 2 (1 recuadro)"  << endl;
	cin >> barcos[1][0];
	cin >> barcos[1][1];
	barcos[1][2] = 0;
	coordenadas[1][0] = barcos[1][0];
	coordenadas[1][1] = barcos[1][1];
	coordenadas[1][2] = 1;

	cout <<"Barco 3 (2 recuadro)"  << endl;
	cin >> barcos[2][0];
	cin >> barcos[2][1];
	barcos[2][2] = 1;
	coordenadas[2][0] = barcos[2][0];
	coordenadas[2][1] = barcos[2][1];
	coordenadas[2][2] = 1;
	coordenadas[3][0] = barcos[2][0];
	coordenadas[3][1] = barcos[2][1] + 1;
	coordenadas[3][2] = 1;
	
	cout <<"Barco 4 (2 recuadro)"  << endl;
	cin >> barcos[3][0];
	cin >> barcos[3][1];
	barcos[3][2] = 1;
	coordenadas[4][0] = barcos[3][0];
	coordenadas[4][1] = barcos[3][1];
	coordenadas[4][2] = 1;
	coordenadas[5][0] = barcos[3][0];
	coordenadas[5][1] = barcos[3][1] + 1;
	coordenadas[5][2] = 1;
	
	cout <<"Barco 5 (3 recuadro)"  << endl;
	cin >> barcos[4][0];
	cin >> barcos[4][1];
	barcos[4][2] = 2;
	coordenadas[6][0] = barcos[4][0];
	coordenadas[6][1] = barcos[4][1];
	coordenadas[6][2] = 1;
	coordenadas[7][0] = barcos[4][0];
	coordenadas[7][1] = barcos[4][1] + 1;
	coordenadas[7][2] = 1;
	coordenadas[8][0] = barcos[4][0];
	coordenadas[8][1] = barcos[4][1] + 2;
	coordenadas[8][2] = 1;

	for(int i = 0; i < 9 ; i++){
		cout << "Coordenadas: " << coordenadas[i][0] << " " << coordenadas[i][1] <<endl;
	}
	//graph.Posicionamiento5x5(x,y);
    graph.inicializaGrafica(level);
    //usleep(100000);
//}

}

// g++ Grafica.cpp -lX11 -o Grafica -lm
