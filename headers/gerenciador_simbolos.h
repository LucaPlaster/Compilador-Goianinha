
#ifndef GERENCIADOR_SIMBOLOS_H
#define GERENCIADOR_SIMBOLOS_H

#include "tipos_dados.h"

#define TAMANHO_NOME 64
#define MAX_VARIAVEIS 100
#define MAX_FUNCOES 100
#define MAX_ESCOPOS 100
#define MAX_ARGUMENTOS 10

/**
 * Estrutura que representa uma entrada na tabela de símbolos para variáveis/parâmetros.
 * 
 * Armazena informações sobre:
 * - nome_identificador: Nome da variável ou parâmetro
 * - tipo_simbolo: Tipo de dado (int ou car)
 * - posicao_memoria: Posição/offset para geração de código
 * - eh_parametro: Flag indicando se é parâmetro de função
 */
typedef struct {
    char nome_identificador[TAMANHO_NOME];
    TipoVariavel tipo_simbolo;
    int posicao_memoria;
    int eh_parametro;
} RegistroVariavel;

/**
 * Estrutura que representa uma função na tabela de símbolos.
 * 
 * Armazena informações sobre:
 * - nome_funcao: Nome da função
 * - tipo_retorno_funcao: Tipo que a função retorna
 * - num_parametros: Quantidade de parâmetros que a função recebe
 * - tipos_params: Array com os tipos de cada parâmetro
 */
typedef struct {
    char nome_funcao[TAMANHO_NOME];
    TipoVariavel tipo_retorno_funcao;
    int num_parametros;
    TipoVariavel tipos_params[MAX_ARGUMENTOS];
} RegistroFuncao;

/**
 * Estrutura que representa uma tabela de símbolos (um escopo).
 * 
 * Cada escopo mantém:
 * - registros_variaveis: Array de variáveis/parâmetros declarados neste escopo
 * - contador_variaveis: Número de variáveis neste escopo
 * - offset_atual: Offset de memória para próxima variável
 * - registros_funcoes: Array de funções declaradas neste escopo
 * - contador_funcoes: Número de funções neste escopo
 */
typedef struct {
    RegistroVariavel registros_variaveis[MAX_VARIAVEIS];
    int contador_variaveis;
    int offset_atual;
    
    RegistroFuncao registros_funcoes[MAX_FUNCOES];
    int contador_funcoes;
} TabelaEscopo;

/**
 * Estrutura que representa a pilha de tabelas de símbolos.
 * 
 * A pilha permite gerenciar múltiplos escopos aninhados:
 * - escopos: Array de ponteiros para tabelas de símbolos
 * - indice_topo: Índice do topo da pilha
 */
typedef struct {
    TabelaEscopo* escopos[MAX_ESCOPOS];
    int indice_topo;
} PilhaEscopos;

/**
 * Inicializa uma tabela de símbolos vazia.
 * 
 * @param tabela Ponteiro para a tabela a ser inicializada
 */
void inicializar_tabela_escopo(TabelaEscopo* tabela);

/**
 * Adiciona uma função à tabela de símbolos.
 * 
 * @param tabela Tabela onde a função será inserida
 * @param nome Nome da função
 * @param tipo_ret Tipo de retorno da função
 * @param num_params Número de parâmetros
 * @param tipos Array com os tipos dos parâmetros
 */
void adicionar_funcao_tabela(TabelaEscopo* tabela, const char* nome, 
                              TipoVariavel tipo_ret, int num_params, 
                              TipoVariavel* tipos);

/**
 * Busca uma variável na tabela de símbolos pelo nome.
 * 
 * @param tabela Tabela onde buscar
 * @param nome Nome da variável a buscar
 * @return Ponteiro para o registro da variável ou NULL se não encontrada
 */
RegistroVariavel* procurar_variavel_tabela(TabelaEscopo* tabela, const char* nome);

/**
 * Busca uma função na tabela de símbolos pelo nome.
 * 
 * @param tabela Tabela onde buscar
 * @param nome Nome da função a buscar
 * @return Ponteiro para o registro da função ou NULL se não encontrada
 */
RegistroFuncao* procurar_funcao_tabela(TabelaEscopo* tabela, const char* nome);

/**
 * Inicializa a pilha global de tabelas de símbolos.
 * Deve ser chamada no início da compilação.
 */
void iniciar_pilha_escopos();

/**
 * Libera toda a memória da pilha de tabelas de símbolos.
 * Deve ser chamada ao final da compilação.
 */
void eliminar_pilha_escopos();

/**
 * Cria um novo escopo e o empilha na pilha de tabelas.
 * Chamada ao entrar em um novo bloco.
 */
void criar_novo_escopo();

/**
 * Remove o escopo do topo da pilha.
 * Chamada ao sair de um bloco.
 */
void remover_escopo_atual();

/**
 * Insere uma variável no escopo atual.
 * 
 * @param nome Nome da variável
 * @param tipo Tipo da variável
 * @param eh_param Flag indicando se é parâmetro
 */
void inserir_variavel_escopo(char* nome, TipoVariavel tipo, int eh_param);

/**
 * Insere uma função no escopo atual.
 * 
 * @param nome Nome da função
 * @param tipo_ret Tipo de retorno
 * @param num_params Número de parâmetros
 * @param tipos_params Array com tipos dos parâmetros
 */
void inserir_funcao_escopo(char* nome, TipoVariavel tipo_ret, 
                           int num_params, TipoVariavel* tipos_params);

/**
 * Busca um símbolo (variável) em todos os escopos da pilha.
 * Começa do topo e vai em direção à base.
 * 
 * @param nome Nome do símbolo a buscar
 * @return Ponteiro para o registro ou NULL se não encontrado
 */
RegistroVariavel* buscar_simbolo_global(char* nome);

/**
 * Busca uma função em todos os escopos da pilha.
 * 
 * @param nome Nome da função a buscar
 * @return Ponteiro para o registro ou NULL se não encontrada
 */
RegistroFuncao* buscar_funcao_global(char* nome);

/**
 * Busca uma variável apenas no escopo atual (topo da pilha).
 * 
 * @param nome Nome da variável
 * @return Ponteiro para o registro ou NULL se não encontrada
 */
RegistroVariavel* buscar_variavel_escopo_local(const char* nome);

/**
 * Variável global que mantém a pilha de escopos.
 * Usada por todas as funções de gerenciamento de símbolos.
 */
extern PilhaEscopos pilha_simbolos_global;

#endif
