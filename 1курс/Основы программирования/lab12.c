#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIM " \t\n"

typedef struct NODE 
{
    char * word;
    size_t kol;
    struct NODE * next;
} node_t;
 
int push_word(node_t ** pList, const char * word)//кол-во одинаковых слов
{
    if ( ! *pList )
    {
        *pList = malloc(sizeof(node_t));
        (*pList)->word = malloc(strlen(word) + 1); 
        strcpy((*pList)->word, word);
        (*pList)->kol = 1;
        (*pList)->next = NULL;
        return 0;
    }
    else 
    	if ( ! strcmp((*pList)->word, word) ) 
    	{
        	(*pList)->kol += 1;
       		return 0;
    	}
    	else
        	return push_word(&((*pList)->next), word);
}
 
void dump_list(const node_t * list,FILE * output) //вывод слова и его кол-во заходов
{
    while ( list ) 
    {
        fprintf(output,"%s - %ld\n", list->word, list->kol);
        list = list->next;
    }
}
 
void del_list(node_t ** pList) //освобождение памяти и вход следующего слова
{
    while ( *pList ) 
    {
        node_t * next = (*pList)->next;
        free((*pList)->word);
        free(*pList);
        *pList = next;
    }
}
 
int main(int argc, char *argv[]) 
{
    char buf[BUFSIZ];
	if (argc != 2)
	{
		printf("Вы не ввели файл\n");
		return 1;
	}
    FILE *output=fopen(argv[1],"w");
    while (printf("String: ") && fgets(buf, BUFSIZ, stdin) && *buf != '\n' ) 
    {
        char * ptr;
        node_t * list;
        
        for ( list = NULL, ptr = strtok(buf, DELIM); ptr; ptr = strtok(NULL, DELIM) ) 
        {
            if ( push_word(&list, ptr) ) 
            {
                fprintf(stderr, "Memory error!\n");
                exit(1);
            }
        }
        
        dump_list(list,output);
        fclose(output);
        del_list(&list);
    }
    
    exit(0);
}
