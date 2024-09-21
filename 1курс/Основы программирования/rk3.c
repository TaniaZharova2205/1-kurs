#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100 
#define N 3

typedef struct NODE
{
	int count;
	char* text;
	struct NODE* next;
} Node;

int is_sep(char); // проверяет является ли символ символом-разделителем
void push(Node**, char*, int); // обрабатывает введенное слово
void print1(Node*);
void print2(Node*); // выводит список
void razdel(Node**);
void delete_cell(Node**, Node*);

int main(int argc, char* argv[])
{
	char c, buff[SIZE];
	int i = 0;
	Node* list = NULL;

	if (argc != 2)
	{
		printf("ERROR Few arguments\n");
		exit(-1);
	}

	FILE *in_fd = fopen(argv[1], "r+");

	if (in_fd == NULL) 
	{
		printf("ERROR\n");
		exit(-1);
	}

	while ((c = fgetc(in_fd)) != EOF)
		if (!is_sep(c))
        	buff[i++] = c;
        else 
        	if (i > 0)
        	{
        		buff[i] = '\0';
        		push(&list, buff, i);
        		i = 0;
        	}
	print1(list);
	razdel(&list);
   	print2(list);
   	return 0;
}

int is_sep(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

void push(Node** lst, char* val, int length)
{
    Node* temp;
    if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
    {
        printf("Память закончилась\n");
        exit(-1);
    }
    temp->text = strdup(val);//дублируем строку
    temp->count = length;//кол-во букв в слове
    temp->next = *lst;//присваем указателю temp адрес предыдущего узла
    *lst = temp;//присваем указателю lst адрес нового узла
}

void print1(Node* lst)
{
	while (lst != NULL)
    {
        printf("%s, %d\n", lst->text, lst->count);
        lst = lst->next;
    }
    printf("\n");
}

void print2(Node* lst)
{
	while (lst != NULL)
	{
    	printf("%s\n", lst->text);
        free(lst->text);
        lst = lst->next;
    }
}

void razdel(Node** lst)
{
	Node* p = *lst;
	while (p != NULL)
	{
    	if (p->count < N)
        	delete_cell(lst, p);
        p = p->next;
    }
}

void delete_cell(Node **lst, Node *cell)
{
	Node *p = *lst;
	char a;
	if (p != cell)
	{
		while(p->next != cell)
        	p = p->next;
        p->next = cell->next;
    }
    else
       	*lst = (*lst)->next;
}


