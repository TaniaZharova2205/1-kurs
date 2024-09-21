%{
#include <stdio.h>
int integ = 0;//целая часть
int corpart = 1;//числитель 
int denominator = 1;//знаменатель
int yyerror(char const*);//ошибка
int yylex(void);
%}
%token SIGN WHOLE_PART FRACTION_PART NL WORD
%%
input: {printf("enter a fraction\n");}
 	| input frac NL 
	| input error NL {yyerrok; yyclearin;}
 	;
frac:    NL {printf("No one digit line\n");} 
	| WORD NL {printf("No one digit line\n");}
	| sign WHOLE_PART FRACTION_PART  { 
 				 	   corpart = $2 % $3;
 					   integ = $2 / $3;
 				 	   denominator = $3;
 				 	   if (corpart == 0) printf("%d\n", integ);
 				 	   else
 				 	   printf("%d+%d/%d\n", integ, corpart, denominator);
					  }	 
 	;
sign: 
	| SIGN 
 	;
%%
int yyerror(char const* error) {
fprintf(stderr, "%s\n", error);
}
int main() {
 return yyparse();
} 
