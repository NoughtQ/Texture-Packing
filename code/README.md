# The Guide of How to Run Our Program

## Prerequisite

- It's highly recommended that using **Windows OS** to run our program(like powershell), because our development environment is Windows, and we haven't tested whether our program works well in other OS.
- Be sure that change your directory to `./code/build/` where you can find the Makefile.

## Run the FFDH Approximation Algorithm

1. Compile the source codes.

```sh
$ make
```

2. Run our program.

```sh
$ ./ttpMain
```

3. Now you are running our program in default mode, which requires you to input the information manually. The sample input format and output result are shown below(the words after `//` are comments, which shouldn't be input):

```
// Sample input:
18                           // Fixed width of the resulting texture
7                            // The number of items
7 3                          // Item 1 info
5 8
10 3
6 4
5 3
2 5
8 2                          // Item 7 info
The total height: 28.00      // Output result
The ideal height(Area / Width): 8.67
The minimum height: 13.00    
```

Is it very easy? **To check more information**, you can use the command arguments we provide to you. We list all the available arguments and corresponding brief description of their functions:

- `--debug` or `-d`: Print the **debug information**, includeing:
    - the height-decreasingly sorted item data
    - the occupied-by-items width for each level
    - the positions of items
    - (need cooperate with argument `-of`)the input file for drawing the items by draw.py
- `--infile` or `-if`: Use **file input** in directory `INPUTDIR`(macro definition) rather than terminal input.
- `--outfile` or `-of`: Use **file output** in directory `OUTPUTDIR`(macro definition) rather than terminal output.
- `--timing` or `-t`: Activate the timing function, instead of output the correct result (and debug infomation, so this argument will <u>deactivate the debug mode</u>), the program will output the **timing information** after executing the algorithm `ITERATIONS` times.


