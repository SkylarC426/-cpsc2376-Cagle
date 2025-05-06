#ifndef CONNECT4_H
#define CONNECT4_H

#include <vector>
#include <SDL2/SDL.h>

//Token state in cells
enum class Token { EMPTY, PLAYER1, PLAYER2 };

//Game states
enum class GameState { ONGOING, PLAYER1_WINS, PLAYER2_WINS, DRAW };

class ConnectFour {
public:
    static constexpr int Rows = 6; //row count
    static constexpr int Cols = 7; //column count
    static constexpr int CellSize = 100; //pixel size of cell
    static constexpr int WindowWidth = Cols * CellSize; //total width of created window
    static constexpr int WindowHeight = Rows * CellSize; //total height of created window

    ConnectFour(); //constructor
    void reset(); //clears board resets to p1 turn
    bool dropToken(int col); // drops a token in column
    void switchPlayer(); //toggles between players
    GameState status() const; // returns game state
    void draw(SDL_Renderer* renderer) const; //renders current board
    Token getCurrentPlayer() const { return currentPlayer; } //returns which player's turn it is

private:
    std::vector<std::vector<Token>> board; //2d grid
    Token currentPlayer; //who moves next
    bool checkWin(int r, int c) const; // checks for 4 in a row
};

#endif