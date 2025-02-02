#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <sstream>
using namespace std;
// Structure representing a state in the 8-puzzle.
struct Node {
    vector<int> board;      // 9 elements representing the board in row-major order.
    int g;                  // Cost so far (depth).
    int h;                  // Heuristic (number of misplaced tiles).
    int f;                  // f = g + h.
};
// Comparator for the priority queue (min-heap based on f-value).
struct CompareNode {
    bool operator()(const Node &a, const Node &b) const {
        return a.f > b.f;
    }
};
// Utility: Print the board in a 3x3 matrix format.
void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; i++) {
        cout << (board[i] == 0 ? " " : to_string(board[i])) << " ";
        if ((i + 1) % 3 == 0)
            cout << endl;
    }
    cout << "---------" << endl;
}

// Calculate the heuristic: number of misplaced tiles (ignoring the blank, which is 0).
int calculateHeuristic(const vector<int>& board, const vector<int>& goal) {
    int misplaced = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 0 && board[i] != goal[i])
            misplaced++;
    }
    return misplaced;
}

// Utility: Convert board vector to a string representation for hashing.
string boardToString(const vector<int>& board) {
    stringstream ss;
    for (int num : board) {
        ss << num;
    }
    return ss.str();
}

// Check if a given puzzle configuration is solvable.
bool isSolvable(const vector<int>& board) {
    int inversions = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) continue;
        for (int j = i + 1; j < 9; j++) {
            if (board[j] == 0) continue;
            if (board[i] > board[j])
                inversions++;
        }
    }
    return (inversions % 2 == 0);
}

// Generate all valid successors by moving the blank (0) in four possible directions.
vector<vector<int>> getSuccessors(const vector<int>& board) {
    vector<vector<int>> successors;
    int zeroPos = find(board.begin(), board.end(), 0) - board.begin();
    int row = zeroPos / 3;
    int col = zeroPos % 3;
    vector<pair<int, int>> moves = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (auto move : moves) {
        int newRow = row + move.first;
        int newCol = col + move.second;
        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            int newPos = newRow * 3 + newCol;
            vector<int> newBoard = board;
            swap(newBoard[zeroPos], newBoard[newPos]);
            successors.push_back(newBoard);
        }
    }
    return successors;
}
// The A* search function.
void solvePuzzle(const vector<int>& initial, const vector<int>& goal) {
    if (!isSolvable(initial)) {
        cout << "The given puzzle is not solvable." << endl;
        return;
    }
    priority_queue<Node, vector<Node>, CompareNode> openList;
    unordered_set<string> closedList;
    Node start;
    start.board = initial;
    start.g = 0;
    start.h = calculateHeuristic(initial, goal);
    start.f = start.g + start.h;
    openList.push(start);
    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();
        string boardStr = boardToString(current.board);
        if (closedList.find(boardStr) != closedList.end())
            continue;
        closedList.insert(boardStr);
        // Print current board state
        cout << "Step " << current.g << " (f = " << current.f << "):" << endl;
        printBoard(current.board);
        // Goal check.
        if (current.board == goal) {
            cout << "Solution found in " << current.g << " moves!" << endl;
            return;
        }

        // Generate successors.
        vector<vector<int>> successors = getSuccessors(current.board);
        for (auto childBoard : successors) {
            string childStr = boardToString(childBoard);
            if (closedList.find(childStr) != closedList.end())
                continue;
            Node childNode;
            childNode.board = childBoard;
            childNode.g = current.g + 1;
            childNode.h = calculateHeuristic(childBoard, goal);
            childNode.f = childNode.g + childNode.h;
            openList.push(childNode);
        }
    }
    cout << "No solution found." << endl;
}
int main() {
    cout << "Enter the initial state of the puzzle (9 numbers with 0 as blank):" << endl;
    vector<int> initial(9);
    for (int i = 0; i < 9; i++) {
        cin >> initial[i];
    }
    vector<int> goal = {1, 2, 3, 4 , 5, 6, 7, 8, 0};
    solvePuzzle(initial, goal);
    return 0;
}
