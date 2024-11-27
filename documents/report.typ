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
    
    #fakebold[Outputs]: 
    - _curHeight_: the "minimum" height of the bin 

    #fakebold[Procedure]: FFDH(_W_: #fakebold[double], _n_: #fakebold[integer], _rect_: #fakebold[Item array], _isDebug_: #fakebold[bool]) 
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

== FFDH Algorithm

=== Correctness Tests

=== Performance Tests

== Advanced Approximation Algorithm

=== Correctness Tests

=== Performance Tests

= Chapter 4: Analysis and Comments

#v(.5em)

== Space Complexity

*Conclusion*:

- FFDH algorithm: $O(N)$
- advanced approximation algorithm:

*Analysis*:

- FFDH algorithm: 
- advanced approximation algorithm:

== Time Complexity

*Conclusion*:

- FFDH algorithm: $O(N^2)$
- advanced approximation algorithm:

*Analysis*:

- FFDH algorithm:
- advanced approximation algorithm:

== Further Improvement

#v(.5em)

= Appendix: Source code

== File Structure

#table(columns: 1fr, align: left)[
  ```
  .
├── README.md
├── code
│   ├── Makefile
│   ├── README.pdf
│   ├── build
│   ├── scripts
│   │   ├── getStopWord
│   │   ├── getStopWord.cpp
│   │   ├── html2txt.py
│   │   ├── iist_diagram.py
│   │   ├── invIndexFunc.cpp
│   │   ├── invIndexHeader.h
│   │   ├── invIndexSearch.cpp
│   │   ├── invIndexTest.cpp
│   │   ├── search_main.cpp
│   │   ├── search_test.cpp
│   │   └── wordStem
│   └── data
│       ├── file_word_count.txt
│       ├── search_test
│       ├── shakespeare-master
│       ├── shakespeare_works
│       ├── stop_words.txt
│       ├── inverted_index_tests
│       ├── txt_title.txt
│       ├── word_count.txt
│       └── word_docs.txt
└── documents
    └── report-p1.pdf
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