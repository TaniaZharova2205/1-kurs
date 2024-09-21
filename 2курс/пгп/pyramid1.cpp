#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "pyramid.h"
/* Polytop Graph static space definition */
static XVertex vertex[NVERT];
static XFace face[(NFACE+1)];
static XEdge edge[NEDGE];
static XPoint face4[NF4][(4+1)]; /* 3-top faces top location */
static XPoint face5[NF5][(5+1)];
static XPoint scale;             /* scale (pixel/cell) for x & y */ 

int assoc(XPolyGraph* pg) 
{
	pg->vertex = vertex;
	pg->edge = edge;
	pg->face = face;
	return(0);
} /* assoc */

/* Check Resize window when configure event */
int resize(unsigned w, unsigned h) {
	static XRectangle bak = {0, 0, 0, 0 };
	if((bak.width == w) && (bak.height == h))
		return(0);      /* remove window */
	bak.width = w; bak.height = h; 
	return(NFACE);          /* resize window */
} /* resize */

/* Check window scale when resize */
int rescale(unsigned w, unsigned h) {
	int x, y;      /* pixel for cell by x & y */
	x = w / NUNIT; y = h / NUNIT;
	if((scale.x == x) && (scale.y == y))
		return(0);    /* small resize without change scale */
	scale.x = x; scale.y = y;
	return(NFACE);  /* change scale */
} /* rescale */

int rebuild() { /* depending on graph ! */
	static XPoint vconf[] = { /* vertex location in x,y cells */
  		{2, 8}, {5, 2}, {11, 2}, {14, 8}, {8, 14}, {8,10}, {10,8}, {9,6}, {7,6}, {6,8}
	}; /* vconf */
	static int fconf4[NF4][(4+1)] = {    /* Vertex index */
  		{0, 1, 8, 9, 0},                      /* for 3-top faces */
  		{1, 2, 7, 8, 1},                      /* (begin = end vertex) */
  		{2, 3, 6, 7, 2},
  		{3, 4, 5, 6, 3},
  		{0, 4, 5, 9, 0}
	}; /* fconf4 */
	static int fconf5[NF5][(5+1)] = { {5, 6, 7, 8, 9, 5} };  
	static int econf[NEDGE][2] = { /* 2 Vertex index for each edge */
		{0, 1}, {0, 4}, {0, 9},     /* incident vertex 0 */            
		{1, 2}, {1, 8},                    /* incident vertex 1 */
		{2, 3}, {2, 7},
		{3, 4}, {3, 6},
		{4, 5},
		{5, 6}, {5, 9},
		{6, 7},
		{7, 8},
		{8,9}
	}; /* edge */
	int i, j;                          /* vertex, edge, face index */
	for(i=0; i < NVERT; i++) {    /* compute vertex pixel location */
		vertex[i].x = scale.x * vconf[i].x;
		vertex[i].y = scale.y * vconf[i].y;
	} /* for-vertex */
	for(i=0; i < NEDGE; i++) {   /* vertex pixel location for edge */
		edge[i].x1 = vertex[econf[i][0]].x;
		edge[i].y1 = vertex[econf[i][0]].y;
		edge[i].x2 = vertex[econf[i][1]].x;
		edge[i].y2 = vertex[econf[i][1]].y;
	} /* for-edge */
	for(i=0; i < NF4; i++)                /* vertex pixel location */ 
		for(j=0; j<(4+1); j++) {                  /* for 3-top faces */    
			face4[i][j].x = vertex[fconf4[i][j]].x;
			face4[i][j].y = vertex[fconf4[i][j]].y;
		}  /* for 3-top face */
	for(i=0; i < NF5; i++)                /* vertex pixel location */ 
		for(j=0; j<(5+1); j++) {                  /* for 3-top faces */    
			face5[i][j].x = vertex[fconf5[i][j]].x;
			face5[i][j].y = vertex[fconf5[i][j]].y;
		}
	return(0);
} /* rebuild */

int retrace() { /* depending on graph ! */
	int i=0;  /* total face index */
	int j;    /* n-top face index */
	for(j=0; j<NF4; j++, i++) {    /* fix 3-top faces in face array */
  		face[i].top = face4[j];       /* fix 3-top face array address */
  		face[i].Cn = 4;                /* fix 3-top face top number=3 */
  		face[i].tone = DEFTONE;        /* set face default tone color */
  		face[i].regi = XCreateRegion();      /* Empty region for face */
	} /* face4 */
	for(j=0; j<NF5; j++, i++) {    /* fix 3-top faces in face array */
  		face[i].top = face5[j];       /* fix 3-top face array address */
  		face[i].Cn = 5;                /* fix 3-top face top number=3 */
  		face[i].tone = DEFTONE;        /* set face default tone color */
  		face[i].regi = XCreateRegion();      /* Empty region for face */
		/* for(j=0; j<NF4; j++, i++) { ... } & etc. */
	} /* face5 */
	face[i].tone = DEFTONE;  /* store extern face default tone color */ 
return(0);
} /* retrace */

/* Reconfigure graph when window resize & rescale */
int reconf(unsigned w, unsigned h) {
	if(resize(w, h) == 0)
		return(0);
	if(rescale(w, h) != 0)
		rebuild();
	return(NFACE);
} /* reconf */

/* Ident face by inside point to repaint */
int zotone(int x, int y) {
	static XPoint past = {0, 0}; /* past scale */
	int f=0;                     /* face index */
	if((past.x == scale.x) && (past.y == scale.y)) /* Scale control */
		f = NFACE;      /* when no change scale */
	for( ; f < NFACE; f++) {          /* New regional zone for face */
		XDestroyRegion(face[f].regi);
		face[f].regi = XPolygonRegion(face[f].top, face[f].Cn, 0);
	} /* for */
	past.x = scale.x; past.y = scale.y;              /* Store scale */
	for(f=0; f < NFACE; f++)   /* find face with (x,y) inside */
		if(XPointInRegion(face[f].regi, x, y) == True)
			break;
	face[f].tone = (face[f].tone + 1) % NCOLOR;    /* new face tone */
	return(f);                   /* return pointed face for repaint */
} /* zotone */
