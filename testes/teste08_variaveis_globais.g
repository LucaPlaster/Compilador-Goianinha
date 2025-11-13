
/* Teste 08: Variáveis globais e locais */
int global_x, global_y;

int usar_globais() {
    retorne global_x + global_y;
}

programa {
    int local_z;
    global_x = 10;
    global_y = 20;
    local_z = usar_globais();
    escreva local_z;
}
