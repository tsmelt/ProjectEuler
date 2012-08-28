// 5.c
// Tyler_Smelt@hmc.edu
// 8/27/2012
// C implementation of Problem 5 from projecteuler.net
// Calculates the smallest positive number that is evenly divisible by
// all of the numbers from 1 to 20 (or any other number)
// Compiled with tcc

#include <stdio.h>
#include <string.h>

char divisible(unsigned int n, unsigned int max);

int main(int argc, char *argv[]) {
    unsigned int maxDiv = 20;
    unsigned int min = 1;
    
    if(argc > 1) {
        maxDiv = atoi(argv[1]);
    }
    
    while(!divisible(min, maxDiv)) {
        min++;
    }
    
    printf("Smallest number divisible by numbers 1 to %u: %u\n", maxDiv, min);
    return 0;
}

char divisible(unsigned int n, unsigned int max) {
    int i;
    
    for(i=1; i<=max; i++) {
        if(n % i) {
            return 0;
        }
    }
    
    return 1;
}