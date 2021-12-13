#ifndef OPPONENT_HPP
#define OPPONENT_HPP

#include "Game.hpp"
#include <SDL.h>
#include "Ball.hpp"

class Opponent
{
	private:
		// Variables
		SDL_Rect opponentRect;
		Game* game;
		int directionToMove = 1;
	public:
		// Constructor
		Opponent(Game* game);
		// Methods
		void update();
		void draw();
		// Variables
		Ball* ball;
};

#endif