A ([01]*00+[01]*)
%%
[ \t]{A}/[ \t] puts(yytext+1);
^{A}/[ \t] puts(yytext);
[ \t]{A}$ puts(yytext+1);
^{A}$ puts(yytext);
. ;
