%{
	#include <stdio.h>
	#include <stdlib.h>

	int id = 0, dig = 0, key = 0, op = 0;
%}
%token DIGIT ID KEY OP

%%
input:
DIGIT input { dig++; }
| ID input { id++; }
| KEY input { key++; }
| OP input {op++;}
| DIGIT { dig++; }
| ID { id++; }
| KEY { key++; }
| OP { op++;}
;
%%

#include <stdio.h>
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void main()  {
	yyin = stdin;
	do {
		yyparse();
	} while (!feof(yyin));
	printf("%-20s: %d\n", "identifiers", id);
	printf("%-20s: %d\n", "numbers", dig);
	printf("%-20s: %d\n", "keywords", key);
	printf("%-20s: %d\n", "operators", op);
}

int yyerror() {
	printf("Error\n");
}
