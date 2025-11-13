
# =============================================================================
# Makefile para o Compilador da Linguagem Goianinha
# =============================================================================

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lm

# Diretórios
SRC_DIR = .
LEXICO_SINTATICO_DIR = $(SRC_DIR)/lexico_sintatico
ESTRUTURAS_DIR = $(SRC_DIR)/estruturas_dados
SEMANTICO_DIR = $(SRC_DIR)/analisador_semantico
GERADOR_DIR = $(SRC_DIR)/gerador_mips
HEADERS_DIR = $(SRC_DIR)/headers
TESTES_DIR = $(SRC_DIR)/testes
SAIDAS_DIR = $(SRC_DIR)/saidas
MIPS_DIR = $(SRC_DIR)/mips_gerado

# Arquivos fonte
SRCS = $(LEXICO_SINTATICO_DIR)/main.c \
       $(LEXICO_SINTATICO_DIR)/goianinha.tab.c \
       $(LEXICO_SINTATICO_DIR)/lex.yy.c \
       $(ESTRUTURAS_DIR)/arvore_sintatica.c \
       $(ESTRUTURAS_DIR)/gerenciador_simbolos.c \
       $(SEMANTICO_DIR)/analisador_semantico.c \
       $(GERADOR_DIR)/gerador_mips.c

# Nome do executável
TARGET = goianinha

# Arquivos de teste
ARQUIVOS_TESTE := $(wildcard $(TESTES_DIR)/*.g)

# =============================================================================
# Regra principal: compila tudo
# =============================================================================
all: $(TARGET)

# =============================================================================
# Compila o executável final
# =============================================================================
$(TARGET): $(SRCS)
	@echo "Compilando o executável..."
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -o $(TARGET) $(SRCS) $(LDFLAGS)
	@echo "Compilação concluída! Executável: $(TARGET)"

# =============================================================================
# Gera o código do analisador sintático (Bison)
# =============================================================================
$(LEXICO_SINTATICO_DIR)/goianinha.tab.c $(LEXICO_SINTATICO_DIR)/goianinha.tab.h: $(LEXICO_SINTATICO_DIR)/goianinha.y
	@echo "Gerando analisador sintático com Bison..."
	bison -d -o $(LEXICO_SINTATICO_DIR)/goianinha.tab.c $(LEXICO_SINTATICO_DIR)/goianinha.y

# =============================================================================
# Gera o código do analisador léxico (Flex)
# =============================================================================
$(LEXICO_SINTATICO_DIR)/lex.yy.c: $(LEXICO_SINTATICO_DIR)/goianinha.l $(LEXICO_SINTATICO_DIR)/goianinha.tab.h
	@echo "Gerando analisador léxico com Flex..."
	flex -o $(LEXICO_SINTATICO_DIR)/lex.yy.c $(LEXICO_SINTATICO_DIR)/goianinha.l

# =============================================================================
# Executa os testes
# =============================================================================
test: all
	@echo ""
	@echo "========================================"
	@echo "    EXECUTANDO TESTES DO COMPILADOR"
	@echo "========================================"
	@mkdir -p $(SAIDAS_DIR)
	@mkdir -p $(MIPS_DIR)
	@for arquivo_teste in $(ARQUIVOS_TESTE); do \
		nome_base=$$(basename $$arquivo_teste .g); \
		echo ""; \
		echo ">>> Testando: $$arquivo_teste"; \
		./$(TARGET) $$arquivo_teste $(MIPS_DIR)/$$nome_base.asm > $(SAIDAS_DIR)/$$nome_base.txt 2>&1; \
		if [ $$? -eq 0 ]; then \
			echo "    [OK] Teste $$nome_base passou!"; \
		else \
			echo "    [ERRO] Teste $$nome_base falhou!"; \
		fi; \
	done
	@echo ""
	@echo "========================================"
	@echo "    TESTES CONCLUÍDOS"
	@echo "========================================"
	@echo "Resultados em: $(SAIDAS_DIR)/"
	@echo "Código MIPS em: $(MIPS_DIR)/"
	@echo ""

# =============================================================================
# Limpa arquivos gerados
# =============================================================================
clean:
	@echo "Limpando arquivos gerados..."
	@rm -f $(TARGET)
	@rm -f $(LEXICO_SINTATICO_DIR)/lex.yy.c 
	@rm -f $(LEXICO_SINTATICO_DIR)/goianinha.tab.c 
	@rm -f $(LEXICO_SINTATICO_DIR)/goianinha.tab.h
	@rm -rf $(SAIDAS_DIR)
	@rm -rf $(MIPS_DIR)
	@echo "Limpeza concluída."

# =============================================================================
# Ajuda
# =============================================================================
help:
	@echo "Makefile do Compilador Goianinha"
	@echo ""
	@echo "Comandos disponíveis:"
	@echo "  make          - Compila o compilador"
	@echo "  make test     - Executa todos os testes"
	@echo "  make clean    - Remove arquivos gerados"
	@echo "  make help     - Mostra esta mensagem"
	@echo ""

.PHONY: all test clean help
