
/* Teste 16: Condicionais aninhados */
programa {
    int x, y;
    x = 10;
    y = 5;
    
    se (x > 0) entao {
        se (y > 0) entao {
            escreva "Ambos positivos";
        }
        senao {
            escreva "X positivo, Y nao";
        }
    }
    senao {
        escreva "X nao positivo";
    }
}
