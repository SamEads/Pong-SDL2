#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <SDL.h>
#include <string>
#include "InputSystem.hpp"

class Game
{
	public:
		Game();
		InputSystem* inputSystem;
		SDL_Renderer* renderer;
		const char* title = "Game";
	private:
		SDL_Window* window;
		bool isRunning = false;
		bool fullscreen = false;
		void handleEvents();
		void update();
		void render();
		void clean();
};

#endif