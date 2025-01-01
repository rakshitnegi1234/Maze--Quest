#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <algorithm>
#include <ctime>
#include <stack>

using namespace std;

// Constants
const int cellSize = 40;
const int rows = 15, cols = 15;

// Directions for A*, BFS, and DFS
const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Node structure for A* Pathfinding
struct Node {
    pair<int, int> position;
    int cost, heuristic;

    Node(pair<int, int> pos, int c, int h) : position(pos), cost(c), heuristic(h) {}

    bool operator>(const Node& other) const {
        return cost + heuristic > other.cost + other.heuristic;
    }
};

// Maze Solver and Visualization Class
class MazeSolver {
private:
    vector<vector<int>> maze;
    sf::RenderWindow window;
    pair<int, int> start = {-1, -1}, end = {-1, -1}; // Undefined start and end initially
    int algorithmChoice = 0; // 0 = A*, 1 = BFS, 2 = DFS
    bool solved = false;
    float timeTaken = 0;
    int steps = 0;

    // Separate matrices for each algorithm's path
    vector<vector<bool>> pathAStar, pathBFS, pathDFS;

public:
    MazeSolver() : window(sf::VideoMode(cols * cellSize, rows * cellSize), "Interactive Maze Solver") {
        maze.resize(rows, vector<int>(cols, 0)); // 0 = empty, 1 = wall, 2 = start, 3 = end
        pathAStar.resize(rows, vector<bool>(cols, false));
        pathBFS.resize(rows, vector<bool>(cols, false));
        pathDFS.resize(rows, vector<bool>(cols, false));
    }

