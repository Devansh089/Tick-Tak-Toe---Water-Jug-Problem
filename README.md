# Tic Tac Toe Game with AI (Magic Square Method)

## 📌 Problem Statement
Design and implement a **Tic Tac Toe game** in C++ where the player competes against an AI-controlled opponent. The AI should use **magic square properties** to make optimal moves, blocking the player's winning chances and attempting to win whenever possible.

---

## 🎯 Objective
- Enable a human player (`X`) to play Tic Tac Toe against a computer-controlled opponent (`O`).
- Ensure the AI is **strategic** using the **Magic Square Algorithm** for quick win detection and blocking.
- Provide a **command-line interface** for gameplay.

---

## 🗂 Data Structures Used
1. **`vector<char>`**  
   - Stores the current state of the board (`'X'`, `'O'`, or `' '` for empty).
   - Index mapping:  
     ```
     0 | 1 | 2
     3 | 4 | 5
     6 | 7 | 8
     ```

2. **`const int magic[9]`**  
   - Magic square mapping to positions for win-checking using sum=15 logic:  
     ```
     8  1  6
     3  5  7
     4  9  2
     ```

3. **`vector<int>`**  
   - Stores magic numbers for positions occupied by each player.

4. **Arrays for win conditions**  
   - Predefined `wins[8][3]` list for standard row/column/diagonal checking.

---

## ⚙️ Algorithms

### 1. **State Generation**
- The **board state** is a vector of 9 characters.
- On each turn:
  - Player move is inserted directly from input.
  - AI move is computed via the **Magic Square Algorithm**.

### 2. **AI Move Selection (Magic Square Method)**
The AI selects moves in priority order:
1. **Win Move:** If AI can complete a line (sum=15 with two AI magic numbers + empty position), choose that.
2. **Block Move:** If the player can win in the next move, block it.
3. **Center Control:** Choose the center if available (index 4).
4. **Corner Preference:** Choose one of the corners.
5. **Edge Preference:** Choose one of the sides.
6. **Fallback:** Choose any remaining empty space.

### 3. **Winner Detection**
- Either:
  - Check using predefined winning combinations (`wins` array).
  - OR by checking if any 3 magic numbers sum to 15.

---

## 🛠 Utility Functions

| Function | Purpose |
|----------|---------|
| `printBoard()` | Displays the current game board in a user-friendly grid format. |
| `checkWin()` | Checks whether a player (`X` or `O`) has won using winning line combinations. |
| `collectMagic()` | Collects magic square values for a given player's moves. |
| `completes15()` | Checks if adding a candidate move completes a sum of 15 with existing moves. |
| `computerMove()` | Implements AI's decision-making using the magic square algorithm. |

---

## 💡 Use Cases
- **Educational**: Demonstrates how to apply **magic squares** to a game logic problem.
- **Game AI Development**: Example of turn-based decision-making logic.
- **Problem Solving Practice**: Uses combinatorics and optimization.
- **Beginner Game Programming**: Introduces board representation, user input handling, and AI strategy.

---

## 🖥 Sample Output
```text
Tic-Tac-Toe (Magic Square AI)
You are X, computer is O.

Board:
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9

User's turn
Your move (1-9): 1
 You entered: 1

Board:
 X | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9

 Computer's turn
 Computer chooses index 4 (pos 5)

Board:
 X | 2 | 3
---+---+---
 4 | O | 6
---+---+---
 7 | 8 | 9

User's turn
Your move (1-9): 4
 You entered: 4

Board:
 X | 2 | 3
---+---+---
 X | O | 6
---+---+---
 7 | 8 | 9

 Computer's turn
 Computer chooses index 6 (pos 7)

Board:
 X | 2 | 3
---+---+---
 X | O | 6
---+---+---
 O | 8 | 9

User's turn
Your move (1-9): 2
 You entered: 2

Board:
 X | X | 3
---+---+---
 X | O | 6
---+---+---
 O | 8 | 9

 Computer's turn
 Computer chooses index 2 (pos 3)

Board:
 X | X | O
---+---+---
 X | O | 6
---+---+---
 O | 8 | 9

Computer WINS.
Game over.

```
---

