#pragma once
#include <SDL2/SDL.h>

struct Vector2 {
    float x;
    float y;
};
// Game class
class Game
{
public:
	Game() {};
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput() {
	    SDL_Event event;
        //While there is still events in the queue
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                //Handle different event types here
                case SDL_QUIT:
                    mIsRunning = false;
                    break;
            }
        }
        //Get state of keyboard
        const Uint8* state = SDL_GetKeyboardState(NULL);
        //If escape is pressed, also end loop
        if (state[SDL_SCANCODE_ESCAPE]) {
            mIsRunning = false;
        }
	};
	void UpdateGame();
	void GenerateOutput();
	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;
	// Game should continue to run
	bool mIsRunning;
	// Direction of paddle
	int mPaddleDir;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
	Uint32 mTicksCount;
};

