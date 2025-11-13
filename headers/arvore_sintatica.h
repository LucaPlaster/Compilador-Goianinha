
#ifndef ARVORE_SINTATICA_H
#define ARVORE_SINTATICA_H

#include "tipos_dados.h"

/**
 * Estrutura que representa um nó da Árvore Sintática Abstrata (AST).
 * 
 * Cada nó contém:
 * - tipo_no: O tipo do nó (programa, função, expressão, etc.)
 * - valor_texto: String que armazena valores textuais (nomes de variáveis, etc.)
 * - valor_numerico: Valor numérico para constantes inteiras
 * - numero_linha: Linha do código fonte onde o elemento aparece (para mensagens de erro)
 * - tipo_var: O tipo de dado associado ao nó (int, car, etc.)
 * - nos_filhos: Array de ponteiros para os nós filhos
 * - quantidade_filhos: Número de filhos que este nó possui
 */
typedef struct NoArvore {
    TipoNo tipo_no;
    char* valor_texto;
    int valor_numerico;
    int numero_linha;
    TipoVariavel tipo_var;
    struct NoArvore** nos_filhos;
    int quantidade_filhos;
} NoArvore;

/**
 * Cria um novo nó da árvore sintática abstrata.
 * 
 * @param tipo O tipo do nó a ser criado
 * @param linha Número da linha no código fonte
 * @param texto Valor textual (pode ser NULL)
 * @param numero Valor numérico (usado para constantes)
 * @param tipo_dado Tipo de dado associado ao nó
 * @param num_filhos Número de filhos que o nó terá
 * @param ... Lista variável de nós filhos
 * @return Ponteiro para o novo nó criado
 */
NoArvore* construir_no_arvore(TipoNo tipo, int linha, char* texto, int numero, 
                               TipoVariavel tipo_dado, int num_filhos, ...);

/**
 * Imprime a árvore sintática abstrata de forma hierárquica.
 * Útil para debugging e visualização da estrutura do programa.
 * 
 * @param raiz Nó raiz da árvore a ser impressa
 * @param profundidade Nível de indentação (usar 0 para a raiz)
 */
void exibir_arvore(NoArvore* raiz, int profundidade);

/**
 * Libera toda a memória alocada para a árvore sintática.
 * Deve ser chamada ao final da compilação para evitar vazamentos de memória.
 * 
 * @param raiz Nó raiz da árvore a ser liberada
 */
void desalocar_arvore(NoArvore* raiz);

#endif
