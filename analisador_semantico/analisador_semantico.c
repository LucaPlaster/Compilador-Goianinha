#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/analisador_semantico.h"
#include "../headers/gerenciador_simbolos.h"

/**
 * Variáveis globais para rastrear contexto durante análise semântica.
 * - tipo_retorno_funcao_contexto: tipo que a função atual deve retornar
 * - nome_funcao_contexto: nome da função sendo analisada
 */
static TipoVariavel tipo_retorno_funcao_contexto = TIPO_DESCONHECIDO;
static char *nome_funcao_contexto = NULL;

// Declaração da função principal de percurso da AST
TipoVariavel percorrer_e_validar_no(NoArvore *raiz);

/**
 * Coleta os tipos dos parâmetros de uma função.
 * 
 * Percorre o nó de parâmetros e extrai os tipos de cada um,
 * armazenando-os em um array.
 * 
 * @param no_parametros Nó contendo a lista de parâmetros
 * @param array_tipos Array onde os tipos serão armazenados
 * @param contador Ponteiro para o contador de parâmetros encontrados
 */
void coletar_tipos_dos_parametros(NoArvore* no_parametros, TipoVariavel* array_tipos, int* contador) {
    // Verifica se o nó é válido e se ainda há espaço no array
    if (!no_parametros || *contador >= MAX_ARGUMENTOS) return;
    
    if (no_parametros->tipo_no == NO_LISTA) {
        // Se é uma lista, processa cada filho recursivamente
        for (int i = 0; i < no_parametros->quantidade_filhos; i++) {
            coletar_tipos_dos_parametros(no_parametros->nos_filhos[i], array_tipos, contador);
        }
    } else if (no_parametros->tipo_no == NO_IDENTIFICADOR) {
        // Se é um identificador (parâmetro), adiciona seu tipo ao array
        array_tipos[*contador] = no_parametros->tipo_var;
        (*contador)++;
    }
}

/**
 * Verifica se os tipos dos argumentos em uma chamada de função
 * correspondem aos tipos dos parâmetros formais.
 * 
 * @param no_argumento Nó contendo os argumentos da chamada
 * @param info_funcao Informações da função sendo chamada
 * @param indice_arg Índice do argumento atual
 */
void validar_tipos_dos_argumentos(NoArvore* no_argumento, RegistroFuncao* info_funcao, int indice_arg) {
    if (!no_argumento) return;
    
    if (no_argumento->tipo_no == NO_LISTA) {
        // Se é uma lista, valida cada argumento
        for (int i = 0; i < no_argumento->quantidade_filhos; i++) {
            validar_tipos_dos_argumentos(no_argumento->nos_filhos[i], info_funcao, indice_arg);
            // Incrementa índice apenas para nós que não são listas
            if(no_argumento->nos_filhos[i]->tipo_no != NO_LISTA) indice_arg++;
        }
    } else {
        // Obtém o tipo do argumento fornecido
        TipoVariavel tipo_argumento_fornecido = percorrer_e_validar_no(no_argumento);
        
        // Verifica se o índice é válido
        if (indice_arg < info_funcao->num_parametros) {
            TipoVariavel tipo_parametro_esperado = info_funcao->tipos_params[indice_arg];
            
            // Verifica se os tipos são compatíveis
            if (tipo_argumento_fornecido != tipo_parametro_esperado) {
                printf("ERRO SEMANTICO: Argumento %d da funcao '%s' tem tipo incompativel. "
                       "Esperado tipo %d mas recebeu tipo %d (linha %d)\n",
                       indice_arg + 1, info_funcao->nome_funcao, 
                       tipo_parametro_esperado, tipo_argumento_fornecido, 
                       no_argumento->numero_linha);
                exit(1);
            }
        }
    }
}

