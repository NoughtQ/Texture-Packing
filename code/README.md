# The Guide of How to Run Our Program

这里是中文版的说明，下面英文说明仅针对于运行ttpMain。这里针对generate和BLMain做一些补充说明。

1. 生成可执行文件的步骤相同，只需要到`./code/build/`使用`make`或`mingw32-make`命令即可。

2. `generate`的使用比较繁琐，它仅支持通过文件输入，输入文件的位置在`./code/input/generate/generate_in.txt`。文件输入格式在generate_main.cpp的注释中比较详细的说明了，这里就直接粘贴过来了

    ```cpp
    /**************** 
     * @ generate_in file format:
     * generateMode(decide the mode of the generation)
     * n(number of test cases you want to generate)
     * 
     * @ generateMode 1
     * maxHeight_1 maxWeight_1 num_1 mode_1 filename_1
     * ...
     * maxHeight_n maxWeight_n num_n mode_n filename_n
     * 
     * @ generateMode 2
     * Height_1 Weight_1 hNum_1 wNum_1 filename_1
     * ...
     * Height_n Weight_n hNum_n wNum_n filename_n
    *****************/
    ```

    其中更具体的参数说明，还请参考程序中的注释，这里不多加赘述。

    （如果不想研究，也可以直接赋值同目录位置的`sample1`和`sample2`到`generate_in.txt`中以生成测试文件，或者直接使用我们提供的测试样例）

3. `BLMain`在运行后，引导已经较为充分，这里仅做简短补充。

    - 首先，文件输入只支持在`.\code\input\`下的文件名（需完整输入）
    - 如果不开启`test mode`即意为开启`debug mode`，在`debug mode`会生成`upBound`的更新信息以及最后的矩形位置结果在`./code/outputs/BL/debug/`下的`debugfile_BL.txt`和`debugfile_BL_Change.txt`中。同时也会在`./code/outputs/BL/recs/`中生成用于可视化的文件。

4. `./code/scripts/pycode/`中的两个python文件仅是为了绘制曲线和可视化结果所用。由于只针对比较特殊的文件，若真正运行，可能需要修改一些细节。由于这不是项目的主要内容，这里不过多展开。

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


