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


# Funcao: fatorial
fatorial:
    sw $ra, -4($sp)     # Salva return address
    sw $fp, -8($sp)     # Salva frame pointer anterior
    move $fp, $sp       # Atualiza frame pointer
    addiu $sp, $sp, -8  # Ajusta stack pointer
    addiu $sp, $sp, -4  # Aloca espaco para variavel
    # Comando: se_senao
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
    li $t0, 0          # Carrega constante
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    sle $t0, $t0, $t1   # Menor ou igual
    beq $t0, $zero, Label_0  # Se falso, vai para else
    # Comando: retorne
    li $t0, 0          # Carrega constante
    move $v0, $t0       # Move resultado para $v0
    j fatorial_saida          # Vai para epilogo da funcao
    j Label_1                # Pula para fim
Label_0:
    addiu $sp, $sp, -4  # Empilha operando esquerdo
    sw $t0, 0($sp)
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
    sub $t0, $t0, $t1   # Subtracao
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    mul $t0, $t0, $t1   # Multiplicacao
    lw $t1, 0($sp)      # Desempilha operando esquerdo
    addiu $sp, $sp, 4
    move $t2, $t0
    move $t0, $t1
    move $t1, $t2
    # Comando: retorne
    move $v0, $t0       # Move resultado para $v0
    j fatorial_saida          # Vai para epilogo da funcao
Label_1:
fatorial_saida:
    move $sp, $fp       # Restaura stack pointer
    lw $ra, -4($sp)     # Restaura return address
    lw $fp, -8($sp)     # Restaura frame pointer
    jr $ra              # Retorna para chamador

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
    # Comando: escreva
    move $a0, $t0       # Move valor para $a0
    li $v0, 1           # Syscall 1: print_int
    syscall

# ===============================================
# Finalizacao do programa
# ===============================================
li $v0, 10      # Syscall 10: exit
syscall
