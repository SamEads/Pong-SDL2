#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "InputSystem.hpp"

enum align
{
	left,
	right,
	center
};

class Game
{
	public:
		// Constructor
		Game();
		// Variables
		InputSystem* inputSystem;
		SDL_Renderer* renderer;
		const char* title = "Pong";
		int gameWidth = 640;
		int gameHeight = 480;
		int screenPadding_Y = 64;
		int screenPadding_X = 32;
		int leftScore = 0;
		int rightScore = 0;
		TTF_Font* mainFont;
		bool npcMode = true;
	private:
		// Methods
		void handleEvents();

		void playGame();
		void updateGame();
		void renderGame();

		void mainMenu();
		void updateMainMenu();
		void renderMainMenu();

		void displayWinner();

		void clean();
		void drawText(int x, int y, const char* msg, align alignStyle = left);
		// Variables
		SDL_Window* window;
		bool isRunning = false;
		bool fullscreen = false;
};

#endif