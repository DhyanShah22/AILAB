#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs(int startnode,int goalNode,vector<vector<int>>& graph, vector<int>& visited) {
    queue<int> que;
    que.push(startnode);
    visited[startnode] = 1;
    int currnode;

    while (!que.empty()) {
        currnode = que.front();
        que.pop();
        cout << currnode << " ";

        if(currnode == goalNode) break;
        for (int neighbor : graph[currnode]) {

            if (!visited[neighbor]) {
                que.push(neighbor);
                visited[neighbor] = 1;
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> graph(nodes);
    vector<int> visited(nodes, 0);

    cout << "Enter the edges (fromNode toNode):" << endl;
    for (int i = 0; i < edges; i++) {
        int fromNode, toNode;
        cin >> fromNode >> toNode;

        if (fromNode < 0 || fromNode >= nodes || toNode < 0 || toNode >= nodes) {
            cout << "Invalid edge! Nodes must be between 0 and " << nodes - 1 << endl;
            i--; 
            continue;
        }

        graph[fromNode].push_back(toNode);
        graph[toNode].push_back(fromNode);
    }

    cout << "Adjacency List:" << endl;
    for (int i = 0; i < nodes; i++) {
        cout << i << ": ";
        for (int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    cout << "BFS Traversal" << endl;
    cout << "Enter the start node: ";
    int startNode;
    cin >> startNode;

    cout<<endl;

    int goalNode;
    cout << "Enter the goal node: ";
    cin >> goalNode;

    if (startNode < 0 || startNode >= nodes || goalNode<0||goalNode>=nodes) {
        cout << "Invalid start node or goal ! Must be between 0 and " << nodes - 1 << endl;
        return 1;
    }

    bfs(startNode,goalNode, graph, visited);

    
    return 0;
}