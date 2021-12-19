%{
	#include <stdio.h>
	#include <stdbool.h>

	bool is_single_comment = false, is_comment = false;
%}
identifier [a-zA-Z][a-zA-Z0-9]*
%%
#.* {
	printf("%-20s - %s\n", yytext, "preprocessor directive");
}
int |
float |
char |
double |
while |
for |
struct |
typedef |
do |
if |
break |
continue |
void |
switch |
return |
else |
goto {
	printf("%-20s - %s\n", yytext, "keyword");
}
[\/\/] {
	is_comment = is_single_comment = true;
}
"/*" {
	is_comment = true;
}
"*/" {
	if (is_comment)
		is_comment = false;
}
[\n] {
	if (is_single_comment)
		is_comment = is_single_comment = false;
}
[ \t\r]+ {
	; // white space
}
[\{\}\,\;\:\[\]\(\)] {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "punctuator");
}
{identifier}(\[[0-9]*\])? {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "identifier");
}
\".*\" {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "string");
}
[0-9]*\.[0-9]+ {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "float");
}
[0-9]+ {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "integer");
}
= {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "assignment operator");
}
[\+\-\*\/] {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "arithmetic operator");
}
\! |
\&\& |
\|\| {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "logical operator");
}
\<= |
\>= |
\< |
== |
\> {
	if (!is_comment)
		printf("%-20s - %s\n", yytext, "relational operator");
}
%%

void main()	{
	yylex();
}

int yywrap() {
	return 1;
}
