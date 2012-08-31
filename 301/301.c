// 301.c
// Tyler_Smelt@hmc.edu
// 8/30/2012
// C implementation of Problem 301 from projecteuler.net
// Yay brute force!

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    unsigned long long n;
    unsigned long long n1, n2, n3;
    unsigned long long count = 0;
    int progress = 0;

    if(argc > 1) {
        n = (unsigned long long) strtoul(argv[1], NULL, 10);
    }
    else {
        n = 1073741824; // 2^30
    }
    
    // Run through all specified integers
    for(n1=0; n1<n;) {
        n1++;
        n2 = 2 * n1;
        n3 = 3 * n1;
        if(!(n1 ^ n2 ^ n3)) {
            count++;
        }
        
        // Update progress bar (almost doubles execution time)
        // if(n1*100 > progress*n) {
            // printf("%d%% ... ", progress);
            // progress += 10;
        // }
    }
    
    // Print run time
    int t = clock();
    printf("Done\nCompleted in %.3f seconds\n", ((float) t) / CLOCKS_PER_SEC);
    
    // Print results
    printf("X(n,2n,3n) = 0 for %llu of %llu integers\n", count, n);
    
    return 0;
}
