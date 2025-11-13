
/* Teste 20: Programa completo com vários recursos */

int global;

int calcular(int a, int b) {
    int temp;
    temp = a * b + global;
    retorne temp;
}

int eh_par(int n) {
    int resto;
    resto = n - (n / 2) * 2;
    se (resto == 0) entao {
        retorne 1;
    }
    senao {
        retorne 0;
    }
}

programa {
    int num, resultado, i;
    
    global = 5;
    
    escreva "Testando calculo:";
    novalinha;
    resultado = calcular(3, 4);
    escreva resultado;
    novalinha;
    
    escreva "Numeros pares de 0 a 10:";
    novalinha;
    i = 0;
    enquanto (i <= 10) execute {
        se (eh_par(i)) entao {
            escreva i;
            novalinha;
        }
        i = i + 1;
    }
    
    escreva "Fim do programa";
    novalinha;
}
