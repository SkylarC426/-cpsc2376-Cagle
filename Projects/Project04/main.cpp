#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Connect4.h"
#include <cstdlib>
#include <cstdio>

int main(int, char**) {
    //Initialize SDL systems
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    //Load sounds
    Mix_Chunk* dropSound = Mix_LoadWAV("drop.wav"); //played on drop
    Mix_Chunk* winSound = Mix_LoadWAV("win.wav"); //played on win

    //Create window and renderer
    SDL_Window* win = SDL_CreateWindow("Connect Four", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ConnectFour::WindowWidth, ConnectFour::WindowHeight, 0); //in order: title, x and y position, width and height, normal window (not fullscreen or borderless or resizeable)
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED); //handles software acceleration

    //Initialize TTF for status display
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24); //font and size

    //win counter for p1 and 2
    int wins1 = 0;
    int wins2 = 0;

    bool quit = false; //global quit flag
    ConnectFour game; //game instance

    //Loop to keep the game up
    while (!quit) {
        game.reset();
        bool gameOver = false;
        GameState result = GameState::ONGOING;

        // Game loop
        while (!quit && !gameOver) {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                //quits game when esc clicked or closed out of window
                if (e.type == SDL_QUIT) quit = gameOver = true;
                if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = gameOver = true;

                //allows mouse click to drop the piece
                if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                    int col = e.button.x / ConnectFour::CellSize;
                    if (game.dropToken(col)) {
                        Mix_PlayChannel(-1, dropSound, 0); //plays drop sound
                        result = game.status();
                        if (result != GameState::ONGOING) 
                            gameOver = true; //game ends
                        else
                            game.switchPlayer(); //next player's turn
                    }
                }
            }

            //Draws board
            game.draw(ren);

            //Displays status in window title
            Token cur = game.getCurrentPlayer();
            char titleBuf[128];
            std::snprintf(titleBuf, sizeof(titleBuf),
                "Connect Four - X:%d O:%d - Turn: %c",
                wins1, wins2,
                (cur == Token::PLAYER1 ? 'X' : 'O'));
            SDL_SetWindowTitle(win, titleBuf);

            SDL_RenderPresent(ren);
            SDL_Delay(16); //frame delay to keep games at about 60fps
        }

        if (!quit) {
            //Play win sound and updates counter
            Mix_PlayChannel(-1, winSound, 0);
            if (result == GameState::PLAYER1_WINS) ++wins1;
            else if (result == GameState::PLAYER2_WINS) ++wins2;

            //Shows dialog at end of game
            const char* msg = (result == GameState::PLAYER1_WINS) ? "Player X wins!"
                : (result == GameState::PLAYER2_WINS) ? "Player O wins!" : "It's a draw!";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game Over", msg, win);

            //Ask to replay pop up window
            const SDL_MessageBoxButtonData btns[] = { {0,0,"No"},{SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,1,"Yes"} };
            SDL_MessageBoxData mb = { SDL_MESSAGEBOX_INFORMATION,win, "Play Again?", "Do you want to play again?", SDL_arraysize(btns), btns, nullptr };
            int bid; 
            SDL_ShowMessageBox(&mb, &bid);
            if (bid != 1) quit = true; //exits if choice is no
        }
    }

    //Closes stuff
    Mix_FreeChunk(dropSound);
    Mix_FreeChunk(winSound);
    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}