/**
 * Processa uma lista de identificadores em uma declaração de variável.
 * 
 * Quando declaramos múltiplas variáveis do mesmo tipo (ex: int x, y, z;),
 * esta função processa cada identificador e insere na tabela de símbolos.
 * 
 * @param no_lista Nó contendo a lista de identificadores
 * @param tipo_herdado Tipo a ser atribuído a todos os identificadores
 */
void processar_declaracoes_variaveis(NoArvore *no_lista, TipoVariavel tipo_herdado) {
    if (!no_lista) return;
    
    if (no_lista->tipo_no == NO_IDENTIFICADOR) {
        // Processa um único identificador
        char *nome_var = no_lista->valor_texto;
        
        if (nome_var && buscar_variavel_escopo_local(nome_var) == NULL) {
            // Variável ainda não declarada neste escopo - insere
            inserir_variavel_escopo(nome_var, tipo_herdado, 0);
            no_lista->tipo_var = tipo_herdado;
        } else if (nome_var) {
            // Variável já existe no escopo atual - erro de redeclaração
            printf("ERRO SEMANTICO: Variavel '%s' ja foi declarada neste escopo (linha %d)\n", 
                   nome_var, no_lista->numero_linha);
            exit(1);
        }
    } else if (no_lista->tipo_no == NO_LISTA) {
        // Se é uma lista, processa cada elemento recursivamente
        for (int i = 0; i < no_lista->quantidade_filhos; i++) {
            if (no_lista->nos_filhos[i]) {
                processar_declaracoes_variaveis(no_lista->nos_filhos[i], tipo_herdado);
            }
        }
    }
}

/**
 * Conta o número de argumentos em uma chamada de função.
 * 
 * @param no Nó contendo os argumentos
 * @return Número total de argumentos
 */
int contar_numero_de_argumentos(NoArvore *no) {
    if (!no) return 0;
    
    if (no->tipo_no == NO_LISTA) {
        // Se é uma lista, soma recursivamente
        int total = 0;
        for (int i = 0; i < no->quantidade_filhos; i++) {
            total += contar_numero_de_argumentos(no->nos_filhos[i]);
        }
        return total;
    }
    
    // Se é um nó folha (identificador, constante ou expressão), conta como 1
    if (no->tipo_no == NO_IDENTIFICADOR || 
        no->tipo_no == NO_CONSTANTE || 
        no->tipo_no == NO_EXPRESSAO) {
        return 1;
    }
    
    return 0;
}

/**
 * Extrai o nó contendo a lista de parâmetros de uma função.
 * 
 * @param no_funcao Nó da função
 * @return Nó contendo os parâmetros ou NULL se não houver
 */
NoArvore *extrair_no_parametros(NoArvore *no_funcao) {
    if (no_funcao && no_funcao->quantidade_filhos > 0 && 
        no_funcao->nos_filhos[0] && 
        no_funcao->nos_filhos[0]->tipo_no == NO_FUNCAO) {
        
        NoArvore *funcao_interna = no_funcao->nos_filhos[0];
        
        if (funcao_interna->quantidade_filhos > 0 && 
            funcao_interna->nos_filhos[0] && 
            funcao_interna->nos_filhos[0]->tipo_no == NO_LISTA) {
            return funcao_interna->nos_filhos[0];
        }
    }
    return NULL;
}

/**
 * Insere os parâmetros formais de uma função na tabela de símbolos.
 * 
 * Os parâmetros são inseridos no escopo da função como variáveis especiais
 * (marcadas como parâmetros).
 * 
 * @param no_params Nó contendo a lista de parâmetros
 */
void inserir_parametros_na_tabela(NoArvore *no_params) {
    if (!no_params || no_params->tipo_no != NO_LISTA) return;
    
    // Percorre cada parâmetro
    for (int i = 0; i < no_params->quantidade_filhos; i++) {
        NoArvore *parametro = no_params->nos_filhos[i];
        
        if (parametro && parametro->tipo_no == NO_IDENTIFICADOR && parametro->valor_texto) {
            // Insere o parâmetro na tabela (flag eh_parametro = 1)
            inserir_variavel_escopo(parametro->valor_texto, parametro->tipo_var, 1);
        } else if (parametro && parametro->tipo_no == NO_LISTA) {
            // Se é uma lista aninhada, processa recursivamente
            inserir_parametros_na_tabela(parametro);
        }
    }
}

