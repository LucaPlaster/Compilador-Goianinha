
#ifndef TIPOS_DADOS_H
#define TIPOS_DADOS_H

/**
 * Enumeração que define os tipos de dados suportados pela linguagem Goianinha.
 * 
 * - TIPO_INTEIRO: Representa o tipo int da linguagem
 * - TIPO_CARACTERE: Representa o tipo car (caractere) da linguagem
 * - TIPO_VAZIO: Usado para funções que não retornam valor ou procedimentos
 * - TIPO_DESCONHECIDO: Usado quando o tipo ainda não foi determinado
 * - TIPO_INVALIDO: Usado quando há erro de tipo
 */
typedef enum {
    TIPO_INTEIRO,
    TIPO_CARACTERE,
    TIPO_VAZIO,
    TIPO_DESCONHECIDO,
    TIPO_INVALIDO
} TipoVariavel;

/**
 * Enumeração que define os tipos de nós que podem existir na AST.
 * 
 * - NO_PROGRAMA: Raiz da árvore, representa o programa completo
 * - NO_FUNCAO: Nó que representa uma declaração de função
 * - NO_DECL_VAR: Nó que representa declaração de variável
 * - NO_BLOCO: Nó que representa um bloco de código
 * - NO_COMANDO: Nó que representa um comando (if, while, etc)
 * - NO_EXPRESSAO: Nó que representa uma expressão
 * - NO_IDENTIFICADOR: Nó que representa um identificador
 * - NO_CONSTANTE: Nó que representa uma constante (literal)
 * - NO_LISTA: Nó auxiliar para representar listas de elementos
 */
typedef enum {
    NO_PROGRAMA,
    NO_FUNCAO,
    NO_DECL_VAR,
    NO_BLOCO,
    NO_COMANDO,
    NO_EXPRESSAO,
    NO_IDENTIFICADOR,
    NO_CONSTANTE,
    NO_LISTA
} TipoNo;

#endif
