#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ROUNDS 10
#define VERBOSE false
#define NUM_TESTS 10000000
#define INITIAL_BALANCE 1000000
#define BET 0.5

double run_round(double balance) {
    if(balance < 1) return -balance;
    int result = rand() % 30 + 1;
    if (result <= 10) return BET * balance * result;
    return -(balance * BET);
}

double run_test(){
    double balance = INITIAL_BALANCE;
    
    for (int i = 0; i < ROUNDS; i++) {
        #if VERBOSE
            printf("\n------\nRound %d\n", i + 1);
            printf("Previous balance: %.0f\n", balance);
            printf("[[Simulating...]]\n");
        #endif 
        int result = run_round(balance);
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
        printf("Number of rounds per test: %d\n", ROUNDS);
        printf("Initial balance: %d\n", INITIAL_BALANCE);
        printf("Bet: %.2f%%\n", BET * 100);
        printf("[--------[ Running tests ]--------]\n");
    #endif

    
    double totalGain = 0;
    double gain;
    double res;
    int totalLoss = 0;
    int totalProfitable = 0;

    #pragma omp parallel for private(res) private(gain) reduction(+:totalGain) reduction(+:totalLoss) reduction(+:totalProfitable) schedule(guided, 1)
    for(int i = 0; i < NUM_TESTS; i++){
        res = run_test();
        #if !VERBOSE
            //printf("Round %d: %.0f\n", i, res);
        #endif
        gain = res - INITIAL_BALANCE;
        totalGain += gain;
        if(gain > 0) totalProfitable++;
        if(res == 0) totalLoss++;
    }

    printf("Average gain: %.0f (%.2f%%)\n", (double) (totalGain / NUM_TESTS), (double) ((totalGain / NUM_TESTS) / INITIAL_BALANCE) * 100.0);
    printf("Total loss: %.2f%%\n", (float) ((totalLoss * 100 )/ NUM_TESTS));
    printf("Some money left: %.2f%%\n", (float) ((NUM_TESTS - totalLoss) * 100) / NUM_TESTS);
    printf("Profitable: %.2f%%\n", (float) ((totalProfitable * 100) / NUM_TESTS));

    return 0;
}
