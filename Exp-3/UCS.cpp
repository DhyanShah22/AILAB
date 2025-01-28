#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
};

struct Node {
    int vertex, cost;

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

vector<int> uniformCostSearch(int start, int goal, vector<vector<Edge>>& graph) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    unordered_map<int, int> minCost;

    unordered_map<int, int> parent;

    pq.push({start, 0});
    minCost[start] = 0;
    parent[start] = -1;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int currentNode = current.vertex;
        int currentCost = current.cost;

        if (currentNode == goal) {
            vector<int> path;
            int node = goal;
            while (node != -1) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : graph[currentNode]) {
            int nextNode = edge.to;
            int newCost = currentCost + edge.cost;

            if (minCost.find(nextNode) == minCost.end() || newCost < minCost[nextNode]) {
                minCost[nextNode] = newCost;
                parent[nextNode] = currentNode;
                pq.push({nextNode, newCost});
            }
        }
    }

    return {};
}

int main() {
    int numNodes = 6;
    vector<vector<Edge>> graph(numNodes);

    graph[0].push_back({1, 1});
    graph[0].push_back({2, 4});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 6});
    graph[2].push_back({3, 3});
    graph[3].push_back({4, 1});
    graph[4].push_back({5, 5});

    int start = 0, goal = 5;

    vector<int> path = uniformCostSearch(start, goal, graph);

    if (!path.empty()) {
        cout << "Shortest Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found from " << start << " to " << goal << "." << endl;
    }

    return 0;
}