## 📊 Time Complexity
- **Winner check:** O(1) — only 8 winning lines to check.
- **AI move selection:** O(9²) worst case — checking all available positions and possible sums.
- **Overall:** O(1) per turn — because board size is fixed (3×3).

---

## 🏆 Conclusion
This implementation demonstrates how **mathematical properties** like magic squares can be applied to **game AI** to produce efficient and unbeatable opponents for small board games like Tic Tac Toe.  
It’s a simple yet powerful way to introduce both **AI decision-making** and **mathematical problem solving** in programming.

---






# Water Jug Problem Solver

## Problem Statement
The **Water Jug Problem** is a classic puzzle:  
You are given two jugs with known capacities `x` and `y`. You need to measure out exactly `goal` liters of water using only the following allowed operations:
1. Fill a jug completely.
2. Empty a jug completely.
3. Pour water from one jug into the other until one jug is either full or empty.

This program solves the problem using a step-by-step simulation of operations.

---

## Objective
- To determine if the **goal volume** can be measured using the given jug sizes.
- If possible, show the sequence of jug states `(amount_x, amount_y)` that leads to the goal.
- Verify solvability using the **greatest common divisor (GCD)** rule:  
  The goal is achievable if and only if `goal` is a multiple of `gcd(x, y)` and `goal ≤ max(x, y)`.

---

## Data Structures Used
- **Integer Variables**:
  - `x`, `y`: Capacities of the jugs.
  - `amount_x`, `amount_y`: Current volumes of water in each jug.
- **Functions**: Used to represent state-changing operations.

---

## Algorithms

### 1. State Generation
State is represented as `(amount_x, amount_y)` — volumes of water in each jug.
The possible transitions are:
- **Fill** a jug:
  - `fill_x()`: Set `amount_x = x`
  - `fill_y()`: Set `amount_y = y`
- **Empty** a jug:
  - `empty_x()`: Set `amount_x = 0`
  - `empty_y()`: Set `amount_y = 0`
- **Pour** water from one jug into another until one is empty or full:
  - `pour_x_to_y()`: Pour from jug X to Y.
  - `pour_y_to_x()`: Pour from jug Y to X.

### 2. Goal Checking
```cpp
bool reached_goal(int goal) {
    return (amount_x == goal || amount_y == goal);
}
```

### 3. Solvability Check (Mathematical)
```cpp
gcd_val = gcd(x, y)
if (goal > max(x, y) || goal % gcd_val != 0):
    Not achievable
```

---

## Utility Functions
- **fill_x / fill_y**: Fill the jug to its capacity.
- **empty_x / empty_y**: Empty the jug.
- **pour_x_to_y / pour_y_to_x**: Transfer water between jugs.
- **reached_goal**: Check if current state has the goal volume.

---

## Use Cases
1. **Measuring specific quantities** where only certain container sizes are available.
2. **Real-world applications**:
   - Mixing solutions in a lab.
   - Cooking measurements without precise measuring tools.
   - Resource allocation in manufacturing.

---

## Sample Run

### Input:
```
Enter capacity of jug x: 4
Enter capacity of jug y: 3
Enter goal volume: 2
```

### Output:
```
Starting state:
(0, 0)
(4, 0)
(1, 3)
(1, 0)
(0, 1)
(4, 1)
(2, 3)
Goal 2 reached.
```

---

## Example Explanation
For **x = 4**, **y = 3**, **goal = 2**:
1. Fill jug X: `(4, 0)`
2. Pour from X to Y: `(1, 3)`
3. Empty jug Y: `(1, 0)`
4. Pour from X to Y: `(0, 1)`
5. Fill jug X: `(4, 1)`
6. Pour from X to Y: `(2, 3)` — goal reached.

---

## Complexity
- **Time Complexity**: O(max(x, y)) steps in worst case.
- **Space Complexity**: O(1) since only current state is stored.

---
