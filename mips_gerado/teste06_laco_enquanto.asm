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
    # Comando: enquanto
Label_0:
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    slt $t0, $t0, $t1   # Menor que
    beq $t0, $zero, Label_1  # Se falso, sai do loop
    # Comando: escreva
    move $a0, $t0       # Move valor para $a0
    li $v0, 1           # Syscall 1: print_int
    syscall
    # Comando: novalinha
    la $a0, quebra_linha # Carrega string de quebra de linha
    li $v0, 4            # Syscall 4: print_string
    syscall
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    add $t0, $t0, $t1   # Adicao
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    j Label_0                # Volta para inicio do loop
Label_1:

# ===============================================
# Finalizacao do programa
# ===============================================
li $v0, 10      # Syscall 10: exit
syscall
