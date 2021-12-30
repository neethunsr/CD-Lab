%{
int flag=1,a=0,b=0;
%}
%%
[^ab\n] {flag=0;}
a {
if(a!=0)
flag=0;
}
b {
if(a==1 || b==1)
flag=0;
else
{
a=1;b=1;
}
}
\n return 0;
%%
int yywrap(){
return 0;
}
int main()
{
yylex();
if(flag)
printf("Valid string\n");
else
printf("Invalid string\n");
return 0;
}