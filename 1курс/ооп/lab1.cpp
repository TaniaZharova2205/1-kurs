#include <stdio.h>
#include <math.h>

class Point2
{
	private:
		int x;
		int y;
	public:
		Point2 (int _x, int _y) : x(_x), y(_y) {};//конструктор с двумя параметрами 
		int getx() {return x;};
		int gety() {return y;};
		double distance (Point2*q,Point2*r)
		{
			double d2 = (r->x-q->x)*(r->x-q->x)+(r->y-q->y)*(r->y-q->y);
			return (sqrt(d2));
		}
};

int main( int argc, char* argv[])
{
	double min=10000;
	Point2** p;
	Point2* t;
	Point2* q;
	int x,y,k,r,g,l;
	int i=0;
	int j=0;
	if (argc < 2)
		return (-1);
	p = new Point2*[argc];//выделение памяти через new
	while(++i < argc)
	{
		sscanf(argv[i], "%d%*c%d", &x, &y);
		p[j]= new Point2(x, y);
		j++;
	}
	p[j]=NULL;
	for (i=0; p[i] != NULL; i++)
	{
		t = p[i];
		for (j=0; p[j] != NULL; j++)
		{
			q=p[j];
			if ((Point2::distance(t,q))<min && (Point2::distance(t,q))>0)
			{
				min=Point2::distance(t,q);
				k=t->getx();
				g=t->gety();
				r=q->getx();
				l=q->gety();
			}	
		}
	}
	
	printf("\nНаиболее близкие точки:\n(%d;%d)\n(%d;%d)\n\nРасстояние между ними равно:\n%f\n", k, g, r, l, min);
	for (j=0; p[j] != NULL; j++)
		delete p[j];
	delete []p;
	return 0;
}
