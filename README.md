## Searching Problems Server-Side Solver
**The following documentation refers to an ongoing project as part of our CS major in Bar Ilan University.** 


### Background


The following project demonstrates a `C++`-written server which operates as a generic problem solver. It makes usage of a few searching
algorithms, and can handle simultanous clients connections and operate as a parrallel server that way. In addition, it uses a generic
Cache Manager which can save and load preiously solved problems.


This project can be used a solver of various problems, e.g navigation and best route planner.


### Key Features
* Wide usage of templates and generics concept.
* Implementation of [AStar](https://en.wikipedia.org/wiki/A*_search_algorithm),
[Best-FS](https://en.wikipedia.org/wiki/Best-first_search),
[BFS](https://en.wikipedia.org/wiki/Breadth-first_search), 
[DFS](https://en.wikipedia.org/wiki/Depth-first_search) searching algorithms.
* Multi-Threading implementation.
* Usage of C++ STL, I/O, Mutex libraries.
* Usage of OOP SOLID principle and Bridge design pattern.
* Organized work using Github repository.

### Usage Example
In the current implementation, the problem is an NxN sized matrix and the solution is the shortest path from the initial state to the
goal state. Value of each cell is it's cost. For example:


Client request: 


```
# matrix input line by line
3,4,9,0,5
6,3,5,2,1
4,9,5,-1,2
9,-1,4,8,5
1,8,5,3,5
0,0 #initial cell
4,4 #goal cell

#note: '-1' stands for an impassable cell.
```

### Running the program
Download and run the [python script](https://github.com/Boris-il/GenericServerSide/blob/master/auto_client.py) with `python3 auto_client.py -vv`.


It sends the [test matrix](https://github.com/Boris-il/GenericServerSide/blob/master/matrix_test.txt) to the server.

### Authors
Yuval Machlev,
Boris Ilchenkov

Bar-Ilan University, Israel.
