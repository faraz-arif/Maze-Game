#include<iostream>
using namespace std;
void mazeGame();
void inputMazeDimension(int& r, int& c);
void printMaze(int** m, int r, int c);
void printMazePlayer(int** m, int r, int c, int x, int y);
void playerMove(int** m, int& xCord, int& yCord, int r, int c, int& movedDistance);
void deallocateMaze(int** m, int r, int c);
void deallocateVisited(bool** m, int r, int c);
bool checkLegal(int** m, int r, int c, int key, int x, int y);
void checkWin(int x, int y, int r, int c);
void shortestPath(int** m, int r, int c, int x, int y, int distance, int& minDistance, bool** visited);
int main() {
    mazeGame();
    return 0;
}
// TASK 1 functions
void mazeGame() {
    srand(time(0));
    int rows = 0, columns = 0;
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                                       MAZE GAME                  " << endl;
    inputMazeDimension(rows, columns);
    int** maze = new int* [rows];
    for (int i = 0; i < rows; i++) {
        maze[i] = new int[columns];
    }
    // for(int i = 0; i < rows; i++) {
    //     for(int j = 0; j < columns; j++) {
    //         if((i == 0 && j == 0) || (j == columns - 1 && i == rows -1)) {
    //             maze[i][j] = 1;
    //         }
    //         else {
    //             maze[i][j] = rand() % 2;
    //         }
    //     }
    // }
    bool** visitedCoords = new bool* [rows];
    for (int i = 0; i < rows; i++) {
        visitedCoords[i] = new bool[columns];
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            visitedCoords[i][j] = false;
        }
    }
    int minDistance = rows * columns;
    while (minDistance >= rows * columns) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if ((i == 0 && j == 0) || (j == columns - 1 && i == rows - 1)) {
                    maze[i][j] = 1;
                }
                else {
                    maze[i][j] = rand() % 2;
                }
            }
        }
        shortestPath(maze, rows, columns, 0, 0, 0, minDistance, visitedCoords);
    }
    printMaze(maze, rows, columns);
    int playerX = 0, playerY = 0;
    int playerDistance = 0;
    playerMove(maze, playerX, playerY, rows, columns, playerDistance);
    if (playerDistance <= minDistance) {
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                       YOU MOVED THROUGH THE SHORTEST PATH" << endl;
    }
    else {
        cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                   YOU DID NOT MOVED THROUGH THE SHORTEST PATH" << endl;
    }
    deallocateMaze(maze, rows, columns);
    deallocateVisited(visitedCoords, rows, columns);
    return;
}
void inputMazeDimension(int& r, int& c) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Enter the number of Rows of the maze:  ";
    cin >> r;
    cout << "Enter the number of columns of the maze:   ";
    cin >> c;
    return;
}
void printMaze(int** m, int r, int c) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    return;
}
void printMazePlayer(int** m, int r, int c, int x, int y) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (i == x && j == y) {
                cout << 'X' << " ";
            }
            else if (i == r - 1 && j == c - 1) {
                cout << 'Y' << " ";
            }
            else {
                cout << *(*(m + i) + j) << " ";
            }
        }
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    return;
}
void deallocateMaze(int** m, int r, int c) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                           GAME END! FREEING UP RAM          " << endl;
    for (int i = 0; i < r; i++) {
        delete[] * (m + i);
    }
    delete[] m;
    return;
}
void deallocateVisited(bool** m, int r, int c) {
    for (int i = 0; i < r; i++) {
        delete[] * (m + i);
    }
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    delete[] m;
    return;
}
void playerMove(int** m, int& xCord, int& yCord, int r, int c, int& movedDistance) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    int attempts = r * c;
    while (((xCord != r - 1) || (yCord != c - 1)) && attempts--) {
        printMazePlayer(m, r, c, xCord, yCord);
        char playerInput = ' ';
        cout << "Current Position (" << xCord << "," << yCord << ") and the maximum moves left are " << attempts << " : " << endl;
        cout << "Enter the location to move to (l for right, j for left, i for upwards and k for downwards or q to quit):    ";
        cin >> playerInput;
        while (cin.fail() || (playerInput != 'l' && playerInput != 'j' && playerInput != 'i' && playerInput != 'k' && playerInput != 'q')) {
            cerr << "Error! Enter the movement again:    ";
            cin >> playerInput;
        }
        if (playerInput == 'j') {
            if (checkLegal(m, r, c, 1, xCord, yCord)) {
                yCord--;
                movedDistance++;
            }
            else {
                cerr << "Illegal Move! " << endl;
            }
        }
        else if (playerInput == 'l') {
            if (checkLegal(m, r, c, 2, xCord, yCord)) {
                yCord++;
                movedDistance++;
            }
            else {
                cerr << "Illegal Move! " << endl;
            }
        }
        else if (playerInput == 'i') {
            if (checkLegal(m, r, c, 3, xCord, yCord)) {
                xCord--;
                movedDistance++;
            }
            else {
                cerr << "Illegal Move! " << endl;
            }
        }
        else if (playerInput == 'k') {
            if (checkLegal(m, r, c, 4, xCord, yCord)) {
                xCord++;
                movedDistance++;
            }
            else {
                cerr << "Illegal Move! " << endl;
            }
        }
        else if (playerInput == 'q') {
            return;
        }
    }
    checkWin(xCord, yCord, r, c);
    return;
}
bool checkLegal(int** m, int r, int c, int key, int x, int y) {
    if (key == 1) {
        if (y - 1 < 0) {
            return false;
        }
        else {
            if (m[x][y - 1] != 1) {
                return false;
            }
            return true;
        }
    }
    else if (key == 2) {
        if (y + 1 >= c) {
            return false;
        }
        else {
            if (m[x][y + 1] != 1) {
                return false;
            }
            return true;
        }
    }
    else if (key == 3) {
        if (x - 1 < 0) {
            return false;
        }
        else {
            if (m[x - 1][y] != 1) {
                return false;
            }
            return true;
        }
    }
    else if (key == 4) {
        if (x + 1 >= r) {
            return false;
        }
        else {
            if (m[x + 1][y] != 1) {
                return false;
            }
            return true;
        }
    }
    return false;
}
void checkWin(int x, int y, int r, int c) {
    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    if ((x == r - 1) && (y == c - 1)) {
        cout << "                                                YOU WIN!                   " << endl;
    }
    else {
        cout << "                                           BETTER LUCK NEXT TIME!         " << endl;
    }
    return;
}
void shortestPath(int** m, int r, int c, int x, int y, int distance, int& minDistance, bool** visited) {
    if (x < 0 || y < 0 || x >= r || y >= c) {
        return;
    }
    else if (m[x][y] == 0) {
        return;
    }
    else if (visited[x][y] == true) {
        return;
    }
    else if (distance >= minDistance) {
        return;
    }
    else if ((x == r - 1 && y == c - 1) && (distance < minDistance)) {
        minDistance = distance;
        return;
    }
    else {
        visited[x][y] = true;
        shortestPath(m, r, c, x + 1, y, distance + 1, minDistance, visited);
        shortestPath(m, r, c, x, y + 1, distance + 1, minDistance, visited);
        shortestPath(m, r, c, x - 1, y, distance + 1, minDistance, visited);
        shortestPath(m, r, c, x, y - 1, distance + 1, minDistance, visited);
        visited[x][y] = false;
    }
    return;
}