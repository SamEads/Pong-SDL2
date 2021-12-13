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