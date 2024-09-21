//основная функция

#include "dlink.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

class SymLink : public DLink
{
private:
	unsigned char sym;
public:
	SymLink(unsigned char c) : DLink(), sym(c) {};
	SymLink *incr() {return((SymLink *)DLink::incr());};
	SymLink *decr() {return((SymLink *)DLink::decr());};
	SymLink *seek(int);
	int print();
};

SymLink* SymLink::seek(int n)
{
	if (n>0)
		return ((SymLink *)DLink::toTail(n));
	if (n<0)
		return ((SymLink *)DLink::toHead(abs(n)));
	return (this);
	}

int SymLink::print()
{
	SymLink* p = this;
	SymLink* q;
	int n = 0;
	while(p != NULL)
	{
		putchar(p->sym);
		q = p->incr();
		p = q;
		n++;
	}
	return n;
}

int main(int argc, char** argv)
{
	unsigned seed = 0; 
	int count = 0; 
	int length;
	int ch;
	unsigned pos;
	int side;
	SymLink* watch[2];
	SymLink* head;
	SymLink* tail;
	SymLink *p,*q;
	DLink* (DLink::* insert[])(DLink*) = { &DLink::after, &DLink::before };
	if(argc>1)
		seed = atoi(argv[1]);
	watch[0] = head = new SymLink('\n');
	watch[1] = tail = new SymLink('\n');
	tail -> before(head);
	while((ch = getchar()) != '\n')
	{
		q = new SymLink(ch);
		tail -> before(q);
	}
	if((length = head->print()-1) < 2)
		count = length;
	srand(seed);
	while(count<length)
	{
		side = rand()%2;
		while((pos = rand()%length) == 0);
			printf("%*c\n",pos,'^');
		q = head->seek(pos);
		q->excluse();
		(watch[side]->*insert[side])(q);
		head->print();
		count++;
	}
	p = tail;
	while(p != NULL)
	{
		q=p->decr();
		p->excluse();
		delete p;
		p = q;
	}
	return(length+1);
}
