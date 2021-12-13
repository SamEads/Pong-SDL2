#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <SDL.h>

class InputSystem
{
	public:
		Uint8 keyboardStateInfo[SDL_NUM_SCANCODES];
		Uint8 lastKeyboardStateInfo[SDL_NUM_SCANCODES];
		bool IsKeyDown(SDL_Scancode scanCode);
		bool WasKeyJustDown(SDL_Scancode scanCode);
		bool WasKeyJustReleased(SDL_Scancode scanCode);
};

#endif