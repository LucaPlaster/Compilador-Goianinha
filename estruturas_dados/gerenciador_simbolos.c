#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/gerenciador_simbolos.h"

/**
 * Variável global que mantém a pilha de escopos.
 * Esta pilha permite gerenciar múltiplos níveis de escopo aninhados.
 */
PilhaEscopos pilha_simbolos_global;

/**
 * Inicializa uma tabela de símbolos vazia.
 * Zera todos os contadores e prepara a estrutura para uso.
 * 
 * @param tabela Ponteiro para a tabela a ser inicializada
 */
void inicializar_tabela_escopo(TabelaEscopo* tabela) {
    tabela->contador_variaveis = 0;
    tabela->contador_funcoes = 0;
    tabela->offset_atual = 0;
}

/**
 * Adiciona uma nova função à tabela de símbolos.
 * 
 * Esta função armazena informações sobre uma função declarada, incluindo
 * seu nome, tipo de retorno e os tipos de seus parâmetros.
 * 
 * @param tabela Tabela onde a função será inserida
 * @param nome Nome da função
 * @param tipo_ret Tipo de retorno da função
 * @param num_params Número de parâmetros que a função recebe
 * @param tipos Array com os tipos de cada parâmetro
 */
void adicionar_funcao_tabela(TabelaEscopo* tabela, const char* nome, 
                              TipoVariavel tipo_ret, int num_params, 
                              TipoVariavel* tipos) {
    // Verifica se ainda há espaço na tabela
    if (tabela->contador_funcoes >= MAX_FUNCOES) {
        fprintf(stderr, "ERRO: Tabela de funções cheia\n");
        exit(1);
    }
    
    // Obtém referência para a próxima posição livre
    RegistroFuncao* nova_funcao = &tabela->registros_funcoes[tabela->contador_funcoes];
    
    // Copia o nome da função
    strncpy(nova_funcao->nome_funcao, nome, TAMANHO_NOME - 1);
    nova_funcao->nome_funcao[TAMANHO_NOME - 1] = '\0';
    
    // Define o tipo de retorno e número de parâmetros
    nova_funcao->tipo_retorno_funcao = tipo_ret;
    nova_funcao->num_parametros = num_params;
    
    // Copia os tipos dos parâmetros
    for (int i = 0; i < num_params && i < MAX_ARGUMENTOS; i++) {
        nova_funcao->tipos_params[i] = tipos[i];
    }
    
    // Incrementa o contador de funções
    tabela->contador_funcoes++;
}

/**
 * Busca uma variável na tabela de símbolos pelo nome.
 * 
 * Realiza busca linear no array de variáveis.
 * 
 * @param tabela Tabela onde buscar
 * @param nome Nome da variável a buscar
 * @return Ponteiro para o registro da variável ou NULL se não encontrada
 */
RegistroVariavel* procurar_variavel_tabela(TabelaEscopo* tabela, const char* nome) {
    // Percorre todas as variáveis da tabela
    for (int i = 0; i < tabela->contador_variaveis; i++) {
        if (strcmp(tabela->registros_variaveis[i].nome_identificador, nome) == 0) {
            return &tabela->registros_variaveis[i];
        }
    }
    return NULL;  // Não encontrada
}

/**
 * Busca uma função na tabela de símbolos pelo nome.
 * 
 * @param tabela Tabela onde buscar
 * @param nome Nome da função a buscar
 * @return Ponteiro para o registro da função ou NULL se não encontrada
 */
RegistroFuncao* procurar_funcao_tabela(TabelaEscopo* tabela, const char* nome) {
    // Percorre todas as funções da tabela
    for (int i = 0; i < tabela->contador_funcoes; i++) {
        if (strcmp(tabela->registros_funcoes[i].nome_funcao, nome) == 0) {
            return &tabela->registros_funcoes[i];
        }
    }
    return NULL;  // Não encontrada
}

/**
 * Inicializa a pilha global de escopos.
 * Deve ser chamada antes de iniciar a análise semântica.
 */
void iniciar_pilha_escopos() {
    pilha_simbolos_global.indice_topo = -1;  // Pilha vazia
}

/**
 * Libera toda a memória alocada para a pilha de escopos.
 * Deve ser chamada ao final da compilação.
 */
void eliminar_pilha_escopos() {
    // Libera todos os escopos que ainda estão na pilha
    while (pilha_simbolos_global.indice_topo >= 0) {
        free(pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo]);
        pilha_simbolos_global.indice_topo--;
    }
}

/**
 * Cria um novo escopo e o empilha na pilha.
 * Chamada ao entrar em um novo bloco ou função.
 */
void criar_novo_escopo() {
    // Verifica se há espaço na pilha
    if (pilha_simbolos_global.indice_topo >= MAX_ESCOPOS - 1) {
        fprintf(stderr, "ERRO: Pilha de escopos cheia\n");
        exit(1);
    }
    
    // Aloca memória para o novo escopo
    TabelaEscopo* novo_escopo = (TabelaEscopo*)malloc(sizeof(TabelaEscopo));
    if (!novo_escopo) {
        fprintf(stderr, "ERRO: Falha ao alocar memória para novo escopo\n");
        exit(1);
    }
    
    // Inicializa o novo escopo
    inicializar_tabela_escopo(novo_escopo);
    
    // Empilha o novo escopo
    pilha_simbolos_global.indice_topo++;
    pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo] = novo_escopo;
}

