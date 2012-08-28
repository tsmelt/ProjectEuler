// 6.c
// Tyler_Smelt@hmc.edu
// 8/27/2012
// C implementation of Problem 6 from projecteuler.net
// Calculates difference between the sum of the squares of the first
// one hundred (or any other amount) natural numbers and the square of the sum
// Compiled with tcc

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    unsigned long long maxNum = 100;
    unsigned long long sumSquares = 0;
    unsigned long long squareSums = 0;
    unsigned long long diff = 0;
    unsigned long long i;
    
    if(argc > 1) {
        maxNum = atoi(argv[1]);
    }
    printf("Calculating difference for the first %llu natural numbers\n", maxNum);
    
    for(i=1; i<=maxNum; i++) {
        sumSquares += (i * i);
        squareSums += i;
    }
    squareSums *= squareSums;
    diff = (squareSums - sumSquares);
    
    printf("Sum of squares: %llu\n", sumSquares);
    printf("Square of sums: %llu\n", squareSums);
    printf("Difference: %llu\n", diff);
    return 0;
}