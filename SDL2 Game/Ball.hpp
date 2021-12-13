#ifndef BALL_HPP
#define BALL_HPP

#include "Game.hpp"
#include <SDL.h>

class Ball
{
	private:
		// Variables
		Game* game;
	public:
		// Constructor
		Ball(Game* game);
		// Methods
		void update();
		void draw();
		int getX();
		int getY();
		// Variables
		int curXDir = 1;
		int curYDir = 1;
		bool onScreen = true;
		SDL_Rect ballRect;
};

#endif