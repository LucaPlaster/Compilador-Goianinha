%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goianinha.tab.h"

extern int yylineno;
int linha_inicio_comentario = 0;
char buffer_string[1024];
%}

%x ESTADO_COMENTARIO
%x ESTADO_STRING

%%

"programa"          { return PROGRAMA; }
"int"               { return TK_INT; }
"car"               { return TK_CAR; }
"retorne"           { return RETORNE; }
"leia"              { return LEIA; }
"escreva"           { return ESCREVA; }
"novalinha"         { return NOVALINHA; }
"se"                { return SE; }
"entao"             { return ENTAO; }
"senao"             { return SENAO; }
"enquanto"          { return ENQUANTO; }
"execute"           { return EXECUTE; }
"ou"                { return OU; }
"e"                 { return E; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.texto = strdup(yytext); return ID; }
[0-9]+              { yylval.texto = strdup(yytext); return INTCONST; }
'[^']'              { yylval.texto = strdup(yytext); return CARCONST; }

"=="                { return IGUAL; }
"!="                { return DIFERENTE; }
"<="                { return MENORIGUAL; }
">="                { return MAIORIGUAL; }
"="                 { return ATRIBUICAO; }
"<"                 { return MENOR; }
">"                 { return MAIOR; }
";"                 { return PONTOVIRGULA; }
","                 { return VIRGULA; }
"("                 { return ABREPAR; }
")"                 { return FECHAPAR; }
"{"                 { return ABRECHAVE; }
"}"                 { return FECHACHAVE; }
"+"                 { return MAIS; }
"-"                 { return MENOS; }
"*"                 { return MULT; }
"/"                 { return DIV; }
"!"                 { return '!'; }

[ \t\r]+            { }
\n                  { yylineno++; }

"/*"                { BEGIN(ESTADO_COMENTARIO); linha_inicio_comentario = yylineno; }

<ESTADO_COMENTARIO>"*/"       { BEGIN(INITIAL); }
<ESTADO_COMENTARIO>\n         { yylineno++; }
<ESTADO_COMENTARIO>.          { }
<ESTADO_COMENTARIO><<EOF>>    { 
    printf("ERRO: COMENTARIO NAO TERMINA %d\n", linha_inicio_comentario); 
    exit(1); 
}

"\"" {
    BEGIN(ESTADO_STRING);
    linha_inicio_comentario = yylineno;
    buffer_string[0] = '\0';
}

<ESTADO_STRING>[^\"\n\\]+  { strcat(buffer_string, yytext); }
<ESTADO_STRING>\\n         { strcat(buffer_string, "\n"); }
<ESTADO_STRING>\\t         { strcat(buffer_string, "\t"); }
<ESTADO_STRING>\\\"        { strcat(buffer_string, "\""); }

<ESTADO_STRING>"\"" {
    BEGIN(INITIAL);
    yylval.texto = strdup(buffer_string);
    return STRINGCONST;
}

<ESTADO_STRING>\n {
    printf("ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", linha_inicio_comentario);
    exit(1);
}
<ESTADO_STRING><<EOF>> {
    printf("ERRO: STRING NAO TERMINADA %d\n", linha_inicio_comentario);
    exit(1);
}

.                   { 
    printf("ERRO: CARACTERE INVALIDO '%s' %d\n", yytext, yylineno); 
    exit(1);
}

%%

int yywrap(void) {
    return 1;
}
