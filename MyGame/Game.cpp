#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow("Game Programming in C++",
                               100,
                               100,
                               1024,
                               700,
                               0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(
                        mWindow,    // Window to create renderer for
                        -1, // Usually -1
                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
    mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 768.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::GenerateOutput() {
    // Draw the background
	SDL_SetRenderDrawColor(
                        mRenderer,
                        0,  // R
                        0,  // G
                        255,    // B
                        255 //A
                        );
    // Clear the back ground color
    SDL_RenderClear(mRenderer);
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    // Draw the top wall
    SDL_Rect wall{
    0,
    0,
    1024,
    thickness
    };
    SDL_RenderFillRect(mRenderer, &wall);
    // Draw the bottom wall
    wall.y = 700 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    // Draw the right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 700;
    SDL_RenderFillRect(mRenderer, &wall);
    // Draw the paddle
    SDL_Rect paddle{
    static_cast<int>(mPaddlePos.x),
    static_cast<int>(mPaddlePos.y - paddleH/2),
    thickness,
    static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    SDL_Rect ball{
        static_cast<int>(mBallPos.x - thickness/2),
        static_cast<int>(mBallPos.y - thickness/2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
    SDL_RenderPresent(mRenderer);
}

void Game::UpdateGame() {
	// Delta time is the difference in ticks from last time
	// (Converted to seconds;
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	// TODO: Update objects in game world as function of delta time;
	// ...
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
