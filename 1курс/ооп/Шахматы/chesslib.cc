#include "chesslib.h"

int Knight::attack(char* p)
{
	if(deskout(p)>0)
		return (0);
	int x=p[0]-pos[0];
	int y=p[1]-pos[1];
	if(x<0)
		x=-x;
	if(y<0)
		y=-y;
	if((x+y)==3 &&((x==2*y)||(y==2*x)))
		return(1);
	return(0);
}

int Queen::attack(char* p)
{
	if(deskout(p)>0)
		return (0);
	int x=p[0]-pos[0];
	int y=p[1]-pos[1];
	if(x<0)
		x=-x;
	if(y<0)
		y=-y;
	if((x==y) || (x==0) || (y==0))
		return(1);
	return(0);
}

int Amazon::attack(char* s)
{
	if(Knight::attack(s)>0)
		return(1);
	if(Queen::attack(s)>0)
		return(2);
	return(0);
}
