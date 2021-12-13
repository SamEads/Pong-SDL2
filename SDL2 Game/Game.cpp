#include "Game.hpp"
#include "Player.hpp"

Player *player;

Game::Game()
{
	int flags = 0;
	flags = flags | SDL_WINDOW_RESIZABLE;

	if (fullscreen)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 512, 448, flags);
		if (window)
		{
			SDL_SetWindowMinimumSize(window, 256, 224);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}
	}

	inputSystem = new InputSystem();

	player = new Player(this);
	player->x = 16;
	player->y = 16;


	// Run update
	while (isRunning)
	{
		handleEvents();
		update();
		render();
		SDL_Delay(1000 / 60);
	}

	clean();
}

void Game::update()
{
	player->update();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

// Render things
void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	player->draw();

	SDL_RenderPresent(renderer);
}

// Destroy stuff
void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}