#ifndef CONNECT4_H
#define CONNECT4_H

#include <vector>
#include <iostream>

using namespace std;

//constants for rows and columns
const int Rows = 6;
const int Cols = 7;

//Enum for the state of the game
enum class GameState { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };

//enum for the slots on the board
enum class Token { EMPTY, PLAYER_1, PLAYER_2 };

class ConnectFour {
    private:
        vector<vector<Token>> board; //vector representing the board
        Token currentPlayer; //Keeps track of who's turn it is

        bool checkWin(int r, int c) const;

    public: 
        ConnectFour();
        bool play(int col);
        GameState status() const;
        void switchPlayer();
        void reset();
        friend std::ostream& operator<<(std::ostream& os, const ConnectFour& game);
};

#endif