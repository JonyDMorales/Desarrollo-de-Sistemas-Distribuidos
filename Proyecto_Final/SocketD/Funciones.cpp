#include "Funciones.h"


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
        }else{
            XColor color;

		color.flags = DoRed | DoGreen | DoBlue;
        color.red = 65535;
        color.blue = 0;
        color.green = 0;
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