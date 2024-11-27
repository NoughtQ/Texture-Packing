#define ITEMNUM 10000                       // Maximum number of items
#define ITERATIONS 10000                    // Iteration time
#define INPUTDIR "../test/input.txt"        // Directory of the input file

// structure of a single item
typedef struct item {
    double width;     
    double height;
} Item;

// First Fit by Decreasing Height, a basic 2-approximation algorithm
// W: Fixed width of the resulting texture
// n: The number of items
// rect: Items
// isDebug: Flag of debug mode
int FFDH(double W, int n, Item rect[], int isDebug);