#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define DEFTONE 0  //  default face tone
#define Q 24
#define G 42
#define B 56
#define EXT 9

#define WIDTH 128  //  repeat element width
#define HEIGHT 128  //  repeat element height

static unsigned long palette[5];
static int depth;                      /* bit per color pixel */
static int scr;                        /* screen number */
static Display* dpy;     /* X Display */
static GC gc[2];         /* Graphic Context */
static Window root;      /* Main root window */
static Window desk;
static int X0=0;         /* main root wintow x-location */
static int Y0=0;         /* main root wintow y-location */
static unsigned NX=10;   /* Default Boxes' number in each row */
static unsigned NY=10;    /* Default Row's number in game desk */
static int BW,BH;
static XRectangle cell;             /* Box cell */
static Window** box;     /* box (NYxNX) window array address */
static Window* row;      /* NY row window  box containe array  */ 
int size=20;

#endif  //  DEFINITIONS_H_
