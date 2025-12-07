# Compilador para a Linguagem Goianinha

## 📋 Sumário

- [Visão Geral](#-visão-geral)
- [Estrutura do Projeto](#-estrutura-do-projeto)
- [Pré-requisitos](#-pré-requisitos)
- [Como Compilar](#-como-compilar)
- [Como Executar](#-como-executar)
- [Como Testar](#-como-testar)
- [Descrição dos Módulos](#-descrição-dos-módulos)
- [Gramática da Linguagem](#-gramática-da-linguagem)
- [Exemplos de Código](#-exemplos-de-código)
- [Arquitetura do Compilador](#-arquitetura-do-compilador)
- [Geração de Código MIPS](#-geração-de-código-mips)

---

## 📖 Visão Geral

Este projeto implementa um **compilador completo** para a linguagem de programação didática **Goianinha**. O compilador foi desenvolvido como parte de um projeto acadêmico da disciplina de Compiladores e implementa todas as fases clássicas da compilação:

1. **Análise Léxica**: Reconhecimento de tokens usando Flex
2. **Análise Sintática**: Parsing e construção da AST usando Bison
3. **Análise Semântica**: Verificação de tipos, escopos e regras semânticas
4. **Geração de Código**: Tradução para Assembly MIPS

---

## 📂 Estrutura do Projeto

```
compilador_goianinha/
│
├── headers/                          # Arquivos de cabeçalho (.h)
│   ├── tipos_dados.h                # Definições de tipos e enumerações
│   ├── arvore_sintatica.h           # Estrutura da AST
│   ├── gerenciador_simbolos.h       # Tabela de símbolos e pilha de escopos
│   ├── analisador_semantico.h       # Interface do analisador semântico
│   └── gerador_mips.h               # Interface do gerador de código
│
├── lexico_sintatico/                # Análise léxica e sintática
│   ├── goianinha.l                  # Especificação Flex (analisador léxico)
│   ├── goianinha.y                  # Especificação Bison (analisador sintático)
│   └── main.c                       # Função main do compilador
│
├── estruturas_dados/                # Implementações das estruturas de dados
│   ├── arvore_sintatica.c           # Implementação da AST
│   └── gerenciador_simbolos.c       # Implementação da tabela de símbolos
│
├── analisador_semantico/            # Análise semântica
│   └── analisador_semantico.c       # Verificação de tipos e escopos
│
├── gerador_mips/                    # Geração de código MIPS
│   └── gerador_mips.c               # Tradutor AST → Assembly MIPS
│
├── testes/                          # Arquivos de teste (.g)
│   ├── teste01_programa_simples.g
│   ├── teste02_funcao_simples.g
│   ├── ...
│   └── erro01_variavel_nao_declarada.g
│
├── saidas/                          # Saídas da compilação (criado por make test)
├── mips_gerado/                     # Códigos MIPS gerados (criado por make test)
├── Makefile                         # Script de compilação
└── README.md                        # Este arquivo

```

---

## 🔧 Pré-requisitos

Para compilar e executar este projeto, você precisa ter instalado:

- **GCC** (GNU Compiler Collection) versão 7.0 ou superior
- **Flex** (Fast Lexical Analyzer) versão 2.6.0 ou superior
- **Bison** (GNU Parser Generator) versão 3.0 ou superior
- **Make** (GNU Make)
- **SPIM** (opcional, para executar o código MIPS gerado)

### Instalação no Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install build-essential flex bison spim
```

### Verificação das Versões

```bash
gcc --version
flex --version
bison --version
make --version
```

---

## 🔨 Como Compilar

O projeto utiliza um **Makefile** para automatizar o processo de compilação.

### Compilação Completa

Na raiz do projeto, execute:

```bash
make
```

Este comando irá:
1. Gerar o analisador léxico a partir de `goianinha.l` usando Flex
2. Gerar o analisador sintático a partir de `goianinha.y` usando Bison
3. Compilar todos os arquivos `.c`
4. Gerar o executável `goianinha`

### Limpeza de Arquivos Gerados

Para remover todos os arquivos gerados pela compilação:

```bash
make clean
```

---

## 🚀 Como Executar

Após compilar o projeto, você pode usar o compilador da seguinte forma:

### Sintaxe Básica

```bash
./goianinha <arquivo_fonte.g> [arquivo_saida.asm]
```

- **`arquivo_fonte.g`**: Arquivo com código fonte em Goianinha (obrigatório)
- **`arquivo_saida.asm`**: Arquivo de saída em Assembly MIPS (opcional)

### Exemplos de Uso

**1. Compilar e mostrar código MIPS na tela:**

```bash
./goianinha testes/teste01_programa_simples.g
```

**2. Compilar e salvar código MIPS em arquivo:**

```bash
./goianinha testes/teste02_funcao_simples.g saida.asm
```

**3. Compilar e executar no SPIM:**

```bash
./goianinha testes/teste03_expressoes_aritmeticas.g programa.asm
spim -file programa.asm
```

---

## 🧪 Como Testar

O projeto inclui uma suite abrangente de testes que pode ser executada automaticamente.

### Executar Todos os Testes

```bash
make test
```

Este comando irá:
1. Compilar o compilador (se necessário)
2. Criar os diretórios `saidas/` e `mips_gerado/`
3. Executar o compilador para cada arquivo `.g` na pasta `testes/`
4. Salvar a saída de cada compilação em `saidas/`
5. Salvar o código MIPS gerado em `mips_gerado/`

### Interpretar os Resultados

Após executar os testes:

- **Arquivos em `saidas/`**: Contêm a saída completa da compilação, incluindo:
  - Mensagens de cada fase (léxica, sintática, semântica)
  - A estrutura da AST
  - Mensagens de erro (se houver)

- **Arquivos em `mips_gerado/`**: Contêm o código Assembly MIPS gerado (se a compilação foi bem-sucedida)

### Testes Incluídos

#### Testes de Casos Válidos

| Teste | Descrição |
|-------|-----------|
| `teste01` | Programa simples com declarações básicas |
| `teste02` | Função com parâmetros e retorno |
| `teste03` | Expressões aritméticas complexas |
| `teste04` | Comando condicional if-then |
| `teste05` | Comando condicional if-then-else |
| `teste06` | Laço while |
| `teste07` | Múltiplas funções |
| `teste08` | Variáveis globais e locais |
| `teste09` | Operadores relacionais |
| `teste10` | Operadores lógicos |
| `teste11` | Blocos aninhados |
| `teste12` | Sombreamento de variáveis |
| `teste13` | Comentários |
| `teste14` | Strings e caracteres |
| `teste15` | Função recursiva (fatorial) |
| `teste16` | Condicionais aninhados |
| `teste17` | Laços aninhados |
| `teste18` | Função sem parâmetros |
| `teste19` | Expressões com negação |
| `teste20` | Programa completo com múltiplos recursos |

#### Testes de Casos de Erro

| Teste | Erro Esperado |
|-------|---------------|
| `erro01` | Uso de variável não declarada |
| `erro02` | Redeclaração de variável |
| `erro03` | Tipos incompatíveis em atribuição |
| `erro04` | Chamada de função não declarada |
| `erro05` | Número incorreto de argumentos |

---

## 📦 Descrição dos Módulos

### 1. Headers (headers/)

#### `tipos_dados.h`
Define os tipos de dados e enumerações usados em todo o compilador:
- `TipoVariavel`: Tipos suportados (int, car, void, etc.)
- `TipoNo`: Tipos de nós da AST

#### `arvore_sintatica.h`
Define a estrutura da Árvore Sintática Abstrata (AST):
- `NoArvore`: Estrutura de um nó da AST
- Funções para criar, exibir e liberar a AST

#### `gerenciador_simbolos.h`
Define as estruturas para gerenciamento de símbolos:
- `RegistroVariavel`: Informações sobre variáveis
- `RegistroFuncao`: Informações sobre funções
- `TabelaEscopo`: Tabela de símbolos de um escopo
- `PilhaEscopos`: Pilha para gerenciar múltiplos escopos

#### `analisador_semantico.h`
Interface do analisador semântico:
- `executar_analise_semantica()`: Função principal

#### `gerador_mips.h`
Interface do gerador de código:
- `gerar_codigo_assembly_mips()`: Função principal

---

### 2. Léxico e Sintático (lexico_sintatico/)

#### `goianinha.l` (Flex)
Especifica as regras léxicas:
- Palavras reservadas (programa, int, car, se, enquanto, etc.)
- Identificadores e constantes
- Operadores (aritméticos, relacionais, lógicos)
- Tratamento de comentários e strings
- Detecção de erros léxicos

**Principais recursos:**
- Estados exclusivos para processar comentários (`/*...*/`) e strings (`"..."`)
- Detecção de comentários não terminados
- Detecção de strings que ocupam múltiplas linhas
- Contagem automática de linhas para mensagens de erro

#### `goianinha.y` (Bison)
Especifica a gramática da linguagem e constrói a AST:
- Declarações de funções e variáveis
- Comandos (if, while, return, read, write, etc.)
- Expressões (com precedência correta de operadores)
- Ações semânticas para construção da AST

**Características importantes:**
- Gramática completa conforme especificação
- Construção bottom-up da AST
- Tratamento de erros sintáticos

#### `main.c`
Função principal que orquestra todas as fases:
1. Abre o arquivo fonte
2. Chama `yyparse()` para análise léxica/sintática
3. Exibe a AST construída
4. Executa a análise semântica
5. Gera o código MIPS
6. Libera recursos

---

### 3. Estruturas de Dados (estruturas_dados/)

#### `arvore_sintatica.c`
Implementa as funções para manipulação da AST:

- **`construir_no_arvore()`**: Cria um novo nó da AST usando argumentos variádicos (`va_list`)
- **`exibir_arvore()`**: Imprime a AST de forma hierárquica com indentação
- **`desalocar_arvore()`**: Libera recursivamente toda a memória da AST

**Detalhes de implementação:**
- Uso de `malloc` para alocação dinâmica
- Armazenamento de informações de tipo e linha em cada nó
- Estrutura genérica que suporta diferentes tipos de nós

#### `gerenciador_simbolos.c`
Implementa o sistema de tabelas de símbolos:

**Funções principais:**
- **`iniciar_pilha_escopos()`**: Inicializa a pilha vazia
- **`criar_novo_escopo()`**: Cria e empilha um novo escopo
- **`remover_escopo_atual()`**: Desempilha o escopo do topo
- **`inserir_variavel_escopo()`**: Adiciona variável ao escopo atual
- **`inserir_funcao_escopo()`**: Adiciona função ao escopo atual
- **`buscar_simbolo_global()`**: Busca símbolo do topo para a base
- **`buscar_variavel_escopo_local()`**: Busca apenas no escopo atual

**Características:**
- Pilha de tabelas para suportar escopos aninhados
- Sombreamento de variáveis (escopo interno sobrepõe externo)
- Armazenamento de informações de tipo e posição para geração de código
- Tratamento especial para parâmetros de função

---

### 4. Analisador Semântico (analisador_semantico/)

#### `analisador_semantico.c`
Realiza todas as verificações semânticas:

**Verificações implementadas:**

1. **Declarações antes do uso**
   - Verifica se variáveis/funções foram declaradas antes de serem usadas
   - Reporta erro se identificador não existe

2. **Redeclaração de símbolos**
   - Verifica se há redeclaração de variável no mesmo escopo
   - Permite sombreamento em escopos diferentes

3. **Checagem de tipos**
   - Verifica compatibilidade em atribuições
   - Verifica tipos em expressões aritméticas/lógicas
   - Verifica tipo de retorno de funções

4. **Chamadas de função**
   - Verifica se função foi declarada
   - Verifica número correto de argumentos
   - Verifica tipos dos argumentos (compatibilidade com parâmetros formais)

5. **Regras de escopo**
   - Gerencia criação e remoção de escopos
   - Implementa regras de visibilidade

**Função principal:**
```c
TipoVariavel percorrer_e_validar_no(NoArvore *raiz)
```
Percorre recursivamente a AST e realiza verificações em cada nó.

---

### 5. Gerador de Código (gerador_mips/)

#### `gerador_mips.c`
Gera código Assembly MIPS a partir da AST:

**Código gerado:**

1. **Estrutura do programa**
   - Seção `.data` para strings e constantes
   - Seção `.text` para o código
   - Label `main` como ponto de entrada

2. **Funções**
   - Prólogo: salva `$ra` e `$fp`, ajusta `$sp`
   - Corpo da função
   - Epílogo: restaura registradores e retorna

3. **Comandos**
   - `escreva`: syscall 1 (print_int) ou 4 (print_string)
   - `novalinha`: syscall 4 com string "\n"
   - `se/senao`: branches condicionais com labels
   - `enquanto`: loops com labels de início e fim
   - `retorne`: move resultado para `$v0` e salta para epílogo

4. **Expressões**
   - Operadores aritméticos: add, sub, mul, div
   - Operadores relacionais: slt, sgt, seq, sne, sle, sge
   - Operadores lógicos: and, or, negação
   - Atribuição: sw no frame pointer

5. **Variáveis**
   - Alocação na pilha (frame pointer)
   - Load/Store usando offsets negativos

**Convenções usadas:**
- `$t0-$t2`: Temporários para cálculos
- `$fp`: Frame pointer (base do frame atual)
- `$sp`: Stack pointer (topo da pilha)
- `$v0`: Resultado de funções e syscalls
- `$a0`: Argumento para syscalls
- `$ra`: Return address

---

## 📝 Gramática da Linguagem

### Estrutura Geral

```
Programa → DeclFuncVar DeclProg

DeclFuncVar → Tipo id DeclVar; DeclFuncVar
            | Tipo id DeclFunc DeclFuncVar
            | ε

DeclProg → programa Bloco
```

### Tipos

```
Tipo → int | car
```

### Funções

```
DeclFunc → ( ListaParametros ) Bloco

ListaParametros → ε
                | Tipo id
                | Tipo id, ListaParametros
```

### Blocos e Comandos

```
Bloco → { ListaDeclVar ListaComando }

Comando → ;
        | Expr;
        | retorne Expr;
        | leia id;
        | escreva Expr;
        | escreva "string";
        | novalinha;
        | se ( Expr ) entao Comando
        | se ( Expr ) entao Comando senao Comando
        | enquanto ( Expr ) execute Comando
        | Bloco
```

### Expressões

A gramática de expressões implementa precedência correta:

```
Expr → OrExpr | id = Expr

OrExpr → OrExpr ou AndExpr | AndExpr

AndExpr → AndExpr e EqExpr | EqExpr

EqExpr → EqExpr == DesigExpr | EqExpr != DesigExpr | DesigExpr

DesigExpr → DesigExpr < AddExpr | DesigExpr > AddExpr
          | DesigExpr >= AddExpr | DesigExpr <= AddExpr | AddExpr

AddExpr → AddExpr + MulExpr | AddExpr - MulExpr | MulExpr

MulExpr → MulExpr * UnExpr | MulExpr / UnExpr | UnExpr

UnExpr → - PrimExpr | ! PrimExpr | PrimExpr

PrimExpr → id ( ListExpr ) | id ( ) | id
         | intconst | carconst | ( Expr )
```

---

## 💻 Exemplos de Código

### Exemplo 1: Hello World (Goianinha style)

```goianinha
programa {
    escreva "Ola, Mundo!";
    novalinha;
}
```

### Exemplo 2: Função Simples

```goianinha
int dobro(int x) {
    retorne x * 2;
}

programa {
    int valor, resultado;
    valor = 5;
    resultado = dobro(valor);
    escreva resultado;  /* Imprime: 10 */
}
```

### Exemplo 3: Fatorial Recursivo

```goianinha
int fatorial(int n) {
    se (n <= 1) entao {
        retorne 1;
    }
    senao {
        retorne n * fatorial(n - 1);
    }
}

programa {
    int n, resultado;
    n = 5;
    resultado = fatorial(n);
    escreva resultado;  /* Imprime: 120 */
}
```

### Exemplo 4: Laço While

```goianinha
programa {
    int contador;
    contador = 1;
    
    enquanto (contador <= 10) execute {
        escreva contador;
        novalinha;
        contador = contador + 1;
    }
}
```

### Exemplo 5: Verificação de Número Par

```goianinha
int eh_par(int n) {
    int resto;
    resto = n - (n / 2) * 2;
    
    se (resto == 0) entao {
        retorne 1;  /* Verdadeiro */
    }
    senao {
        retorne 0;  /* Falso */
    }
}

programa {
    int num;
    num = 10;
    
    se (eh_par(num)) entao {
        escreva "Par";
    }
    senao {
        escreva "Impar";
    }
}
```

---

## 🏗️ Arquitetura do Compilador

### Fluxo de Compilação

```
Código Fonte (.g)
       ↓
[Análise Léxica - Flex]
       ↓
    Tokens
       ↓
[Análise Sintática - Bison]
       ↓
       AST
       ↓
[Análise Semântica]
       ↓
  AST Validada
       ↓
[Geração de Código]
       ↓
Assembly MIPS (.asm)
```

### Estrutura de Dados Principais

1. **NoArvore**: Nó da AST
   - Armazena tipo do nó, valor, linha, tipo de dado
   - Ponteiros para filhos

2. **TabelaEscopo**: Tabela de símbolos de um escopo
   - Arrays de variáveis e funções
   - Contador de elementos
   - Offset para alocação de memória

3. **PilhaEscopos**: Pilha de tabelas
   - Array de ponteiros para tabelas
   - Índice do topo

---

## 🎯 Geração de Código MIPS

### Estrutura do Código Gerado

```assembly
# Seção de dados
.data
quebra_linha: .asciiz "\n"

# Seção de código
.text
.globl main

# Funções declaradas
funcao1:
    # prólogo
    # corpo
    # epílogo
    jr $ra

# Programa principal
main:
    move $fp, $sp
    # código do programa
    
    # Finalização
    li $v0, 10
    syscall
```

### Convenções de Chamada

- Argumentos são passados via pilha (para simplicidade)
- Resultado retornado em `$v0`
- Variáveis locais armazenadas no frame da função
- Frame pointer (`$fp`) aponta para base do frame atual

### Syscalls Utilizadas

| Syscall | Código | Descrição |
|---------|--------|-----------|
| print_int | 1 | Imprime inteiro em `$a0` |
| print_string | 4 | Imprime string cujo endereço está em `$a0` |
| exit | 10 | Termina o programa |

---

## 📚 Referências

- Alfred V. Aho et al. **Compiladores: Princípios, Técnicas e Ferramentas** (2ª edição). Pearson, 2007.
- David A. Patterson e John L. Hennessy. **Organização e Projeto de Computadores**. Elsevier, 2014.
- [Documentação do Flex](https://github.com/westes/flex)
- [Documentação do Bison](https://www.gnu.org/software/bison/)
- [MIPS Assembly Reference](https://www.cs.cornell.edu/courses/cs3410/2019sp/schedule/slides/10-assembly-pt2-notes-bw.pdf)

---

## 👨‍💻 Autor

Desenvolvido como projeto acadêmico para a disciplina de Compiladores.

---

## 📄 Licença

Este projeto foi desenvolvido para fins educacionais.

**IMPORTANTE**: Conforme especificado nos documentos do trabalho, plágio é considerado crime acadêmico. Este código foi desenvolvido de forma independente com base nas especificações fornecidas e serve apenas como referência de estudo.

---

## 🔍 Notas Adicionais

### Diferenças em relação ao C

A linguagem Goianinha é inspirada em C, mas com algumas simplificações e diferenças:

1. **Sem ponteiros**: Não há conceito de ponteiros
2. **Sem arrays**: Apenas variáveis simples
3. **Apenas dois tipos**: `int` e `car`
4. **Sem structs ou unions**: Apenas tipos primitivos
5. **Palavras-chave em português**: `se`, `entao`, `senao`, `enquanto`, `execute`
6. **Sem preprocessador**: Não há `#include`, `#define`, etc.

### Limitações Conhecidas

1. **Chamadas de função**: Argumentos não são completamente implementados na geração MIPS
2. **Comando leia**: Não está completamente implementado
3. **Tipo car**: Tratado como int na geração de código
4. **Otimizações**: Nenhuma otimização de código é realizada

### Possíveis Melhorias Futuras

- Implementar otimizações de código (eliminação de subexpressões comuns, etc.)
- Adicionar suporte para arrays
- Implementar o comando `leia` completamente
- Melhorar as mensagens de erro
- Adicionar warnings para código suspeito
- Implementar passagem de argumentos via registradores (mais eficiente)

---

**Fim do README**
