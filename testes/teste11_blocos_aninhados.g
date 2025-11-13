
/* Teste 11: Blocos aninhados com escopos */
programa {
    int x;
    x = 10;
    {
        int y;
        y = 20;
        {
            int z;
            z = 30;
            escreva x;
            escreva y;
            escreva z;
            novalinha;
        }
    }
    escreva x;
}
