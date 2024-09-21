#include <iostream>
#include <stdlib.h>
using namespace std;

const char* s = "qwrtpsdfghjklzxcvbnm";
class Alpha
{
	private:
    	unsigned bin;
	public:
    	Alpha() { bin = 66043630; };
    	Alpha(char*);
    	operator char* ();
    	int pop(unsigned);
    	int operator & (Alpha&);
    	int operator()(Alpha&, Alpha&);
};

Alpha::Alpha(char* s)
{
    bin = 0;
    while (*s)
    {
        bin |= 1 << (tolower(*s) - 'a');
        s++;
    }
}

Alpha::operator char* ()
{
    static char s[32];
    unsigned w = bin;
    int i = 0, j = 0;
    while (w > 0)
    {
        if (w & 1)
            s[j++] = 'a' + i;
        i++;
        w  >>= 1;
    }
    s[j] = 0;
    return s;
}

int Alpha::operator() (Alpha& x, Alpha& y)
{
	unsigned b = bin & (x & y);
    return pop(b);
}

int Alpha::operator & (Alpha& y)
{
    return bin ^ y.bin;
}

int Alpha::pop(unsigned b)
{
    int i = 0;
    while (b != 0)
    {
        b = b & (b - 1);
        i++;
    }
    return i;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect quantity of arguments" << endl;
        return -1;
    }
    Alpha A(argv[1]);
    Alpha B((char*)s);
    Alpha H;
    int d = H(A,B);
    cout << "H(" << (char*)A << "," << (char*)B << ")=" << d << endl;
    return 0;
}
