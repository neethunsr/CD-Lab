%{
	#include <stdio.h>
	#include "identify.h"

	extern int yylval;
%}

%%
[ \t];
[+|-|*|/|=|<|>] {
	printf("%-20s - %s\n", yytext, "operator");
	return OP;
}
[0-9]+ {
	printf("%-20s - %s\n", yytext, "number");
	return DIGIT;
}
int|char|bool|float|void|for|do|while|if|else|return|void {
	printf("%-20s - %s\n", yytext, "keyword");
	return KEY;
}
[a-zA-Z0-9]+ {
	printf("%-20s - %s\n", yytext, "identifier");
	return ID;
}
. ;
%%
