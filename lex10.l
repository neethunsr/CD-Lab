%{
#include "y.tab.h"
%}
%%
\n|. { return yytext[0]; }
%%