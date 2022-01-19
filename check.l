%{
#include "y.tab.h"
%}

%%
int|char|float|double {return TYPE;}
struct|union {return RECORD;}
[A-Za-z_][A-Za-z_0-9]* {return ID;}
[0-9]+ {return NUM;}
[ \t]+ {return SPACE;}
\n|. { return yytext[0]; }
%%