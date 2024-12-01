#import "../report-template/template.typ": *
#import "@preview/algo:0.3.3": algo, i, d, comment, code

#show: project.with(
  theme: "project",
  course: "Advanced Data Structures and Algorithm Analysis",
  title: [Project 6: \ Texture Packing],
  cover_image_size: 50%,
  cover_image_padding: 1em,
  semester: "2024-2025 Autumn&Winter",
  // author: [Huang Xingyao\ $quad quad$ Qian Ziyang],
  school_id: "",
  date: "2024-11-30",
  table_of_contents: true
)

= Chapter 1: Introduction

== Problem Description

#v(.5em)

The project require us to design #fakebold[approximation algorithms] running in polynomial time to solve #fakebold[Texture Packing] problem. We can regard it as a #underline[2-dimension bin packing], with items("rectangle texture" in the problem) and bins("resulting texture" in the problem) having both width and height, but we only need a single bin with #fakebold[bounded width] and #fakebold[unbounded height], and we should keep the bin with a (nearly) minimum height.

== Backgound of Data Structures and Algorithms

=== FFDH Algorithm

#v(.5em)

Just like texture packing problem is the 2D version of bin packing problem, the #fakebold[FFDH] (i.e. First-Fit Decreasing-Height) algorithm is also the 2D version of FFD algorithm in bin packing problem. 

- It's an #fakebold[offline algorithm], which means that the algorithm doesn't process the input data unless it gets all input data, and in our algorithm, all items should be sorted by their height in a decreasing order.
- Before placing the current item, the algorithm scans the levels from bottom to top in the bin, then #underline[places the item in the first level where it will fit]. 
- A new level will be created only if the item does not fit in any previous ones.

#figure(image("images/1.png", width: 95%), caption: "FFDH Approximation Algorithm")

=== Advanced Approximation Algorithm

#v(.5em)


= Chapter 2: Algorithm Specification

#v(.5em)

In this chapter, we will introduce approximation algorithms of FFDH(basic version) and (advanced version) in details, including aspects below, to enable readers have a comprehensive and thorough understanding of these algorithm.

- Description of approximation algotithms with pseudocodes.
- Calculation of approximation ratio of algorithm with proof.

Beware that our project doesn't use complex data structures and we only use arrays and structures in C, so it's meaningless to introduce them and we should only focus on the algorithm implementation.

== FFDH Algorithm

#v(.5em)

Initially, let's take a look at the pseudocode of FFDH to gain a deeper insight into this kind of approximation algorithm.

#algo(
  header: [
    #fakebold[Inputs]:
    - _W_: Fixed width of the bin(i.e. resulting texture)
    - _n_: The number of items
    - _rect_: Multiple rectangle texture, i.e. items
    - _isDebug_: Flag of debug mode
    - _outFile_: Flag of file output mode
    
    #fakebold[Outputs]: 
    - _curHeight_: the "minimum" height of the bin 

    #fakebold[Procedure]: FFDH(_W_: #fakebold[double], _n_: #fakebold[integer], _rect_: #fakebold[Item array], _isDebug_: #fakebold[bool], _outFile_: #fakebold[bool]) 
  ],
  block-align: left,
)[
  Begin #i\ 
  Sort _rect_[] by item's height in decreasing order \ 
  for _item_ in _rect_[] do #i \
    for _level_ in existing levels do #i \
      if _level_'s width + _item_[i]$->$_width_ $<=$ _W_ then #i \
        put the _item_ into this level and update the state \
        break #d \
      end #d \

    if no level can fit the _item_ then #i \
      create a new level \ 
      put the _item_ into this level \ 
      update the state #d \
    end #d \
  end  \

  print debug info if the user using the debug mode \

  return the current height of the bin as the "minimum" height #d \
  End
]

We can divide the procedure into four steps:

1. Sort all items by their height in decreasing order.
2. For all items, put them into the bin in the sorted order.
  - Scan all levels from bottom to top, find the first level that can accomodate the current item.
  - If no levels can fit it, then create a new level and put it into the new level.
3. (if necessary)Print the debug info, including:
    - the height-decreasingly sorted item data,
    - the occupied-by-items width for each level,
    - the positions of items.
4. Return the current height of the bin as the "minimum" height.

#line(length: 100%, stroke: .3pt)

Now we should figure out the approximation ratio of this algorithm. We claim that FFDH algorithm is a #fakebold[2-approximation algorithm]. Here is the proof:

