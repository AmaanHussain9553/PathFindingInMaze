# Finding path in a maze from start point to end point

The program contains functions that create a maze structure with obstacles by reading in text files with specifications for the maze size. It uses a search algorithm that 
goes through the maze from the start point to the end point while avoiding obstacles (coordinates of all these are in .txt files that is run with the program).

The program:

1. Uses a 2D array within a struct to create the maze structure which also stores start, end and obstacles points
2. Uses a linked list implementation of stack in order to find the path from the start to end point
3. Contains functions to push, pop, display and reset stack
4. Contains functions that show the algorithm of how the coordinates are pushed and popped from the stack while generating the created maze and the accurate solution in
getting from the start point to the end point

To run:
./main "input filename"

Coding Details:

Language C

No graphical requirements and can be run on any IDE that can compile C code
