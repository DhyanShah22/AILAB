#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

const char HUMAN = 'X';
const char AI = 'O';
const char EMPTY = ' ';

void printBoard(const vector<char>& board){
    cout<< endl;
    for(int i = 0; i < 9; i++){
        cout << (board[i] == EMPTY ? '_' : board[i]) << " ";
        if(i % 3 == 2){
            cout <<endl;
        }
    }
    cout<<endl;
}

bool isMovesLeft(const vector<char>& board){
    return find(board.begin(), board.end(), EMPTY) != board.end();
}

int evaluate(const vector<char>& b){
    const int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };
    for(auto&w : wins){
        if(b[w[0]] != EMPTY && b[w[0]] == b[w[1]] && b[w[1]] == b[w[2]]){
            return (b[w[0]] == AI) ? 10 : -10;
        }
    }
    return 0;
}

int minimax(vector<char>& board, bool isMax){
    int score = evaluate(board);
    if(score || !isMovesLeft(board)){
        return score;
    }

    int best = isMax ? INT_MIN : INT_MAX;
    for(int i = 0; i < 9; i++){
        if(board[i] == EMPTY){
            board[i] = isMax ? AI : HUMAN;
            int val = minimax(board, !isMax);
            board[i] = EMPTY;
            best = isMax ? max(best, val) : min(best, val);
        }
    }
    return best;
}

int findBestMove(vector<char>& board){
    int bestVal = INT_MIN, bestMove = -1;
    for(int i = 0; i < 9; i++){
        if(board[i] == EMPTY){
            board[i] = AI;
            int moveVal = minimax(board, false);
            board[i] = EMPTY;
            if (moveVal > bestVal) {
                bestVal = moveVal;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

int main(){
    vector<char> board(9, EMPTY);
    cout << "You are X. AI is O.\n";
    printBoard(board);

    while(true){
        int move;
        cout << "Enter your move (0-8): ";
        cin >> move;
        if (move < 0 || move > 8 || board[move] != EMPTY) {
            cout << "Invalid move. Try again.\n";
            continue;
        }
        board[move] = HUMAN;
        printBoard(board);

        int result = evaluate(board);
        if (result == -10) { cout << "You win!\n"; break; }
        if (!isMovesLeft(board)) { cout << "It's a draw!\n"; break; }

        int aiMove = findBestMove(board);
        board[aiMove] = AI;
        cout << "AI played at position " << aiMove << endl;
        printBoard(board);

        result = evaluate(board);
        if (result == 10) { cout << "AI wins!\n"; break; }
        if (!isMovesLeft(board)) { cout << "It's a draw!\n"; break; }
    }
    return 0;
}