%{
/**
 * Analisador Sintático para a Linguagem Goianinha
 * 
 * Este arquivo define a gramática da linguagem Goianinha e as ações semânticas
 * para construção da Árvore Sintática Abstrata (AST). É processado pelo Bison
 * para gerar o parser.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/arvore_sintatica.h"

struct NoArvore;

// Declarações de funções externas
extern int yylex();
extern int yylineno;
void yyerror(const char *s);

// Variável global que armazenará a raiz da AST
NoArvore* raiz_arvore_sintatica = NULL;
%}

/**
 * União que define os possíveis tipos de valores semânticos dos símbolos.
 */
%union {
    int valor_inteiro;
    char* texto;
    struct NoArvore* no;
}

/* ========== TOKENS (SÍMBOLOS TERMINAIS) ========== */

/* Palavras reservadas */
%token PROGRAMA TK_INT TK_CAR RETORNE LEIA ESCREVA NOVALINHA 
%token SE ENTAO SENAO ENQUANTO EXECUTE

/* Tokens com valor associado */
%token <texto> ID
%token <texto> STRINGCONST
%token <texto> CARCONST
%token <texto> INTCONST

/* Operadores */
%token MAIS MENOS MULT DIV 
%token IGUAL DIFERENTE MENOR MAIOR MAIORIGUAL MENORIGUAL ATRIBUICAO
%token OU E

/* Delimitadores */
%token ABREPAR FECHAPAR ABRECHAVE FECHACHAVE VIRGULA PONTOVIRGULA

/* ========== TIPOS DOS NÃO-TERMINAIS ========== */

%type <no> Programa DeclFuncVar DeclProg Tipo DeclVar DeclFunc 
%type <no> ListaParametros ListaParametrosCont Bloco ListaDeclVar 
%type <no> ListaComando Comando Expr OrExpr AndExpr EqExpr 
%type <no> DesigExpr AddExpr MulExpr UnExpr PrimExpr ListExpr

/* Símbolo inicial da gramática */
%start Programa

%%

/* ========== PROGRAMA PRINCIPAL ========== */

/**
 * Um programa em Goianinha consiste de:
 * - Declarações de funções e variáveis globais (opcional)
 * - Declaração do bloco principal (obrigatório)
 */
Programa: DeclFuncVar DeclProg
    {
        raiz_arvore_sintatica = construir_no_arvore(NO_PROGRAMA, yylineno, NULL, 0, 
                                                     TIPO_VAZIO, 2, $1, $2);
        $$ = raiz_arvore_sintatica;
    }
;

/* ========== DECLARAÇÕES DE FUNÇÕES E VARIÁVEIS GLOBAIS ========== */

/**
 * Pode haver múltiplas declarações de variáveis e funções antes do programa principal.
 * Cada declaração pode ser:
 * - Uma variável: Tipo id DeclVar;
 * - Uma função: Tipo id DeclFunc
 * - Vazio (epsilon)
 */
DeclFuncVar: Tipo ID DeclVar PONTOVIRGULA DeclFuncVar
    {
        // Cria nó para declaração de variável(is)
        NoArvore* no_atual = construir_no_arvore(NO_DECL_VAR, yylineno, $2, 0, 
                                                  $1->tipo_var, 1, $3);
        // Se houver mais declarações, cria uma lista
        $$ = $5 ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                       TIPO_DESCONHECIDO, 2, no_atual, $5) : no_atual;
    }
| Tipo ID DeclFunc DeclFuncVar
    {
        // Cria nó para declaração de função
        NoArvore* no_atual = construir_no_arvore(NO_FUNCAO, yylineno, $2, 0, 
                                                  $1->tipo_var, 1, $3);
        // Se houver mais declarações, cria uma lista
        $$ = $4 ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                       TIPO_DESCONHECIDO, 2, no_atual, $4) : no_atual;
    }
| %empty
    {
        $$ = NULL;  // Não há declarações
    }
;

/* ========== DECLARAÇÃO DO PROGRAMA PRINCIPAL ========== */

/**
 * O programa principal é identificado pela palavra-chave "programa"
 * seguida de um bloco.
 */
DeclProg: PROGRAMA Bloco
    {
        $$ = construir_no_arvore(NO_BLOCO, yylineno, strdup("programa"), 0, 
                                 TIPO_VAZIO, 1, $2);
    }
;

/* ========== TIPOS ========== */

/**
 * A linguagem Goianinha suporta dois tipos: int e car
 */
Tipo: TK_INT
    { 
        $$ = construir_no_arvore(NO_IDENTIFICADOR, yylineno, strdup("int"), 0, 
                                 TIPO_INTEIRO, 0); 
    }
