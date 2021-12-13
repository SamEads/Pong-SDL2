#include <iostream>
#include "Player.hpp"
#include "Game.hpp"

Player::Player(Game* _game)
{
	testRect.x = 0;
	testRect.y = 0;
	testRect.w = 8;
	testRect.h = 96;
	game = _game;
}

void Player::update()
{
	int moveSpd = 6;
	int h = 448 - 96 - 16;
	// x += (game->inputSystem->IsKeyDown(SDL_SCANCODE_RIGHT) - game->inputSystem->IsKeyDown(SDL_SCANCODE_LEFT)) * moveSpd;
	y += (game->inputSystem->IsKeyDown(SDL_SCANCODE_DOWN) - game->inputSystem->IsKeyDown(SDL_SCANCODE_UP)) * moveSpd;
	if (y < 16)
	{
		y = 16;
	}
	else if (y > h)
	{
		y = h;
	}
}

void Player::draw()
{
	testRect.x = x;
	testRect.y = y;
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(game->renderer, &testRect);
}