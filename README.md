## Project Name
Tal & Misha's project
## Usage
Create a new graph, run `solve` method
## Contributing
Work on your branch, pull request from branch to master.

Create issue for task management
## Current version 
Global avail vertex, bug in `connect`(if deg(v) = 3, pull out available)

Hill climber: find how many circles less then g there were if new

random edge (u,v) was added with `count_cycles(u,v)`

if there are no short cycles, adding new edge `connect(u,v)`

if we found a single cycle,
using the statement if there is a single path of length less then g - 2, it's the shortest path,
we recognize it as set of edges from which random edge will be removed(NOT IMPLEMENTED)

if there are more then one cycle: do nothing

