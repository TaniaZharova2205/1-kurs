#ifndef CHESSMAN
#define CHESSMAN
#include <iostream>

class Figure
{
	protected:
		char pos[2];//позиция на доске
	public:
		Figure(char*);//конструктор инициализации
		Figure(){};//конструктор по-умолчанию
		virtual int attack(char*)=0;//чистая виртуальная функция атаки
		virtual char isa()=0;//чистая виртуальная функция маркировки фигуры
		operator char*();//оператор приведения типа
		static int deskout(char*);//функция принадлежности позиции шахматному полю
		int danger();//функция печати шахматного поля с обозначением позиции атаки фигуры
		Figure& operator=(char*);//перегрузка оператора присваивания как функции хода
		int operator==(char*);//проверка расположения фигуры в проверяемой позиции
		int operator!=(char*);//проверка расположения фигуры вне проверяемой позиции
		friend std::ostream& operator<<(std::ostream&,Figure&);//перегрузка оператора вывода
		friend std::istream& operator>>(std::istream&,Figure&);//перегрузка оператора ввода
};
#endif
