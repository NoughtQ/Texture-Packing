#include <stdio.h>
#include <stdlib.h>
#include "ttpHeader.h"

double curWidth[ITEMNUM];                  // Array recording the total item width in each level
int pos[ITEMNUM];                          // Array recording the position(which level) of every item
int level;                                 // Current level of the resulting texture

int cmp(const void * a, const void * b);                // Comparator for decrease-order quicksort function
void printDebugInfo(int n, Item * rect, int outFile);   // Print the debug infomation when using "--debug" command argument

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
                curWidth[j] += rect[i].width;     // Update the width of current level
                pos[i] = j;                       // Record the position of the item
                break;
            } 
        }
        if (j < level)                            // If found, continue to process next loop
            continue;

        // If not found
        ++level;                                  // Create a new level
        curWidth[level - 1] = rect[i].width;      // Update the width of current level
        curHeight += rect[i].height;              // Update the current height
        pos[i] = level - 1;                       // Record the position of the item
    }

    // Print the debug infomation when using "--debug" command argument
    if (isDebug)
        printDebugInfo(n, rect, outFile);

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
// n: The number of items
// rect: Items
// outFile: Flag of file output mode
void printDebugInfo(int n, Item * rect, int outFile) {
    int i;

    if (!outFile) {    // Default output mode(print the info in the terminal)
        printf("Debug Info:\n");
        
        // 1. Print the height-decreasingly sorted item data
        printf("Height-decreasingly sorted item data:\n");
        for (i = 0; i < n; i++) {
            printf("%d: %.2f, %.2f\n", i, rect->width, rect->height);
            ++rect;
        }

        // 2. Print the occupied-by-items width for each level
        printf("\nTotal level: %d\nWidth:\n", level);
        for (i = 0; i < level; i++) {
            printf("%d level: %.2f\n", i, curWidth[i]);
        }

        // 3. Print the positions of items
        printf("\nPosition:\n");
        for (i = 0; i < n; i++) {
            printf("Item %d: level %d\n", i, pos[i]);
        }

        // Deviding line
        printf("====================================\n");
    } else {    // File output mode
        FILE * fp = fopen(OUTPUTDIR, "w");

        fprintf(fp, "Debug Info:\n");
        
        // 1. Print the height-decreasingly sorted item data
        fprintf(fp, "Height-decreasingly sorted item data:\n");
        for (i = 0; i < n; i++) {
            fprintf(fp, "%d: %.2f, %.2f\n", i, rect->width, rect->height);
            ++rect;
        }

        // 2. Print the occupied-by-items width for each level
        fprintf(fp, "\nTotal level: %d\nWidth:\n", level);
        for (i = 0; i < level; i++) {
            fprintf(fp, "%d level: %.2f\n", i, curWidth[i]);
        }

        // 3. Print the positions of items
        fprintf(fp, "\nPosition:\n");
        for (i = 0; i < n; i++) {
            fprintf(fp, "Item %d: level %d\n", i, pos[i]);
        }

        // Deviding line
        fprintf(fp, "====================================\n");

        fclose(fp);
    }
}