# ===============================================
# CODIGO ASSEMBLY MIPS GERADO PELO COMPILADOR GOIANINHA
# ===============================================

# ===============================================
# Secao de Dados (.data)
# ===============================================
.data
quebra_linha: .asciiz "\n"  # String para novalinha

# ===============================================
# Secao de Texto (.text)
# ===============================================
.text
.globl main  # Declara main como ponto de entrada

# ===============================================
# DECLARACOES GLOBAIS E FUNCOES
# ===============================================

# ===============================================
# BLOCO PRINCIPAL (main)
# ===============================================
main:
    move $fp, $sp       # Inicializa frame pointer
    addiu $sp, $sp, -4  # Aloca espaco para variavel
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    # Comando: se_senao
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    sgt $t0, $t0, $t1   # Maior que
    beq $t0, $zero, Label_0  # Se falso, vai para else
    # Comando: se_senao
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    sgt $t0, $t0, $t1   # Maior que
    beq $t0, $zero, Label_2  # Se falso, vai para else
    # Comando: escreva string
.data
string_0: .asciiz "Ambos positivos"
.text
    la $a0, string_0          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
    j Label_3                # Pula para fim
Label_2:
    # Comando: escreva string
.data
string_1: .asciiz "X positivo, Y nao"
.text
    la $a0, string_1          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_3:
    j Label_1                # Pula para fim
Label_0:
    # Comando: escreva string
.data
string_2: .asciiz "X nao positivo"
.text
    la $a0, string_2          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_1:

# ===============================================
# Finalizacao do programa
# ===============================================
li $v0, 10      # Syscall 10: exit
syscall
