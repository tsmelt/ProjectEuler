// 253.c
// Tyler_Smelt@hmc.edu
// 8/29/2012
// C implementation of Problem 253 from projecteuler.net
// Achieves 4-decimal-place accuracy after ~1 billion runs
// For num_pieces=10: avg=3.400740 after 10 billion runs (3.400732 is correct)
// Needs smarter algorithm for the required 6-decimal-place accuracy
// Brute-forcing is an option for small piece counts (10! = 3628800),
// but not for larger piece counts (40! = 8.16E47)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int i;
    int j;
    int n;
    int t;
    char tmp;
    
    unsigned long long runs;
    unsigned long long r;
    char progress = 0;
    
    int num_pieces;
    char *pieces;
    char piece;
    char *placed_pieces;

    char prev;
    char segs;
    char max_segs;
    unsigned long long *M;
    unsigned long long avg_int;
    double avg_float;
    
    // Initialize random number generator and arrays
    srand(time(NULL));
    if(argc > 1) {
        num_pieces = atoi(argv[1]);
    }
    else {
        num_pieces = 40;
    }
    pieces = (char*) malloc(num_pieces);
    placed_pieces = (char*) malloc(num_pieces);
    M = (unsigned long long*) calloc((1 + (1 + num_pieces)/2),
                                     sizeof(unsigned long long));
    for(i=0; i<num_pieces; i++) {
        pieces[i] = i;
    }
    
    // Run multiple times
    if(argc > 2) {
        runs = atoll(argv[2]);
    }
    else {
        runs = 1000000;
    }
    for(r=0; r<runs; r++) {
        // Reset tracking variables
        memset(placed_pieces, 0, num_pieces);
        max_segs = 0;
        
        // Shuffle order in which to pick up pieces (Knuth shuffle)
        for(i=num_pieces; i>1;) {
            n = rand() % i;
            i--;
            tmp = pieces[n];
            pieces[n] = pieces[i];
            pieces[i] = tmp;
        }
        
        // Make caterpillar
        for(i=0; i<num_pieces; i++) {
            // Choose a new piece
            piece = pieces[i];
            placed_pieces[piece] = 1;
            
            // Calculate the number of segments
            prev = 0;
            segs = 0;
            for(j=0; j<num_pieces; j++) {
                if(placed_pieces[j] && !prev) {
                    segs++;
                }
                prev = placed_pieces[j];
            }
            if(segs > max_segs) {
                max_segs = segs;
            }
        }
        
        // Record maximum segments for this run
        M[max_segs]++;
        
        // Update progress bar
        if(r*100 > progress*runs) {
            printf("%d%% ... ", progress);
            progress += 10;
        }
    }
    
    // Compute weighted average
    avg_int = 0;
    for(i=1; i<(1 + (1 + num_pieces)/2); i++) {
        avg_int += (i * M[i]);
    }
    avg_float = ((double) avg_int) / runs;
    
    // Print run time
    t = clock();
    printf("Done\nCompleted in %.3f seconds\n\n", ((float) t) / CLOCKS_PER_SEC);
    
    // Print results
    printf("M   Count\n---------\n");
    for(i=1; i<(1 + (1 + num_pieces)/2); i++) {
        printf("%-3d %llu\n", i, M[i]);
    }
    printf("\nAverage: %.8f\n", avg_float);
    
    // Free arrays
    free(pieces);
    free(placed_pieces);
    free(M);
    return 0;
}
