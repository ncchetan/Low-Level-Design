/*
    Tic Tac Toe
    
    Entities:
        Player
        Move
        Board
        Game 
*/


#include <bits/stdc++.h>

using namespace std;

class Player {
public:
    int id;
    char marker;
    
    char getMarker() {
        return this->marker;
    }
};

class Move {
public:
    int x;
    int y;
    Player* player;
};

class Board {
public:
    int size;
    vector<vector<char>> board;
    int remainingCount;
    
    Board(int size) {
        this->size = size;
        this->remainingCount = size * size;
        this->board = vector<vector<char>>(size, vector<char>(size, '#'));
    }
    
    bool isOver() {
        return remainingCount == 0;
    }
    
    void placeMove(Move* move) {
        if(!move) return;
        int x = move->x;
        int y= move->y;
        Player* player = move->player;
        
        if(board[x][y] != '#') return;
        board[x][y] = player->getMarker();
    }
    
    bool checkWinner(Move* lastMove) {
        if(!lastMove) return false;
        
        return checkRow(lastMove) or checkCol(lastMove) or checkDiagonal(lastMove) or checkCrossDiagonal(lastMove); 
    }
    
    bool checkRow(Move* move) {
        int x = move->x;
        for(int i=0; i<size; i++) {
            if(board[x][i] != move->player->getMarker()) return false;
        }
        return true;
    }
    
    bool checkCol(Move* move) {
        int y = move->y;
        for(int i=0; i<size; i++) {
            if(board[i][y] != move->player->getMarker()) return false;
        }
        return true;
    }
    
    bool checkDiagonal(Move* move) {
        for(int i=0; i<size; i++) {
            if(board[i][i] != move->player->getMarker()) return false;
        }
        return true;
    }
    
    bool checkCrossDiagonal(Move* move) {
        for(int i=size-1; i>=0; i--) {
            if(board[size-1-i][i] != move->player->getMarker()) return false;
        }
        return true;
    }
};

class Game {
public:
    Player* p1;
    Player* p2;
    Board* board;
    
    Player* currentPlayer = p2;
    Move* lastMove;
    
    void play() {
        while(!board->isOver() and !board->checkWinner(lastMove)) {
            currentPlayer = (currentPlayer->id)%2 == 1 ? p2 : p1;
            int x, y;
            cout<<"Enter x and y for "<<currentPlayer->id<<endl;
            cin>>x>>y;
            lastMove->x = x;
            lastMove->y =y;
            lastMove->player = currentPlayer;
            
            board->placeMove(lastMove);
        }
        
        if(board->checkWinner(lastMove)) {
            cout<<"Winner is "<<lastMove->player->id;
        } else {
            cout<<"Game Tied"<<endl;
        }
    }
};

int main() {
    Player* p1 = new Player(1, 'X');
    Player* p2 = new Player(2, 'O');
    Board* board = new Board(3);
    
    Game* game = new Game(p1, p2, board);
    
    game->play();
}

