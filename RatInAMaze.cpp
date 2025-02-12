#include <iostream>
#include <vector>
#include <cstdlib> 
#include <ctime>  

using namespace std;

// Function to generate a solvable random maze
vector<vector<int>> generateMaze(int n) {
    vector<vector<int>> maze(n, vector<int>(n, 0));

    // Seed random number generator
    srand(time(0));

    int x = 0, y = 0;
    maze[x][y] = 1;

    while (x < n - 1 || y < n - 1) {
        int dir = rand() % 2; 
        if (dir == 0 && x < n - 1) {
            x++;
        } else if (y < n - 1) {
            y++;
        }
        maze[x][y] = 1; 
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (maze[i][j] == 0) { 
                maze[i][j] = (rand() % 100 < 30) ? 1 : 0;
            }
        }
    }

    return maze;
}

void printMaze(const vector<vector<int>>& mat) {
    cout << "Maze:\n";
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Recursive function to solve the maze
void solveMaze(vector<vector<int>>& mat, int ro, int colu, string path, vector<string>& res, vector<vector<bool>>& visited) {
    int n = mat.size();
    if (ro < 0 || colu < 0 || ro >= n || colu >= n || mat[ro][colu] == 0 || visited[ro][colu]) {
        return;
    }

    if (ro == n - 1 && colu == n - 1) {
        res.push_back(path);
        return;
    }

    visited[ro][colu] = true;

    solveMaze(mat, ro + 1, colu, path + "D", res, visited);
    solveMaze(mat, ro - 1, colu, path + "U", res, visited);
    solveMaze(mat, ro, colu - 1, path + "L", res, visited);
    solveMaze(mat, ro, colu + 1, path + "R", res, visited);

    visited[ro][colu] = false; //For Backtracking
}

// Function to find all the possible paths in the maze
vector<string> findallPath(vector<vector<int>>& mat) {
    int n = mat.size();
    vector<string> res;
    string path = "";
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    solveMaze(mat, 0, 0, path, res, vis);
    return res;
}

string findShortestPath(const vector<string>& paths) {
    if (paths.empty()) return "No path found!";

    string shortest = paths[0];
    for (const string& path : paths) {
        if (path.length() < shortest.length()) {
            shortest = path;
        }
    }
    return shortest;
}

string findLongestPath(const vector<string>& paths) {
    if (paths.empty()) return "No path found!";

    string longest = paths[0];
    for (const string& path : paths) {
        if (path.length() > longest.length()) {
            longest = path;
        }
    }
    return longest;
}

int main() {
    int n,choice;
    cout << "Enter maze size (n x n): ";
    cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));

    cout << "Choose Maze Input Method:\n";
    cout << "1. Manually Enter the Maze\n";
    cout << "2. Randomly Generate a Maze\n";
    cout << "Enter your choice (1 or 2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the maze (Use 1 for open path and 0 for blocked path):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> mat[i][j];
            }
        }
    } else {
        mat = generateMaze(n);
    }
    printMaze(mat);
    vector<string> res = findallPath(mat);

    if (res.empty()) {
        cout << "No path found!" << endl;
    } else {
        cout << "Paths found:\n";
        for (const string& path : res) {
            cout << path << endl;
        }
        cout << "\nShortest path: " << findShortestPath(res) << endl;
        cout << "Longest path: " << findLongestPath(res) << endl;
    }

    return 0;
}