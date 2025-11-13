
/* Teste 10: Operadores lógicos */
programa {
    int a, b, c;
    a = 1;
    b = 0;
    c = 1;
    
    se (a e c) entao {
        escreva "a AND c eh verdadeiro";
        novalinha;
    }
    
    se (a ou b) entao {
        escreva "a OR b eh verdadeiro";
        novalinha;
    }
    
    se (!b) entao {
        escreva "NOT b eh verdadeiro";
        novalinha;
    }
}
