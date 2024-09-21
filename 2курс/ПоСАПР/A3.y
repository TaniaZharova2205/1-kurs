%{
#include <stdio.h>
int yylex();
int yyerror(char*);
char *mass[] = {"Correct", "Incorrect"};
%}

%%
state:
	|state Q1 '\n' { return 1; }
	|state Q2 '\n' { return 0; }
	|state Q3 '\n' { return 1; }
	|state Q4 '\n' { return 1; }
	|state error '\n' { yyerrok; }
	|state '\n'
;

Q1: '1' Q2
	| '0' Q3
;

Q2: '1'
	| '1' Q1
	| '0' Q4
;

Q3: '0'
	| '1' Q4
	| '0' Q1
;

Q4: '1' Q3
	| '0' Q2
;

%%
int main()
{
	int y = yyparse();
	printf("%s\n",mass[y]);
	return(y);
}

int yyerror(char *s)
{
	return 1;
}

int yylex()
{
	char c = getchar();
	while((c == '\n') || (c == '\t') || (c == ' '))
		return ('\n');
	return (c);
}
