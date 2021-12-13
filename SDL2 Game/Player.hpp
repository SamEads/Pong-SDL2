#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL.h>
#include "Game.hpp"
#include "Ball.hpp"

class Player
{
	private:
		// Variables
		SDL_Rect playerRect;
		Game* game;
	public:
		// Constructor
		Player(Game* _game);
		// Game methods
		void update();
		void draw();
		// Vars
		Ball* ball;
};

#endif