// 9.c
// Tyler_Smelt@hmc.edu
// 8/28/2012
// C implementation of Problem 9 from projecteuler.net
// Finds the only Pythagorean triplet a^2 + b^2 = c^2 for which a + b + c = 1000
// Uses Euclid's formula to generate triplets
// Compiled with tcc

#include <stdio.h>

#define TARGET_SUM  1000

int main(void) {
    unsigned int m, n;
    unsigned int a, b, c;
    
    n = 0;
    a = b = c = 0;
    
    while((a + b + c) != TARGET_SUM) {
        n++;
        m = n;
        a = b = c = 0;
        
        while((a + b + c) < TARGET_SUM) {
            m++;
            a = (m * m) - (n * n);
            b = 2 * m * n;
            c = (m * m) + (n * n);
        }
    }
    
    printf("(%u, %u, %u)\n", a, b, c);
    return 0;
}