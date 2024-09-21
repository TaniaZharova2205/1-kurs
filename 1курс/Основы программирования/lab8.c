#include <stdio.h>
#include <math.h>
double cos(double x)
{
	return cos(x) ;
}
double exp(double x)
{
	return exp(x) ;
}
float f(int x)
{
	double y=20-exp(x)+cos(x);
	return y;
}
int main()
{
	float Ep=0.1;
	double fa,fc,a=0,b=4,c;
	fa=f(a);
	while(fabs(a-b)>Ep)
		c=(a+b)/2;
		fc=f(c);
		if (fc*fa<0)
			b=c;
		else
			a=c;
			fa=fc;
	printf("Корень уравнения равен %lf",a);
}