    // Utility function to calculate Manhattan distance (used in A* and BFS)
    int manhattanDistance(pair<int, int> a, pair<int, int> b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    // DFS for solving the maze
    bool dfs(int x, int y, vector<vector<bool>>& visited, vector<vector<pair<int, int>>>& parent) {
        if (x < 0 || x >= rows || y < 0 || y >= cols || maze[x][y] == 1 || visited[x][y])
            return false;

        visited[x][y] = true;

        if (make_pair(x, y) == end) return true;

        for (auto dir : directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if (dfs(nx, ny, visited, parent)) {
                parent[nx][ny] = {x, y};
                pathDFS[nx][ny] = true;  // Mark this cell as part of DFS path
                return true;
            }
        }
        return false;
    }

    // A* Algorithm for solving the maze
    void aStarSolve() {
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        vector<vector<int>> cost(rows, vector<int>(cols, INT_MAX));
        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

        pq.push(Node(start, 0, manhattanDistance(start, end)));
        cost[start.first][start.second] = 0;

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.position == end) {
                while (current.position != start) {
                    pathAStar[current.position.first][current.position.second] = true;  // Mark A* path
                    current.position = parent[current.position.first][current.position.second];
                }
                pathAStar[start.first][start.second] = true;  // Start point
                return;
            }

            for (auto dir : directions) {
                int nx = current.position.first + dir.first;
                int ny = current.position.second + dir.second;

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] != 1) {
                    int newCost = cost[current.position.first][current.position.second] + 1;
                    if (newCost < cost[nx][ny]) {
                        cost[nx][ny] = newCost;
                        parent[nx][ny] = current.position;
                        pq.push(Node({nx, ny}, newCost, manhattanDistance({nx, ny}, end)));
                    }
                }
            }
        }
    }

    // BFS for solving the maze
    void bfsSolve() {
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

        q.push(start);
        visited[start.first][start.second] = true;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            if (current == end) {
                while (current != start) {
                    pathBFS[current.first][current.second] = true;  // Mark BFS path
                    current = parent[current.first][current.second];
                }
                pathBFS[start.first][start.second] = true;  // Start point
                return;
            }

            for (auto dir : directions) {
                int nx = current.first + dir.first;
                int ny = current.second + dir.second;

                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] != 1 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    parent[nx][ny] = current;
                    q.push({nx, ny});
                }
            }
        }
    }

    // Recursive Backtracking Maze Generation
    void generateMaze(int x, int y) {
        vector<pair<int, int>> stack;
        stack.push_back({x, y});
        maze[x][y] = 1;

        while (!stack.empty()) {
            pair<int, int> current = stack.back();
            stack.pop_back();
            vector<pair<int, int>> neighbors;

            for (auto dir : directions) {
                int nx = current.first + dir.first;
                int ny = current.second + dir.second;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == 0) {
                    neighbors.push_back({nx, ny});
                }
            }

            if (!neighbors.empty()) {
                stack.push_back(current);
                pair<int, int> next = neighbors[rand() % neighbors.size()];
                maze[next.first][next.second] = 1;
                stack.push_back(next);
            }
        }
    }

    // Draw the Maze and the UI
  void drawMaze() {
    window.clear(sf::Color::White);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            cell.setPosition(j * cellSize, i * cellSize);

            if (maze[i][j] == 1) {
                cell.setFillColor(sf::Color::Black);  // Wall
            } 
            else if (maze[i][j] == 2) {
                cell.setFillColor(sf::Color::Green);  // Start
            }
            else if (maze[i][j] == 3) {
                cell.setFillColor(sf::Color::Red);    // End
            } 
            else if (pathAStar[i][j]) {
                cell.setFillColor(sf::Color::Blue);  // A* Path
            } 
            else if (pathBFS[i][j]) {
                cell.setFillColor(sf::Color::Yellow);  // BFS Path
            }
            else if (pathDFS[i][j]) {
                cell.setFillColor(sf::Color::Magenta); // DFS Path
            } 
            else {
                cell.setFillColor(sf::Color::White);   // Empty Space
            }

            window.draw(cell);
        }
    }

    // Instructions
    sf::Font font;
    if (!font.loadFromFile("fonts/ARIALBD.TTF")) {  // Load the custom font from the 'fonts' folder
        cout << "Failed to load font!" << endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(5, rows * cellSize + 5);
    text.setString("Press 'S' to Solve, 'R' to Reset, 'G' to Generate Maze, '1' for A*, '2' for BFS, '3' for DFS");

    window.draw(text);
    window.display();
}


    // Handle Input Events
    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / cellSize;
                int y = event.mouseButton.y / cellSize;

                if (event.mouseButton.button == sf::Mouse::Left) {
                    maze[y][x] = 1; // Set wall
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    maze[y][x] = 0; // Remove wall
                } else if (event.mouseButton.button == sf::Mouse::Middle) {
                    if (start == make_pair(-1, -1)) {
                        start = {y, x}; // Set start point
                        maze[start.first][start.second] = 2;
                    } else if (end == make_pair(-1, -1)) {
                        end = {y, x}; // Set end point
                        maze[end.first][end.second] = 3;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    resetMaze();
                } else if (event.key.code == sf::Keyboard::G) {
                    generateMaze(rand() % rows, rand() % cols);
                } else if (event.key.code == sf::Keyboard::S) {
                    if (algorithmChoice == 0) {
                        aStarSolve();
                    } else if (algorithmChoice == 1) {
                        bfsSolve();
                    } else if (algorithmChoice == 2) {
                        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
                        vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
                        dfs(start.first, start.second, visited, parent);
                    }
                }
                if (event.key.code == sf::Keyboard::Num1) {
                    algorithmChoice = 0;  // A*
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    algorithmChoice = 1;  // BFS
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    algorithmChoice = 2;  // DFS
                }
            }
        }
    }

    // Reset the Maze
    void resetMaze() {
        maze.clear();
        maze.resize(rows, vector<int>(cols, 0));
        start = {-1, -1};
        end = {-1, -1};
        pathAStar.assign(rows, vector<bool>(cols, false));
        pathBFS.assign(rows, vector<bool>(cols, false));
        pathDFS.assign(rows, vector<bool>(cols, false));
        solved = false;
    }

    // Run the Solver
    void run() {
        while (window.isOpen()) {
            handleInput();
            drawMaze();
        }
    }
};

int main() {
    MazeSolver solver;
    solver.run();
    return 0;
}
