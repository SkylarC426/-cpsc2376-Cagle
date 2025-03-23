#include "Connect4.h"

#include <vector>
#include <iostream>

using namespace std;

//constructor to make board and set starting player, necessary for initializing game state when the connect four object is created
ConnectFour::ConnectFour() {
    reset();
}

//resets board to base state and forces player 1 to start
void ConnectFour::reset() {
    board = vector<vector<Token>>(Rows, vector<Token>(Cols, Token::EMPTY));
    currentPlayer = Token::PLAYER_1;
}

//function to display current board state
void ConnectFour::displayBoard() const {
    for (int r = 0; r < Rows; r++) { //loop to go through rows and cols
        for (int c = 0; c < Cols; c++) {
            char token = (board[r][c] == Token::EMPTY) ? '.' : //displays x for p1, o for p2, and . for a blank space
                (board[r][c] == Token::PLAYER_1) ? 'X' : 'O';
            cout << token << " ";
        }
        cout << endl;
    }
}

//function to drop a token in a col
bool ConnectFour::dropToken(int col) { //drops player token into the column
    if (col < 0 || col >= Cols || board[0][col] != Token::EMPTY) return false; //makes sure tokens can't be placed o.o.b. or in a full col
    for (int r = Rows - 1; r >= 0; r--) { //loop to check for the lowest empty slot to place token in
        if (board[r][col] == Token::EMPTY) {
            board[r][col] = currentPlayer; //if true, place token
            return true;
        }
    }
    return false;
}

//function to check the game status
GameState ConnectFour::status() const { //checks to see if a win or tie
    for (int r = 0; r < Rows; r++) { //scans board through loop
        for (int c = 0; c < Cols; c++) {
            if (board[r][c] == Token::EMPTY) continue; //skips empty cells
            if (checkWin(r, c)) return board[r][c] == Token::PLAYER_1 ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS; //returns winner
        }
    }

    for (int c = 0; c < Cols; ++c) { //checks for any empty spaces left
        if (board[0][c] == Token::EMPTY) return GameState::ONGOING; //if yes, game is still going
    }
    return GameState::DRAW; //if no, then it is a draw
}

//function to check who won
bool ConnectFour::checkWin(int r, int c) const { //analyzes the piece dropped and sees if there are four in a row from that position
    Token token = board[r][c]; //token position
    const int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} }; //goes through all directions: vertical, horizontal, left diagonal and right diagonal

    for (const auto& direction : directions) { 
        int dr = direction[0]; //ups row count
        int dc = direction[1]; // ups col amount
        int count = 1; //makes the token placed have a count of one

        for (int i = 1; i < 4; i++) { //checks to see if 3 pieces are in the same direction
            int nr = r + dr * i;
            int nc = c + dc * i;
            if (nr < 0 || nr >= Rows || nc < 0 || nc >= Cols || board[nr][nc] != token) break;
            count++;
        }
        if (count >= 4) return true; //if four in a row return true
    }
    return false;
}

//function to switch players after a turn ends
void ConnectFour::switchPlayer() {
    currentPlayer = (currentPlayer == Token::PLAYER_1) ? Token::PLAYER_2 : Token::PLAYER_1;
}

//starts new game
void ConnectFour::startGame() {
    reset();
    currentPlayer = Token::PLAYER_1;
}

//overloaded stream insertion operator which displays board, necessary for stream outputing 
std::ostream& operator<<(std::ostream& os, const ConnectFour& game) {
    for (int r = 0; r < Rows; r++) {
        for (int c = 0; c < Cols; c++) {
            char token = (game.board[r][c] == Token::EMPTY) ? '.' :
                (game.board[r][c] == Token::PLAYER_1) ? 'X' : 'O';
            os << token << " ";
        }
        os << endl;
    }
    return os;
}

//function to manage game loop and player turns
void playConnectFour() {
    ConnectFour game; //creates game
    int xWon = 0
    int oWon = 0; //player wins initialized
    cout << "Welcome to Connect Four!" << endl;

    bool running = true;
    while (running) { //game loop
        game.startGame(); //starts game
        game.displayBoard(); //empty board

        // Game loop
        while (game.status() == GameState::ONGOING) {
            int col;
            cout << "Player " << (game.status() == GameState::PLAYER_1_WINS ? 'X' : 'O') 
                 << "'s turn. Enter the column you would like to drop your piece in (1-7): ";

            while (!(cin >> col) || col < 1 || col > 7 || !game.dropToken(col - 1)) { //makes sure input is valid
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Try again: ";
            }
            
            game.displayBoard();//displays board after move
            if (game.status() != GameState::ONGOING) break; //if game done exits
            game.switchPlayer(); //switch player
        }

        //announces game result
        GameState result = game.status(); 
        if (result == GameState::PLAYER_1_WINS) {
            cout << "Player X wins!" << endl;
            xWon++;
        }
        else if (result == GameState::PLAYER_2_WINS) {
            cout << "Player O Wins!" << endl;
            oWon++;
        }
        else {
            cout << "It's a draw!" << endl;
        }

        // Asks the user if they want to play again
        char choice;
        cout << "Player X has won " << xWon << " time(s). Player O has won " << oWon << " time(s)." << endl;
        cout << "Play again? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            cout << "Closing program." << endl;
            running = false;
        }
    }
}
