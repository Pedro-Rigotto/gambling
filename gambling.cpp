#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RODADAS 100
#define VERBOSE false
#define NUM_TESTS 100000
#define SALDO_INICIAL 1000000

double rodada(double saldo, float aposta) {
    if(saldo < 1) return -saldo;
    int resultado = rand() % 30 + 1;
    if (resultado <= 10) return aposta * saldo * resultado;
    return -(saldo * aposta);
}

double faz_teste(){
    double saldo = SALDO_INICIAL;
    float aposta = 0.5;
    
    for (int i = 0; i < RODADAS; i++) {
        #if VERBOSE
            printf("\n------\nRodada %d\n", i + 1);
            printf("Saldo anterior: %.0f\n", saldo);
            printf("Aposta: %f\n", aposta);
            printf("[[Sorteando...]]\n");
        #endif 
        int resultado = rodada(saldo, aposta);
        saldo += resultado;
        #if VERBOSE
            printf("Resultado: %d\n", resultado);
            printf("Novo saldo: %.0f\n", saldo);
            printf("------\n");
        #endif 
    }

    return saldo;
}

int main() {
    srand(time(NULL));
    #if !VERBOSE
        printf("Num de testes: %d\n", NUM_TESTS);
        printf("Saldo inicial: %d\n", SALDO_INICIAL);
    #endif

    
    double ganhoTotal = 0;
    for(int i = 0; i < NUM_TESTS; i++){
        double res = faz_teste();
        #if !VERBOSE
            //printf("Rodada %d: %.0f\n", i, res);
        #endif
        double ganho = res - SALDO_INICIAL;
        ganhoTotal += ganho;
    }

    printf("Ganho medio: %.0f (%.2f%%)\n", (double) (ganhoTotal / NUM_TESTS), (double) ((ganhoTotal / NUM_TESTS) / SALDO_INICIAL) * 100.0);

    return 0;
}