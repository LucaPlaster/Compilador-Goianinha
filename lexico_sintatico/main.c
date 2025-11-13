
/**
 * Arquivo principal do Compilador Goianinha
 * 
 * Este arquivo contém a função main que orquestra todas as fases da compilação:
 * 1. Análise Léxica (Flex)
 * 2. Análise Sintática (Bison)
 * 3. Construção da AST
 * 4. Análise Semântica
 * 5. Geração de Código MIPS
 */

#include <stdio.h>
#include <stdlib.h>
#include "../headers/arvore_sintatica.h"
#include "../headers/analisador_semantico.h"
#include "../headers/gerador_mips.h"

/**
 * Variáveis externas definidas pelo Flex/Bison
 */
extern FILE *yyin;              // Arquivo de entrada do scanner
extern int yyparse();           // Função do parser gerada pelo Bison
extern NoArvore* raiz_arvore_sintatica;  // Raiz da AST construída durante parsing

/**
 * Função principal do compilador.
 * 
 * @param argc Número de argumentos da linha de comando
 * @param argv Array de argumentos: argv[1] = arquivo fonte, argv[2] = arquivo saída (opcional)
 * @return 0 se sucesso, 1 se erro
 */
int main(int argc, char** argv) {
    // Verifica se o nome do arquivo fonte foi fornecido
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_fonte.g> [arquivo_saida.asm]\n", argv[0]);
        return 1;
    }
    
    // Abre o arquivo fonte
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "ERRO: Nao foi possivel abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }
    
    printf("\n");
    printf("==================================================\n");
    printf("       COMPILADOR DA LINGUAGEM GOIANINHA         \n");
    printf("==================================================\n");
    printf("Arquivo fonte: %s\n", argv[1]);
    printf("==================================================\n\n");
    
    // FASE 1 e 2: Análise Léxica e Sintática (gera a AST)
    printf("=== Fase 1 e 2: Analise Lexica e Sintatica ===\n");
    if (yyparse() != 0) {
        fprintf(stderr, "ERRO: Analise sintatica falhou\n");
        fclose(yyin);
        return 1;
    }
    printf("Analise sintatica concluida com sucesso!\n");
    
    // Verifica se a AST foi construída
    if (!raiz_arvore_sintatica) {
        fprintf(stderr, "ERRO: AST nao foi construida\n");
        fclose(yyin);
        return 1;
    }
    
    // Imprime a AST (para debugging)
    printf("\n=== Arvore Sintatica Abstrata (AST) ===\n");
    exibir_arvore(raiz_arvore_sintatica, 0);
    printf("\n");
    
    // FASE 3: Análise Semântica
    executar_analise_semantica(raiz_arvore_sintatica);
    
    // FASE 4: Geração de Código MIPS
    printf("=== Fase 4: Geracao de Codigo MIPS ===\n");
    
    // Determina o nome do arquivo de saída
    FILE* arquivo_saida;
    if (argc >= 3) {
        arquivo_saida = fopen(argv[2], "w");
        if (!arquivo_saida) {
            fprintf(stderr, "ERRO: Nao foi possivel criar o arquivo de saida '%s'\n", argv[2]);
            desalocar_arvore(raiz_arvore_sintatica);
            fclose(yyin);
            return 1;
        }
        printf("Gerando codigo MIPS em: %s\n", argv[2]);
    } else {
        arquivo_saida = stdout;
        printf("Gerando codigo MIPS na saida padrao:\n");
        printf("-----------------------------------\n");
    }
    
    // Gera o código MIPS
    gerar_codigo_assembly_mips(raiz_arvore_sintatica, arquivo_saida);
    
    if (argc >= 3) {
        fclose(arquivo_saida);
        printf("Codigo MIPS gerado com sucesso!\n");
    }
    
    // Libera recursos
    printf("\n=== Liberando recursos ===\n");
    desalocar_arvore(raiz_arvore_sintatica);
    fclose(yyin);
    
    printf("\n");
    printf("==================================================\n");
    printf("       COMPILACAO CONCLUIDA COM SUCESSO!         \n");
    printf("==================================================\n\n");
    
    return 0;
}
