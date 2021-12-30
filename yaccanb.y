%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror();
int flag=0;
%}
%%
start : string '\n' {printf("Valid string\n"); return 0;}
string : 'a' string 'b'{flag=1;}
|
;
%%
int main()
{
yyparse();
return 0;
}
void yyerror() {
printf("Invalid string\n");
exit(1);
}