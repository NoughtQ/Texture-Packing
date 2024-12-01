#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "headers/ttpHeader.h"

double curWidth[ITEMNUM];                  // Array recording the total item width in each level
int pos[ITEMNUM];                          // Array recording the position(which level) of every item
double levelHeight[ITEMNUM];               // Height of each level(depending on the first item in the level)
int level;                                 // Current level of the resulting texture
extern std::string outFileName;                 // Name of the output file

int cmp(const void * a, const void * b);                // Comparator for decrease-order quicksort function
void printDebugInfo(double W, int n, Item * rect, int outFile);   // Print the debug infomation when using "--debug" command argument

// First Fit by Decreasing Height, a basic 2-approximation algorithm
// W: Fixed width of the resulting texture
// n: The number of items
// rect: Items
// isDebug: Flag of debug mode
// outFile: Flag of file output mode
int FFDH(double W, int n, Item rect[], int isDebug, int outFile) {
    double curHeight = 0;                  // Current height of the resulting texture
    int i, j;

    // Initially, sort all items by their heights in decreasing order
    qsort(rect, n, sizeof(rect[0]), cmp);

    // initialize elements in curWidth to zero
    level = 0;
    for (i = 0; i < n; i++)
        curWidth[i] = 0;

    // Handle all items
    for (i = 0; i < n; i++) {
        // Find the first fit existing level
        for (j = 0; j < level; j++) {
            // Find it!
            if (curWidth[j] + rect[i].width <= W) {
                rect[i].x = curWidth[j];              // Update the position of the item
                rect[i].y = levelHeight[j];
                curWidth[j] += rect[i].width;         // Update the width of current level
                pos[i] = j;                           // Record the position of the item
                break;
            } 
        }
        if (j < level)                                // If found, continue to process next loop
            continue;

        // If not found
        ++level;                                  // Create a new level
        curWidth[level - 1] = rect[i].width;      // Update the width of current level
        levelHeight[level - 1] = curHeight;       // Update the height of the level
        curHeight += rect[i].height;              // Update the current height
        rect[i].x = 0;                            // Update the position of the item
        rect[i].y = levelHeight[level - 1];        
        pos[i] = level - 1;                       // Record the level of the item
    }

    // Print the debug infomation when using "--debug" command argument
    if (isDebug)
        printDebugInfo(W, n, rect, outFile);

    // Return the current height of the resulting texture as the minimal height
    return curHeight;
}   

// Comparator for decrease-order quicksort function
int cmp(const void * a, const void * b) {
    const Item dataA = *(const Item*)a;
    const Item dataB = *(const Item*)b;

    // Sort items by their height in decreasing order
    if (dataB.height < dataA.height) {
        return -1;
    } else if (dataB.height > dataA.height) {
        return 1;
    } else {    // equalf 
        return 0;
    }
}

// Print the debug infomation when using "--debug" command argument
// W: Fixed width of the resulting texture
// n: The number of items
// rect: Items
// outFile: Flag of file output mode
void printDebugInfo(double W, int n, Item * rect, int outFile) {
    int i;

    if (!outFile) {    // Default output mode(print the info in the terminal)
        printf("Debug Info:\n");
        
        // 1. Print the height-decreasingly sorted item data
        printf("Height-decreasingly sorted item data:\n");
        for (i = 0; i < n; i++) {
            printf("%d: %.2f, %.2f\n", i, rect[i].width, rect[i].height);
            // ++rect;
        }

        // 2. Print the occupied-by-items width for each level
        printf("\nTotal level: %d\nWidth:\n", level);
        for (i = 0; i < level; i++) {
            printf("%d level: %.2f\n", i, curWidth[i]);
        }

        // 3. Print the positions of items
        printf("\nPosition:\n");
        for (i = 0; i < n; i++) {
            printf("Item %d: level %d, x: %.2f, y: %.2f\n", i + 1, pos[i], rect[i].x, rect[i].y);
        }

        // Deviding line
        printf("====================================\n");
    } else {    // File output mode
        std::string outDirName;
        outFileName = outFileName == "" ? "output" : outFileName;
        outDirName = OUTPUTDIR + outFileName;
        FILE * fp = fopen(outDirName.c_str(), "w");

        fprintf(fp, "Debug Info:\n");
        
        // 1. Print the height-decreasingly sorted item data
        fprintf(fp, "Height-decreasingly sorted item data:\n");
        for (i = 0; i < n; i++) {
            fprintf(fp, "%d: %.2f, %.2f\n", i, rect[i].width, rect[i].height);
            // ++rect;
        }

        // 2. Print the occupied-by-items width for each level
        fprintf(fp, "\nTotal level: %d\nWidth:\n", level);
        for (i = 0; i < level; i++) {
            fprintf(fp, "%d level: %.2f\n", i, curWidth[i]);
        }

        // 3. Print the positions of items
        fprintf(fp, "\nPosition:\n");
        for (i = 0; i < n; i++) {
            fprintf(fp, "Item %d: level %d, x: %.2f, y: %.2f\n", i + 1, pos[i], rect[i].x, rect[i].y);
        }

        // Deviding line
        fprintf(fp, "====================================\n");

        fclose(fp);

        // 4.(only for file output) Get the input file for draw.py
        std::string drawFileName = "rectangle" + outFileName.substr(6) + ".txt";
        std::string drawDirName = DRAWINPUTDIR + drawFileName;
        fp = fopen(drawDirName.c_str(), "w");

        fprintf(fp, "%.2f\n", W);
        for (i = 0; i < n; i++) {
            fprintf(fp, "%.2f %.2f %.2f %.2f\n", rect[i].x, rect[i].y, rect[i].width, rect[i].height);
        }   

        fclose(fp);

        printf("The output file is saved as %s\n", outDirName.c_str());     // Hint
    }
}