#include <iostream>
#include <string>
#include <vector>
#include "Reversi.h"

using namespace std;

Reversi::Reversi(){
    // cout << "hello world" << endl;
    for(int i = 0; i < 8; ++i){
        board.push_back(vector<char>(8));
    }
    for(int i = 0; i < 8; ++i) { // initialize the board with '-'
        for(int j = 0; j < 8; ++j) {
            board[i][j] = '-';
        } 
    }
    board[3][3] = 'T';
    board[3][4] = 'F';
    board[4][3] = 'F';
    board[4][4] = 'T';
}

void Reversi::printBoard(){
    cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    for (int i = 0; i < 8; i++){
        cout << i+1 << " |";
        for (int j = 0; j < 8; j++)
        {
            cout << " " << board[j][i] << " |";
        }
        cout << endl << "  +---+---+---+---+---+---+---+---+ "<< endl;
    }
    cout << "    1   2   3   4   5   6   7   8 " << endl;
}

void Reversi::makeMove(){


}

void Reversi::checkWin(){
    int boardFull;

    for (int i = 0; i < 8; i++){ // Needs more checks
        for (int j = 0; j < 8; j++){
            if (board[i][j] == '-'){
                boardFull = 0;
                break;
            }
            boardFull = 1;
        }
    }

}

void Reversi::flipPieces(){


}