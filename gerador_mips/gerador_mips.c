#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/arvore_sintatica.h"
#include "../headers/gerenciador_simbolos.h"
#include "../headers/gerador_mips.h"

/**
 * GERADOR DE CÓDIGO MIPS PARA A LINGUAGEM GOIANINHA
 * 
 * Este módulo percorre a árvore sintática abstrata e gera código em
 * linguagem Assembly MIPS que pode ser executado no simulador SPIM.
 * 
 * O código gerado segue as convenções:
 * - $t0-$t9: registradores temporários para cálculos
 * - $fp: frame pointer (ponteiro para frame da função atual)
 * - $sp: stack pointer (ponteiro para topo da pilha)
 * - $v0: resultado de funções e syscalls
 * - $a0-$a3: argumentos de funções/syscalls
 * - $ra: endereço de retorno
 */

// Declaração da função recursiva de geração
void percorrer_e_gerar_codigo(NoArvore* raiz, FILE* saida);

/**
 * Variáveis globais para geração de labels únicos
 */
static int contador_labels = 0;          // Contador para labels de controle de fluxo
static int contador_labels_string = 0;   // Contador para labels de strings
static char *nome_funcao_em_execucao = NULL;  // Nome da função sendo processada

/**
 * Gera um novo label único para controle de fluxo (if, while, etc).
 * 
 * @return String com o label (deve ser liberada após uso)
 */
char* gerar_label_unico() {
    char* label = malloc(20);
    if (!label) {
        fprintf(stderr, "ERRO: Falha ao alocar memoria para label\n");
        exit(1);
    }
    sprintf(label, "Label_%d", contador_labels++);
    return label;
}

/**
 * Gera um novo label único para strings literais.
 * 
 * @return String com o label (deve ser liberada após uso)
 */
char* gerar_label_string() {
    char* label = malloc(20);
    if (!label) {
        fprintf(stderr, "ERRO: Falha ao alocar memoria para label de string\n");
        exit(1);
    }
    sprintf(label, "string_%d", contador_labels_string++);
    return label;
}

/**
 * Gera a seção .data com strings e constantes pré-definidas.
 * 
 * @param saida Arquivo de saída
 */
void gerar_secao_dados(FILE* saida) {
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, "# Secao de Dados (.data)\n");
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, ".data\n");
    fprintf(saida, "quebra_linha: .asciiz \"\\n\"  # String para novalinha\n");
    fprintf(saida, "\n");
}

/**
 * Função principal de geração de código MIPS.
 * 
 * Inicializa o arquivo assembly com as seções necessárias e
 * chama a função recursiva para percorrer a AST.
 * 
 * @param raiz Raiz da árvore sintática
 * @param saida Arquivo onde o código será escrito
 */
void gerar_codigo_assembly_mips(NoArvore* raiz, FILE* saida) {
    if (!raiz || !saida) return;
    
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, "# CODIGO ASSEMBLY MIPS GERADO PELO COMPILADOR GOIANINHA\n");
    fprintf(saida, "# ===============================================\n\n");
    
    // Gera a seção de dados
    gerar_secao_dados(saida);
    
    // Inicia a seção de texto (código)
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, "# Secao de Texto (.text)\n");
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, ".text\n");
    fprintf(saida, ".globl main  # Declara main como ponto de entrada\n\n");
    
    // Percorre a AST gerando o código
    percorrer_e_gerar_codigo(raiz, saida);
    
    // Finaliza o programa com syscall de saída
    fprintf(saida, "\n# ===============================================\n");
    fprintf(saida, "# Finalizacao do programa\n");
    fprintf(saida, "# ===============================================\n");
    fprintf(saida, "li $v0, 10      # Syscall 10: exit\n");
    fprintf(saida, "syscall\n");
}

/**
 * Função recursiva que percorre a AST e gera código MIPS.
 * 
 * Para cada tipo de nó, gera as instruções MIPS correspondentes.
 * 
 * @param raiz Nó atual da AST
 * @param saida Arquivo de saída
 */
