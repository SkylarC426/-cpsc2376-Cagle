#include "Connect4.h"
#include <SDL2/SDL2_gfxPrimitives.h>

//constructor to initailize board and current player
ConnectFour::ConnectFour() { reset(); }

//resets
void ConnectFour::reset() {
    //creates a grid with rows*columns of empty tokens
    board.assign(Rows, std::vector<Token>(Cols, Token::EMPTY)); 
    currentPlayer = Token::PLAYER1;
}

//drops token in col
bool ConnectFour::dropToken(int col) {
    if (col < 0 || col >= Cols || board[0][col] != Token::EMPTY) return false; //false if occupied

    //finds lowest empty cell in col
    for (int r = Rows - 1; r >= 0; --r) { 
        if (board[r][col] == Token::EMPTY) {
            board[r][col] = currentPlayer;
            return true; //drops if EMPTY
        }
    }
    return false;
}

//toggles between player 1 and 2
void ConnectFour::switchPlayer() {
    currentPlayer = (currentPlayer == Token::PLAYER1) ? Token::PLAYER2 : Token::PLAYER1;
}


GameState ConnectFour::status() const {
    //Loop to Check for win
    for (int r = 0; r < Rows; ++r) {
        for (int c = 0; c < Cols; ++c) {
            if (board[r][c] == Token::EMPTY) continue;
            if (checkWin(r, c))
                return (board[r][c] == Token::PLAYER1)
                ? GameState::PLAYER1_WINS
                : GameState::PLAYER2_WINS;
        }
    }
    //Check for draw or ongoing if no win
    for (int c = 0; c < Cols; ++c)
        if (board[0][c] == Token::EMPTY) return GameState::ONGOING;
    return GameState::DRAW;
}

//checks for 4 in a row
bool ConnectFour::checkWin(int r, int c) const {
    Token tok = board[r][c]; //token
    //checks 4 direction vectors, down, right, down right, and up right
    static const int dirs[4][2] = { {1,0},{0,1},{1,1},{1,-1} };
    for (auto& d : dirs) {
        //includes starting cell and then checks 3 in each direction
        int rowCount = 1;
        for (int i = 1; i < 4; ++i) {
            int nr = r + d[0] * i, nc = c + d[1] * i;
            //stops counting in Out of Bounds direction
            if (nr < 0 || nr >= Rows || nc < 0 || nc >= Cols || board[nr][nc] != tok)
                break;
            ++rowCount;
        }
        //if 4 or more its a win
        if (rowCount >= 4) return true;
    }
    return false;
}

//makes the background and draws cicles for the tokens
void ConnectFour::draw(SDL_Renderer* renderer) const {
    //makes screen blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    //draws each cell as a circle
    for (int r = 0; r < Rows; ++r) {
        for (int c = 0; c < Cols; ++c) {
            //computes cell size
            int x = c * CellSize + CellSize / 2;
            int y = r * CellSize + CellSize / 2;
            int rad = CellSize / 2 - 8; //padding

            Uint8 rc = 255, gc = 255, bc = 255; //white for empty
            if (board[r][c] == Token::PLAYER1) { rc = 255; gc = 0; bc = 0; } //red for p1
            else if (board[r][c] == Token::PLAYER2) { rc = 255; gc = 255; bc = 0; } //yellow for p2
            filledCircleRGBA(renderer, x, y, rad, rc, gc, bc, 255); //draws filled circle
        }
    }
}