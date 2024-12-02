#define ITEMNUM 1000000                           // Maximum number of items
#define ITERATIONS 1                              // Iteration time
#define INPUTDIR "../inputs/FFDH/inputs/"         // Directory of the input file
#define OUTPUTDIR "../outputs/FFDH/outputs/"      // Directory of the output file
#define DRAWINPUTDIR "outputs/FFDH/rects/"     // Input file for draw.py

// structure of a single item
typedef struct item {
    double width;     
    double height;
    double x;          // Position of the upper left point of the item
    double y;      
} Item;

// First Fit by Decreasing Height, a basic 2-approximation algorithm
// W: Fixed width of the resulting texture
// n: The number of items
// rect: Items
// isDebug: Flag of debug mode
// outFile: Flag of file output mode
int FFDH(double W, int n, Item rect[], int isDebug, int outFile);