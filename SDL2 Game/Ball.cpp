#include "Ball.hpp"

Ball::Ball(Game* _game)
{
	game = _game;
	ballRect.x = game->gameWidth / 2;
	ballRect.y = game->gameHeight / 2;
	ballRect.w = 8;
	ballRect.h = 8;
}

void Ball::update()
{
	int moveSpd = 3;
	ballRect.x += curXDir * moveSpd;
	ballRect.y += curYDir * moveSpd;
	if (ballRect.y + ballRect.h > game->gameHeight - game->screenPadding_Y)
	{
		curYDir = -1;
		ballRect.y = game->gameHeight - game->screenPadding_Y - ballRect.h;
	}
	else if (ballRect.y < game->screenPadding_Y)
	{
		ballRect.y = game->screenPadding_Y;
		curYDir = 1;
	}
}

int Ball::getX()
{
	return ballRect.x;
}

int Ball::getY()
{
	return ballRect.y;
}

void Ball::draw()
{
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(game->renderer, &ballRect);
}