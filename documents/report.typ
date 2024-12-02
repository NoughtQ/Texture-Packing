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
  date: "2024-12-02",
  table_of_contents: true
)

= Chapter 1: Introduction

== Problem Description

#v(.5em)

The project require us to design #fakebold[approximation algorithms] running in polynomial time to solve #fakebold[Texture Packing] problem. We can regard it as a #underline[2-dimension bin packing], with items("rectangle texture" in the problem) and bins("resulting texture" in the problem) having both width and height, but we only need a single bin with #fakebold[bounded width] and #fakebold[unbounded height], and we should keep the bin with a (nearly) minimum height.

== Backgound of Algorithms

=== BL Algorithm

#v(.5em)

#fakebold[BL algorithm] (Bottom-up left-justified algorithm) was first described by Baker et al. It works as follows: Let $L$ be a sequence of rectangular items. The algorithm iterates the sequence in the given order. For each considered item $r in L$ , it searches for the bottom-most position to place it and then shifts it as far to the left as possible. Hence, #underline[it places at the bottom-most left-most possible coordinate $(x,y)$ in the strip].


=== FFDH Algorithm

#v(.5em)

Just like texture packing problem is the 2D version of bin packing problem, the #fakebold[FFDH] (i.e. First-Fit Decreasing-Height) algorithm is also the 2D version of FFD algorithm in bin packing problem. 

- It's an #fakebold[offline algorithm], which means that the algorithm doesn't process the input data unless it gets all input data, and in our algorithm, all items should be sorted by their height in a decreasing order.
- Before placing the current item, the algorithm scans the levels from bottom to top in the bin, then #underline[places the item in the first level where it will fit]. 
- A new level will be created only if the item does not fit in any previous ones.

#figure(image("images/1.png", width: 95%), caption: "FFDH Approximation Algorithm")

=== Mersenne Twister Algorithm

#v(.5em)
   
The Mersenne Twister is an efficient pseudo-random number generator known for its long period and high-quality random numbers. It's based on a specific Mersenne prime (a prime number of the form \($2^p - 1$\)), using a 624-word state vector of 32-bit integers. It generates random numbers through a series of bit operations like shifts and masks. Widely used for its speed, long period, and randomness quality.


= Chapter 2: Algorithm Specification

#v(.5em)

In this chapter, we will introduce approximation algorithms of FFDH(basic version) and (advanced version) in details, including aspects below, to enable readers have a comprehensive and thorough understanding of these algorithm.

- Description of approximation algotithms with pseudocodes.
- Calculation of approximation ratio of algorithm with proof.

== BL Algorithm

#v(.5em)

First of all, we provide the pseudocode of BL algorithm below.

#algo(
  header: [
    #fakebold[Procedure]:BL(_rect_: #fakebold[POINT array], _W_: #fakebold[double], _n_: #fakebold[integer],  _isDebug_: #fakebold[bool], _debugFile_: #fakebold[string]) 
  ],
  block-align: left,
)[
  Begin #i\ 
  Initialize upBound list with rightmost and initial points \
  Set _maxHeight_ to 0 \
  Sort _recs_ by width in descending order \

  while there is _rec_ remained do #i\
    Find the proper position of the rec \
    Place the rectangle and update upBound \
    Update _maxHeight_ if needed \
    If _isDebug_, log upBound #d\
  end \

  If _isDebug_, log all _recs_ \
  return _maxHeight_ #d \
  End
]

Among them, upBound is maintained through a #fakebold[bidirectional linked list]. The implementation of the bidirectional linked list is to directly call the `list` in the STL container.The reason for using a bidirectional linked list is that we need to frequently insert and delete upBound, but the need for search operations is very small.

Each element is a `POINT` structure as shown below.

#table(align: left, columns: 1fr, stroke: .5pt)[

```cpp
struct POINT{
    double x;
    double y;
    double width;

    //Overload the equal operator
    bool operator==(const POINT& other)
    {
        return x==other.x && y==other.y && width==other.width;
    };
};
```

]

