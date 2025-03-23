#ifndef CONNECT4_H
#define CONNECT4_H

#include <vector>
#include <iostream>

using namespace std;

//constants for rows and columns
const int Rows = 6;
const int Cols = 7;

//Enum for the state of the game
enum GameState { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };

//enum for the slots on the board
enum Token { EMPTY, PLAYER_1, PLAYER_2 };

//class for the game logic
class ConnectFour {
private:
    vector<vector<Token>> board; //vector for the board
    Token currentPlayer; //what token gets placed based on the current player

    bool checkWin(int r, int c) const; //function to check for a win

public:
    //constructors
    ConnectFour(); 
    
    //functions
    bool dropToken(int col); //drop token in a col
    GameState status() const; //check state of game
    void switchPlayer(); //switch player
    void reset(); //reset game
    void displayBoard() const; //display game board
    void startGame();//starts game
    friend std::ostream& operator<<(std::ostream& os, const ConnectFour& game); //friend to output board
};

#endif
