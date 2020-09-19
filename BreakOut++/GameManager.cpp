#include "GameManager.h"
namespace EngineSDL {
	GameManager* GameManager::sInstance = NULL;

	GameManager* GameManager::Instance() {
		if (sInstance == NULL) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	GameManager::GameManager() {
		mQuit = false;

		//Initialize SDL
		mGraphics = Graphics::Instance();

		// Quits the game if SDL fails to initialize
		if (!Graphics::Initialized())
			mQuit = true;

		//Initialize AssetManager
		mAssetManager = AssetManager::Instance();

		//Initialize InputManager
		mInputManager = InputManager::Instance();

		//Initialize AudioManager
		mAudioManager = AudioManager::Instance();

		//Initialize Timer
		mTimer = Timer::Instance();

		mStartScreen = new StartScreen();
	}

	GameManager::~GameManager() {

		AudioManager::Release();
		mAudioManager = NULL;

		AssetManager::Release();
		mAssetManager = NULL;

		Graphics::Release();
		mGraphics = NULL;

		InputManager::Release();
		mInputManager = NULL;

		Timer::Release();
		mTimer = NULL;

		delete mStartScreen;
		mStartScreen = NULL;


	}

	void GameManager::EarlyUpdate() {

		mInputManager->Update();
		mTimer->Reset();


	}

	void GameManager::Update() {
		//Game objects update here
		mStartScreen->Update();

	}

	void GameManager::LateUpdate() {

		mInputManager->UpdatePreviousInput();
	}

	void GameManager::Render() {

		mGraphics->ClearBackBuffer();

		//all rendering here
		mStartScreen->Render();

		mGraphics->Render();
	}

	void GameManager::Run() {
		while (!mQuit) {
			mTimer->Update();
			while (SDL_PollEvent(&mEvents) != 0) {
				if (mEvents.type == SDL_QUIT) {
					mQuit = true;
				}
			}

			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

				EarlyUpdate();
				Update();
				LateUpdate();

				Render();
			}

		}
	}
}







