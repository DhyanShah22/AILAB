#include<iostream>
#include<vector>

using namespace std;

void dfs(vector<vector<int>>& graph, int s, vector<bool>& visited){
    visited[s] = true;
    cout << s << " ";
    for(int i = 0; i < graph[s].size(); i++){
        if(!visited[graph[s][i]]){
            dfs(graph, graph[s][i], visited);
        }
    }
}

int main(){
    int vert, edge;
    cout<<"Enter nodes:"<<endl;
    cin>>vert;
    cout<<"Enter edge:"<<endl;
    cin>>edge;

    vector<vector<int>>graph(vert+1);

    cout<<"Enter edges:";
    for(int i = 0; i < edge; i++){
        int m,n;
        cin>>m>>n;
        graph[m].push_back(n);
        graph[n].push_back(m);
        }
    cout << "Enter the starting node:";
    int s;
    cin >>s;
    vector<bool> visited(graph.size(), false);
    dfs(graph,s,visited);
    
    return 0;
}