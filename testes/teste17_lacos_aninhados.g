
/* Teste 17: Laços aninhados */
programa {
    int i, j;
    i = 0;
    enquanto (i < 3) execute {
        j = 0;
        enquanto (j < 2) execute {
            escreva i;
            escreva j;
            novalinha;
            j = j + 1;
        }
        i = i + 1;
    }
}
