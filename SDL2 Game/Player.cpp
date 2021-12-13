#include <iostream>
#include "Player.hpp"
#include "Game.hpp"

Player::Player(Game* _game)
{
	game = _game;
	playerRect.w = 8;
	playerRect.h = 96;
	playerRect.x = game->screenPadding_X;
	playerRect.y = (game->gameHeight / 2) - (playerRect.h / 2);
}

void Player::update()
{
	int moveSpd = 6;
	int h = game->gameHeight - playerRect.h - game->screenPadding_Y;
	SDL_Scancode down = SDL_SCANCODE_DOWN;
	SDL_Scancode up = SDL_SCANCODE_UP;
	if (!game->npcMode)
	{
		down = SDL_SCANCODE_S;
		up = SDL_SCANCODE_W;
	}
	playerRect.y += (game->inputSystem->IsKeyDown(down) - game->inputSystem->IsKeyDown(up)) * moveSpd;
	if (playerRect.y < game->screenPadding_Y)
	{
		playerRect.y = game->screenPadding_Y;
	}
	else if (playerRect.y > h)
	{
		playerRect.y = h;
	}
	if (SDL_HasIntersection(&ball->ballRect, &playerRect))
	{
		ball->curXDir = 1;
	}
	if (ball->ballRect.x > game->gameWidth - 32)
	{
		ball->onScreen = false;
		game->leftScore++;
	}
}

void Player::draw()
{
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(game->renderer, &playerRect);
}