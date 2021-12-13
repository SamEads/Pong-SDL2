#include "Ball.hpp"
#include "Game.hpp"
#include "Opponent.hpp"
#include "Player.hpp"

Ball* ball;
Opponent* opponent;
Player* player;

Game::Game()
{
	int flags = 0;
	// flags = flags | SDL_WINDOW_RESIZABLE;

	if (fullscreen)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWidth, gameHeight, flags);
		if (window)
		{
			SDL_SetWindowMinimumSize(window, gameWidth, gameHeight);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}
	}

	TTF_Init();
	mainFont = TTF_OpenFont("font.ttf", 16);

	inputSystem = new InputSystem();
	memset(inputSystem->lastKeyboardStateInfo, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(inputSystem->keyboardStateInfo, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);

	player = new Player(this);
	opponent = new Opponent(this);

	mainMenu();

	clean();
}

int menuChoice;
bool inMainMenu;
void Game::mainMenu()
{
	menuChoice = 0;
	inMainMenu = true;
	leftScore = 0;
	rightScore = 0;
	while (isRunning && inMainMenu)
	{
		memcpy(inputSystem->lastKeyboardStateInfo, inputSystem->keyboardStateInfo, sizeof(Uint8) * SDL_NUM_SCANCODES);
		memcpy(inputSystem->keyboardStateInfo, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
		handleEvents();
		std::cout << "---" << std::endl;
		updateMainMenu();
		renderMainMenu();
		SDL_Delay(1000 / 60);
	}
	if (isRunning)
		playGame();
}

void Game::updateMainMenu()
{
	if (inputSystem->WasKeyJustDown(SDL_SCANCODE_DOWN))
	{
		menuChoice++;
	}
	else if (inputSystem->WasKeyJustDown(SDL_SCANCODE_UP))
	{
		menuChoice--;
	}
	if (menuChoice < 0)
	{
		menuChoice = 1;
	}
	else if (menuChoice > 1)
	{
		menuChoice = 0;
	}
	if (inputSystem->WasKeyJustDown(SDL_SCANCODE_Z) || inputSystem->WasKeyJustDown(SDL_SCANCODE_X) || inputSystem->WasKeyJustDown(SDL_SCANCODE_SPACE) || inputSystem->WasKeyJustDown(SDL_SCANCODE_RETURN))
	{
		npcMode = (menuChoice == 0) ? true : false;
		inMainMenu = false;
	}
}

void Game::renderMainMenu()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	drawText(gameWidth / 2, gameHeight / 2 - gameHeight / 4, "PONG", align::center);
	std::string p1pointer = (menuChoice == 0) ? "> " : "";
	std::string p2pointer = (menuChoice == 1) ? "> " : "";
	drawText(gameWidth / 2, (gameHeight / 2 - gameHeight / 4) + 96, (p1pointer + "1 PLAYER GAME").c_str(), align::center);
	drawText(gameWidth / 2, (gameHeight / 2 - gameHeight / 4) + 128, (p2pointer + "2 PLAYER GAME").c_str(), align::center);
	drawText(gameWidth / 2, (gameHeight / 2 - gameHeight / 4) + 224, "FIRST TO 10 POINTS WINS", align::center);

	SDL_RenderPresent(renderer);
}

bool alive;
void Game::playGame()
{
	// New ball, reset life
	alive = true;
	ball = new Ball(this);

	// Update ptr
	opponent->ball = ball;
	player->ball = ball;

	// Run update @ 60 FPS
	while (alive && isRunning)
	{
		memcpy(inputSystem->lastKeyboardStateInfo, inputSystem->keyboardStateInfo, sizeof(Uint8) * SDL_NUM_SCANCODES);
		memcpy(inputSystem->keyboardStateInfo, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
		handleEvents();
		updateGame();
		renderGame();
		SDL_Delay(1000 / 60);
	}

	// Delete ball at loss
	delete ball;

	// Start game over if game was not cancelled out
	if (isRunning)
	{
		if (leftScore >= 10 || rightScore >= 10)
		{
			mainMenu();
		}
		else
			playGame();
	}

	// If game was cancelled out delete everything else
	delete player;
	delete opponent;
}

void Game::updateGame()
{
	opponent->update();
	player->update();
	ball->update();

	if (!ball->onScreen)
	{
		alive = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
		default:
			break;
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

// Render things
SDL_Rect playAreaRectangle;
void Game::renderGame()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	playAreaRectangle.x = screenPadding_X - 16;
	playAreaRectangle.w = gameWidth - (screenPadding_X * 2) + 32;
	playAreaRectangle.y = screenPadding_Y;
	playAreaRectangle.h = gameHeight - (screenPadding_Y * 2);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
	SDL_RenderFillRect(renderer, &playAreaRectangle);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &playAreaRectangle);

	player->draw();
	opponent->draw();
	ball->draw();

	drawText(gameWidth / 2, 16, "PONG", align::center);
	drawText(16, 32, ("P1 Score: " + std::to_string(leftScore)).c_str());
	drawText(gameWidth - 16, 32, ("P2 Score: " + std::to_string(rightScore)).c_str(), align::right);

	SDL_RenderPresent(renderer);
}

void Game::drawText(int x, int y, const char* msg, align alignStyle)
{
	SDL_Surface* surf;
	SDL_Texture* tex;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(mainFont, msg, { 255, 255, 255 });
	tex = SDL_CreateTextureFromSurface(renderer, surf);
	int extraWidth = 0;
	if (alignStyle == right)
	{
		extraWidth -= surf->w;
	}
	else if (alignStyle == center)
	{
		extraWidth -= surf->w / 2;
	}
	rect.x = x + extraWidth;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	SDL_FreeSurface(surf);
	SDL_RenderCopy(renderer, tex, NULL, &rect);
	SDL_DestroyTexture(tex);
}

// Destroy stuff
void Game::clean()
{
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}