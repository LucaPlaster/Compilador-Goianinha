
#ifndef ANALISADOR_SEMANTICO_H
#define ANALISADOR_SEMANTICO_H

#include "arvore_sintatica.h"

/**
 * Função principal do analisador semântico.
 * 
 * Percorre a árvore sintática abstrata e realiza as seguintes verificações:
 * - Checagem de declarações antes do uso
 * - Verificação de escopos
 * - Checagem de tipos em expressões e atribuições
 * - Validação de chamadas de função (número e tipo de parâmetros)
 * - Verificação de tipo de retorno de funções
 * 
 * Se encontrar algum erro semântico, imprime mensagem de erro e termina a compilação.
 * 
 * @param raiz Raiz da árvore sintática a ser analisada
 */
void executar_analise_semantica(NoArvore* raiz);

#endif
