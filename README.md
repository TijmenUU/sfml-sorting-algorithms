# sfml-sorting-algorithms
Sorting algorithms visualized with the help of SFML.

## Algorithms included
- Bubble sort
- Heap sort
- Insertion sort
- Merge sort
- Quick sort (of the insertion sort variety)

### Nice-to-have's
- Radix sort
  - I've looked into count/bucket/radix sort, but I cannot think of an enjoyable
    visual representation for it.
- Bogo sort
  - What sorting algorithm visualizer is complete without this classic?
- Trim sort
- Shell sort
- Multi threaded sorts
- Etc.

## Requirements
Currently only tested on Linux, but there are no dependencies that should make
this incompatible with a Windows system or any other OS that has SFML.

- SFML (2.5.0)
- make
- g++/clang++ (C++17 preferred, minimally C++14, see the `makefile`)

## Style
The code has been formatted using `clang-format`. Hence it may look a little odd
in some places.