| TK_CAR
    { 
        $$ = construir_no_arvore(NO_IDENTIFICADOR, yylineno, strdup("car"), 0, 
                                 TIPO_CARACTERE, 0); 
    }
;

/* ========== DECLARAÇÃO DE MÚLTIPLAS VARIÁVEIS ========== */

/**
 * Após o primeiro identificador, pode haver mais variáveis separadas por vírgula.
 * Exemplo: int x, y, z;
 */
DeclVar: VIRGULA ID DeclVar
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $2, 0, 
                                               TIPO_DESCONHECIDO, 0);
        $$ = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, $3);
    }
| %empty
    {
        $$ = NULL;  // Não há mais variáveis
    }
;

/* ========== DECLARAÇÃO DE FUNÇÃO ========== */

/**
 * Uma função é declarada com:
 * - Lista de parâmetros entre parênteses
 * - Bloco que contém o corpo da função
 */
DeclFunc: ABREPAR ListaParametros FECHAPAR Bloco
    {
        $$ = construir_no_arvore(NO_FUNCAO, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, $2, $4);
    }
;

/* ========== LISTA DE PARÂMETROS ========== */

/**
 * A lista de parâmetros pode estar vazia ou conter um ou mais parâmetros.
 */
ListaParametros: %empty
    { 
        $$ = NULL;  // Sem parâmetros
    }
| ListaParametrosCont
    { 
        $$ = $1; 
    }
;

/**
 * Lista não-vazia de parâmetros, separados por vírgula.
 */
ListaParametrosCont: Tipo ID
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $2, 0, 
                                               $1->tipo_var, 0);
        $$ = construir_no_arvore(NO_LISTA, yylineno, strdup("lista_params"), 0, 
                                 TIPO_DESCONHECIDO, 1, no_id);
    }
| Tipo ID VIRGULA ListaParametrosCont
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $2, 0, 
                                               $1->tipo_var, 0);
        $$ = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, $4);
    }
;

/* ========== BLOCO ========== */

/**
 * Um bloco contém:
 * - Declarações de variáveis locais (opcional)
 * - Lista de comandos (opcional)
 */
Bloco: ABRECHAVE ListaDeclVar ListaComando FECHACHAVE
    {
        $$ = construir_no_arvore(NO_BLOCO, yylineno, NULL, 0, 
                                 TIPO_VAZIO, 2, $2, $3);
    }
;

/* ========== LISTA DE DECLARAÇÕES DE VARIÁVEIS LOCAIS ========== */

/**
 * Dentro de um bloco, pode haver declarações de variáveis locais.
 */
ListaDeclVar: %empty
    { 
        $$ = NULL;  // Sem declarações locais
    }
| Tipo ID DeclVar PONTOVIRGULA ListaDeclVar
    {
        NoArvore* no_decl = construir_no_arvore(NO_DECL_VAR, yylineno, $2, 0, 
                                                 $1->tipo_var, 1, $3);
        $$ = $5 ? construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                      TIPO_DESCONHECIDO, 2, no_decl, $5) : no_decl;
    }
;

/* ========== LISTA DE COMANDOS ========== */

/**
 * Um bloco pode conter uma sequência de comandos.
 */
ListaComando: Comando
    {
        $$ = $1;
    }
| Comando ListaComando
    {
        $$ = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $2);
    }
;

/* ========== COMANDOS ========== */

/**
 * Definição de todos os tipos de comandos suportados pela linguagem.
 */
Comando: PONTOVIRGULA
    {
        // Comando vazio
        $$ = NULL;
    }
| Expr PONTOVIRGULA
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("expr"), 0, 
                                 TIPO_VAZIO, 1, $1);
    }
| RETORNE Expr PONTOVIRGULA
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("retorne"), 0, 
                                 TIPO_VAZIO, 1, $2);
    }
| LEIA ID PONTOVIRGULA
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $2, 0, 
                                               TIPO_DESCONHECIDO, 0);
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("leia"), 0, 
                                 TIPO_VAZIO, 1, no_id);
    }
| ESCREVA Expr PONTOVIRGULA
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("escreva"), 0, 
                                 TIPO_VAZIO, 1, $2);
    }
| ESCREVA STRINGCONST PONTOVIRGULA
    {
        NoArvore* no_string = construir_no_arvore(NO_CONSTANTE, yylineno, $2, 0, 
                                                   TIPO_CARACTERE, 0);
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("escreva_string"), 0, 
                                 TIPO_VAZIO, 1, no_string);
    }
| NOVALINHA PONTOVIRGULA
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("novalinha"), 0, 
                                 TIPO_VAZIO, 0);
    }
| SE ABREPAR Expr FECHAPAR ENTAO Comando
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("se"), 0, 
                                 TIPO_VAZIO, 2, $3, $6);
    }