we determine a line segment by determining the left endpoint coordinates and the length of the line segment. we record all the line segments that can be covered by the projection from top to bottom in order from right to left.

For example, for the following situation:

#figure(image("images/6.png", width: 60%), caption: "An Example for Records of Line Segments")

The upBound will be describe as below:

#table(align: left, columns: 1fr, stroke: .5pt)[
```
x: 100 y: 0 width: 0        #Acting as a sentinel without affecting the results
x: 97 y: 217 width: 3
x: 59 y: 265 width: 38
x: 55 y: 191 width: 4
x: 53 y: 273 width: 2
x: 38 y: 250 width: 15
x: 30 y: 278 width: 8
x: 0 y: 259 width: 30
```
]


=== Algorithm Analysis

#v(.5em)

This algorithm is a 3-approximation algorithm after sorting the rectangles in descending order of width. Here is the proof:

#let render(theme_name) = [
  #state_block_theme.update(theme_name)

  #proof(name: [Proof])[
Let $h^*$ denote the the height of the lower edge of a tallest piece whose upper edge is at height $h_"BL"$. If $y$ denote the height of this piece, then $h_"BL"=h^*+y$.Let $A$ denote the region of the bin up to height $h^*$.

Suppose $A$ is at least half occupied. Then we have $h_"OPT" gt.eq max(y,h^* / 2)$;

hence, $y > h^* / 2$ implies:

$
frac(h_"BL", h_"OPT") lt.eq frac(y+h^*, y) < frac(y+2y, y)=3
$

and if $y lt.eq h^* / 2$, we have:

$
frac(h_"BL", h_"OPT") lt.eq frac(h^* / 2+h^*, h^* / 2)=3
$

As a result, we only need to show that $A$ is at least half occupied.

We assert that for every horizontal line in area $A$, the sum of the lengths of the lines crossing the rectangle must be no less than the sum of the lengths of the lines crossing the blank area.(We can ignore all lines that cross the intersection of the rectangles, since obviously they have measure 0)

This conclusion is guaranteed by the following facts:

1. Each horizontal line must pass through a rectangle attached to the left edge. This is obvious because the width of the placed rectangle is decreasing.
2. Assuming that the horizontal line $l$ passes through a blank area $S$, it is guaranteed by 1 that there must be a rectangle on its left. Secondly, it is obvious that the width of the rectangle on the left is greater than the width of $S$, which is guaranteed by the fact that the width of the rectangle placed in the upper layer must be greater than $S$ (if not, $S$ can be placed in a new rectangle, and the width of the upper rectangle is not greater than the rectangle on the left of $S$)

Therefore, for each horizontal line l in A, it must meet our assertion.
Integrating each line, it can be seen that half of the area in A is occupied.
  ]

  #v(.5em)
]
#render("thickness")

=== BL_Change: A Failed Attempt

#v(.5em)

We try to optimize the order of rectangles. Divide all rectangles into two groups, one with a width less than w/2, and sort them in descending order of height/width; the other with a width greater than w/2, and sort them in descending order of width.

This optimization order is based on the following observations:
In the original algorithm, rectangles larger than w/2 are almost all arranged in a single row, resulting in a large waste of space on the right side.

But we failed to do better in my implementation. This optimization algorithm only has a slight advantage in small and medium-sized data. When the data volume is large enough, it will cause greater space waste due to the defects of my own algorithm implementation.

== FFDH Algorithm

#v(.5em)

The main data structure we used is a `struct` called `Item`. Each `Item` contains four elements(all double values): `width`, `height`, `x` and `y`, which represent the width, the height and the lower left point of the item respectively.

#figure(image("images/5.png", width: 30%), caption: [The `struct Item`])

Now let's take a look at the pseudocode of FFDH to gain a deeper insight into this kind of approximation algorithm.

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
  breakable: true
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

1. #fakebold[Sort] all items by their height in decreasing order.
2. For all items, put them into the bin in the sorted order.
  - Scan all levels from bottom to top, #fakebold[find the first level that can accomodate the current item].
  - If no levels can fit it, then #fakebold[create a new level] and put it into the new level.
