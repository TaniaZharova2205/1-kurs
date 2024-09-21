%{  
#include <stdio.h>  
int yylex();  
void yyerror(char const *);  
%}  
 
%token ONE ZERO;  

%%  
 
input: {printf("Input bin set\n");}  
| input line;  
 
line: '\n' {printf("Empty line\n");}  
| EXP '\n' {printf("Correct\n");}  
| error '\n' {yyerrok;};  
 
EXP: COR;  
COR: ZERO ONE | ZERO COR ONE;  
%%  
int yylex()  
{  
char c;  
c=getchar();  
if(c=='1')  
return ONE;  
if(c=='0')  
return ZERO;  
if(c==EOF)  
return 0;  
return c;  
}  
 
void yyerror(char const *str)  
{  
fprintf(stderr, "%s\n", str);  
}  
 
int main()  
{  
 
return(yyparse());  
}