| SE ABREPAR Expr FECHAPAR ENTAO Comando SENAO Comando
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("se_senao"), 0, 
                                 TIPO_VAZIO, 3, $3, $6, $8);
    }
| ENQUANTO ABREPAR Expr FECHAPAR EXECUTE Comando
    {
        $$ = construir_no_arvore(NO_COMANDO, yylineno, strdup("enquanto"), 0, 
                                 TIPO_VAZIO, 2, $3, $6);
    }
| Bloco
    {
        $$ = $1;
    }
;

/* ========== EXPRESSÕES ========== */

/**
 * Uma expressão pode ser uma expressão lógica OU ou uma atribuição.
 */
Expr: OrExpr
    {
        $$ = $1;
    }
| ID ATRIBUICAO Expr
    {
        NoArvore* no_id = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $1, 0, 
                                               TIPO_DESCONHECIDO, 0);
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("="), 0, 
                                 TIPO_DESCONHECIDO, 2, no_id, $3);
    }
;

/**
 * Expressão com operador lógico OU (menor precedência dos operadores lógicos).
 */
OrExpr: OrExpr OU AndExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("ou"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| AndExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão com operador lógico E.
 */
AndExpr: AndExpr E EqExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("e"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| EqExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão com operadores de igualdade (== e !=).
 */
EqExpr: EqExpr IGUAL DesigExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("=="), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| EqExpr DIFERENTE DesigExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("!="), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| DesigExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão com operadores relacionais (<, >, <=, >=).
 */
DesigExpr: DesigExpr MENOR AddExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("<"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| DesigExpr MAIOR AddExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup(">"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| DesigExpr MAIORIGUAL AddExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup(">="), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| DesigExpr MENORIGUAL AddExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("<="), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| AddExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão com operadores aditivos (+ e -).
 */
AddExpr: AddExpr MAIS MulExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("+"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| AddExpr MENOS MulExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("-"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| MulExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão com operadores multiplicativos (* e /).
 */
MulExpr: MulExpr MULT UnExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("*"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| MulExpr DIV UnExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("/"), 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
| UnExpr
    {
        $$ = $1;
    }
;

/**
 * Expressão unária (negação aritmética ou lógica).
 */
UnExpr: MENOS PrimExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("negacao"), 0, 
                                 TIPO_DESCONHECIDO, 1, $2);
    }
| '!' PrimExpr
    {
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, strdup("!"), 0, 
                                 TIPO_DESCONHECIDO, 1, $2);
    }
| PrimExpr
    {
        $$ = $1;
    }
;

/**
 * Expressões primárias (identificadores, constantes, chamadas de função).
 */
PrimExpr: ID ABREPAR ListExpr FECHAPAR
    {
        // Chamada de função com argumentos
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, $1, 0, 
                                 TIPO_DESCONHECIDO, 1, $3);
    }
| ID ABREPAR FECHAPAR
    {
        // Chamada de função sem argumentos
        $$ = construir_no_arvore(NO_EXPRESSAO, yylineno, $1, 0, 
                                 TIPO_DESCONHECIDO, 0);
    }
| ID
    {
        // Variável ou identificador
        $$ = construir_no_arvore(NO_IDENTIFICADOR, yylineno, $1, 0, 
                                 TIPO_DESCONHECIDO, 0);
    }
| CARCONST
    {
        // Constante de caractere
        $$ = construir_no_arvore(NO_CONSTANTE, yylineno, $1, 0, 
                                 TIPO_CARACTERE, 0);
    }
| INTCONST
    {
        // Constante inteira
        $$ = construir_no_arvore(NO_CONSTANTE, yylineno, $1, 0, 
                                 TIPO_INTEIRO, 0);
    }
| ABREPAR Expr FECHAPAR
    {
        // Expressão entre parênteses
        $$ = $2;
    }
;

/**
 * Lista de expressões (argumentos de chamada de função).
 */
ListExpr: Expr
    {
        $$ = construir_no_arvore(NO_LISTA, yylineno, strdup("args"), 0, 
                                 TIPO_DESCONHECIDO, 1, $1);
    }
| ListExpr VIRGULA Expr
    {
        $$ = construir_no_arvore(NO_LISTA, yylineno, NULL, 0, 
                                 TIPO_DESCONHECIDO, 2, $1, $3);
    }
;

%%

/**
 * Função de tratamento de erros sintáticos.
 * Chamada automaticamente pelo parser quando encontra um erro.
 */
void yyerror(const char *s) {
    fprintf(stderr, "ERRO: Erro sintático na linha %d\n", yylineno);
    exit(1);
}
