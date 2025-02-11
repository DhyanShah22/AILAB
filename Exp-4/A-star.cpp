#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

struct Node {
    string name;
    int g;  
    int h;  
    int f;  

    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

unordered_map<string, vector<pair<string, int>>> adj;
unordered_map<string, int> heuristic;

void aStar(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> g_cost;
    unordered_map<string, string> parent;

    g_cost[start] = 0;
    pq.push({start, 0, heuristic[start], heuristic[start]});
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.name == goal) {
            cout << "Path found: ";
            string path = goal;
            while (path != start) {
                cout << path << " <- ";
                path = parent[path];
            }
            cout << start << "\nTotal Cost: " << current.g << endl;
            return;
        }

        for (auto neighbor : adj[current.name]) {
            string next = neighbor.first;
            int cost = neighbor.second;
            int new_g = current.g + cost;
            int new_f = new_g + heuristic[next];

            if (!g_cost.count(next) || new_g < g_cost[next]) {
                g_cost[next] = new_g;
                parent[next] = current.name;
                pq.push({next, new_g, heuristic[next], new_f});
            }
        }
    }
    cout << "No path found!" << endl;
}

int main() {
    heuristic["S"] = 7;
    heuristic["A"] = 10;
    heuristic["B"] = 9;
    heuristic["C"] = 5;
    heuristic["G"] = 0;

    adj["S"].push_back({"A", 1});
    adj["A"].push_back({"S", 1});
    adj["S"].push_back({"B", 1});
    adj["B"].push_back({"S", 1});
    adj["A"].push_back({"B", 9});
    adj["B"].push_back({"A", 9});
    adj["B"].push_back({"C", 6});
    adj["C"].push_back({"B", 6});
    adj["C"].push_back({"G", 5});
    adj["G"].push_back({"C", 5});
    adj["B"].push_back({"G", 12});
    adj["G"].push_back({"B", 12});

    string start = "S", goal = "G";
    aStar(start, goal);
    
    return 0;
}