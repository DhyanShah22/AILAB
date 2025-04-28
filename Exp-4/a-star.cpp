#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

struct Node {
    vector<int> board;
    int g, h, f;
    Node(vector<int> b, int g_val, int h_val) : board(b), g(g_val), h(h_val), f(g_val + h_val) {}
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f; // Min-Heap based on f
    }
};

inline void printBoard(const vector<int>& board) {
    for (int i = 0; i < 9; ++i) {
        cout << (board[i] ? to_string(board[i]) : " ") << " ";
        if (i % 3 == 2) cout << "\n";
    }
    cout << "---------\n";
}

inline int calculateHeuristic(const vector<int>& board, const vector<int>& goal) {
    int misplaced = 0;
    for (int i = 0; i < 9; ++i)
        if (board[i] && board[i] != goal[i])
            ++misplaced;
    return misplaced;
}

inline string boardKey(const vector<int>& board) {
    return string(board.begin(), board.end());
}

bool isSolvable(const vector<int>& board) {
    int inv = 0;
    for (int i = 0; i < 9; ++i)
        for (int j = i + 1; j < 9; ++j)
            if (board[i] && board[j] && board[i] > board[j])
                ++inv;
    return inv % 2 == 0;
}

vector<vector<int>> getSuccessors(const vector<int>& board) {
    vector<vector<int>> successors;
    int zero = find(board.begin(), board.end(), 0) - board.begin();
    int r = zero / 3, c = zero % 3;
    vector<pair<int, int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};

    for (auto [dr, dc] : moves) {
        int nr = r + dr, nc = c + dc;
        if (nr >= 0 && nr < 3 && nc >= 0 && nc < 3) {
            int nPos = nr * 3 + nc;
            auto newBoard = board;
            swap(newBoard[zero], newBoard[nPos]);
            successors.push_back(newBoard);
        }
    }
    return successors;
}

void solvePuzzle(const vector<int>& initial, const vector<int>& goal) {
    if (!isSolvable(initial)) {
        cout << "The given puzzle is not solvable.\n";
        return;
    }

    priority_queue<Node, vector<Node>, CompareNode> openList;
    unordered_set<string> closedList;
    openList.emplace(initial, 0, calculateHeuristic(initial, goal));

    while (!openList.empty()) {
        Node current = openList.top(); openList.pop();
        string key = boardKey(current.board);

        if (closedList.count(key)) continue;
        closedList.insert(key);

        cout << "Step " << current.g << " (f = " << current.f << "):\n";
        printBoard(current.board);

        if (current.board == goal) {
            cout << "Solution found in " << current.g << " moves!\n";
            return;
        }

        for (auto& succ : getSuccessors(current.board))
            if (!closedList.count(boardKey(succ)))
                openList.emplace(succ, current.g + 1, calculateHeuristic(succ, goal));
    }
    cout << "No solution found.\n";
}

int main() {
    cout << "Enter the initial state of the puzzle (9 numbers, 0 for blank):\n";
    vector<int> initial(9);
    for (auto& num : initial) cin >> num;
    vector<int> goal = {1,2,3,4,5,6,7,8,0};

    solvePuzzle(initial, goal);
}
