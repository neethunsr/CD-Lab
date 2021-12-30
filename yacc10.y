%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror();
int flag=0;
%}
%%
start : string '\n' {printf("Valid string\n"); return 0;} ;
string : L string
| ;
L : A B;
A : '1' '0'
| '1' '1';
B : '0' '0' '0'
| '1' '1' '0';
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