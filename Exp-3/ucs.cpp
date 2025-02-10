#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    char vertex;
    int cost;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) {
        return a.cost > b.cost; 
    }
};

void uniformCostSearch(char start, char goal, unordered_map<char, vector<pair<char, int>>>& graph) {
    priority_queue<Node, vector<Node>, CompareNode> pq;
    unordered_map<char, int> minCost;
    unordered_map<char, char> parent;

    pq.push({start, 0});
    minCost[start] = 0;

    cout << "Nodes visited (step-by-step with cost):\n";

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        cout << current.vertex << " (Cost: " << current.cost << ")\n";

        if (current.vertex == goal) {
            cout << "\nMinimum Cost to reach " << goal << ": " << current.cost << endl;

            string path = "";
            char node = goal;
            while (node != start) {
                path = " -> " + string(1, node) + path;
                node = parent[node];
            }
            path = start + path;
            cout << "Shortest Path: " << path << endl;
            return;
        }

        for (auto& neighbor : graph[current.vertex]) {
            char nextVertex = neighbor.first;
            int edgeCost = neighbor.second;
            int newCost = current.cost + edgeCost;

            if (!minCost.count(nextVertex) || newCost < minCost[nextVertex]) {
                minCost[nextVertex] = newCost;
                parent[nextVertex] = current.vertex;
                pq.push({nextVertex, newCost});
            }
        }
    }
    cout << "No path found to " << goal << endl;
}

int main() {
    unordered_map<char, vector<pair<char, int>>> graph;
    int edges;

    cout << "Enter number of edges: ";
    cin >> edges;

    cout << "Enter the graph edges (start vertex, end vertex, cost):\n";
    for (int i = 0; i < edges; ++i) {
        char u, v;
        int cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost});
        graph[v].push_back({u, cost});
    }

    char start, goal;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the goal node: ";
    cin >> goal;

    cout << "\nPerforming UCS from " << start << " to " << goal << "...\n";
    uniformCostSearch(start, goal, graph);

    return 0;
}
