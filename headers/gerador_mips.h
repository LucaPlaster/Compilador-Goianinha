
#ifndef GERADOR_MIPS_H
#define GERADOR_MIPS_H

#include "arvore_sintatica.h"
#include <stdio.h>

/**
 * Função principal do gerador de código MIPS.
 * 
 * Percorre a árvore sintática abstrata e gera instruções em Assembly MIPS
 * correspondentes ao programa fonte. O código gerado pode ser executado
 * no simulador SPIM.
 * 
 * @param raiz Raiz da árvore sintática
 * @param arquivo_saida Arquivo onde o código Assembly será escrito
 */
void gerar_codigo_assembly_mips(NoArvore* raiz, FILE* arquivo_saida);

#endif
