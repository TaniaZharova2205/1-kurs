#include <math.h>
#include <iostream>
#include <iomanip> 
using namespace std;

class Point2
{
	private:
		float x, y;
		Point2(float _x, float _y) : x(_x), y(_y) { };
	public:
		float getx() { return x; };
		float gety() { return y; };
		static Point2 Polar(float, float, float, float);
		Point2() { x = y = 0.0; };
};

inline Point2 Point2::Polar(float R, float F, float x, float y) // переводим полярные координаты в декартовые
{
	Point2 p(R*cos(F)+x, R*sin(F)+y);
	return p;
}
int main(int argc, char *argv[])
{
	float edge, angle, pi, radius, cntx, cnty;
	pi = acos(-1.0);
	int i = 0;
	Point2 vertex[4];

	if (argc < 5) // проверка на количество аргументов
	{
		cout << "NEED MORE ARGUMENTS" << endl;
		return (-1);
	} 
	edge = atof(argv[1])*sqrt(2); // диагональ
	angle = atof(argv[2]) / 180 * pi;// угол отклонения
	cntx = atof(argv[3]);//центр смещения
	cnty = atof(argv[4]);
	radius = edge/2; //радиус
	cout << "Центр в точке:" << '(' << cntx << ';' << cnty << ')'<< endl << endl;
	
	if (!(cntx<=0 && cnty>=0))
	{
		cout << "Incorrect offset coordinates" << endl;
		return (-2);
	}
	
	while (i < 4) // отклонение по вершинам
    {
		vertex[i] = Point2::Polar(radius, angle, cntx, cnty);
		angle += (pi/2);
		i++;
	}
	do
	{
		--i;
		//cout << '(' << setprecision(2) << vertex[i].getx() << " ; " << setprecision(2) << vertex[i].gety() << ')' << endl;
		printf ("(%.2f ; %.2f)\n", vertex[i].getx(), vertex[i].gety());
	} while(i > 0);

	return 0;
}
