#include <stdio.h>
int EPS = 8;

double input()
{
	double a;
	while(scanf("%lf", &a) == 0) 
	{
		printf("повторите ввод\n");
		while(getchar() != '\n');
	}
	return a;
}

int input_s()
{
	int a;
	while((scanf("%d", &a) == 0) || (a < 2) || (a > 16))
	{
		printf("повторите ввод\n");
		while(getchar() != '\n');
	}
	return a;
}

void I(int Int, int s)
{
	int a[100], i = 0;
	do {
		a[i] = Int % s;
		i++;
		Int /= s;
	} 
	while (Int > 0);
	for (i = i - 1; i >= 0; i--)
		printf("%X", a[i]);
}

void R(double Real, int s)
{
	int i, k;
	for (i = 0; i < EPS; i++) {
		Real *= s;
		k = (int) Real;
		printf("%X", k);
		Real -= k;
	}
}

int main()
{
	int s, Int;
	double a, Real;
	a = input();
	s = input_s();
	if (a<0)
	{
		a=-a;
		printf("-");
	}
	Int = (int) a;
	Real = a - Int;
	I(Int, s);
	printf(",");
	R(Real, s);
	printf("\n");
	return 0;
}








