#include "Opponent.hpp"
#include <SDL.h>

int randTimer, moveSpd, decisionTimer;
int getRandomInRange(int lowerQuartile, int higherQuartile)
{
	return lowerQuartile + std::rand() % (higherQuartile - lowerQuartile + 1);
}

Opponent::Opponent(Game* _game)
{
	game = _game;
	opponentRect.x = game->gameWidth - game->screenPadding_X;
	opponentRect.w = 8;
	opponentRect.x -= opponentRect.w;
	opponentRect.h = 96;
	opponentRect.y = (game->gameHeight / 2) - (opponentRect.h / 2);
	randTimer = getRandomInRange(30, 60);
	moveSpd = getRandomInRange(2, 6);
	decisionTimer = 40;
}

void Opponent::update()
{
	int h = game->gameHeight - opponentRect.h - game->screenPadding_Y;
	if (game->npcMode)
	{
		double yBallMidPoint = ball->ballRect.y + int (ball->ballRect.h / 2);
		double yOpponentMidPoint = opponentRect.y + int (opponentRect.h / 2);
		decisionTimer--;
		if (decisionTimer <= 0)
		{
			decisionTimer = 20;
			directionToMove = (yBallMidPoint > yOpponentMidPoint) ? 1 : -1;
		}
		opponentRect.y += (directionToMove * moveSpd);
		randTimer--;
		if (randTimer <= 0)
		{
			randTimer = getRandomInRange(60, 60 * 4);
			moveSpd = getRandomInRange(3, 6);
			std::cout << moveSpd;
		}
	}
	else
	{
		moveSpd = 6;
		opponentRect.y += (game->inputSystem->IsKeyDown(SDL_SCANCODE_DOWN) - game->inputSystem->IsKeyDown(SDL_SCANCODE_UP)) * moveSpd;
	}
	if (opponentRect.y < game->screenPadding_Y)
	{
		opponentRect.y = game->screenPadding_Y;
	}
	else if (opponentRect.y > h)
	{
		opponentRect.y = h;
	}
	if (SDL_HasIntersection(&ball->ballRect, &opponentRect))
	{
		ball->curXDir = -1;
	}
	if (ball->ballRect.x < game->screenPadding_X - ball->ballRect.w)
	{
		ball->onScreen = false;
		game->rightScore++;
	}
}

void Opponent::draw()
{
	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(game->renderer, &opponentRect);
}