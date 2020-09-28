#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr)
		sInstance = new ScreenManager();
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {

	mInputManager = InputManager::Instance();

	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {
	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}

void ScreenManager::Update() {
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Update();
		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
			if (mStartScreen->SelectedScreen() == 0) {

				mCurrentScreen = play;
				mStartScreen->ResetAnimation();
				mPlayScreen->StartNewGame();

			}
			else {
				SDL_Quit();
				exit(0);
			}

		}
		break;
	case play:
		mPlayScreen->Update();
		
		if (mPlayScreen->GameOver()) {
			mCurrentScreen = start;
		}

		break;
	}
}

void ScreenManager::Render() {
	switch (mCurrentScreen)
	{
	case start:
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	}
}