3. (if necessary)#fakebold[Print the debug info], including:
    - the height-decreasingly sorted item data,
    - the occupied-by-items width for each level,
    - the positions of items.
4. #fakebold[Return] the current height of the bin as the "minimum" height.


Now we should figure out the approximation ratio of this algorithm. It was proved that FFDH algorithm is a #fakebold[2.7-approximation algorithm] (the conclusion is given by Wikipedia). Because it is difficult for us to prove this approximation ratio based on our mathematical knowledge, and the relevant proof content cannot be directly checked on the Internet (need to pay to unlock the paper), so unfortunately the proof part is omitted.

== Large-scale Random Number Generation Strategy

#v(.5em)

Here we only take the generation of uniformly distributed integers as an example. The codes for other types are similar.The following code only shows the most basic operations. With these distributed numbers, generating samples is easy.

#table(align: left, columns: 1fr, stroke: .5pt)[
```cpp
#include<random>
using namespace std;

...
    random_device seed;
    mt19937 gen(seed());
    
    uniform_int_distribution<> height(1, maxHeight);
    h = height(gen);
...
```
]

The basic process is to call `random_device` to generate a random number seed, call `mt19937` to generate a relatively high-quality pseudo-random number, and call the corresponding random distribution class to convert the pseudo-random number into the random variable we need.

== Optimal Solution Sample Generation Strategy

#v(.5em)

#algo(
  header: [
    #fakebold[Procedure]: square_generate(_Height_: #fakebold[double], _Width_: #fakebold[double], _hNum_: #fakebold[integer], _wNum_: #fakebold[integer]) 
  ],
  block-align: left,
  breakable: true
)[
  Begin #i\ 
    Initialize _recs_ as an empty vector \
    Initialize random number generator _gen_ \
    Initialize uniform distributions height and width \
    \
    Initialize vectors _hp_ and _wp_ \
    Add 0 and _Height_ to _hp_ \
    Add 0 and _Width_ to _wp_ \
    \
    while (the size of _hp_ is less than _hNum_ + 1) do #i \
        Generate a random number _h_ \
        If _h_ is not in _hp_ then #i \
            Add _h_ to _hp_ #d \
        end #d\
    end \
    \ 
    while (the size of _wp_ is less than _wNum_ + 1) do #i \
        Generate a random number _w_ \
        If _w_ is not in _wp_ then #i \
            Add _w_ to _wp_ #d \
        end #d \
    end \
    \
    Sort _hp_ and _wp_ \
    \
    for _i_ from 1 to _hNum_ do #i \
        for _j_ from 1 to _wNum_ do #i \
            Calculate the width and height of the rectangle \
            Add the rectangle to _recs_ #d \
        end #d \
    end \
    \
    return _recs_ #d \
  End
]

As shown in the pseudo code, the large rectangle is divided into _hNum_ $dot$ _wNum_ blocks by generating split points on the edges of the large rectangle.


= Chapter 3: Testing Results

#v(.5em)

In this chapter, we will test our approximation algorithms to check their correctness and performance, which lays a solid foundation for our following analysis on time complexity. We will use test tables and curve diagrams to make our explanation more graphically and vividly.

== BL Algorithm

=== Correctness Tests

#v(.5em)

How to verify the correctness of an approximate algorithm? We think that it is only necessary to ensure that the approximate algorithm runs as expected and does not violate the requirements.

The following three examples test three typical situations: 

- The first group is a simple case of a full square, which is easy to judge whether the logic is correct. 
- The second group is a more general rectangle, which can be used to see whether the more complex position relationship is correct. 
- The third group is a special case where there is an optimal solution, in which the sizes of the rectangles are close and there are no extreme rectangles. It can be seen that in the newer version.

*Sample 1*

- Input: 10 squares with a side length of 6 and the width is 20
- Output figure:
  
