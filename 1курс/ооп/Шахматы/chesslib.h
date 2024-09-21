#ifndef CHESSLIB
#define CHESSLIB
#include "chessman.h"

class Knight : virtual public Figure
{
	public:
		Knight(char*p):Figure(p) {};
		Knight() {};
		char isa() {return 'K';};
		int attack(char*);
};

class Queen : virtual public Figure
{
	public:
		Queen(char*p):Figure(p) {};
		Queen() {};
		char isa() {return 'Q';};
		int attack(char*);
};

class Amazon : public Knight, public Queen
{
	public:
		Amazon(char*p):Figure(p) {};
		Amazon() {};
		char isa() {return 'A';};
		int attack(char*);
};
#endif
