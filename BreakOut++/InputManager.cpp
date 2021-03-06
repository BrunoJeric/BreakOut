#include "InputManager.h"
namespace EngineSDL {
	InputManager* InputManager::sInstance = nullptr;

	InputManager* InputManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new InputManager();
		}
		return sInstance;
	}

	void InputManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	InputManager::InputManager() {
		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
		mPrevKeyboardState = new Uint8[mKeyLength];
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	}

	InputManager::~InputManager() {
		delete[] mPrevKeyboardState;
		mPrevKeyboardState = nullptr;
	}

	bool InputManager::KeyDown(SDL_Scancode scanCode) {
		return mKeyboardState[scanCode];
	}

	bool InputManager::KeyPressed(SDL_Scancode scanCode) {
		return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
	}
	bool InputManager::KeyReleased(SDL_Scancode scanCode) {
		return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
	}

	Vector2 InputManager::MousePosition() {
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}

	bool InputManager::MouseButtonDown(MOUSE_BUTTON button) {

		Uint32 mask = 0;
		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;
		case right:
			mask = SDL_BUTTON_RMASK;
			break;
		case middle:
			mask = SDL_BUTTON_MMASK;
			break;
		}
		return (mMouseState & mask);
	}

	bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) {

		Uint32 mask = 0;
		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;
		case right:
			mask = SDL_BUTTON_RMASK;
			break;
		case middle:
			mask = SDL_BUTTON_MMASK;
			break;
		}
		return !(mPrevMouseState & mask) && (mMouseState & mask);
	}
	bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) {

		Uint32 mask = 0;
		switch (button)
		{
		case left:
			mask = SDL_BUTTON_LMASK;
			break;
		case right:
			mask = SDL_BUTTON_RMASK;
			break;
		case middle:
			mask = SDL_BUTTON_MMASK;
			break;
		}
		return (mPrevMouseState & mask) && !(mMouseState & mask);
	}

	void InputManager::Update() {
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
	}

	void InputManager::UpdatePreviousInput() {
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
		mPrevMouseState = mMouseState;
	}
}