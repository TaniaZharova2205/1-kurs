//реализвции конструкторов и методов dlink.h

#include <stdio.h>
#include "dlink.h"

DLink::DLink()//инициализация в ноль
{
	next = prev = NULL;
}

DLink* DLink::incr() //возвращает указатель на следующий элемент списка
{
	return (next);
}

DLink* DLink::decr() //возвращает указатель на предыдущий элемент списка
{
	return (prev); 
}

DLink* DLink::append(DLink* p)//для склеивания двух списков или добавления нового элемента p перед головой списка вызывающего эту функцию
{
	p->next = this;//указатель next элемента p станет указывать на голову списка
	prev = p;//указатель prev головы вместо NULL будет занесен указатель на объект p
	return (p);//возвращает указатель на объект p
}

void DLink::excluse()// удаляет текущие объекты из списка
{
	if (next != NULL)//если удаляемый объект не является хвостом списка
		next -> prev = prev;//связь для идущего за ним элемента
	if (prev != NULL)//если эелемент не является головой списка
		prev -> next = next;
	return;
}

DLink* DLink::after(DLink* p) //вставляет элемент р после текущего элемента
{
	p->next = next;
	p->prev = this;
	if (next != NULL)//не явл хвостом списка
		next->prev = p;//prev следующего элемента на объект р
	next = p;
	return (p->next);
}	

DLink *DLink::before(DLink *p)
{
	p->next = this;
	p->prev = prev;
	if (prev != NULL)
		prev->next = p;
	prev = p;
	return (p->prev);
}

DLink *DLink::toHead() //находит и возвращет указатель на голову списка
{
	DLink *p = this, *q = NULL;

	while(p != NULL) //пока не ноль смещаются в голову списку
	{
		q = p;//q указывает на голову 
		p = p->prev;
	}
	return (q);//возвращет значение головы
}

DLink *DLink::toHead(int n)//перемещние на n позиций по направлению его головы 
{
	int i = 0;
	DLink *p = this, *q = this;

	while(p != NULL)
	{
		q = p; 
		if (i == n)
			break;
		p = p->prev;
		i++;
	}
	return (q);
}

DLink *DLink::toTail()
{
	DLink *p = this, *q = NULL;

	while(p != NULL)
	{
		q = p;
		p = p->next;
	}
	
	return (q);
}

DLink *DLink::toTail(int n) 
{
	int i = 0;
	DLink *p = this, *q = this;

	while(p != NULL)
	{
		q = p; 
		if (i == n)
			break;
		p = p->next;
		i++;
	}
	return (q);
}
