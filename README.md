## Project Name
Tal & Misha's project
## Usage
Create a new graph, run `solve` method
## Contributing
Work on your branch, pull request from branch to master.

Create issue for task management
## Current version 
*bug fixes:*

1. Global avail vertex.

2. bug in `connect`(if deg(v) = 3, pull out available)
3. bug in `disconnect()` `sigmentation fault` resolved

*Hill climber:*
1. find how many circles less than g there were if new
random edge (u,v) was added with `count_cycles(u,v)`

2. if there are no short cycles, adding new edge `connect(u,v)`

3. if we found a single cycle,
using the statement:

    **If there is a single path of length less than g - 2, it's the shortest path.**

    we recognize it as set of edges from which random edge is removed `replaceEdgeOnCycle()`,

    and the edge `(u,v)` is added to `E` with `connect(u,v)`

5. if there are more than one cycle: do nothing

