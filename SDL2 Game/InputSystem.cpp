#include "InputSystem.hpp"
#include <iostream>

/*
* Creation aided by faluk's simple keyboard implementation
* https://www.falukdevelop.com/2016/08/18/simple-sdl-2-keyboard-key-status/
*/

bool InputSystem::IsKeyDown(SDL_Scancode scanCode)
{
	return keyboardStateInfo[scanCode];
}

bool InputSystem::WasKeyJustDown(SDL_Scancode scanCode)
{
	return (keyboardStateInfo[scanCode] && !lastKeyboardStateInfo[scanCode]);
}

bool InputSystem::WasKeyJustReleased(SDL_Scancode scanCode)
{
	return (!keyboardStateInfo[scanCode] && lastKeyboardStateInfo[scanCode]);
}

void InputSystem::update()
{
	memcpy(lastKeyboardStateInfo, keyboardStateInfo, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(keyboardStateInfo, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}