#figure(image("images/7.png", width: 60%), caption: "Correctness Test 1 for BL Algorithm")

- Comment: The result is as expected.

*Sample 2*

- Input: 10 randomly generated rectangles and the width is 100

#table(align: left, columns: 1fr, stroke: .5pt)[
```
100 10
99 54
2 82
8 28
38 99
59 51
78 86
30 9
3 51
39 26
53 59
```
]

- Output figure:
  
#figure(image("images/8.png", width: 60%), caption: "Correctness Test 2 for BL Algorithm")

- Comment: The result is as expected.

*Sample 3*

- Input：This is an example of random rectangles generated by the second type of random rectangles introduced above. The size of the large rectangle is 400 $times$ 200, and a total of `4*4` rectangles are generated.
  


#table(align: left, columns: 1fr, stroke: .5pt)[
```
200 16
86 272
5 272
45 272
64 272
86 72
5 72
45 72
64 72
86 13
5 13
45 13
64 13
86 43
5 43
45 43
64 43
```
]

- Output figure:
  
#figure(image("images/9.png", width: 60%), caption: "Correctness Test 3 for BL Algorithm")

- Comment: The result is as expected.

=== Performance Tests

#v(.5em)

In order to simulate the real scene as realistically as possible, we selected samples generated by uniform distribution and normal distribution for time testing.

Since there is no essential difference between the floating point case and the integer case, 
only the integer case is analyzed here.


*Uniform distribution*

#figure(
  table( 
    fill: (x, y) =>
    if x == 0 {
      gray.lighten(80%)
    },
    align: center + horizon,
    columns: (1fr, 1fr, 1fr), [File name], [Size], [Time(s)], [uniform_int_10], [10], [0.00029159], [uniform_int_50], [50], [0.000112231], [uniform_int_100], [100], [0.0004264], [uniform_int_500], [500], [0.001882206], [uniform_int_1000], [1000], [0.006107088], [uniform_int_5000], [5000], [0.0226485], [uniform_int_10000], [10000], [0.0588621], ), caption: "Performance Tests for BL Algorithm in Uniform Distribution"
)

The curve is drawn as follows:

#figure(image("images/BL_diagram_Ui.png", width: 100%), caption: "Curve Diagram for BL Algorithm in Uniform Distribution")

*Normal distribution*

#figure(
  table( 
    fill: (x, y) =>
    if x == 0 {
      gray.lighten(80%)
    },
    align: center + horizon,
    columns: (1fr, 1fr, 1fr), [File name], [Size], [Time(s)], [normal_int_10], [10], [0.000039636], [normal_int_50], [50], [0.000127671], [normal_int_100], [100], [0.00043265], [normal_int_500], [500], [0.001962675], [normal_int_1000], [1000], [0.00571202], [normal_int_5000], [5000], [0.02116575], [normal_int_10000], [10000], [0.05734626], ), caption: "Performance Tests for BL Algorithm in Normal Distribution"
)

The curve is drawn as follows:

#figure(image("images/BL_diagram_Ni.png", width: 100%), caption: "Curve Diagram for BL Algorithm in Normal Distribution")

*Analysis*:

From the time complexity analysis in chapter 4, we can see that the time complexity of the BL algorithm is $O(n^2)$. However, in actual measurement, the secondary factor is not significant. The main reason may be that it is difficult for `upBound` to maintain an average size of $O(n)$ when the data scale is small, making the primary factor more prominent.

== FFDH Algorithm

=== Correctness Tests

#v(.5em)

*Sample 1*

- Purpose: check the correctness in #fakebold[the normal case, with relatively small waste space]. 
- Input: See the input file in directory `./code/inputs/FFDH/inputs/input1`
- Expected Result:

#figure(image("images/2.png", width: 50%), caption: "Correctness Test 1 for FFDH Algorithm")