void percorrer_e_gerar_codigo(NoArvore* raiz, FILE* saida) {
    if (!raiz) return;
    
    switch (raiz->tipo_no) {
        case NO_PROGRAMA: {
            // Processa o programa principal
            fprintf(saida, "# ===============================================\n");
            fprintf(saida, "# DECLARACOES GLOBAIS E FUNCOES\n");
            fprintf(saida, "# ===============================================\n\n");
            
            // Primeira passagem: gera código para funções e variáveis globais
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i]) {
                    if (raiz->nos_filhos[i]->tipo_no == NO_FUNCAO || 
                        raiz->nos_filhos[i]->tipo_no == NO_DECL_VAR) {
                        percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                    }
                }
            }
            
            // Segunda passagem: procura e gera o bloco main
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i] && 
                    raiz->nos_filhos[i]->tipo_no == NO_BLOCO && 
                    raiz->nos_filhos[i]->valor_texto && 
                    strcmp(raiz->nos_filhos[i]->valor_texto, "programa") == 0) {
                    
                    fprintf(saida, "# ===============================================\n");
                    fprintf(saida, "# BLOCO PRINCIPAL (main)\n");
                    fprintf(saida, "# ===============================================\n");
                    fprintf(saida, "main:\n");
                    fprintf(saida, "    move $fp, $sp       # Inicializa frame pointer\n");
                    
                    // Gera código do bloco principal
                    percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                    break;
                }
            }
            break;
        }
        
        case NO_FUNCAO: {
            if (raiz->valor_texto) {
                // É uma declaração de função
                nome_funcao_em_execucao = strdup(raiz->valor_texto);
                
                fprintf(saida, "\n# Funcao: %s\n", raiz->valor_texto);
                fprintf(saida, "%s:\n", raiz->valor_texto);
                
                // Prólogo da função: salva registradores importantes
                fprintf(saida, "    sw $ra, -4($sp)     # Salva return address\n");
                fprintf(saida, "    sw $fp, -8($sp)     # Salva frame pointer anterior\n");
                fprintf(saida, "    move $fp, $sp       # Atualiza frame pointer\n");
                fprintf(saida, "    addiu $sp, $sp, -8  # Ajusta stack pointer\n");
                
                // Gera código do corpo da função
                for (int i = 0; i < raiz->quantidade_filhos; i++) {
                    if (raiz->nos_filhos[i]) {
                        percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                    }
                }
                
                // Epílogo da função: restaura registradores e retorna
                fprintf(saida, "%s_saida:\n", nome_funcao_em_execucao);
                fprintf(saida, "    move $sp, $fp       # Restaura stack pointer\n");
                fprintf(saida, "    lw $ra, -4($sp)     # Restaura return address\n");
                fprintf(saida, "    lw $fp, -8($sp)     # Restaura frame pointer\n");
                fprintf(saida, "    jr $ra              # Retorna para chamador\n\n");
                
                free(nome_funcao_em_execucao);
                nome_funcao_em_execucao = NULL;
            } else {
                // Apenas processa os filhos (estrutura interna da função)
                for (int i = 0; i < raiz->quantidade_filhos; i++) {
                    if (raiz->nos_filhos[i]) {
                        percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                    }
                }
            }
            break;
        }
        
        case NO_DECL_VAR: {
            // Declaração de variável: aloca espaço na pilha
            fprintf(saida, "    addiu $sp, $sp, -4  # Aloca espaco para variavel\n");
            break;
        }
        
        case NO_BLOCO: {
            // Bloco: processa todos os comandos dentro dele
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                }
            }
            break;
        }
        
        case NO_COMANDO: {
            if (!raiz->valor_texto) break;
            
            if (strcmp(raiz->valor_texto, "escreva") == 0) {
                // Comando escreva <expressão>
                fprintf(saida, "    # Comando: escreva\n");
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                    // Avalia a expressão (resultado fica em $t0)
                    percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                    
                    // Imprime o valor (syscall 1: print integer)
                    fprintf(saida, "    move $a0, $t0       # Move valor para $a0\n");
                    fprintf(saida, "    li $v0, 1           # Syscall 1: print_int\n");
                    fprintf(saida, "    syscall\n");
                }
                
            } else if (strcmp(raiz->valor_texto, "escreva_string") == 0) {
                // Comando escreva "string"
                fprintf(saida, "    # Comando: escreva string\n");
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0] && 
                    raiz->nos_filhos[0]->valor_texto) {
                    
                    // Cria um label para a string na seção .data
                    char* label_str = gerar_label_string();
                    
                    // Adiciona a string na seção .data
                    fprintf(saida, ".data\n");
                    fprintf(saida, "%s: .asciiz \"%s\"\n", label_str, raiz->nos_filhos[0]->valor_texto);
                    fprintf(saida, ".text\n");
                    
                    // Imprime a string (syscall 4: print string)
                    fprintf(saida, "    la $a0, %s          # Carrega endereco da string\n", label_str);
                    fprintf(saida, "    li $v0, 4           # Syscall 4: print_string\n");
                    fprintf(saida, "    syscall\n");
                    
                    free(label_str);
                }
                
            } else if (strcmp(raiz->valor_texto, "novalinha") == 0) {
                // Comando novalinha
                fprintf(saida, "    # Comando: novalinha\n");
                fprintf(saida, "    la $a0, quebra_linha # Carrega string de quebra de linha\n");
                fprintf(saida, "    li $v0, 4            # Syscall 4: print_string\n");
                fprintf(saida, "    syscall\n");
                
            } else if (strcmp(raiz->valor_texto, "retorne") == 0) {
                // Comando retorne <expressão>
                fprintf(saida, "    # Comando: retorne\n");
                if (nome_funcao_em_execucao) {
                    if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                        // Avalia a expressão de retorno
                        percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                        fprintf(saida, "    move $v0, $t0       # Move resultado para $v0\n");
                    }
                    // Pula para o epílogo da função
                    fprintf(saida, "    j %s_saida          # Vai para epilogo da funcao\n", 
                           nome_funcao_em_execucao);
                }
                
            } else if (strcmp(raiz->valor_texto, "se") == 0 || 
                       strcmp(raiz->valor_texto, "se_senao") == 0) {
                // Comando if-then ou if-then-else
                fprintf(saida, "    # Comando: %s\n", raiz->valor_texto);
                
                char* label_else = gerar_label_unico();
                char* label_fim = gerar_label_unico();
                
                // Avalia a condição
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                }
                
                // Se falso, pula para else ou fim
                if (raiz->quantidade_filhos == 3) {
                    fprintf(saida, "    beq $t0, $zero, %s  # Se falso, vai para else\n", label_else);
                } else {
                    fprintf(saida, "    beq $t0, $zero, %s  # Se falso, vai para fim\n", label_fim);
                }
                
                // Bloco then
                if (raiz->quantidade_filhos > 1 && raiz->nos_filhos[1]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[1], saida);
                }
                
                // Se há else
                if (raiz->quantidade_filhos == 3) {
                    fprintf(saida, "    j %s                # Pula para fim\n", label_fim);
                    fprintf(saida, "%s:\n", label_else);
                    
                    if (raiz->nos_filhos[2]) {
                        percorrer_e_gerar_codigo(raiz->nos_filhos[2], saida);
                    }
                }
                
                fprintf(saida, "%s:\n", label_fim);
                
                free(label_else);
                free(label_fim);
                
            } else if (strcmp(raiz->valor_texto, "enquanto") == 0) {
                // Comando while
                fprintf(saida, "    # Comando: enquanto\n");
                
                char* label_inicio = gerar_label_unico();
                char* label_fim = gerar_label_unico();
                
                // Label de início do loop
                fprintf(saida, "%s:\n", label_inicio);
                
                // Avalia a condição
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                }
                
                // Se falso, sai do loop
                fprintf(saida, "    beq $t0, $zero, %s  # Se falso, sai do loop\n", label_fim);
                
                // Corpo do loop
                if (raiz->quantidade_filhos > 1 && raiz->nos_filhos[1]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[1], saida);
                }
                
                // Volta para o início
                fprintf(saida, "    j %s                # Volta para inicio do loop\n", label_inicio);
                fprintf(saida, "%s:\n", label_fim);
                
                free(label_inicio);
                free(label_fim);
                
            } else {
                // Outros comandos: apenas processa os filhos
                for (int i = 0; i < raiz->quantidade_filhos; i++) {
                    if (raiz->nos_filhos[i]) {
                        percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                    }
                }
            }
            break;
        }
        
        case NO_EXPRESSAO: {
            if (!raiz->valor_texto) break;
            
            // Verifica se é uma chamada de função
            RegistroFuncao* funcao_chamada = buscar_funcao_global(raiz->valor_texto);
            
            if (funcao_chamada != NULL) {
                // É uma chamada de função
                fprintf(saida, "    # Chamada de funcao: %s\n", raiz->valor_texto);
                
                // TODO: Processar argumentos e fazer a chamada
                // Por simplicidade, assumimos função sem argumentos
                fprintf(saida, "    jal %s              # Chama funcao\n", raiz->valor_texto);
                fprintf(saida, "    move $t0, $v0       # Move resultado para $t0\n");
                
            } else if (raiz->quantidade_filhos == 2) {
                // Expressão binária
                if (!raiz->nos_filhos[0] || !raiz->nos_filhos[1]) break;
                
                // Avalia o operando esquerdo (resultado em $t0)
                percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                
                // Salva o resultado na pilha
                fprintf(saida, "    addiu $sp, $sp, -4  # Empilha operando esquerdo\n");
                fprintf(saida, "    sw $t0, 0($sp)\n");
                
                // Avalia o operando direito (resultado em $t0)
                percorrer_e_gerar_codigo(raiz->nos_filhos[1], saida);
                
                // Recupera o operando esquerdo da pilha
                fprintf(saida, "    lw $t1, 0($sp)      # Desempilha operando esquerdo\n");
                fprintf(saida, "    addiu $sp, $sp, 4\n");
                
                // Troca $t0 e $t1 para manter a ordem correta
                fprintf(saida, "    move $t2, $t0\n");
                fprintf(saida, "    move $t0, $t1\n");
                fprintf(saida, "    move $t1, $t2\n");
                
                // Realiza a operação apropriada
                if (strcmp(raiz->valor_texto, "+") == 0) {
                    fprintf(saida, "    add $t0, $t0, $t1   # Adicao\n");
                } else if (strcmp(raiz->valor_texto, "-") == 0) {
                    fprintf(saida, "    sub $t0, $t0, $t1   # Subtracao\n");
                } else if (strcmp(raiz->valor_texto, "*") == 0) {
                    fprintf(saida, "    mul $t0, $t0, $t1   # Multiplicacao\n");
                } else if (strcmp(raiz->valor_texto, "/") == 0) {
                    fprintf(saida, "    div $t0, $t0, $t1   # Divisao\n");
                } else if (strcmp(raiz->valor_texto, "<") == 0) {
                    fprintf(saida, "    slt $t0, $t0, $t1   # Menor que\n");
                } else if (strcmp(raiz->valor_texto, ">") == 0) {
                    fprintf(saida, "    sgt $t0, $t0, $t1   # Maior que\n");
                } else if (strcmp(raiz->valor_texto, "==") == 0) {
                    fprintf(saida, "    seq $t0, $t0, $t1   # Igual a\n");
                } else if (strcmp(raiz->valor_texto, "!=") == 0) {
                    fprintf(saida, "    sne $t0, $t0, $t1   # Diferente de\n");
                } else if (strcmp(raiz->valor_texto, "<=") == 0) {
                    fprintf(saida, "    sle $t0, $t0, $t1   # Menor ou igual\n");
                } else if (strcmp(raiz->valor_texto, ">=") == 0) {
                    fprintf(saida, "    sge $t0, $t0, $t1   # Maior ou igual\n");
                } else if (strcmp(raiz->valor_texto, "e") == 0) {
                    fprintf(saida, "    and $t0, $t0, $t1   # AND logico\n");
                } else if (strcmp(raiz->valor_texto, "ou") == 0) {
                    fprintf(saida, "    or $t0, $t0, $t1    # OR logico\n");
                } else if (strcmp(raiz->valor_texto, "=") == 0) {
                    // Atribuição
                    if (raiz->nos_filhos[0]->valor_texto) {
                        RegistroVariavel* var = buscar_simbolo_global(raiz->nos_filhos[0]->valor_texto);
                        if (var) {
                            fprintf(saida, "    sw $t1, %d($fp)     # Atribui a %s\n", 
                                   var->posicao_memoria * (-4), var->nome_identificador);
                            fprintf(saida, "    move $t0, $t1       # Resultado da atribuicao\n");
                        }
                    }
                }
                
            } else if (raiz->quantidade_filhos == 1) {
                // Expressão unária
                if (!raiz->nos_filhos[0]) break;
                
                // Avalia o operando
                percorrer_e_gerar_codigo(raiz->nos_filhos[0], saida);
                
                if (strcmp(raiz->valor_texto, "negacao") == 0 || strcmp(raiz->valor_texto, "-") == 0) {
                    fprintf(saida, "    neg $t0, $t0        # Negacao aritmetica\n");
                } else if (strcmp(raiz->valor_texto, "!") == 0) {
                    fprintf(saida, "    seq $t0, $t0, $zero # Negacao logica\n");
                }
            }
            break;
        }
        
        case NO_CONSTANTE: {
            // Constante inteira
            fprintf(saida, "    li $t0, %d          # Carrega constante\n", 
                   raiz->valor_numerico);
            break;
        }
        
        case NO_IDENTIFICADOR: {
            // Acesso a variável
            if (!raiz->valor_texto) break;
            
            RegistroVariavel* var = buscar_simbolo_global(raiz->valor_texto);
            if (var) {
                fprintf(saida, "    lw $t0, %d($fp)     # Carrega %s\n", 
                       var->posicao_memoria * (-4), var->nome_identificador);
            }
            break;
        }
        
        default: {
            // Para outros tipos de nós, apenas processa os filhos
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i]) {
                    percorrer_e_gerar_codigo(raiz->nos_filhos[i], saida);
                }
            }
            break;
        }
    }
}
