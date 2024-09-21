#include <stdio.h>
#include <iostream>
using namespace std;

class Line;
class Dot
{
	friend class Line;
	friend istream& operator>>(istream&, Dot&);
	private:
		float x;
		float y;
	public:
		//Dot(float xx=0.0, float yy = 0.0) : x(xx), y(yy) {};//список инициализации
    Dot(){x=0.0; y=0.0;}
};


class Line
{
	private:
		Dot p1;
		Dot p2;
	public:
		Line(Dot& p, Dot& q) : p1(p), p2(q) {};//список инициализации
    //Line(){p1=p;p2=q;}
		void print();
};

void Line::print()
{
	float x;
	float t;
	int t1, t2;
	if (p1.y>p2.y) //меняем местами точки, если первая координата выше второй
	{
		t = p1.y;
		p1.y = p2.y;
		p2.y = t;

		t = p1.x;
		p1.x = p2.x;
		p2.x = t;
	}

	if ((t1 = (float)((int)p1.y )) != p1.y )// если начальный Y не целый, то начинаем с целого Y+1
		t1++;
	t2 = (int)p2.y;
	for (int i = t1; i<=t2; i++)//перебор целых Y из диапазона
	{
		x = ((i - p1.y)*(p2.x-p1.x))/(p2.y-p1.y)+p1.x; //вычисление X
		if ((float)((int) x ) == x)//если получившееся X целое, то выводим
			cout<<x<<";"<<i<<endl;
	}

	return;
}

istream& operator>>(istream& input, Dot& p)
{
	char semicolon=';';
	input >> p.x >> semicolon >> p.y;;
	return(input);
}

int main()
{
	Dot d1,d2;
	cout << "Input xa;ya xb;yb or exit" <<endl;
	while(cin >> d1 >> d2)
	{
		Line l(d1,d2);
		l.print();
	}
}