- Actual Result: 

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/outputs/FFDH/outputs/output1`][
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
Item 1: level 0, x: 0.00, y: 0.00
Item 2: level 0, x: 6.00, y: 0.00
Item 3: level 0, x: 11.00, y: 0.00
Item 4: level 1, x: 0.00, y: 8.00
Item 5: level 0, x: 15.00, y: 0.00
Item 6: level 1, x: 7.00, y: 8.00
Item 7: level 1, x: 11.00, y: 8.00
====================================
The total height: 35.00
The ideal height(Area / Width): 9.89
The "minimum" height: 13.00

```
]

As the debug info show above, our program can figure out this case #text(green)[properly].

*Sample 2*

- Purpose: check the correctness in #fakebold[the normal case, with relatively large waste space]. 
- Input: See the input file in directory `./code/inputs/FFDH/inputs/input2`
- Expected Result:

#figure(image("images/3.png", width: 90%), caption: "Correctness Test 2 for FFDH Algorithm")

- Actual Result:

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/outputs/FFDH/outputs/output2`][
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
Item 1: level 0, x: 0.00, y: 0.00
Item 2: level 0, x: 4.00, y: 0.00
Item 3: level 0, x: 10.00, y: 0.00
Item 4: level 1, x: 0.00, y: 10.00
Item 5: level 2, x: 0.00, y: 15.00
Item 6: level 3, x: 0.00, y: 19.00
====================================
The total height: 35.00
The ideal height(Area / Width): 15.11
The "minimum" height: 22.00
```
]

As the debug info show above, our program can figure out this case #text(green)[properly]. However, there is some bias for the calculation of the algorithm calculated and the optimal solution.


*Sample 3*

- Purpose: check the correctness in #fakebold[the large-scale case, with very large waste space]. 
- Input: See the input file in directory `./code/inputs/FFDH/inputs/input3`
- Expected Result:

#figure(image("images/4.png", width: 100%), caption: "Correctness Test 3 for FFDH Algorithm")

- Actual Result:

