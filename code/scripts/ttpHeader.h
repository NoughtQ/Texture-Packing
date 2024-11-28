#define ITEMNUM 1000000                           // Maximum number of items
#define ITERATIONS 1                             // Iteration time
#define INPUTDIR "../test/uniform_double_160000"        // Directory of the input file
#define OUTPUTDIR "../test/FFDH/output2"                   // Directory of the output file

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
// outFile: Flag of file output mode
int FFDH(double W, int n, Item rect[], int isDebug, int outFile);