#let render(theme_name) = [
  #state_block_theme.update(theme_name)

  #proof(name: [Proof])[
    Assume that:

    - all items have been sorted by their height in decreasing order
    - $L$: the list of items
    - $O P T(L)$: the optimal solution(the actual minimum height) of texture packing
    - $F F D H(L)$: the solution attained from the FFDH algorithm
    - $w_i$: the width of the ith item
    - $h_i$: the height of the ith item
      - $h_0$: the highest height
    - $W$: the fixed width of the bin
    - $A = sum_(i=1)^n w_i dot h_i$：the total area of all items

    First of all, we can determine the upper bound of the $O P T(L)$

    - Obviously, $O P T(L) gt.eq h_0$
    - $O P T(L) gt.eq frac(A, W)$, because the item on the right side represents the ideal result when all items fill the bin "tightly", i.e. no space waste in the bin.


    Claim: $F F D H(L)$ satisfies the inequality below:

    $ F F D H(L) lt.eq frac(A, W) + h_0 lt.eq 2 O P T(L) $

    - let $h_r = F F D H(L) - h_0$, which is the remaining height of the bin in FFDH algorithm
    - then we should prove that $h_r lt.eq frac(A, W)$. Because this approximation algorithm is also a #fakebold[greedy algorithm], which always put the highest item into the bin first, it ensures that the correctness of this inequality

    As a consequence, the approximation ratio $rho = frac(F F D H(L), O P T(L)) lt.eq 2$, and we can guarantee that FFDH is a 2-approximation algorithm.


    Beware that our proof is not very rigor, and the actual approximation ratio may be less than 2.
  ]

  #v(.5em)
]
#render("thickness")


== Advanced Approximation Algorithm

= Chapter 3: Testing Results

#v(.5em)

In this chapter, we will test our approximation algorithms to check their correctness and performance, which lays a solid foundation for our following analysis on time complexity. We will use test tables and curve diagrams to make our explanation more graphically and vividly.

== FFDH Algorithm

=== Correctness Tests

#v(.5em)

*Test 1*

- Purpose: check the correctness in #fakebold[the normal case, with relatively small waste space]. 
- Input: See the input file in directory `./code/test/FFDH/input1`
- Expected Result:

#figure(image("images/2.png", width: 50%), caption: "Correctness Test 1 for FFDH Algorithm")

- Actual Result: 

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/test/FFDH/output1`][
```
Debug Info:
Height-decreasingly sorted item data:
0: 6.00, 8.00
1: 5.00, 7.00
2: 4.00, 6.00
3: 7.00, 5.00
4: 3.00, 4.00
5: 4.00, 3.00
6: 6.00, 2.00

Total level: 2
Width:
0 level: 18.00
1 level: 17.00

Position:
Item 0: level 0
Item 1: level 0
Item 2: level 0
Item 3: level 1
Item 4: level 0
Item 5: level 1
Item 6: level 1
====================================
The total height: 35.00
The ideal height(Area / Width): 9.89
The "minimum" height: 13.00
```
]

As the debug info show above, our program can figure out this case #text(green)[properly].

*Test 2*

- Purpose: check the correctness in #fakebold[the normal case, with relatively large waste space]. 
- Input: See the input file in directory `./code/test/FFDH/input2`
- Expected Result:

#figure(image("images/3.png", width: 90%), caption: "Correctness Test 2 for FFDH Algorithm")

- Actual Result:

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/test/FFDH/output2`][
```
Debug Info:
Height-decreasingly sorted item data:
0: 4.00, 10.00
1: 6.00, 7.00
2: 2.00, 6.00
3: 15.00, 5.00
4: 13.00, 4.00
5: 17.00, 3.00

Total level: 4
Width:
0 level: 12.00
1 level: 15.00
2 level: 13.00
3 level: 17.00

Position:
Item 0: level 0
Item 1: level 0
Item 2: level 0
Item 3: level 1
Item 4: level 2
Item 5: level 3
====================================
The total height: 35.00
The ideal height(Area / Width): 15.11
The "minimum" height: 22.00
```
]

As the debug info show above, our program can figure out this case #text(green)[properly]. However, there is some bias for the calculation of the algorithm calculated and the optimal solution.


*Test 3*

- Purpose: check the correctness in #fakebold[the large-scale case, with very large waste space]. 
- Input: See the input file in directory `./code/test/FFDH/input3`
- Expected Result:

#figure(image("images/4.png", width: 100%), caption: "Correctness Test 3 for FFDH Algorithm")

- Actual Result:

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/test/FFDH/output3`][
```
Debug Info:
Height-decreasingly sorted item data:
0: 2.00, 10000.00
1: 2.00, 2.00
2: 18.00, 1.00
3: 18.00, 1.00
...
10000: 18.00, 1.00
10001: 18.00, 1.00

Total level: 10001
Width:
0 level: 4.00
1 level: 18.00
2 level: 18.00
3 level: 18.00
...
9999 level: 18.00
10000 level: 18.00

