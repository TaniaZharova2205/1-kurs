#include "xfloor.c"

int main(int argc, char** argv) {
	if (argc < 4) {
		return -1;
	}
	XEvent event;
	unsigned int done = 0;  //  exit code
	size = atoi(argv[1]);
	NX = atoi(argv[2]);
	NY = atoi(argv[3]);
	BW = BH = size;
	dpy = XOpenDisplay(NULL);
	scr = DefaultScreen(dpy);
	if( (NX * size > DisplayWidth(dpy,scr)) || (NY * size > DisplayHeight(dpy,scr)) ) {
		return(puts("Incorrect large\n"));
	}
	alloc(NX, NY);
	depth = DefaultDepth(dpy, scr);
	colorite(dpy);
	desk = CreateWin(dpy);
	while(done == 0) {
		XNextEvent(dpy, &event);
		switch(event.type) {
			case ButtonPress:
			case ButtonRelease:
				XSetWindowBackground(dpy, event.xbutton.window, palette[event.xbutton.button]) ;
				XClearWindow(dpy,event.xbutton.window);
				break;
			case KeyPress:
			case KeyRelease:
				if(event.xkey.keycode==EXT) {
					recolor(0,&event);
				} else {
					if(event.xkey.keycode==G) {
						recolor(2,&event);
					} else {
						if(event.xkey.keycode==B) {
							recolor(1,&event);
						} else {
							if(event.xkey.keycode==Q) {
								done=1;
							}
						}
					}
				}
				break;
			default:
				break;
		}
	} 
	XDestroySubwindows(dpy, root);
	XDestroyWindow(dpy, root);
	XCloseDisplay(dpy);
	dealloc((void**)box,row);
	return done;
}
