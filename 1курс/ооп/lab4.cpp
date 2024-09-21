#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<cctype>
using namespace std;

class Alpha
{
private:
	unsigned int bin;
public:
	Alpha() { bin=0; };
	Alpha (char*);
	Alpha operator~();
	Alpha operator^(Alpha&);
	Alpha operator+(Alpha&);
	operator char*();
	friend ostream& operator << (ostream&, Alpha&);
};

Alpha::Alpha(char* s)
{
	bin = 0;
	while(*s)
	{
		bin |=(1<<( (tolower(*s)-'a')));
		s++;
	}
}

Alpha Alpha::operator^ (Alpha& y)
{
	Alpha z;
	z.bin = bin & y.bin;
	return(z);
} 

Alpha Alpha::operator + (Alpha& y)
{
	Alpha z;
	z.bin = bin | y.bin;
	return(z);
}

Alpha Alpha::operator~ ()
{
	Alpha q;
	q.bin=~this->bin;
	return Alpha(q);
}

ostream& operator<<(ostream& out, Alpha& z)
{
	unsigned bit = 1;
	int i;
	for (i = 0; i<26; i++)
	{
		if((z.bin & bit)>0)
			out<<(char)('a'+ i);
		bit = bit << 1;
	}
	return (out);
}

Alpha::operator char*()
{
	static char s[32];
	unsigned w=bin;
	int i=0, j=0;
	while(w>0)
	{
		if (w & 1)
			s[j++]='a'+i;
		i++;
		w = w >> 1;
	}
	s[j++] = '\n';
	s[j] = '\0';
	return(s);
}

int main(int argc, char* argv[])
{
	if (argc!=3)
	{
		puts("Usage: 2 arguments only");
		return(-1);
	}
	Alpha x(argv[1]);
	Alpha y(argv[2]);
	Alpha z;
	Alpha q;
	q = x^y;
	z = ~(x+y);
	cout<< "Пересечение введенных множеств: " << q <<endl;
	cout<<"Набор букв, которых нет ни в одном из множеств: "<< z <<endl; // cout«(char*)z;
	return(0);
}
