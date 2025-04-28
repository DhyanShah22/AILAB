#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct State {
    int x, y; 
    string action;
    State* parent;
    
    State(int _x, int _y, string _action, State* _parent)
        : x(_x), y(_y), action(_action), parent(_parent) {}
};

void printSolution(State* state) {
    if (state == nullptr) return;
    printSolution(state->parent);
    cout << state->action << " "<< state->x << " " << state->y <<endl;
}

void bfs(int m, int n, int d) {
    queue<State*> q;
    set<pair<int, int>> visited;
    
    State* start = new State(0, 0, "Start", nullptr);
    q.push(start);
    visited.insert({0, 0});
    
    cout << "Search Space (All Explored States):\n";
    
    while (!q.empty()) {
        State* curr = q.front();
        q.pop();
        
        cout << "(" << curr->x << ", " << curr->y << ")\n";
        
        if (curr->x == d || curr->y == d) {
            cout << "\nSolution Steps:\n";
            printSolution(curr);
            return;
        }
        
        vector<State*> nextMoves = {
            new State(m, curr->y, "Fill Jug 1", curr),
            new State(curr->x, n, "Fill Jug 2", curr),
            new State(0, curr->y, "Empty Jug 1", curr),
            new State(curr->x, 0, "Empty Jug 2", curr),
            new State(min(curr->x + curr->y, m), max(0, curr->x + curr->y - m), "Pour Jug2 -> Jug1", curr),
            new State(max(0, curr->x + curr->y - n), min(curr->x + curr->y, n), "Pour Jug1 -> Jug2", curr)
        };
        
        for (auto next : nextMoves) {
            if (!visited.count({next->x, next->y})) {
                visited.insert({next->x, next->y});
                q.push(next);
            } else {
                delete next; 
            }
        }
    }
    
    cout << "No solution exists.\n";
}

int main() {
    int m, n, d;
    cout << "Enter capacity of Jug 1: ";
    cin >> m;
    cout << "Enter capacity of Jug 2: ";
    cin >> n;
    cout << "Enter target volume: ";
    cin >> d;
    
    if (d > max(m, n)) {
        cout << "Target volume cannot be larger than both jug capacities.\n";
        return 0;
    }
    
    bfs(m, n, d);
    
    return 0;
}
