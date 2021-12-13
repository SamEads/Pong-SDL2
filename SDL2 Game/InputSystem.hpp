#ifndef InputSystem_hpp
#define InputSystem_hpp

#include <SDL.h>

class InputSystem
{
	public:
		const Uint8 IsKeyDown(SDL_Scancode scanCode);
};

#endif