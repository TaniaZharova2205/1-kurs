#ifndef XFLOOR_H_
#define XFLOOR_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/keysymdef.h>
#include <stdlib.h>
#include <stdio.h>

int colorite(Display* dpy);
Window CreateWin(Display* dpy);
int relink(void* r, void** b);
int alloc(unsigned _nx, unsigned _ny);
int dealloc(void** b, void* r);
int recolor(int ColorId, XEvent* Ev);

#endif  //  XFLOOR_H_
