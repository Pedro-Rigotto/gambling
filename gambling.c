#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROUNDS 100
#define VERBOSE false
#define NUM_TESTS 10000000
#define INITIAL_BALANCE 1000000

double run_round(double balance, float bet) {
    if(balance < 1) return -balance;
    int result = rand() % 30 + 1;
    if (result <= 10) return bet * balance * result;
    return -(balance * bet);
}

double run_test(){
    double balance = INITIAL_BALANCE;
    float bet = 0.5;
    
    for (int i = 0; i < ROUNDS; i++) {
        #if VERBOSE
            printf("\n------\nRound %d\n", i + 1);
            printf("Previous balance: %.0f\n", balance);
            printf("Bet: %f\n", bet);
            printf("[[Simulating...]]\n");
        #endif 
        int result = run_round(balance, bet);
        balance += result;
        #if VERBOSE
            printf("Result: %d\n", result);
            printf("New balance: %.0f\n", balance);
            printf("------\n");
        #endif 
    }

    return balance;
}

int main() {
    srand(time(NULL));
    #if !VERBOSE
        printf("Number of tests: %d\n", NUM_TESTS);
        printf("Initial balance: %d\n", INITIAL_BALANCE);
    #endif

    
    double totalGain = 0;
    double gain;
    double res;

    #pragma omp parallel for private(res) private(gain) reduction(+:totalGain) schedule(guided, 1)
    for(int i = 0; i < NUM_TESTS; i++){
        res = run_test();
        #if !VERBOSE
            //printf("Round %d: %.0f\n", i, res);
        #endif
        gain = res - INITIAL_BALANCE;
        totalGain += gain;
    }

    printf("Average gain: %.0f (%.2f%%)\n", (double) (totalGain / NUM_TESTS), (double) ((totalGain / NUM_TESTS) / INITIAL_BALANCE) * 100.0);

    return 0;
}
