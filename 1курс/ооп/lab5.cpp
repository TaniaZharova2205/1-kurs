#include <stdlib.h>
#include <iostream>
using namespace std;


class Alpha // класс множества латинских букв
{
	private:
		unsigned bin; // бинарный код подмножества латинских букв
	public:
		Alpha () { bin=0; }; // конструктор по умолчанию
		Alpha (char*); // конструктор инициализации по стороке
		int operator, ( Alpha& ); // перегразка оператора &
		int operator () ( Alpha&, Alpha& ); // перегрузка оператора ( )
		int pop ( unsigned ); // быстрый подсчет единичных разрядов
		friend ostream& operator << (ostream&, Alpha& ); // перегрузка оператора <<
		operator char*(); // перегрузка оператора приведение типа
};


// конструктор множества букв по строке
Alpha::Alpha ( char* s )
{
	bin=0;
	while(*s)
	{
		bin |= (1 << (tolower(*s)-'a'));
		s++;
	}
}


// оператор вывода подмножеств букв
ostream& operator << (ostream& out, Alpha& z)
{
	unsigned bit=1;
	int i;
	for (i=0; i<26; i++)
	{
		if((z.bin & bit) > 0)
			out << (char)('a'+i);
		bit = bit << 1;
	}
	return out;
}

//оператор преобразования множества в строку
Alpha::operator char* ()
{
	static char s[32];
	unsigned b=bin;
	int i=0;
	int j=0;
	while(b>0)
	{
		if (b & 1)
			s[j++] = 'A' + i;
		i++;
		b >>= 1;
	}
	s[j] = 0;
	return (s);
}


// скалярное произведение
int Alpha::operator , (Alpha& y)
{
	
	return pop( bin & y.bin); // ^ - оператор побитового И
	// pop – функция быстрого подсчета ед. разрядов
}


// расстояние Хемминга
int Alpha::operator () (Alpha& x, Alpha& y)
{
	return pop( x.bin ^ y.bin ); // ^ - оператор побитового исключающего ИЛИ
	// pop – функция быстрого подсчета ед. разрядов
}


// быстрый подсчет единичных разрядов
int Alpha::pop(unsigned b) // в функцию передается беззнаковое число
{
	int i=0; // счетчик единичных разрядов
	while ( b != 0) // пока в числе имеются 1 разряды
	{
		b = b & ( b - 1); // число уменьшается на 1 и применяется &
		i++; // счетчик разрядов увеличивается на 1
	}
	return ( i ); // возврат числа единичных разрядов
}


//основная функция
int main (int argc,char* argv[])
{
	Alpha A(argv[1]); // буквы 1-го аргумента
	Alpha B(argv[2]); // буквы 2-го аргумента
	Alpha H; // пустой набор – интерфейсный объект
	// операции вычисления расстояния Хемминга
	int d = H(A , B); // вычисление расстояния Хемминга
	// =H.operator () (A, B);
	int s = (A , B); // вычисление скалярного произведения
	// =A.operator , ( B );
	cout << "H (" << A << ", " << B << " ) = " << d << "\n";
	// красным выделен перегруженный
	// в классе оператор <<
	cout << "(" << ( char* ) A; // красным выделен перегруженный
	cout << ", " << ( char* ) B; // в классе оператор приведения типа
	cout << " ) = " << s << "\n";
	return (0);
} 
