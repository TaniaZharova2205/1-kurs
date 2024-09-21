#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENBUF 1024
#define NUMSTR 128

void output(char *result[]) // вывод
{
    int i = 0;
    putchar('\n');
    while (result[i] != NULL)
    {
        printf("%s", result[i]);
        i++;
        putchar('\n');
    }
}

int main()
{
    char *p, c, buf[LENBUF], *result[NUMSTR];
    int i = 0, j, k = 0;
    printf("Input your text\n");
    while ((c = getchar()) != EOF)
    {
        if (c != ' ' && c != '\t') // игнорирование символов табуляции и пробела
        {
            if (c != '\n') // чтение строки
            {
                buf[i] = c;
                i++;
            }
            else
            {
                /*for (int n = 0; n < i; n++)
                    printf("%c", buf[n]);*/
                buf[i] = '\0';
		if ((p = (char *)malloc((i + 1) * sizeof(char))) == NULL) // выделение памяти под получившуюся строку
                {
                    printf("Not enough space for new string\n");
                    exit(1);
                }
                for (j = 0; j <= i; j++) //заполнение строки p
                    p[j] = buf[j];

                result[k] = p;
                k++;
                i = 0;
            }
        }
    }

    result[k] = NULL;
    output(result);
    for (j = 0; j < i; j++)
        free(result[j]);

    return 0;
}
