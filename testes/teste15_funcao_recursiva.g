
/* Teste 15: Função recursiva (fatorial) */
int fatorial(int n) {
    int resultado;
    se (n <= 1) entao {
        retorne 1;
    }
    senao {
        resultado = n * fatorial(n - 1);
        retorne resultado;
    }
}

programa {
    int res;
    res = fatorial(5);
    escreva res;
}
