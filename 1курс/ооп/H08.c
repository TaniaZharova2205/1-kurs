#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long unll;

unll f(unsigned char);
void printbin(long long);
int errmes(void);

int main(int argc, char *argv[])
{
    long long result;
    unsigned char n;

    if (argc != 2) 
	return errmes();
    n = (unsigned char)atoi(argv[1]);
    if (n < 2 || ((2*n-1) > (sizeof(long long)*8))) 
    	return errmes();
    result = f(n);
    fprintf(stdout, "В 2 системе счисления: ");
    printbin(result);
    fputc('\n', stdout); 
    fprintf(stdout, "В 8 системе счисления: %llo\n", result);
    fprintf(stdout, "В 16 системе счисления: %llX\n", result);
    return 0;
}

//выичсление значения выражения 
unll f(unsigned char n)
{
    return ((long long)1 << n) * ((1 << (n - 1)) - 1);
}
// в двоичную систему счисления
void printbin(long long val)
{
    int flag;
    unll mask = 1;
    flag = 0;
    mask <<= sizeof(unll) * 8 - 1;
    while (mask != 0)
    {
        if (val & mask)
        {
            flag = 1;
            fputc('1', stdout);
        }
        else
            if (flag) 
		fputc('0', stdout);
        mask >>= 1;
    }
    return;
}
// проверка на ввод
int errmes(void)
{
    fprintf(stderr, "Введите число меньше %ld и больше 1\n ", (sizeof(long long) * 8) / 2);
    return -1;
}
