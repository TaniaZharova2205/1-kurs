#include <stdio.h>

int input()
{
	int a;
	while((scanf("%d", &a) == 0) || (a < 1) || (a > 100)) 
	{
		printf("повторите ввод а\n");
		while(getchar() != '\n');
	}
	return a;
}

void F(int a)
{	
	if ((a < 20) && (a > 10))
		printf("лет\n");
	else
	{
		switch (a % 10)
		{
 			case 1: 
 				printf("год\n");
 			 	break;
 			case 2:
 			case 3:
 			case 4: 
 				printf("года\n");
 			 	break;
 			default: 
 				printf("лет\n");
 			 	break;
 		}
 	
 	}
}

void M(int a)
{
	printf("Ваш возраст %d ", a);
	F(a);
	
	if (a < 18) 
	{
		printf("Вам до совершеннолетия %d ", 18 - a);
		F(18 - a);
	}
	else 
	{	if (a == 18)
			printf("Вы совершеннолетний\n");
		else 
		{
			printf("Вы совершеннолетний %d ", a - 18);
			F(a - 18);
		}
	}
	if (a < 60)
	{
		printf("Вам до пенсии %d ", 60 - a);
		F(60 - a);
	}
	else
	{	if (a == 60)
			printf("Вы на пенсии\n");
		else 
		{
			printf("Вы на пенсии %d ", a - 60);
			F(a - 60);
		}
	}
}

int main()
{
	int a;
	a = input();
	M(a);
	
	return 0;
}

