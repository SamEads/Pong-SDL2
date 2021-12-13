#ifndef Player_hpp
#define Player_hpp

#include <SDL.h>
#include "Game.hpp"

class Player
{
	private:
		SDL_Rect testRect;
	public:
		// Constructor
		Player(Game* _game);
		// Game methods
		void update();
		void draw();
		// Vars
		Game* game;
		float x = 0;
		float y = 0;
};

#endif