/**
 * Função principal do analisador semântico.
 * 
 * Inicializa a pilha de escopos, percorre toda a AST realizando
 * verificações semânticas e depois libera os recursos.
 * 
 * @param raiz Raiz da árvore sintática abstrata
 */
void executar_analise_semantica(NoArvore *raiz) {
    printf("\n=== Iniciando Analise Semantica ===\n");
    
    // Inicializa a pilha de tabelas de símbolos
    iniciar_pilha_escopos();
    
    // Cria um escopo global para variáveis e funções globais
    criar_novo_escopo();
    
    // Percorre a AST realizando as verificações
    percorrer_e_validar_no(raiz);
    
    // Libera a pilha de tabelas
    eliminar_pilha_escopos();
    
    printf("=== Analise Semantica Concluida com Sucesso ===\n\n");
}

/**
 * Função recursiva que percorre a AST e realiza verificações semânticas.
 * 
 * Para cada tipo de nó, realiza verificações específicas como:
 * - Checagem de tipos em expressões
 * - Validação de declarações
 * - Verificação de escopos
 * - Checagem de chamadas de função
 * 
 * @param raiz Nó atual da AST
 * @return Tipo resultante do nó (para propagação de tipos)
 */
TipoVariavel percorrer_e_validar_no(NoArvore *raiz) {
    if (!raiz) return TIPO_DESCONHECIDO;
    
    TipoVariavel tipo_resultado = TIPO_DESCONHECIDO;
    
    switch (raiz->tipo_no) {
        case NO_PROGRAMA: {
            // PRIMEIRA PASSAGEM: Registra todas as funções e variáveis globais
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                NoArvore *filho = raiz->nos_filhos[i];
                
                if (filho && filho->tipo_no == NO_FUNCAO && filho->valor_texto) {
                    // Verifica se a função já foi declarada
                    if (buscar_funcao_global(filho->valor_texto) != NULL) {
                        printf("ERRO SEMANTICO: Funcao '%s' ja foi declarada (linha %d)\n", 
                               filho->valor_texto, filho->numero_linha);
                        exit(1);
                    }
                    
                    // Extrai informações dos parâmetros
                    NoArvore* no_params = extrair_no_parametros(filho);
                    TipoVariavel tipos_params[MAX_ARGUMENTOS];
                    int num_params = 0;
                    
                    if(no_params) {
                        coletar_tipos_dos_parametros(no_params, tipos_params, &num_params);
                    }
                    
                    // Insere a função na tabela global
                    inserir_funcao_escopo(filho->valor_texto, filho->tipo_var, 
                                         num_params, tipos_params);
                    
                } else if (filho && filho->tipo_no == NO_DECL_VAR) {
                    // Processa declaração de variável global
                    percorrer_e_validar_no(filho);
                }
            }
            
            // SEGUNDA PASSAGEM: Analisa o corpo das funções e o programa principal
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i] && raiz->nos_filhos[i]->tipo_no != NO_DECL_VAR) {
                    percorrer_e_validar_no(raiz->nos_filhos[i]);
                }
            }
            break;
        }
        
        case NO_BLOCO: {
            // Cria um novo escopo ao entrar em um bloco
            criar_novo_escopo();
            
            // Processa todas as declarações e comandos do bloco
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if (raiz->nos_filhos[i]) {
                    percorrer_e_validar_no(raiz->nos_filhos[i]);
                }
            }
            
            // Remove o escopo ao sair do bloco
            remover_escopo_atual();
            break;
        }
        
        case NO_DECL_VAR: {
            // Declaração de variável(is)
            if (raiz->valor_texto) {
                // Verifica se já existe no escopo atual
                if (buscar_variavel_escopo_local(raiz->valor_texto) != NULL) {
                    printf("ERRO SEMANTICO: Variavel '%s' ja foi declarada neste escopo (linha %d)\n", 
                           raiz->valor_texto, raiz->numero_linha);
                    exit(1);
                }
                
                // Insere a primeira variável
                inserir_variavel_escopo(raiz->valor_texto, raiz->tipo_var, 0);
            }
            
            // Processa outras variáveis da mesma declaração
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if(raiz->nos_filhos[i]) {
                    processar_declaracoes_variaveis(raiz->nos_filhos[i], raiz->tipo_var);
                }
            }
            break;
        }
        
        case NO_FUNCAO: {
            if (raiz->valor_texto) {
                // É uma declaração de função
                criar_novo_escopo();
                
                // Salva o contexto da função
                nome_funcao_contexto = raiz->valor_texto;
                tipo_retorno_funcao_contexto = raiz->tipo_var;
                
                // Insere os parâmetros formais no escopo da função
                inserir_parametros_na_tabela(extrair_no_parametros(raiz));
                
                // Analisa o corpo da função
                for (int i = 0; i < raiz->quantidade_filhos; i++) {
                    if (raiz->nos_filhos[i]) {
                        percorrer_e_validar_no(raiz->nos_filhos[i]);
                    }
                }
                
                // Remove o escopo e restaura o contexto
                remover_escopo_atual();
                nome_funcao_contexto = NULL;
                tipo_retorno_funcao_contexto = TIPO_DESCONHECIDO;
            } else {
                // É apenas a estrutura da função (parâmetros + bloco)
                for (int i = 0; i < raiz->quantidade_filhos; i++) {
                    if (raiz->nos_filhos[i]) {
                        percorrer_e_validar_no(raiz->nos_filhos[i]);
                    }
                }
            }
            break;
        }
        
        case NO_IDENTIFICADOR: {
            // Uso de um identificador - verifica se foi declarado
            if (!raiz->valor_texto) return TIPO_DESCONHECIDO;
            
            // Primeiro tenta encontrar como variável
            RegistroVariavel* var = buscar_simbolo_global(raiz->valor_texto);
            if (var) {
                tipo_resultado = var->tipo_simbolo;
            } else {
                // Se não é variável, tenta encontrar como função
                RegistroFuncao* func = buscar_funcao_global(raiz->valor_texto);
                if (func) {
                    tipo_resultado = func->tipo_retorno_funcao;
                } else {
                    // Não foi declarado - erro
                    printf("ERRO SEMANTICO: Identificador '%s' nao foi declarado (linha %d)\n", 
                           raiz->valor_texto, raiz->numero_linha);
                    exit(1);
                }
            }
            
            // Atualiza o tipo no nó
            raiz->tipo_var = tipo_resultado;
            break;
        }
        
        case NO_CONSTANTE: {
            // Constante já tem tipo definido
            tipo_resultado = raiz->tipo_var;
            break;
        }
        
        case NO_COMANDO: {
            if (!raiz->valor_texto) break;
            
            if (strcmp(raiz->valor_texto, "retorne") == 0) {
                // Comando return - verifica se o tipo retornado é compatível
                TipoVariavel tipo_retorno = TIPO_VAZIO;
                
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                    tipo_retorno = percorrer_e_validar_no(raiz->nos_filhos[0]);
                }
                
                // Verifica compatibilidade com o tipo declarado da função
                if (tipo_retorno_funcao_contexto != TIPO_DESCONHECIDO && 
                    tipo_retorno != tipo_retorno_funcao_contexto) {
                    printf("ERRO SEMANTICO: Tipo de retorno incompativel na funcao '%s' (linha %d)\n", 
                           nome_funcao_contexto, raiz->numero_linha);
                    exit(1);
                }
            } else {
                // Outros comandos - apenas processa os filhos
                for(int i = 0; i < raiz->quantidade_filhos; ++i) {
                    if(raiz->nos_filhos[i]) {
                        percorrer_e_validar_no(raiz->nos_filhos[i]);
                    }
                }
            }
            break;
        }
        
        case NO_EXPRESSAO: {
            if (!raiz->valor_texto) {
                tipo_resultado = TIPO_DESCONHECIDO;
                break;
            }
            
            // Verifica se é uma chamada de função (identificada pelo nome no valor_texto)
            // Se o primeiro filho é um ID e não há operador, é chamada de função
            RegistroFuncao* func_chamada = buscar_funcao_global(raiz->valor_texto);
            
            if (func_chamada != NULL) {
                // É uma chamada de função
                
                // Obtém os argumentos (se houver)
                NoArvore* no_args = (raiz->quantidade_filhos > 0) ? raiz->nos_filhos[0] : NULL;
                int num_args_fornecidos = contar_numero_de_argumentos(no_args);
                
                // Verifica se o número de argumentos está correto
                if (num_args_fornecidos != func_chamada->num_parametros) {
                    printf("ERRO SEMANTICO: Funcao '%s' espera %d argumento(s), "
                           "mas recebeu %d (linha %d)\n",
                           func_chamada->nome_funcao, func_chamada->num_parametros, 
                           num_args_fornecidos, raiz->numero_linha);
                    exit(1);
                }
                
                // Valida os tipos dos argumentos
                if (no_args) {
                    validar_tipos_dos_argumentos(no_args, func_chamada, 0);
                }
                
                tipo_resultado = func_chamada->tipo_retorno_funcao;
                
            } else if (strcmp(raiz->valor_texto, "=") == 0) {
                // É uma atribuição
                if (raiz->quantidade_filhos < 2 || 
                    !raiz->nos_filhos[0] || 
                    !raiz->nos_filhos[1] || 
                    raiz->nos_filhos[0]->tipo_no != NO_IDENTIFICADOR) {
                    printf("ERRO SEMANTICO: Atribuicao invalida (linha %d)\n", 
                           raiz->numero_linha);
                    exit(1);
                }
                
                // Obtém os tipos dos dois lados da atribuição
                TipoVariavel tipo_esquerda = percorrer_e_validar_no(raiz->nos_filhos[0]);
                TipoVariavel tipo_direita = percorrer_e_validar_no(raiz->nos_filhos[1]);
                
                // Verifica compatibilidade de tipos
                if (tipo_esquerda != tipo_direita) {
                    printf("ERRO SEMANTICO: Atribuicao com tipos incompativeis (linha %d)\n", 
                           raiz->numero_linha);
                    exit(1);
                }
                
                tipo_resultado = tipo_esquerda;
                
            } else {
                // É uma expressão aritmética, relacional ou lógica
                if (raiz->quantidade_filhos > 0 && raiz->nos_filhos[0]) {
                    tipo_resultado = percorrer_e_validar_no(raiz->nos_filhos[0]);
                }
                if (raiz->quantidade_filhos > 1 && raiz->nos_filhos[1]) {
                    percorrer_e_validar_no(raiz->nos_filhos[1]);
                }
                
                // Expressões resultam em tipo int (incluindo comparações e lógicas)
                tipo_resultado = TIPO_INTEIRO;
            }
            
            raiz->tipo_var = tipo_resultado;
            break;
        }
        
        default: {
            // Para outros tipos de nós, apenas percorre os filhos
            for (int i = 0; i < raiz->quantidade_filhos; i++) {
                if(raiz->nos_filhos[i]) {
                    percorrer_e_validar_no(raiz->nos_filhos[i]);
                }
            }
            break;
        }
    }
    
    return tipo_resultado;
}
