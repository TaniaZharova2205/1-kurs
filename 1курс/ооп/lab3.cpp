#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Magic
{
	private:
		unsigned** tab;
		int row;
		int col;
		int degree;
	public:
		Magic(int);
		~Magic();
		void print();
		void horse3();
		int reflect(int);
};

Magic::Magic(int n)//динамическое распределение памяти на двумерный масссив
{
	degree = n;//число столбцов и строк матрицы
	tab = new unsigned* [degree];//распределить память под 1-мерный массив указателей на беззнаковые целые размером degree по адресу tab используя оператор new
	for(row = 0; row<degree; row++)//под каждый указатель полученного массива указателей распределить одномерный массив беззнаковых целых из degree элементов, используя оператор new в цикле
		tab[row] = new unsigned [degree];
	for(row = 0; row<degree; row++)
		for(col=0; col< degree; col++)
			tab[row][col] = 0;
}

Magic::~Magic()//деструктор
{
	for(row=0; row < degree; row++)
		delete [](tab[row]);//освободить память, распределенную под degree одномерных массивов беззнаковых целых (из degree элементов каждый) по адресам от tab[0] до tab[degree-1]
	delete [](tab);//освободить память, распределенную под 1-мерный массив указателей на беззнаковые целые, состоящий из degree указателей по адресу tab:

}

void Magic::print()//вывод квадрата
{
	int degree2;
	int len=0;
	degree2 = (degree * degree);//самое большое число
/*	while(degree2>0)
	{
		degree2 /= 10;
		len++;
	}*/
	for(row = 0; row<degree; row++)
	{
		for(col=0; col< degree; col++)
			if (tab[row][col]<10)
				printf("0%d ", tab[row][col]);
			else
				printf("%d ", tab[row][col]);
		putchar('\n');
	}
	putchar('\n');
	return;
}

int Magic::reflect(int k)
{
	if(k<0)
		return(k+degree);
	if(k>(degree-1))
		return(k-degree);
	return(k); 
}

void Magic::horse3()
{
	int i, j, degree2=(degree*degree), z=1;
	row = (degree-2);//строки
	col = (degree / 2);//столбики
	tab[row][col] = z;
	while(z<degree2)
	{
		i=reflect(row+1);
		j=reflect(col+1);
		if(tab[i][j]>0)
		{
			i=reflect(row+2);
			j=reflect(col);	
		}
		row = i;
		col = j;
		++z;
		tab[row][col] = z;
	}
	return;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
		return(puts("Usage: magic degree"));
	int n = atoi(argv[1]);
	if((n%2)==0)
	{
		puts("Usage: magic 5 or 7, 11, 17, 19, 23, ...");
		return(n);
	}
	Magic mag(n);
	mag.horse3();
	mag.print();
	return(n);
}
