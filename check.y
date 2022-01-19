%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    char display[100];
    int yylex();
    void yyerror();
%}

%union {
    char *str; //Ptr to constant string (strings are malloc'd)
};
%token TYPE ID RECORD NUM SPACE
%%
    start : TYPE SPACE ID dec {return 0;}
    dec : '(' rest '\n' {printf("\nValid Function Declaration\n");}
    |typedec {printf("\nValid Type Declaration\n");}
    |RECORD '{' D '}'
    rest : TYPE SPACE ID arglist ')' ';'
    |')' ';'
    arglist : ',' TYPE SPACE ID
    | ;
    typedec : C ',' varlist ';'
    |';'
    varlist : ID C ',' varlist
    |ID C
    D : D TYPE C SPACE ID ';'
    |TYPE C SPACE ID ';'
    C : '[' NUM ']' C
    | ;
%%

int main() {
    yyparse();
    return 0;
}

void yyerror() {
    printf("\nDeclaration is not valid\n");
    exit(1);
}