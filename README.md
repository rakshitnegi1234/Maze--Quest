Maze Game - Interactive Maze Solver

This project implements an interactive maze game with a graphical user interface (GUI) using SFML in C++. The game generates a random maze and allows players to solve it using three different algorithms: A*, Breadth-First Search (BFS), and Depth-First Search (DFS). The player can navigate the maze manually and watch how each algorithm solves the maze.

Features

Random Maze Generation: Automatically generates a random maze with walls and empty spaces.
Multiple Solving Algorithms: Choose between A*, BFS, or DFS for solving the maze.
User Interaction: You can click to create walls or set the start and end points. You can also solve the maze using different algorithms.
Visual Representation: The maze is displayed in a grid with different colors for walls, start, end, and paths found by each algorithm.
Instructions Display: The game shows on-screen instructions for easy navigation.
How to Play
Set up the Game:

Clone or download the source code to your local machine.
Ensure that SFML is properly installed on your system. SFML is used for graphical rendering and event handling.
Build the Game:

Open your terminal or command prompt.

Navigate to the directory containing the source code (maze_game.cpp).
Compile the C++ code using a C++ compiler with SFML support:
sh
Copy code
g++ -o maze_game maze_game.cpp -lsfml-graphics -lsfml-window -lsfml-system
Run the Game:

After compilation, run the executable to start the game:
sh
Copy code
./maze_game
Game Controls:

Left-click: Place a wall in the maze.
Right-click: Remove a wall from the maze.
Middle-click: Set the start or end point (alternates between start and end).
'R': Reset the maze (clear all walls and points).
'G': Generate a new random maze.
'S': Solve the maze using the currently selected algorithm.
'1': Select A* algorithm.
'2': Select BFS algorithm.
'3': Select DFS algorithm.

Maze Visualization:

Black cells represent walls.
Green cell is the start point.
Red cell is the end point.
Blue cells represent the A* path.
Yellow cells represent the BFS path.
Magenta cells represent the DFS path.
Algorithms Used
1. A* (A-star) Algorithm:
A* is a heuristic-based algorithm that finds the shortest path from the start to the end point by evaluating nodes based on both the cost from the start node and a heuristic estimate of the cost to the goal.
Manhattan Distance is used as the heuristic, which calculates the absolute sum of the horizontal and vertical distances between two points.
2. Breadth-First Search (BFS):
BFS explores all possible paths from the start point, level by level, until it reaches the end point. It guarantees the shortest path in an unweighted grid.
3. Depth-First Search (DFS):
DFS explores paths as far as possible before backtracking. It may not find the shortest path, but it will always find a path if one exists.
Compilation
To compile the program, you need a C++ compiler and SFML libraries. Here’s how to do it:

Install SFML on your system:

On Ubuntu:

sh
Copy code
sudo apt-get install libsfml-dev
On Windows: Download SFML from the official website.

Compile the program with SFML linked:

sh
Copy code
g++ -o maze_game maze_game.cpp -lsfml-graphics -lsfml-window -lsfml-system
This will create an executable file named maze_game.

Directory Structure

maze_game.cpp: The main C++ source code file containing the game logic.
/fonts/ARIALBD.TTF: Custom font used for displaying instructions (ensure the font is available or replace it with any font you prefer).

/README.md: Documentation describing how to use and compile the game.
Instructions for Running the Game
Generating and Solving the Maze:

Generate a Maze: Click the 'G' key to generate a random maze. You will see a grid of walls and empty spaces.
Set Start and End Points: Left-click to create walls or right-click to remove them. Set the start and end points by middle-clicking on two cells.

Solve the Maze: Press 'S' to start solving the maze. The algorithm selected will try to find a path from the start to the end. If a path is found, it will be highlighted in different colors depending on the algorithm used.
Additional Features & Future Improvements.

Maze Generation Improvements: The current maze generation uses a simple recursive backtracking approach. More advanced maze generation algorithms like Prim’s Algorithm or Kruskal’s Algorithm could be added.

Path Optimization: After solving the maze, the path could be optimized further or displayed with step-by-step visualization.

User Interface Enhancements: Add a more intuitive interface for selecting the algorithms and displaying performance metrics (time taken, number of steps, etc.).

Conclusion
This project provides a fun and educational interactive maze solver with visualization of classic pathfinding algorithms. It helps users understand how A*, BFS, and DFS solve mazes and can be used as a foundation for further improvements and learning in pathfinding algorithms.