Position:
Item 0: level 0
Item 1: level 0
Item 2: level 1
Item 3: level 2
...
Item 10000: level 9999
Item 10001: level 10000
====================================
The total height: 20002.00
The ideal height(Area / Width): 10000.20
The "minimum" height: 20000.00
```
]

As the debug info show above, our program can figure out this case #text(green)[properly]. However, there is very big bias for the calculation of the algorithm calculated and the optimal solution, and $frac(F F G H(L), O P T(L)) approx 2$, where $F F D H(L)$ and $O P T(L)$ are the solution of FFFH algorithm and optimal solution respectively.

=== Performance Tests

#v(.5em)

The dominant factor having infulence on the time complexity in FFDH algorithm is *the number of items*, i.e. the input size. Consequently, we will show the correlation between run time and input sizes by running our program in distinct input sizes, which are listed in the test table with corresponding results below.

Note that our randomly-generated input data complies the #underline[uniform distribution], which means that all numbers within the specified range will be selected for equal possible(this description is not mathematically rigor, because the probability of choosing one single number is zero).

#show table.cell.where(x: 0): strong

#set text(size: 12pt)

#figure(
  table( 
    fill: (x, y) =>
    if x == 0 {
      gray.lighten(80%)
    },
    align: center + horizon,
    columns: (10em, 1fr, 1fr, 1fr, 1fr, 1fr), [Number of Items], [10,000], [20,000], [40,000], [80,000], [160,000], [Iterations], [100], [50], [10], [5], [1], [Ticks], [4068], [7560], [6113], [12382], [10304], [Total Time(s)], [4.068], [7.560], [6.113], [12.382], [10.304], [Duration(s)], [0.04068], [0.1512], [0.6113], [2.4764], [10.304]), caption: "Performance Tests for FFDH Algorithm"
)

#set text(size: 14pt)

Based on the table above, we use a Python program to draw the curve diagram of run time--input size, representing the time complexity of FFDH algorithm in a graphic and direct way.

#figure(image("images/FFDH_diagram.png", width: 110%), caption: "Curve Diagram for FFDH Algorithm in Performance Test")

We use a *quadratic polynomial curve* fitting data point, and find that there is such a curve, $y = 4.19 times 10^(-10) x^2 + 2.89 times 10^(-6) x + 3.83 times 10^(-2)$, that can pass almost all the data points, which shows that the FFDH algorithm can complete the calculation within the quadratic polynomial time. The theoretical analysis of time complexity will be explained in Chapter 4.



== Advanced Approximation Algorithm

=== Correctness Tests

=== Performance Tests

= Chapter 4: Analysis and Comments

#v(.5em)

== Space Complexity

*Conclusion*:

- FFDH algorithm: $O(N)$, $N$ is the number of items.
- advanced approximation algorithm:

*Analysis*:

- FFDH algorithm: Except the single variables, we have used some arrays, including `rect[]`, `curWidth[]` and `pos[]`, which contain the infomation of items, current width for each level and the position of each item respectively. Apparently, the level is less than or equal to the number of items(we use $N$ to represent it). As a consequence, these three arrays are proportional to $N$, and the total space is less than $c dot N$, when $c$ is just a constant.

- advanced approximation algorithm:

== Time Complexity

*Conclusion*:

- FFDH algorithm: $O(N^2)$, $N$ is the number of items.
- advanced approximation algorithm:

*Analysis*:

- FFDH algorithm:
  - Before putting all items into the bin serially, we use the built-in function `qsort()`(i.e. the quick sort) to sort these items by their height in decreasing order. As we known in FDS course, the average time complexity of quicksort is $O(N log N)$, and the worst time complexity is $O(N^2)$
  - Now let's consider the core part of FFDH algorithm: it consists of a loop with two layers, the outer one corresponds to $N$ directly, the inner one is controlled by `level`. As we have analyzed in Space Complexity, `level` $lt.eq N$. So the overall time consumption of the loop is less than $c N^2$, when $c$ is a constant
  - The last part of the algorithm is printing the debug info. Since it just prints the information of items sequentially, its time complexity is just $O(N)$
  - In a nutshell, the total time complexity is $O(N^2)$
- advanced approximation algorithm:

== Further Improvement

#v(.5em)

= Appendix: Source code

== File Structure

#table(columns: 1fr, align: left)[
```
.
├── code
│   ├── README.md
│   ├── build
│   │   └── Makefile
│   ├── scripts
│   │   ├── generate.cpp
│   │   ├── ttpHeader.h
│   │   ├── ttpMain.cpp
│   │   ├── FFDH.cpp
│   │   ├── curve.py
│   │   └── 
│   └── test
│       ├── FFDH
│       │   ├── input1
│       │   ├── input2
│       │   ├── input3
│       │   ├── output1
│       │   ├── output2
│       │   └── output3
│       └── 
└── documents
    └── report.pdf
  ```
]

== ttpHeader.cpp

#importCode("../code/scripts/ttpHeader.h")

== ttpMain.cpp

#importCode("../code/scripts/ttpMain.cpp")

== FFDH.cpp

#importCode("../code/scripts/FFDH.cpp")

= Declaration

#v(.5em)

#fakebold[#fakeitalic[We hereby declare that all the work done in this project titled "Texture Packing" is of our independent effort as a group.]]

// = Signatures

// #align(center)[
// #grid(columns: 2)[
//   #image("images/signature_hxy.png", width: 60%)
// ][#image("images/signature_qzy.jpg", width: 60%)]
// ]