%{
#include<stdio.h>
%}

%%

\/\/.* ;
\/\*(.*\n)*.*\*\/ ;
%%

main()
{
yyin=fopen("l3.c","r");
yylex();
}

int yywrap()
{
return 1;
}
