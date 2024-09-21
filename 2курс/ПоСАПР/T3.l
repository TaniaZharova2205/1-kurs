DIGIT [0-9]
%{
#include <stdio.h>
#include "y.tab.h"
extern int yylval;
%}
%%
[-+] { yylval = yytext[0]; return SIGN; }
{DIGIT}+ { yylval = atoi(yytext); return WHOLE_PART; }
\/[1-9]{DIGIT}* { yylval = atoi(++yytext); return FRACTION_PART; }
\n { return NL; }
([a-z]*[A-Z]*)+ { return WORD; };
