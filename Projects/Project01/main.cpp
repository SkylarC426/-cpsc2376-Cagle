#include <iostream>
#include <vector>


using namespace std; //found out about this its so nice
//don't need to put std before cout and cin

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

public:
    ConnectFour() { //constructor to initialize the board and sets the starting player
        makeBoard();
        currentPlayer = Token::PLAYER_1;
    }

    void makeBoard() { //makes board with empty tokens
        board = vector<vector<Token>>(Rows, vector<Token>(Cols, Token::EMPTY));
    }

    void displayBoard() { //formats the board and displays it
        for (int r = 0; r < Rows; r++) { //row loop
            for (int c = 0; c < Cols; c++) { //column loop
                cout << (board[r][c] == Token::PLAYER_1 ? 'X' : (board[r][c] == Token::PLAYER_2 ? 'O' : '.')) << " ";
            }
            cout << endl;
        }
        cout << "1 2 3 4 5 6 7" << endl; // column numbers for the players
    }

    bool dropToken(int col) { //drops player token into the column
        if (col < 0 || col >= Cols || board[0][col] != Token::EMPTY) return false;//sees if column is valid or full 
        for (int r = Rows - 1; r >= 0; r--) { //starts at bottom row and checks to see if any space till it gets to max
            if (board[r][col] == Token::EMPTY) {
                board[r][col] = currentPlayer; //places token in first available spot
                return true;
            }
        }
        return false;
    }

    GameState gameStatus() { //checks to see if a win or tie
        for (int r = 0; r < Rows; r++) { //checking for a win condition
            for (int c = 0; c < Cols; c++) {
                if (board[r][c] == Token::EMPTY) continue;
                if (checkWin(r, c)) return board[r][c] == Token::PLAYER_1 ? GameState::PLAYER_1_WINS : GameState::PLAYER_2_WINS;
            }
        }

        for (int c = 0; c < Cols; ++c) { //checks for a draw
            if (board[0][c] == Token::EMPTY) return GameState::ONGOING;
        }
        return GameState::DRAW;
    }

    bool checkWin(int r, int c) { //analyzes the piece dropped and sees if there are four in a row from that position
        Token token = board[r][c]; //token position
        const int directions[4][2] = { {1,0}, {0,1}, {1,1}, {1,-1} }; //goes through all directions: vertical, horizontal, left diagonal and right diagonal

        for (const auto& direction : directions) { //mpre comments
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

    void switchPlayer() { //switches turn
        currentPlayer = (currentPlayer == Token::PLAYER_1) ? Token::PLAYER_2 : Token::PLAYER_1;
    }

    void play() { //the main game loop

        //vari's for amount of games won by each player
        int xWon = 0;
        int oWon = 0;

        //rules
        cout << "Welcome to Connect Four. You and another play take turns dropping your pieces in and try to get four of your piece in a row. They can connect horizontally, vertically, and diagonally." << endl;
       
        bool running = true;
        while (running) { //loop to keep playing after 1 game
            makeBoard();
            currentPlayer = Token::PLAYER_1;
            displayBoard();

            while (gameStatus() == GameState::ONGOING) {
                int col;
                cout << "Player " << (currentPlayer == Token::PLAYER_1 ? 'X' : 'O') << "'s turn. Enter the column you would like to drop your piece in (1-7): ";
                while (!(cin >> col) || col < 1 || col > 7 || !dropToken(col - 1)) { //code to make sure the user puts in a valid number
                    cin.clear(); //clears error flags
                    cin.ignore(1000, '\n'); //gets rid of nasty input
                    cout << "Invalid input. Try again: ";
                }

                displayBoard();
                if (gameStatus() != GameState::ONGOING) break; //makes sure game is or is not won
                switchPlayer();
            }

            GameState result = gameStatus(); //results
            if (result == GameState::PLAYER_1_WINS) {
                cout << "Player X wins!" << endl;
                xWon++;
            }
                
            else if (result == GameState::PLAYER_2_WINS) {
                cout << "Player O Wins!" << endl;
                oWon++;
            }

            else cout << "It's a draw!" << endl;

            char choice; //asking to play again
            cout << "Player X has won " << xWon << " time(s). Player O has won " << oWon << " time(s)." << endl;
            cout << "Play again? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') running = false; //checking for valid input
        }
    }

};

//small main to start the game
int main() {
    ConnectFour game;
    game.play();
    return 0;
}