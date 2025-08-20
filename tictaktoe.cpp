#include <iostream>
#include <vector>
#include <array>
using namespace std;

const int EMPTY = 2;
const int PLAYER_X = 3;
const int PLAYER_O = 5;

vector<int> grid(10, EMPTY);
int moveCount = 1;

const array<array<int, 3>, 8> WIN_PATTERNS = {{
    {{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}},
    {{1, 4, 7}}, {{2, 5, 8}}, {{3, 6, 9}},
    {{1, 5, 9}}, {{3, 5, 7}}
}};

void displayGrid() {
    auto symbol = [](int val) -> char {
        if (val == PLAYER_X) return 'X';
        if (val == PLAYER_O) return 'O';
        return ' ';
    };
    cout << "\n";
    for (int row = 0; row < 3; ++row) {
        cout << " " << symbol(grid[1 + row * 3]) << " | "
             << symbol(grid[2 + row * 3]) << " | "
             << symbol(grid[3 + row * 3]) << "\n";
        if (row < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

int getOpenCell() {
    for (int i = 1; i <= 9; ++i)
        if (grid[i] == EMPTY) return i;
    return 0;
}

int canWin(int player) {
    int target = player * player * EMPTY;
    for (auto &line : WIN_PATTERNS) {
        int a = line[0], b = line[1], c = line[2];
        int product = grid[a] * grid[b] * grid[c];
        if (product == target) {
            if (grid[a] == EMPTY) return a;
            if (grid[b] == EMPTY) return b;
            return c;
        }
    }
    return 0;
}

int pickStrategicMove() {
    if (grid[5] == EMPTY) return 5;
    for (int pos : {2, 4, 6, 8})
        if (grid[pos] == EMPTY) return pos;
    return getOpenCell();
}

void makeMove(int preferred) {
    int pos = preferred;
    if (pos < 1 || pos > 9 || grid[pos] != EMPTY) {
        for (int alt : {1, 3, 7, 9, 2, 4, 6, 8, 5}) {
            if (grid[alt] == EMPTY) {
                pos = alt;
                break;
            }
        }
    }
    grid[pos] = (moveCount % 2 == 1) ? PLAYER_X : PLAYER_O;
    cout << "Move " << moveCount << ": Player "
         << ((moveCount % 2 == 1) ? 'X' : 'O') << " chooses " << pos << "\n";
    moveCount++;
}

int detectWinner() {
    for (auto &line : WIN_PATTERNS) {
        int product = grid[line[0]] * grid[line[1]] * grid[line[2]];
        if (product == PLAYER_X * PLAYER_X * PLAYER_X) return PLAYER_X;
        if (product == PLAYER_O * PLAYER_O * PLAYER_O) return PLAYER_O;
    }
    return 0;
}

void autoPlay() {
    switch (moveCount) {
        case 1:
            makeMove(1);
            break;
        case 2:
            makeMove(grid[5] == EMPTY ? 5 : 1);
            break;
        case 3:
            makeMove(grid[9] == EMPTY ? 9 : 3);
            break;
        case 4: {
            int block = canWin(PLAYER_X);
            makeMove(block ? block : pickStrategicMove());
            break;
        }
        case 5: {
            int win = canWin(PLAYER_X);
            if (win) { makeMove(win); break; }
            int block = canWin(PLAYER_O);
            if (block) { makeMove(block); break; }
            makeMove(grid[7] == EMPTY ? 7 : 3);
            break;
        }
        default: {
            int current = (moveCount % 2 == 1) ? PLAYER_X : PLAYER_O;
            int opponent = (current == PLAYER_X) ? PLAYER_O : PLAYER_X;
            int win = canWin(current);
            if (win) { makeMove(win); break; }
            int block = canWin(opponent);
            if (block) { makeMove(block); break; }
            int strategic = pickStrategicMove();
            makeMove(strategic ? strategic : getOpenCell());
            break;
        }
    }
}

int main() {
    cout << "Tic-Tac-Toe Simulation: AI vs AI\n";
    displayGrid();

    while (moveCount <= 9) {
        autoPlay();
        displayGrid();
        int winner = detectWinner();
        if (winner == PLAYER_X) {
            cout << "Player X wins!\n";
            break;
        }
        if (winner == PLAYER_O) {
            cout << "Player O wins!\n";
            break;
        }
        if (moveCount > 9) {
            cout << "It's a draw!\n";
            break;
        }
    }
    return 0;
}