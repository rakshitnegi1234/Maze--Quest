#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <conio.h>  // For _getch() to capture user input without pressing enter

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

enum class CellType {
    EMPTY,
    WALL,
    START,
    EXIT,
    PATH
};

struct Cell {
    CellType type;
    bool visited;
};

// Function prototypes
void generateMaze(vector<vector<Cell>>& maze, int startX, int startY);
void printMaze(const vector<vector<Cell>>& maze, int playerX, int playerY);
bool solveMaze(vector<vector<Cell>>& maze, int startX, int startY, int endX, int endY);
void playGame(vector<vector<Cell>>& maze, int startX, int startY, int endX, int endY);

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    vector<vector<Cell>> maze(HEIGHT, vector<Cell>(WIDTH, { CellType::WALL, false }));

    // Generate maze with random starting point
    int startX = rand() % WIDTH;
    int startY = rand() % HEIGHT;

    generateMaze(maze, startX, startY);

    // Set exit point (bottom right corner)
    int endX = WIDTH - 1;
    int endY = HEIGHT - 1;
    maze[endY][endX].type = CellType::EXIT;

    // Set starting point
    maze[startY][startX].type = CellType::START;

    // Play the game
    playGame(maze, startX, startY, endX, endY);

    return 0;
}

void generateMaze(vector<vector<Cell>>& maze, int startX, int startY) {
    stack<pair<int, int>> stack;
    stack.push({ startX, startY });
    maze[startY][startX].type = CellType::START;

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        maze[y][x].visited = true;

        vector<pair<int, int>> neighbors;

        // Add unvisited neighbors
        if (x > 1 && !maze[y][x - 2].visited) {
            neighbors.push_back({ x - 2, y });
        }
        if (x < WIDTH - 2 && !maze[y][x + 2].visited) {
            neighbors.push_back({ x + 2, y });
        }
        if (y > 1 && !maze[y - 2][x].visited) {
            neighbors.push_back({ x, y - 2 });
        }
        if (y < HEIGHT - 2 && !maze[y + 2][x].visited) {
            neighbors.push_back({ x, y + 2 });
        }

        if (!neighbors.empty()) {
            // Choose random neighbor
            int randIndex = rand() % neighbors.size();
            int nx = neighbors[randIndex].first;
            int ny = neighbors[randIndex].second;

            // Carve path between current cell and chosen neighbor
            maze[(y + ny) / 2][(x + nx) / 2].type = CellType::EMPTY;
            maze[ny][nx].type = CellType::EMPTY;
            stack.push({ nx, ny });
        } else {
            // No unvisited neighbors, backtrack
            stack.pop();
        }
    }
}

void printMaze(const vector<vector<Cell>>& maze, int playerX, int playerY) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                cout << "P ";
            } else {
                switch (maze[y][x].type) {
                    case CellType::WALL:
                        cout << "# ";
                        break;
                    case CellType::EMPTY:
                        cout << "  ";
                        break;
                    case CellType::START:
                        cout << "S ";
                        break;
                    case CellType::EXIT:
                        cout << "E ";
                        break;
                    case CellType::PATH:
                        cout << "* ";
                        break;
                }
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

bool solveMaze(vector<vector<Cell>>& maze, int startX, int startY, int endX, int endY) {
    stack<pair<int, int>> stack;
    stack.push({ startX, startY });

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;
        maze[y][x].visited = true;

        if (x == endX && y == endY) {
            // Reached the exit
            return true;
        }

        vector<pair<int, int>> neighbors;

        // Add valid neighboring cells
        if (x > 0 && maze[y][x - 1].type != CellType::WALL && !maze[y][x - 1].visited) {
            neighbors.push_back({ x - 1, y });
        }
        if (x < WIDTH - 1 && maze[y][x + 1].type != CellType::WALL && !maze[y][x + 1].visited) {
            neighbors.push_back({ x + 1, y });
        }
        if (y > 0 && maze[y - 1][x].type != CellType::WALL && !maze[y - 1][x].visited) {
            neighbors.push_back({ x, y - 1 });
        }
        if (y < HEIGHT - 1 && maze[y + 1][x].type != CellType::WALL && !maze[y + 1][x].visited) {
            neighbors.push_back({ x, y + 1 });
        }

        if (!neighbors.empty()) {
            // Move to the next cell
            int nx = neighbors.front().first;
            int ny = neighbors.front().second;
            stack.push({ nx, ny });
            maze[ny][nx].type = CellType::PATH;
        } else {
            // Backtrack
            stack.pop();
        }
    }

    return false;
}

void playGame(vector<vector<Cell>>& maze, int startX, int startY, int endX, int endY) {
    int playerX = startX;
    int playerY = startY;

    while (true) {
        printMaze(maze, playerX, playerY);

        char move = _getch();  // Get user input without pressing enter

        int newX = playerX;
        int newY = playerY;

        switch (move) {
            case 'w':
                newY--;
                break;
            case 's':
                newY++;
                break;
            case 'a':
                newX--;
                break;
            case 'd':
                newX++;
                break;
        }

        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && maze[newY][newX].type != CellType::WALL) {
            playerX = newX;
            playerY = newY;

            if (playerX == endX && playerY == endY) {
                cout << "Congratulations! You've reached the exit!\n";
                break;
            }
        }
    }
}