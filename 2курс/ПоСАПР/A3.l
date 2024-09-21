%Start ZZ OZ ZO OO 
%{ 
#include <stdio.h> 
char* mas[] = {"Correct","Incorrect"}; 
%} 
%% 
<ZZ>0 BEGIN OZ; 
<OZ>0 BEGIN ZZ; 
<ZO>0 BEGIN OO; 
<OO>0 BEGIN ZO; 
<ZZ>1 BEGIN ZO; 
<ZO>1 BEGIN ZZ; 
<OZ>1 BEGIN OO; 
<OO>1 BEGIN OZ; 
0 BEGIN OZ; 
1 BEGIN ZO;  
<ZO>[^01] return 0; 
[^01] return 1; 
%% 
int main(int argc, char* argv[]) 
{ 
int ret = yylex(); 
printf("%s\n",mas[ret]); 
return(ret); 
} 
