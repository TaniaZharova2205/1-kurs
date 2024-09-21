#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define x 6
#define y 8
void mas(int a[][y])//формирует массив а из рандомных чисел от -5 до 15
{
	int i,j;
	for(i = 0;i<x;i++)
	{
		for(j = 0;j<y;j++)
		{
			a[i][j] = rand()%21-5;
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void masb(int a[][y],int b[])//формирует массив b из суммы чисел в каждой строке массива а
{
	int i,j,sum=0;
	for(i = 0;i<x;i++)
	{
		for(j = 0;j<y;j++)
			sum+=a[i][j];
		b[i]=sum;
		sum = 0;
	}
}
int max(int b[])//ищет максимальное число в массиве b и возвращает индекс этого числа
{
	int ma = 0,maind;
	for(int i = 0;i<x;i++)
	{
		if(b[i]>ma)
		{
			ma = b[i];
			maind=i;
		}
	}
	printf("Максимальная сумма в %d строке:\n %d\n",maind+1,ma);
	return maind;
}
int min(int b[])//ищет минимальное число в массиве b и возвращает индекс этого числа
{
	int mi = 121, miind;
	for(int i = 0;i<x;i++)
	{
		if(b[i]<mi)
		{
			mi = b[i];
			miind=i;
		}
	}
	printf("Минимальная сумма в %d строке:\n %d\n\n",miind+1,mi);
	return miind;
}
void zam(int mi, int ma, int a[][y])//заменяет в массиве а строки с наименьшей и наибольшей суммами 
{
	int j,g;
	for (j=0;j<y;j++)
	{
		g=a[mi][j];
		a[mi][j]=a[ma][j];
		a[ma][j]=g;
	}
}
int main()
{
	int j , i , a[x][y] , ma, b[x], mi;
	mas(a);//формирует массив а из рандомных чисел от -5 до 15
	masb(a,b);//формирует массив b из суммы чисел в каждой строке массива а
	ma = max(b);//ищет максимальное число в массиве b ии возвращает индекс этого числа
	mi = min(b);//ищет минимальное число в массиве b ии возвращает индекс этого числа
	zam(mi,ma,a);//заменяет в массиве а строки с наименьшей и наибольшей суммами  
	for(i = 0;i<x;i++)//вывод измененного массива а
	{
		for(j = 0;j<y;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
}
