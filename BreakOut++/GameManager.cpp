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

		mPhysicsManager = PhysicsManager::Instance();

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::PlatformLayer, PhysicsManager::CollisonFlags::BallLayer);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::BallLayer, PhysicsManager::CollisonFlags::PlatformLayer |PhysicsManager::CollisonFlags::BrickLayer);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::BrickLayer, PhysicsManager::CollisonFlags::BallLayer); 



		mScreenManager = ScreenManager::Instance();

	}

	GameManager::~GameManager() {

		ScreenManager::Release();
		mScreenManager = NULL;

		PhysicsManager::Release();
		mPhysicsManager = NULL;

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



	}

	void GameManager::EarlyUpdate() {

		mInputManager->Update();
		mTimer->Reset();


	}

	void GameManager::Update() {
		//Game objects update here
		mScreenManager->Update();

	}

	void GameManager::LateUpdate() {

		mPhysicsManager->Update();
		mInputManager->UpdatePreviousInput();
	}

	void GameManager::Render() {

		mGraphics->ClearBackBuffer();

		//all rendering here
		mScreenManager->Render();

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







