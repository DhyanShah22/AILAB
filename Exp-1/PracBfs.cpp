#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void bfs(int stratnode, int goalnode, vector<vector<int>>& graph, vector<int>&visited){
    queue<int> que;
    que.push(stratnode);
    visited[stratnode] = 1;
    int currnode;

    while(!que.empty()){
        currnode = que.front();
        que.pop();
        cout<< currnode <<" ";

        if(currnode == goalnode) break;
        for(int neighbor : graph[currnode]){
            if(!visited[neighbor]){
                que.push(neighbor);
                visited[neighbor] = 1;
            }
        }
    }
}

int main(){
    int nodes, edges;
    cout<<"Enter the number of node: "<<endl;
    cin>>nodes;
    cout<<"Enter the number of edges: "<<endl;
    cin>>edges;

    vector<vector<int>>graph(nodes);
    vector<int> visited(nodes, 0);

    cout<<"Enter the edges: from-to "<<endl;
    for(int i = 0; i < edges; i++){
        int fromNode, toNode;
        cin>>fromNode>>toNode;

        if(fromNode < 0 || fromNode >= nodes || toNode < 0 || toNode >= nodes){
            cout<<"Invalid Edge!"<<endl;
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

    cout<<"BFS Traversal"<<endl;
    int startNode, goalNode;
    cout<<"Enter start node: "<<endl;
    cin>>startNode;

    cout<<"Enter goal node: "<<endl;
    cin>>goalNode;

    if(startNode < 0 || startNode >= nodes ||goalNode < 0 || goalNode>=nodes){
            cout<<"Invalid!"<<endl;
            return 1;
        }

    bfs(startNode, goalNode, graph, visited);

    return 0;
}