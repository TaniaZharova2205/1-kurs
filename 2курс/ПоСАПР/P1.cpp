#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Car
{
private:
    
	int oil;//кол-во бензина в машине
	int GSN;//номер заправки
	int consumption;//максимальный расход топлива
public:
    
	Car(int x, int y, int z): oil(x), GSN(y), consumption(z) {};
	int out_Oil() {return oil;};
	int out_GSN() {return GSN;};
	int out_Consumption() {return consumption;};
	
	void expenditure(int k) 
	{
		oil -= k;//узнаем можем ли мы поехать на эту заправку
	};
	
	void refill() 
	{
		oil = consumption;// возвращаем исходное значение длины
	};
	
	void in_GSL() 
	{
		GSN++ ;// 2
	};

	void output() 
	{
		printf("%d ", GSN-1);
	};
	~Car() {};

};

void Station(Car K, char** S, int L) 
{
	int i;
	for (i = 1; i < L; i++) 
	{
		if (atoi(S[K.out_GSN()]) > K.out_Oil()) 
		{
			K.output();
			K.refill();
		}
		K.expenditure(atoi(S[K.out_GSN()]));
		K.in_GSL();
	}
}

int main(int argc, char* argv[]) 
{
	if (argc < 2) 
	{
		fprintf(stderr, "Error: Invalid number of parameters entered\n");
		return 0;
	}
	int Oil, i;
	cin >> Oil;
	for (i = 1; i < argc; i++) 
	{
		if (atoi(argv[i]) > Oil) 
		{
			printf("Машина не доедет до пункта назначения, так как не преодолеет расстояние между АЗС\n");
			return 0;
		}
	}
	Car K(Oil, 1, Oil);
	Station(K, argv, argc);
	printf("\n");
}
