#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define BUFLEN 1024

struct stack
{
    char *data;
    struct stack *next;
} *start = NULL; 

void is(int i) // проверка, хватает ли памяти в буфере
{
    if (i > BUFLEN)
    {
        printf("The word is too long.\n");
        exit(1);
    }
}

void output(void) // вывод
{
	printf("\nOutput:\n");
    struct stack *p;

    putchar('\n');
    for (p = start; p != NULL; p = p->next)
    {
        printf("%s", p->data);
        putchar('\n');
    }

}

void st(void)
{
    int i = 0, j;
    char c, *p_w, buf[BUFLEN];
    struct stack *p;
    while ((c = getchar()) != EOF)
    {
        if (isalpha(c)) // игнорирование символов не букв
        {
            if (i > BUFLEN)
                printf("Not enough space in buffer\n");
            buf[i] = c;
            i++;
            is(i);
        }
        if (c == ' ' || c == '\t' || c == '\n')
        {
            buf[i] = '\0';
            if ((p_w = (char *)malloc((i + 1) * sizeof(char))) == NULL) // выделение памяти под получившееся слово
            {
                printf("Not enough space for new word\n");
                exit(1);
            }
            for (j = 0; j <= i; j++) //заполнение строки словом
                p_w[j] = buf[j];

            if ((p = (struct stack *)malloc(sizeof(struct stack))) == NULL)
            {
                printf("Error\n");
                exit(1);
            }

            p->next = start;
            start = p;
            p->data = p_w;
            i = 0;
        }
    }
}


int main()
{
    struct stack *p = NULL;
    printf("Input your text\n\n");

    st();
    output();
   
    return 0;
}
