
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
#if defined(__cplusplus)
}
#endif
#endif