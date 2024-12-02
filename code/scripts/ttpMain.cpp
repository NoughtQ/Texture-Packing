#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include "headers/ttpHeader.h"

double Width;                // Fixed width of the resulting texture
int n;                       // The number of items
Item rect[ITEMNUM];          // Items
double totalHeight;          // The sum of all heights of items 
double Area;                 // Area of all items
int isDebug;                 // Flag of debug mode
int isTiming;                // Flag of timing mode
int outChoice;               // Flag of file output mode
clock_t start, stop;         // Record of start and stop time of the approximation algorithm
std::string outFileName = "";     // Name of the output file

// Input handler
void getInput(int argc, char * argv[]);
// Print the timing infomation
void printTime(clock_t start, clock_t end, int outFile);

int main(int argc, char * argv[]) {
    int i;
    double miniHeight;    // Result
    
    getInput(argc, argv);                                    // Input

    // Execution of approximation algorithm
    if (isTiming) {
        start = clock();                                         // Start timing
        for (i = 0; i < ITERATIONS; i++)                         // Multiple execution of algorithms
            miniHeight = FFDH(Width, n, rect, 0, outChoice);     // Execute!
        stop = clock();                                          // Stop timing
        printTime(start, stop, outChoice);                       // Print the timing infomation
    } else {
        miniHeight = FFDH(Width, n, rect, isDebug, outChoice);   // Execute!
        // Output  
        if (!outChoice) {
            printf("The total height: %.2f\n", totalHeight);
            printf("The ideal height(Area / Width): %.2f\n", Area / Width);        
            printf("The \"minimum\" height: %.2f\n", miniHeight);    // Output the result in the terminal
        } else {       // Output the result in the file
            std::string outDirName = OUTPUTDIR + outFileName;

            FILE * fp = fopen(outDirName.c_str(), "r");
            if (fgetc(fp) == 'T') {        // If the file contains the info of last execution
                fclose(fp);
                FILE * fp = fopen(outDirName.c_str(), "w");      // Clean the original content in the file
            } else {                       // Otherwise, the file is just empty or contains the debug info
                fclose(fp);
                FILE * fp = fopen(outDirName.c_str(), "a");      // Append the output to the file           
            }
            fprintf(fp, "The total height: %.2f\n", totalHeight);         
            fprintf(fp, "The ideal height(Area / Width): %.2f\n", Area / Width); 
            fprintf(fp, "The \"minimum\" height: %.2f\n", miniHeight);    // Output the result in the file
            fclose(fp);
        }    
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
            else if (!strcmp(argv[i], "-if") || !strcmp(argv[i], "--infile"))
                choice = 1;
            // Handle file output mode
            else if (!strcmp(argv[i], "-of") || !strcmp(argv[i], "--outfile"))
                outChoice = 1;
            // Handle timing mode
            else if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--timing"))
                isTiming = 1;
        }
    }

    if (!choice) {    // Terminal input
        scanf("%lf", &Width);
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%lf%lf", &rect[i].width, &rect[i].height);
            totalHeight += rect[i].height;
            Area += rect[i].height * rect[i].width;
        }
    } else {          // File input
        std::string inFileName;           // Name of the input file
        std::string inDirName;            // The whole directory of the input file

        printf("Please input the input file name:\n");
        std::cin >> inFileName;
        inDirName = INPUTDIR + inFileName;
        outFileName = "output" + inFileName.substr(5);


        FILE * fp = fopen(inDirName.c_str(), "r");     // Read the input file
        if (fp == NULL) {     // If it can't open the file, exit the program
            printf("Fail to read the input file. Please ensure that you use the true directory.");
            exit(1);
        }
        fscanf(fp, "%lf", &Width);     // Similar to terminal input
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%lf%lf", &rect[i].width, &rect[i].height);
            totalHeight += rect[i].height;
            Area += rect[i].height * rect[i].width;
        }

        fclose(fp);
    }
}

// Print the timing infomation
void printTime(clock_t start, clock_t end, int Outfile) {
    clock_t tick;       // Ticks
    double duration;    // Duration(unit: seconds)
    int iterations;

    iterations = ITERATIONS;     // Set iteration time, for obvious timing result
    tick = end - start;          // Calculate tick numbers
    duration = ((double)(tick)) / CLOCKS_PER_SEC;      // Calculate the total duration of multiple execution of the algorithm

    // Print the timing info
    if (!Outfile) {    // Default output mode(print the info in the terminal)
        printf("\nTiming Result:\n");
        printf("Iterations: %d\n", iterations);
        printf("Ticks: %lu\n", (long)tick);   
        printf("Duration: %.6fs\n", duration);  
    } else {           // File output mode
        FILE * fp = fopen(OUTPUTDIR, "w");
        if (fp == NULL) {    // If it can't open the file, exit the program
            printf("Fail to open the output file. Please ensure that you use the true directory.");
            exit(1);   
        }
        fprintf(fp, "\nTiming Result:\n");
        fprintf(fp, "Iterations: %d\n", iterations);
        fprintf(fp, "Ticks: %lu\n", (long)tick);   
        fprintf(fp, "Duration: %.6fs\n", duration);    

        fclose(fp);
    }
}