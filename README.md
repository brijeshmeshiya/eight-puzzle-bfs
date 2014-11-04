eight-puzzle-bfs
================

The 8 puzzle consists of eight numbered, movable tiles set in a 3x3 frame. One cell of the frame is always empty thus making 
it possible to move an adjacent numbered tile into the empty cell.

|````|````|````|                    |````|````|````|
|    |  8 |  7 |                    |  1 |  2 |  3 |
|````|````|````|                    |````|````|````| 
|  6 |  5 |  4 |   -------->        |  4 |  5 |  6 |
|````|````|````|                    |````|````|````|
|  3 |  2 |  1 |                    |  7 |  8 |  1 |
````````````````                    ````````````````
   Start State                         Goal State

I've used Breadth First Search Algorithm to solve this puzzle . It will lead to Optimal Solution if Solution Exists.
