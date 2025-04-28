#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<vector<int>>& graph, int start,vector<bool>& visited){
    visited[start] = true;
    cout << start << " ";
    for(int i = 0; i < graph[start].size(); i++){
        if(!visited[graph[start][i]]){
            dfs(graph, graph[start][i],visited);
        }
    }
}

int main(){
    cout << "Enter the vertices:";
    int v;
    cin >> v;
    vector<vector<int>> graph(v+1);
    cout << "Enter the edges:";
    int e;
    cin >> e;
    for(int i = 0; i < e; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        }
    cout << "Enter the starting node:";
    int s;
    cin >>s;
    vector<bool> visited(graph.size(), false);
    dfs(graph,s,visited);
    
    return 0;
}