#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ttpHeader.h"

double Width;                // Fixed width of the resulting texture
int n;                       // The number of items
Item rect[ITEMNUM];          // Items
FILE * fp;                   // File pointer
int isDebug;                 // Flag of debug mode
int isTiming;                // Flag of timing mode
clock_t start, stop;         // Record of start and stop time of the approximation algorithm

// Input handler
void getInput(int argc, char * argv[]);
// Print the timing infomation
void printTime(clock_t start, clock_t end);

int main(int argc, char * argv[]) {
    int i;
    double miniHeight;   // Result
    
    getInput(argc, argv);                                    // Input

    // Execution of approximation algorithm
    if (isTiming) {
        start = clock();                                     // Start timing
        for (i = 0; i < ITERATIONS; i++)                     // Multiple execution of algorithms
            miniHeight = FFDH(Width, n, rect, 0);
        stop = clock();                                      // Stop timing
        printTime(start, stop);                              // Print the timing infomation
    } else {
        miniHeight = FFDH(Width, n, rect, isDebug);          
        printf("The minimum height: %.2f\n", miniHeight);    // Output
    }

    return 0;
}

// Input handler
void getInput(int argc, char * argv[]) {
    int i;
    int choice = 0;    // Choice whether receiving terminal input or file input
    
    // If using command arguments
    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            // Handle debug mode
            if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug"))
                isDebug = 1;
            // Handle file input mode
            else if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file"))
                choice = 1;
            // Handle timing mode
            if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--timing"))
                isTiming = 1;
        }
    }

    if (!choice) {    // Terminal input
        scanf("%lf", &Width);
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%lf%lf", &rect[i].width, &rect[i].height);
        }
    } else {          // File input
        fp = fopen(INPUTDIR, "r");     // Read the input file
        fscanf(fp, "%lf", &Width);     // Similar to terminal input
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%lf%lf", &rect[i].width, &rect[i].height);
        }
    }
}

// Print the timing infomation
void printTime(clock_t start, clock_t end) {
    clock_t tick;       // Ticks
    double duration;    // Duration(unit: seconds)
    int iterations;

    iterations = ITERATIONS;     // Set iteration time, for obvious timing result
    tick = end - start;          // Calculate tick numbers
    duration = ((double)(tick)) / CLOCKS_PER_SEC;      // Calculate the total duration of multiple execution of the algorithm

    // Print the timing info
    printf("\nTiming Result:\n");
    printf("Iterations: %d\n", iterations);
    printf("Ticks: %lu\n", (long)tick);   
    printf("Duration: %.2fs\n", duration);  
}