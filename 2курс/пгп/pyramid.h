#define MB0 5                       /* extern face top number */
#define NF4 5           		/* 3 top inner face number */
#define NF5 1              
           
#define NFACE (NF4+NF5)               
#define NEDGE ((4*NF4+5*NF5+MB0)/2)        
#define NVERT (NEDGE-(NFACE+1)+2)    /* vertex number (=5) by Euler */
#define NCOLOR 4        /* face color number */
#define NUNIT 18         /* unit cell number by X & Y */
#define EWIDTH 2        /* contour line width */
#define VDOT 8          /* vertex dot size */
#define DEFTONE 0       /* default face tone */
typedef XPoint XVertex;
typedef XSegment XEdge;
typedef struct {
	XPoint* top;   /* face vertex location array */
	int Cn;        /* face vertex  number */
	int tone;      /* face tone color index */
	Region regi;   /* face space region */
} XFace; 
typedef struct {
	XVertex* vertex;    /* vertex array */
	XFace* face;       /* face array */
	XEdge* edge;    /* edge path array */
} XPolyGraph;
int relink(XPolyGraph*);
GC congraph(Display*);
Window canvas(Display*);
int colorite(Display*);
int regraph(Display*, Window, GC, int);
int reset(Display*, Window, int);
int reface(Display*, Window, GC, int);
int assoc(XPolyGraph*);
int resize(unsigned, unsigned);
int rescale(unsigned, unsigned);
int rebuild();
int retrace();
int reconf(unsigned, unsigned);
int zotone(int, int);
int rekey(XEvent*);
int dispatch(Display*, Window, GC);
