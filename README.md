How It Works
Maze Generation
The maze is generated using a recursive backtracking algorithm, where the maze cells are visited randomly, and walls are placed dynamically. The algorithm ensures there is always a path from the start to the end.

Pathfinding Algorithms
A Algorithm*: Finds the shortest path by combining the actual cost and heuristic (Manhattan distance).
BFS Algorithm: Explores all possible paths level by level, guaranteeing the shortest path in an unweighted maze.
DFS Algorithm: Explores paths recursively and backtracks when it reaches a dead end.
Visualization
The maze and solution paths are drawn using SFML. Different colors represent walls, paths, start, and end points, and the solution path based on the selected algorithm.

Event Handling
The program handles mouse and keyboard inputs to allow maze manipulation and algorithm selection. Each input is processed in real-time to update the maze and paths.

Dependencies
This project requires SFML to compile and run. You can download it from SFML's official website.

Conclusion
This maze game is an interactive way to visualize and compare the A*, BFS, and DFS algorithms. It can be used for learning how different pathfinding algorithms work and how they solve mazes in real time.