#table(align: left, columns: 1fr, stroke: .5pt)[`./code/outputs/FFDH/outputs/output3`][
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
Item 0: level 0, x: 0.00, y: 0.00
Item 1: level 0, x: 2.00, y: 0.00
Item 2: level 1, x: 0.00, y: 10000.00
Item 3: level 2, x: 0.00, y: 10001.00
...
Item 10000: level 9999, x: 0.00, y: 19998.00
Item 10001: level 10000, x: 0.00, y: 19999.00
====================================
The total height: 20002.00
The ideal height(Area / Width): 10000.20
The "minimum" height: 20000.00
```
]

As the debug info show above, our program can figure out this case #text(green)[properly]. However, there is very big bias for the calculation of the algorithm calculated and the optimal solution, and $frac(F F G H(L), O P T(L)) approx 2 lt.eq 2.7$, where $F F D H(L)$ and $O P T(L)$ are the solution of FFFH algorithm and optimal solution respectively.

=== Performance Tests

#v(.5em)

The dominant factor having infulence on the time complexity in FFDH algorithm is *the number of items*, i.e. the *input size*. Consequently, we will show the correlation between run time and input sizes by running our program in distinct input sizes, which are listed in the test table with corresponding results below.

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

== Comparative Analysis

=== FFDH Advantages analysis

#v(.5em)

Take the result graph generated by uniform_int_100 test data as an example.



#set text(size: 10pt)

#grid(columns: (1fr, 1fr, 1fr))[#figure(image("images/10.png"), caption: "Ui_100_BL.png")][#figure(image("images/11.png"), caption: "Ui_100_C.png")][#figure(image("images/12.png"), caption: "Ui_100_F.png")]

#set text(size: 14pt)

It can be seen that the FFDH algorithm has a higher space utilization rate. The main reason is that BL and even the failed improved algorithms of BL cannot solve the huge space waste caused by sorting by width. For example, in the BL algorithm, after sorting by width, all rectangles with a width greater than w/2 have to be arranged in a separate row, and the degree of space waste on the other side is much greater than the degree of space waste in the vertical direction of the FFDH algorithm.
This makes the FFDH algorithm obtain better results in almost all our test samples.

=== Failure of algorithm improvement

#v(.5em)

Here is a more detailed explanation of the failure of the BL_change algorithm. Take the generated image of the normal_int_10000 test data as an example.

#grid(columns: (1fr, 1fr))[#figure(image("images/13.png"), caption: "Ni_100_BL.png")][#figure(image("images/14.png"), caption: "Ni_100_C.png")]

There is a very obvious anomaly in the upper half of the image of the improved algorithm. The reason is that I did not fully implement the BL algorithm to put the rectangle as far to the left as possible (my implementation method was to put the rectangle at the lowest position that can be placed, and then take the leftmost position node).
However, due to time constraints, we were unable to fix this problem.

= Chapter 4: Analysis and Comments

#v(.5em)

== Space Complexity

#v(.5em)

*Conclusion*:

Both BL algorithm and FFDH algorithm are $O(N)$, where$N$ is the number of items.

*Analysis*:

- #fakebold[BL algorithm]:
  - Storing rectangle information:
    - Rectangle information is stored in `vector<rectangle> *recs`, with a space complexity of $O(N)$.
  - Store upper bound information:
    - The upBound list stores the upper bound information, which contains $n$ elements in the worst case, and has a space complexity of $O(N)$.
  - Temporary variables and auxiliary data structures:
    - vector<POINT> kill is used to store the points to be deleted, which contains $n$ elements in the worst case, and has a space complexity of $O(N)$.
    - Other temporary variables (such as height, rightPoint, pointCase, etc.) occupy constant space, and have a space complexity of $O(1)$.

  Based on the above analysis, the space complexity of the entire algorithm is $O(N)$.

- #fakebold[FFDH algorithm]: Except the single variables, we have used some arrays, including `rect[]`, `curWidth[]` and `pos[]`, which contain the infomation of items, current width for each level and the position of each item respectively. Apparently, the level is less than or equal to the number of items(we use $N$ to represent it). As a consequence, these three arrays are proportional to $N$, and the total space is less than $c dot N$, when $c$ is just a constant.


== Time Complexity

#v(.5em)

*Conclusion*:

Both BL algorithm and FFDH algorithm are $O(N^2)$, where$N$ is the number of items.


*Analysis*:

- #fakebold[BL algorithm]:

  - #fakebold[Initialization and sorting]:
    - `sort`: The time complexity of the sorting operation is $O(N log N)$.
  - #fakebold[Main loop]:
    - The main loop `while (cnt < (*recs).size())` runs $n$ times.
    - In each loop, the inner loop `for (auto p=upBound.begin(); p!=upBound.end(); p++)` traverses the upBound list. The length of the upBound list can reach $n$ in the worst case, so the time complexity of the inner loop is $O(N)$.
    - In the inner loop, there is also a nested loop `for (auto it=p; it!=upBound.begin(); it--)`, which also needs to traverse the upBound list in the worst case, with a time complexity of $O(N)$.
    - Overall, the time complexity of the main loop is $O(N^2)$.
  - #fakebold[Insert and delete operations]:
    - Operations such as `upBound.insert(p, {...})` and `upBound.remove(*p)` require $O(N)$ time in the worst case, because upBound is a linked list.

  Based on the above analysis, the time complexity of the entire algorithm is $O(N^2)$.

- #fakebold[FFDH algorithm]:
  - Before putting all items into the bin serially, we use the built-in function `qsort()`(i.e. the quick sort) to sort these items by their height in decreasing order. As we known in FDS course, the average time complexity of quicksort is $O(N log N)$, and the worst time complexity is $O(N^2)$.
  - Now let's consider the core part of FFDH algorithm: it consists of a loop with two layers, the outer one corresponds to $N$ directly, the inner one is controlled by `level`. As we have analyzed in Space Complexity, `level` $lt.eq N$. So the overall time consumption of the loop is less than $c N^2$, when $c$ is a constant.
  - The last part of the algorithm is printing the debug info. Since it just prints the information of items sequentially, its time complexity is just $O(N)$.
  - In a nutshell, the total time complexity is $O(N^2)$.


== Further Improvement

#v(.5em)

1. #fakebold[Algorithm Refinement]: 
  - Use a modified version of the RF algorithm. First, put rectangles with a width greater than w/2 at the bottom in order. Then sort rectangles with a width less than w/2 by height. Take a layer from the remaining rectangles each time (similar to the FFDH algorithm), and then alternately descend (similar to BL, but once as close to the lower right as possible, once as close to the lower left as possible, and alternately).
  - Since the RF algorithm is a 2-approximation algorithm, this algorithm can probably also be close to 2-approximation.


2. #fakebold[Testing sample construction]: Although we come up with some samples for correctness tests, probably some crucial tests are still lost, and potential bugs may exists in our programs owing to our incomplete consideration. From our standpoint, it's difficult to find all cases for a program, but we're fully convinced that by delicate techniques and tricks for testing results, we can come up with tests as complete as possible.

3. #fakebold[Original algorithm design]: Since there are many approximation algorithms that solve such problems nowadays, and our ability and time are limited, the two algorithms we implemented are actually based on existing algorithms (but we only refer to the algorithm theory, the code is our originality). In the future, with the comprehensive understanding of the approximity algorithm, we believe that we have the ability to design a completely original approximate algorithm.

= Appendix: Source code

== File Structure

#table(columns: 1fr, align: left)[
```
.
├── code
│   ├── README.md
│   ├── build
│   │   └── Makefile
│   ├── fig
│   ├── inputs
│   │   ├── BL
│   │   └── FFDH
│   ├── outputs
│   │   ├── BL
│   │   └── FFDH
│   └── scripts
│       ├── headers
│       │   ├── header.h
│       │   └── ttpHeader.h
│       ├── BL.cpp
│       ├── BLMain.cpp
│       ├── generate.cpp
│       ├── generate_main.cpp
│       ├── ttpMain.cpp
│       ├── FFDH.cpp
│       ├── curve.py
│       └── draw.py
└── documents
    └── report.pdf
  ```
]

== header.h

#importCode("../code/scripts/headers/header.h")

== BL.cpp

#importCode("../code/scripts/BL.cpp")

== BLMain.cpp

#importCode("../code/scripts/BLMain.cpp")

== ttpHeader.h

#importCode("../code/scripts/headers/ttpHeader.h")

== FFDH.cpp

#importCode("../code/scripts/FFDH.cpp")

== ttpMain.cpp

#importCode("../code/scripts/ttpMain.cpp")

== generate.cpp

#importCode("../code/scripts/generate.cpp")

== generate_main.cpp

#importCode("../code/scripts/generate_main.cpp")


= References

#v(.5em)

1. Wikipedia. Strip packing problem, #link("https://en.wikipedia.org/wiki/Strip_packing_problem")[#text(fill: blue)[https://en.wikipedia.org/wiki/Strip_packing_problem]]

2. Brenda S. Baker, E. G. Coffman, JR and Ronald L. Rivest, _Orthogonal Packings in Two Dimensions_, #link("https://epubs.siam.org/doi/abs/10.1137/0209064")[#text(fill: blue)[https://epubs.siam.org/doi/abs/10.1137/0209064]]

3. E. G. Coffman, JR., M. R. Garey, D. S. Johnson, and R. E. Tarjan, _Performance Bounds for Level-Oriented Two-Dimensional Packing Algorithms_, #link("https://epubs.siam.org/doi/abs/10.1137/0209062")[#text(fill: blue)[https://epubs.siam.org/doi/abs/10.1137/0209062]] 

= Declaration

#v(.5em)

#fakebold[#fakeitalic[We hereby declare that all the work done in this project titled "Texture Packing" is of our independent effort as a group.]]

// = Signatures

// #align(center)[
// #grid(columns: 2)[
//   #image("images/signature_hxy.png", width: 60%)
// ][#image("images/signature_qzy.jpg", width: 60%)]
// ]