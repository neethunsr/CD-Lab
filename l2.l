%{
int nlines,nwords,nchars;
%}

%%
\n {
nchars++;nlines++; 
}

[^ \n\t]+ {nwords++, nchars=nchars+yyleng;}
. {nchars++;}
%%
int yywrap(void)  
{
return 1;
}
int main(int argc, char*argv[]) 
{
yyin=fopen(argv[1],"r");
yylex();
printf("No. of Lines = %d\nNo. of Characters=%d\nNo. of Words=%d\n",nlines,nchars,nwords);

return 0;
} 
