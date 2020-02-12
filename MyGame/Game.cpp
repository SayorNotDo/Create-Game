#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow("Pong",
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
	mPaddlePos.y = 700.0f/2.0f;
    	mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 700.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	ot_PaddlePos.x = 1024 - mPaddlePos.x - thickness;
	ot_PaddlePos.y = 700.0f/2.0f;
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
   // wall.x = 1024 - thickness;
   // wall.y = 0;
   // wall.w = thickness;
   // wall.h = 700;
   // SDL_RenderFillRect(mRenderer, &wall);
    // Draw the paddle
    SDL_Rect paddle{
    	static_cast<int>(mPaddlePos.x),
    	static_cast<int>(mPaddlePos.y - paddleH/2),
    	thickness,
    	static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    // Draw the another paddle
    SDL_Rect ot_paddle{
    	static_cast<int>(ot_PaddlePos.x),
	static_cast<int>(ot_PaddlePos.y - paddleH/2),
	thickness,
	static_cast<int>(paddleH)
    };   
    SDL_RenderFillRect(mRenderer, &ot_paddle);
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
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	// Delta time is the difference in ticks from last time
	// (Converted to seconds;
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	if (deltaTime > 0.05f)
	{
	deltaTime = 0.05f;
	}
	// TODO: Update objects in game world as function of delta time;
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH/2.0f + thickness)) {
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos.y > (700.0f - paddleH/2.0f - thickness)) {
			mPaddlePos.y = 700.0f - paddleH/2.0f - thickness;
		}	
	}
	if (ot_PaddleDir != 0) {
		ot_PaddlePos.y += ot_PaddleDir * 300.0f * deltaTime;
		if (ot_PaddlePos.y < (paddleH/2.0f + thickness)) {
			ot_PaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (ot_PaddlePos.y > (700.0f - paddleH/2.0f - thickness)) {
			ot_PaddlePos.y = 700.0f - paddleH/2.0f - thickness;
		}
	}
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
		mBallVel.y *= -1;
	}
	if (mBallPos.y >= 700-thickness && mBallVel.y > 0.0f) {
		mBallVel.y *= -1;
	}
	if (mBallPos.x >=1024-thickness && mBallVel.x > 0.0f) {
		mBallVel.x *= -1.0f;
	}
	// difference of the value
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-different is small enough
		 diff <= paddleH/2.0f &&
		 mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		 mBallVel.x < 0.0f
	   ) {
		mBallVel.x *= -1.0f;
	}
	// difference of the value
	float ot_diff = ot_PaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	ot_diff = (ot_diff > 0.0f) ? ot_diff : ot_diff;
	if (
		// Our y-different is small enough
		ot_diff <= paddleH/2.0f &&
		mBallPos.x <= 1020.0f && mBallPos.x >=1000.0f &&
		// The ball is moving to the right
		mBallVel.x > 0.0f		
	) {
		mBallVel.x *= -1.0f;
	}
}


void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
