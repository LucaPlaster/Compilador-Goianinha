#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "../headers/arvore_sintatica.h"

/**
 * Função que constrói um novo nó da árvore sintática abstrata.
 * 
 * Esta função aloca memória para um novo nó, inicializa seus campos
 * e conecta seus filhos usando argumentos variádicos.
 * 
 * @param tipo Tipo do nó (programa, função, expressão, etc.)
 * @param linha Número da linha no código fonte (para mensagens de erro)
 * @param texto Valor textual associado ao nó (pode ser NULL)
 * @param numero Valor numérico para constantes (0 se não aplicável)
 * @param tipo_dado Tipo de dado associado ao nó
 * @param num_filhos Quantidade de nós filhos
 * @param ... Lista variável de ponteiros para nós filhos
 * @return Ponteiro para o nó criado
 */
NoArvore* construir_no_arvore(TipoNo tipo, int linha, char* texto, int numero, 
                               TipoVariavel tipo_dado, int num_filhos, ...) {
    // Aloca memória para o novo nó
    NoArvore* novo_no = (NoArvore*)malloc(sizeof(NoArvore));
    if (!novo_no) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para nó da árvore\n");
        exit(1);
    }
    
    // Inicializa os campos básicos do nó
    novo_no->tipo_no = tipo;
    novo_no->numero_linha = linha;
    novo_no->valor_texto = texto ? strdup(texto) : NULL;
    novo_no->valor_numerico = numero;
    novo_no->tipo_var = tipo_dado;
    novo_no->quantidade_filhos = num_filhos;
    
    // Se o nó tem filhos, aloca espaço para o array de filhos
    if (num_filhos > 0) {
        novo_no->nos_filhos = (NoArvore**)malloc(sizeof(NoArvore*) * num_filhos);
        if (!novo_no->nos_filhos) {
            fprintf(stderr, "ERRO: Falha ao alocar memória para filhos do nó\n");
            exit(1);
        }
        
        // Usa stdarg.h para processar a lista variável de argumentos
        va_list argumentos;
        va_start(argumentos, num_filhos);
        
        // Adiciona cada filho ao array
        for (int i = 0; i < num_filhos; i++) {
            novo_no->nos_filhos[i] = va_arg(argumentos, NoArvore*);
        }
        
        va_end(argumentos);
    } else {
        novo_no->nos_filhos = NULL;
    }
    
    return novo_no;
}

/**
 * Função auxiliar que converte o tipo de nó em string legível.
 * Útil para depuração e visualização da árvore.
 * 
 * @param tipo Tipo do nó
 * @return String representando o tipo
 */
static const char* obter_nome_tipo_no(TipoNo tipo) {
    switch(tipo) {
        case NO_PROGRAMA: return "PROGRAMA";
        case NO_FUNCAO: return "FUNCAO";
        case NO_DECL_VAR: return "DECLARACAO_VARIAVEL";
        case NO_BLOCO: return "BLOCO";
        case NO_COMANDO: return "COMANDO";
        case NO_EXPRESSAO: return "EXPRESSAO";
        case NO_IDENTIFICADOR: return "IDENTIFICADOR";
        case NO_CONSTANTE: return "CONSTANTE";
        case NO_LISTA: return "LISTA";
        default: return "DESCONHECIDO";
    }
}

/**
 * Função auxiliar que converte o tipo de variável em string legível.
 * 
 * @param tipo Tipo da variável
 * @return String representando o tipo
 */
static const char* obter_nome_tipo_variavel(TipoVariavel tipo) {
    switch(tipo) {
        case TIPO_INTEIRO: return "int";
        case TIPO_CARACTERE: return "car";
        case TIPO_VAZIO: return "void";
        case TIPO_DESCONHECIDO: return "desconhecido";
        case TIPO_INVALIDO: return "invalido";
        default: return "?";
    }
}

/**
 * Função que imprime a árvore sintática de forma hierárquica.
 * Utiliza indentação para mostrar a estrutura aninhada da árvore.
 * 
 * @param raiz Nó raiz da árvore ou subárvore
 * @param profundidade Nível de indentação (0 para a raiz)
 */
void exibir_arvore(NoArvore* raiz, int profundidade) {
    if (!raiz) return;
    
    // Imprime a indentação baseada na profundidade
    for (int i = 0; i < profundidade; i++) {
        printf("  ");
    }
    
    // Imprime informações do nó
    printf("[%s", obter_nome_tipo_no(raiz->tipo_no));
    
    if (raiz->valor_texto) {
        printf(" '%s'", raiz->valor_texto);
    }
    
    if (raiz->tipo_no == NO_CONSTANTE && !raiz->valor_texto) {
        printf(" %d", raiz->valor_numerico);
    }
    
    printf(" (tipo: %s)", obter_nome_tipo_variavel(raiz->tipo_var));
    printf(" linha:%d", raiz->numero_linha);
    printf("]\n");
    
    // Recursivamente imprime todos os filhos
    for (int i = 0; i < raiz->quantidade_filhos; i++) {
        exibir_arvore(raiz->nos_filhos[i], profundidade + 1);
    }
}

/**
 * Função que libera recursivamente toda a memória da árvore.
 * Importante para evitar vazamentos de memória.
 * 
 * @param raiz Nó raiz da árvore a ser liberada
 */
void desalocar_arvore(NoArvore* raiz) {
    if (!raiz) return;
    
    // Libera recursivamente todos os filhos primeiro
    for (int i = 0; i < raiz->quantidade_filhos; i++) {
        desalocar_arvore(raiz->nos_filhos[i]);
    }
    
    // Libera o array de filhos se existir
    if (raiz->nos_filhos) {
        free(raiz->nos_filhos);
    }
    
    // Libera a string de texto se existir
    if (raiz->valor_texto) {
        free(raiz->valor_texto);
    }
    
    // Finalmente libera o próprio nó
    free(raiz);
}
