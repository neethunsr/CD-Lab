%{
int i;
%}

%%
[0-9]+ {i = atoi(yytext);

if(i%2==0)
printf("Input Number is Even");

else
printf("Input Number is Odd");
};
%%
int yywrap(){}
int main()
{
yylex();
return 1;
}
