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
    # Comando: se
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    seq $t0, $t0, $t1   # Igual a
    beq $t0, $zero, Label_1  # Se falso, vai para fim
    # Comando: escreva string
.data
string_0: .asciiz "a eh 10"
.text
    la $a0, string_0          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_1:
    # Comando: novalinha
    la $a0, quebra_linha # Carrega string de quebra de linha
    li $v0, 4            # Syscall 4: print_string
    syscall
    # Comando: se
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    sne $t0, $t0, $t1   # Diferente de
    beq $t0, $zero, Label_3  # Se falso, vai para fim
    # Comando: escreva string
.data
string_1: .asciiz "a diferente de b"
.text
    la $a0, string_1          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_3:
    # Comando: novalinha
    la $a0, quebra_linha # Carrega string de quebra de linha
    li $v0, 4            # Syscall 4: print_string
    syscall
    # Comando: se
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    sgt $t0, $t0, $t1   # Maior que
    beq $t0, $zero, Label_5  # Se falso, vai para fim
    # Comando: escreva string
.data
string_2: .asciiz "a maior que b"
.text
    la $a0, string_2          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_5:
    # Comando: novalinha
    la $a0, quebra_linha # Carrega string de quebra de linha
    li $v0, 4            # Syscall 4: print_string
    syscall
    # Comando: se
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    slt $t0, $t0, $t1   # Menor que
    beq $t0, $zero, Label_7  # Se falso, vai para fim
    # Comando: escreva string
.data
string_3: .asciiz "b menor que a"
.text
    la $a0, string_3          # Carrega endereco da string
    li $v0, 4           # Syscall 4: print_string
    syscall
Label_7:
    # Comando: novalinha
    la $a0, quebra_linha # Carrega string de quebra de linha
    li $v0, 4            # Syscall 4: print_string
    syscall

# ===============================================
# Finalizacao do programa
# ===============================================
li $v0, 10      # Syscall 10: exit
syscall
