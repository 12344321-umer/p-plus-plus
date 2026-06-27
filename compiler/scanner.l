%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

int line_count = 1;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*
INT         {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+
SCIENTIFIC  {DIGIT}+("."{DIGIT}+)?[eE][+-]?{DIGIT}+
STRING      \"([^\"\\\n]|\\.)*\"

%%

[ \t]                               ;
\n                                  { line_count++; }
"/*"([^*]|\*+[^*/])*\*+"/"         ;
"//"[^\n]*                          ;

"sceneOnHa"     { return SCENEONHA;     }
"sceneOffHa"    { return SCENEOFFHA;    }
"lowkey"        { return LOWKEY;        }
"warnaBro"      { return WARNABRO;      }
"phirBro"       { return PHIRBRO;       }
"chalBro"       { return CHALBRO;       }
"ghosted"       { return GHOSTED;       }
"missKara"      { return MISSKARA;      }
"wapas"         { return WAPAS;         }
"spillTea"      { return SPILLTEA;      }
"numYesKarao"   { return NUMYESKARAO;   }
"floatYesKarao" { return FLOATYESKARAO; }
"noCap"         { return NOCAP;         }
"cap"           { return CAP;           }
"basYar"        { return BASYAR;        }

"<-"            { return ASSIGN;     }
"==?"           { return EQ;         }
"^+"            { return PLUS;       }
"<="            { return LTE;        }
">="            { return GTE;        }
"<"             { return LT;         }
">"             { return GT;         }

"!!"            { return TERMINATOR; }
":::"           { return SEPARATOR;  }
"("             { return LPAREN;     }
")"             { return RPAREN;     }

{SCIENTIFIC}    {
                    yylval.float_val = atof(yytext);
                    return SCIENTIFIC_NUM;
                }

{FLOAT}         {
                    yylval.float_val = atof(yytext);
                    return FLOAT_NUM;
                }

{INT}           {
                    yylval.int_val = atoi(yytext);
                    return INT_NUM;
                }

{STRING}        {
                    yylval.str_val = strdup(yytext);
                    return STRING_LIT;
                }

{ID}            {
                    yylval.str_val = strdup(yytext);
                    return ID;
                }

.               {
                    fprintf(stderr,
                        "Lexer Error [line %d]: invalid token '%s'\n",
                        line_count, yytext);
                }

%%

int yywrap() { return 1; }