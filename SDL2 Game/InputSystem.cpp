#include "InputSystem.hpp"

const Uint8 InputSystem::IsKeyDown(SDL_Scancode scanCode)
{
	const Uint8* keyboardStateInfo = SDL_GetKeyboardState(NULL);
	return keyboardStateInfo[scanCode];
}