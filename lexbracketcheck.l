%{
int open=0, flag=1;
%}

%%
\( {open++;}
\) {
if(open>0)
    open--;
else
    flag=0;
}
\n return 0;
%%

int yywrap() {
    return 0;
}

int main() {
    yylex();
    if(flag && open==0)
        printf("\nBrackets are matching\n");
    else
        printf("\nBrackets mismatch\n");
    return 0;
}