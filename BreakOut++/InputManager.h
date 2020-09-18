#pragma once
#include "SDL.h"
#include "MathHelper.h"	
#include <string.h>
namespace EngineSDL {
	class InputManager {
	public:
		enum MOUSE_BUTTON { left = 0, right, middle };

	private:
		static InputManager* sInstance;

		Uint8* mPrevKeyboardState;
		const Uint8* mKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

	public:
		static InputManager* Instance();
		static void Release();


		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);
		bool KeyDown(SDL_Scancode scanCode);

		bool MouseButtonDown(MOUSE_BUTTON button);
		bool MouseButtonPressed(MOUSE_BUTTON button);
		bool MouseButtonReleased(MOUSE_BUTTON button);

		Vector2	MousePosition();

		void Update();
		void UpdatePreviousInput();
	private:
		InputManager();
		~InputManager();

	};
}