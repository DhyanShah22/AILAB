#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

struct State{
    int x, y;
    string action;
    State* parent;

    State(int _x, int _y, string _action, State* _parent)
        :x(_x), y(_y), action(_action), parent(_parent) {}
};

void printSolution(State* state){
    if(state == nullptr) return;
    printSolution(state->parent);
    cout << state->action << " " << state->x << " " << state->y <<endl;
}

void bfs(int m, int n, int d){
    queue<State*> s;
    set<pair<int , int>>visited;

    State* start = new State(0, 0, "Start", nullptr);
    s.push(start);
    visited.insert({0, 0});

    cout << "Searching Space: "<<endl;

    while(!s.empty()){
        State* curr = s.front();
        s.pop();

        cout<< "( "<< curr->x << ", "<< curr->y << " )"<<endl;

        if(curr->x == d || curr->y == d){
            cout << "\nSolution Steps:\n";
            printSolution(curr);
            return;
        }

        vector<State*> nextMoves = {
            new State(m, curr->y, "Fill Jug 1", curr),
            new State(curr->x, n, "Fill Jug 1", curr),
            new State(0, curr->y, "Empty Jug 1", curr),
            new State(curr->x, 0, "Empty Jug 1", curr),
            new State(min(curr->x + curr->y, m), max(0, curr->x + curr->y - m), "Pour from Jug 2 to Jug 1", curr),
            new State(max(0, curr->x + curr->y - n), min(curr->x + curr->y, n), "Pour from JUg 1 to Jug 2", curr)
        };

        for(auto next : nextMoves){
            if(!visited.count({next->x, next->y})){
                visited.insert({next->x, next->y});
                s.push(next);
            }
            else{
                delete next;
            }
        }
    }
    cout<< "No solution found"<<endl;
}

int main() {
    int m, n ,d;

    cout<<"Enter capacity of Jug 1: "<< endl;
    cin>>m;

    cout<<"Enter capacity of Jug 2: "<< endl;
    cin>>n;

    cout<<"Enter capacity of Expected: "<< endl;
    cin>>d;

    bfs(m, n, d);
    return 0;
}