/**
 * Remove o escopo do topo da pilha.
 * Chamada ao sair de um bloco.
 */
void remover_escopo_atual() {
    // Verifica se há escopos para remover
    if (pilha_simbolos_global.indice_topo < 0) {
        fprintf(stderr, "ERRO: Tentativa de remover escopo de pilha vazia\n");
        exit(1);
    }
    
    // Libera o escopo do topo
    free(pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo]);
    pilha_simbolos_global.indice_topo--;
}

/**
 * Insere uma nova variável no escopo atual (topo da pilha).
 * 
 * @param nome Nome da variável
 * @param tipo Tipo da variável (int ou car)
 * @param eh_param Flag indicando se é parâmetro de função
 */
void inserir_variavel_escopo(char* nome, TipoVariavel tipo, int eh_param) {
    // Verifica se há um escopo ativo
    if (pilha_simbolos_global.indice_topo < 0) {
        fprintf(stderr, "ERRO: Nenhum escopo ativo para inserir variável\n");
        exit(1);
    }
    
    // Obtém o escopo do topo
    TabelaEscopo* escopo_atual = pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo];
    
    // Verifica se há espaço na tabela
    if (escopo_atual->contador_variaveis >= MAX_VARIAVEIS) {
        fprintf(stderr, "ERRO: Tabela de variáveis cheia no escopo atual\n");
        exit(1);
    }
    
    // Obtém referência para a próxima posição livre
    RegistroVariavel* nova_var = &escopo_atual->registros_variaveis[escopo_atual->contador_variaveis];
    
    // Preenche os campos da variável
    strncpy(nova_var->nome_identificador, nome, TAMANHO_NOME - 1);
    nova_var->nome_identificador[TAMANHO_NOME - 1] = '\0';
    nova_var->tipo_simbolo = tipo;
    nova_var->eh_parametro = eh_param;
    nova_var->posicao_memoria = escopo_atual->offset_atual;
    
    // Incrementa contadores
    escopo_atual->contador_variaveis++;
    escopo_atual->offset_atual++;
}

/**
 * Insere uma função no escopo atual.
 * 
 * @param nome Nome da função
 * @param tipo_ret Tipo de retorno da função
 * @param num_params Número de parâmetros
 * @param tipos_params Array com os tipos dos parâmetros
 */
void inserir_funcao_escopo(char* nome, TipoVariavel tipo_ret, 
                           int num_params, TipoVariavel* tipos_params) {
    // Verifica se há um escopo ativo
    if (pilha_simbolos_global.indice_topo < 0) {
        fprintf(stderr, "ERRO: Nenhum escopo ativo para inserir função\n");
        exit(1);
    }
    
    // Obtém o escopo do topo
    TabelaEscopo* escopo_atual = pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo];
    
    // Adiciona a função à tabela
    adicionar_funcao_tabela(escopo_atual, nome, tipo_ret, num_params, tipos_params);
}

/**
 * Busca um símbolo (variável) em todos os escopos da pilha.
 * 
 * A busca começa do topo (escopo mais interno) e vai até a base (escopo global).
 * Isso implementa a regra de sombreamento: variáveis locais sobrepõem globais.
 * 
 * @param nome Nome do símbolo a buscar
 * @return Ponteiro para o registro da variável ou NULL se não encontrada
 */
RegistroVariavel* buscar_simbolo_global(char* nome) {
    // Busca do topo para a base da pilha
    for (int i = pilha_simbolos_global.indice_topo; i >= 0; i--) {
        RegistroVariavel* resultado = procurar_variavel_tabela(
            pilha_simbolos_global.escopos[i], nome
        );
        if (resultado) {
            return resultado;
        }
    }
    return NULL;  // Não encontrada em nenhum escopo
}

/**
 * Busca uma função em todos os escopos da pilha.
 * 
 * @param nome Nome da função a buscar
 * @return Ponteiro para o registro da função ou NULL se não encontrada
 */
RegistroFuncao* buscar_funcao_global(char* nome) {
    // Busca do topo para a base da pilha
    for (int i = pilha_simbolos_global.indice_topo; i >= 0; i--) {
        RegistroFuncao* resultado = procurar_funcao_tabela(
            pilha_simbolos_global.escopos[i], nome
        );
        if (resultado) {
            return resultado;
        }
    }
    return NULL;  // Não encontrada em nenhum escopo
}

/**
 * Busca uma variável apenas no escopo atual (topo da pilha).
 * 
 * Útil para verificar redeclaração de variáveis no mesmo escopo.
 * 
 * @param nome Nome da variável
 * @return Ponteiro para o registro ou NULL se não encontrada
 */
RegistroVariavel* buscar_variavel_escopo_local(const char* nome) {
    // Verifica se há escopo ativo
    if (pilha_simbolos_global.indice_topo < 0) {
        return NULL;
    }
    
    // Busca apenas no escopo do topo
    return procurar_variavel_tabela(
        pilha_simbolos_global.escopos[pilha_simbolos_global.indice_topo], 
        nome
    );
}
