#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void mas(int a[][8])
{
	int i,j;
	for(i = 0;i<8;i++)
	{
		for(j = i+1;j<8;j++)
		{
			a[i][j] = rand()%3;
			if (a[i][j]==2)
				a[i][j]=3;	
		}
		a[i][i] = 0;
	}
	for(i = 1;i<8;i++)
	{
		for(j = 0;j<i;j++)
		{
			if (a[j][i] == 0)
				a[i][j] = 3;
			if (a[j][i] == 1)
				a[i][j] = 1;
			if (a[j][i] == 3)
				a[i][j] = 0;
		}
	}
}
void vm(int a[][8])
{
	int i,j;
	for(i = 0;i<8;i++)
	{
		for(j = 0;j<8;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	}
	printf("\n");
}
int max(int *b)
{
	int ma = 0;
	for(int i = 0;i<8;i++)
	{
		if(b[i]>ma)
			ma = b[i];
	}
	printf("\n");
	return ma;
}
int kol(int *b,int ma)
{
	int k = 0;
	printf("Набравшие максимум:\n");
	for(int i = 0;i<8;i++)
	{
		if(b[i] == ma)
		{
			k+=1;
			printf(" Команда №%d\n",i+1);
		}
	}
	printf("\n");
	return k;
}
int main(void)
{
	int j , i , a[8][8] , k, ma, b[8], sum = 0;
	mas(a);
	vm(a);
	for(i = 0;i<8;i++)
	{
		for(j = 0;j<8;j++)
			sum+=a[i][j];
		b[i]=sum;
		printf("Сумма балов в %d команде:%d\n",i+1,b[i]);
		sum = 0;
	}
	ma = max(b);
	printf("Максимальная сумма:\n %d\n\n",ma);
	k = kol(b,ma);
	printf("Колличество команд,набравших максимум:\n %d\n",k);
}
