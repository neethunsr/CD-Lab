%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
    
extern int yylex();
    
void yyerror(char *msg);
   
int is_pal, i, j;
%}
    
%union {
char* f;
}
    
%token <f> STR
%type <f> E
    
%%
    
S : E {
is_pal = 1;
for (i = 0, j = strlen($1) - 1; i < j; i++, j--) {
if ($1[i] != $1[j]) {
is_pal = 0;
break;
}
}
printf("%s is %s\n", $1, is_pal ? 
"Palindrome" : "not Palindrome");
}
;
    
    
E : STR { $$ = $1; }
;
    
%%
    
void yyerror(char *msg) {
fprintf(stderr, "from here : %s\n", msg);
exit(1);
}
    
void main() {
yyparse();
}
