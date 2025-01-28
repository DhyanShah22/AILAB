#include <bits/stdc++.h>
using namespace std;

class WaterJugSolver {
private:
    int m, n, d;
    set<pair<int, int>> visited;
    
    bool isGoalState(int x, int y) {
        return x == d || y == d || (x + y == d);
    }
    
    vector<pair<pair<int, int>, string>> bfs() {
        queue<pair<pair<int, int>, vector<pair<pair<int, int>, string>>>> q;
        q.push({{0, 0}, {}});
        visited.insert({0, 0});
        
        cout << "Search Space (All Explored States):" << endl;
        
        while (!q.empty()) {
            int x = q.front().first.first;
            int y = q.front().first.second;
            vector<pair<pair<int, int>, string>> path = q.front().second;
            q.pop();
            
            cout << "(" << x << ", " << y << ")" << endl;
            
            if (isGoalState(x, y)) return path;
            
            vector<pair<pair<int, int>, string>> operations = {
                {{m, y}, "Fill jug 1"},
                {{x, n}, "Fill jug 2"},
                {{0, y}, "Empty jug 1"},
                {{x, 0}, "Empty jug 2"},
                {{min(x + y, m), max(0, x + y - m)}, "Pour jug 2 to jug 1"},
                {{max(0, x + y - n), min(x + y, n)}, "Pour jug 1 to jug 2"}
            };
            
            for (auto& op : operations) {
                int nx = op.first.first;
                int ny = op.first.second;
                string action = op.second;
                
                if (!visited.count({nx, ny})) {
                    visited.insert({nx, ny});
                    vector<pair<pair<int, int>, string>> newPath = path;
                    newPath.push_back({{nx, ny}, action});
                    q.push({{nx, ny}, newPath});
                }
            }
        }
        
        return {};
    }
    
public:
    WaterJugSolver(int m, int n, int d) : m(m), n(n), d(d) {}
    
    void solve() {
        vector<pair<pair<int, int>, string>> solution = bfs();
        
        if (solution.empty()) {
            cout << "No solution exists." << endl;
            return;
        }
        
        cout << "\nSolution Steps (with state transitions):" << endl;
        pair<int, int> prev = {0, 0};  // Start from the initial state
        for (const auto& step : solution) {
            pair<int, int> current = step.first;
            string action = step.second;
            cout << "(" << prev.first << ", " << prev.second << ") -> (" 
                 << current.first << ", " << current.second << ") : " 
                 << action << endl;
            prev = current;
        }
    }
};

int main() {
    int m, n, d;
    
    cout << "Enter capacity of first jug (m): ";
    cin >> m;
    
    cout << "Enter capacity of second jug (n): ";
    cin >> n;
    
    cout << "Enter target volume (d): ";
    cin >> d;
    
    if (m <= 0 || n <= 0 || d <= 0) {
        cout << "Invalid input. Capacities and target must be positive." << endl;
        return 1;
    }
    
    if (d > max(m, n)) {
        cout << "Target volume exceeds both jug capacities." << endl;
        return 1;
    }
    
    WaterJugSolver solver(m, n, d);
    solver.solve();
    
    return 0;
}
