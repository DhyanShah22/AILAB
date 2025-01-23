#include <bits/stdc++.h>
using namespace std;

class WaterJugSolver {
private:
    int m, n, d;
    set<pair<int, int>> visited;
    
    bool isGoalState(int x, int y) {
        return x == d || y == d || (x + y == d);
    }
    
    vector<string> bfs() {
        queue<pair<pair<int, int>, vector<string>>> q;
        q.push({{0, 0}, {}});
        visited.insert({0, 0});
        
        while (!q.empty()) {
            int x = q.front().first.first;
            int y = q.front().first.second;
            vector<string> path = q.front().second;
            q.pop();
            
            if (isGoalState(x, y)) return path;
            
            vector<pair<pair<int, int>, string>> operations = {
                {{m, y}, "Fill jug 1"},
                {{x, n}, "Fill jug 2"},
                {{0, y}, "Empty jug 1"},
                {{x, 0}, "Empty jug 2"},
                {{min(x+y, m), max(0, x+y-m)}, "Pour jug 2 to jug 1"},
                {{max(0, x+y-n), min(x+y, n)}, "Pour jug 1 to jug 2"}
            };
            
            for (auto& op : operations) {
                int nx = op.first.first;
                int ny = op.first.second;
                string action = op.second;
                
                if (!visited.count({nx, ny})) {
                    visited.insert({nx, ny});
                    vector<string> newPath = path;
                    newPath.push_back(action);
                    q.push({{nx, ny}, newPath});
                }
            }
        }
        
        return {};
    }
    
public:
    WaterJugSolver(int m, int n, int d) : m(m), n(n), d(d) {}
    
    void solve() {
        vector<string> solution = bfs();
        
        if (solution.empty()) {
            cout << "No solution exists." << endl;
            return;
        }
        
        cout << "Solution Steps:" << endl;
        for (const string& step : solution) {
            cout << step << endl;
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