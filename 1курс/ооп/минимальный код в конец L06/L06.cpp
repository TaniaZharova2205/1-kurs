#include <stdio.h>
#include <stdlib.h>
#include "dlink.h"
using namespace std;

class SymLink : public DLink
{
private:
    unsigned char sym;
public:
    SymLink(unsigned char c) : DLink(), sym(c) {};
    SymLink* incr() {return((SymLink*) DLink::incr());};
    SymLink* decr() {return((SymLink*) DLink::decr());};
    int print();
    SymLink findMin(SymLink*);
    bool operator == (SymLink*);
    int moveBiggest(SymLink *tail, SymLink min);

    void deleteList();
};

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
    return(n-2);
}

SymLink SymLink::findMin(SymLink* tail) {
    SymLink *m=this->incr(), *mn;
    char min = m->sym;
    while (m!=tail) {
        if (m->sym<min) {
            min=m->sym;
        }
        m = m->incr();
    }
    return (SymLink(min));
}

bool SymLink::operator==(SymLink* s) {
    if (this->sym==s->sym) return true;
    else return false;
}
int SymLink::moveBiggest (SymLink* tail, SymLink min) {
    int pos=0, count=0;
    SymLink *q, *p, *m;
    q=p=this;
    m=tail->decr();                                             //Ищем последний элемент в списке
    while((p != NULL))
    {
        if (q==m) q=NULL; else                                  //Если мы дошли до элемента, который был последним, кладём в q NULL
            q = p->incr();
        if ( min==p ) {                                         //Если элемент среди минимальный
            p->excluse();                                       //Убираем его с того места, где он был
            tail->before(p);                                    //Вставляем его в конец
            printf("%*c", pos, '^');                    //Выводим под ним знак ^
            pos=0;                                              //Обнуляем сдвиг для следующего ^
            count++;
        }
        p = q;
        pos++;
    }
    return count;                                               //Вовзращаем количество минимальных
}

void SymLink::deleteList () {
    SymLink *p, *q;
    p=this->decr();
    while(p->decr() != NULL)
    {
        q = p->decr();
        p->excluse();
        delete p;
        p = q;
    }
}

int main()
{
    int count;
    int length=0;
    int ch;
    SymLink* head;
    SymLink* tail;
    SymLink *p, *q, *m, min('z');
    head = new SymLink('\n');
    tail = new SymLink('\n');
    tail ->before(head);
    while ((ch=getchar())!=EOF) {
        while (ch != '\n') {                                    //получаем очередную строку
            q = new SymLink(ch);
            tail->before(q);
            length++;
            ch=getchar();
        }
        min = head->findMin(tail);                              //ищем минимальный элемент
        count = head->moveBiggest(tail, min);                   //сортируем список и помечаем минимальные элементы
        head->print();                                          //выводим отсортированный спсиок
        printf("%*c", length - count + 1, '^');         	//выводим ^ под минимальным символом
        for (int i = 2; i <= count; i++) {                     //выводим ^ под всеми остальными минимальными символами, если такие есть
            printf("^");
        }
        tail->deleteList();                                     //очищаем список
        printf ("\n");
        length=0;
    }
    return 0;
}

