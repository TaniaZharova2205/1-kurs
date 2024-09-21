#include "xfloor.h"
#include "definitions.h"

int colorite(Display* dpy) {
	Colormap cmap;  // color map
	XColor bw;  //  Structure for color allocation
	int i;  //  color index
	static char* spector[] = {
                          "#ffffff",  //  white
                          "#000000"  // black
	};
	cmap = DefaultColormap(dpy, DefaultScreen(dpy));
	for(i=0; i < 2; i++ ) {
		XParseColor(dpy, cmap, spector[i], &bw);  //ИЩЕМ RGB ПО НАЗВАНИЮ
		XAllocColor(dpy, cmap, &bw);
		palette[i] = bw.pixel;
	}
	return 0;
}

Window CreateWin(Display* dpy) {
	XSetWindowAttributes attr;  //  window attributes
	XSizeHints hint;  //  connect with Window Maneger
	int i,j;
	int x, y;  //  window location
	unsigned w, h;  //  window size
	gc[0] = DefaultGC(dpy, scr);
	attr.override_redirect = False;  //  set window maneger control
	attr.background_pixel = palette[DEFTONE];  //  background color
	attr.event_mask = (ButtonPressMask | KeyPressMask);
	scr =  DefaultScreen(dpy);
	w = NX * BW;
	h = NY * BH;
	x = X0;
	y = Y0;
	root = XCreateWindow(dpy, DefaultRootWindow(dpy), x, y, w, h,  //  main window
		1, depth, InputOutput, CopyFromParent,
		(CWOverrideRedirect | CWBackPixel|CWEventMask),  &attr);
	hint.flags = (PMinSize | PPosition | PMaxSize|PResizeInc);
	hint.min_width = hint.max_width = w;
	hint.min_height = hint.max_height = h;
	hint.x = x; hint.y = y;
	hint.width_inc=hint.height_inc = size;
	XSetNormalHints(dpy, root, &hint);
	//  box row  root's subwindow
	attr.override_redirect = True;
	attr.event_mask = (ButtonPressMask | KeyPressMask);
	w = NX * BW; 
	h = BH;
	j=0;
	for(i=0, y = 0; i < NY; i++, y += BH) {
		row[i] = XCreateWindow(dpy, root, x, y, w, h, 0, depth,
			InputOutput, CopyFromParent,
			(CWOverrideRedirect | CWBackPixel| CWEventMask),  &attr);
  	}
	//  Box row's subwindows
	attr.override_redirect = True;
	attr.event_mask = (ButtonPressMask|KeyPressMask | ExposureMask);
	attr.background_pixel = palette[0];
	w = BW; h = BH;
	int k=0;
	for(i=0, y=0; i < NY; i++) {
		for(j=0, x=0 ; j < NX; j++, x += BW) {
		box[i][j] = XCreateWindow(dpy, row[i], x, y, w, h, 1,
			depth, InputOutput, CopyFromParent,
			(CWOverrideRedirect | CWBackPixel | CWEventMask), &attr);
		}
	}
	//  Display windows
	XMapWindow(dpy, root);
	XMapSubwindows(dpy, root);
	for(i=0; i<NY; i++) {
		XMapSubwindows(dpy, row[i]);
	}
	XStoreName(dpy, root, "xpat");
	return root;
} 

int relink(void* r, void** b) {
	row = (Window* ) r;
	box = (Window**) b;
	return 0;
}

int alloc(unsigned _nx, unsigned _ny) {
	void* r;  //  row array pointer
	void** b;  //  box array pointer
	int i;  //  row & position array index
	NX = _nx; NY = _ny; 
	r = calloc(NY, sizeof(unsigned long));
	b = calloc(NY, sizeof(void*));
	for(i=0; i < NY; i++) 
		b[i] = calloc(NX,  sizeof(unsigned long));
	relink(r, b);  //  link to xpat0
	return(0);
}

int dealloc(void** b, void* r) {
	int i;   
	for(i=0; i < NY; i++) {
		free(b[i]);
	}
	free(b);
	free(r);
	return 0;
}

int recolor(int ColorId, XEvent* Ev) {
	int i,j;
	for(i=0; i < NY; i++) {
		for(j=0; j < NX; j++) {
			XSetWindowBackground(dpy, box[i][j], palette[ColorId]) ;
    			XClearWindow(dpy,box[i][j]);
		}
	}
}

/*int invert(int XEvent* Ev) {
	int i,j;
	for(i=0; i < NY; i++) {
		for(j=0; j < NX; j++) {
			XSetWindowBackground(dpy, box[i][j], palette[ColorId]) ;
    			XClearWindow(dpy,box[i][j]);
		}
	}
}*/
