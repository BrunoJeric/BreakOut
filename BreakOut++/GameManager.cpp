#include "GameManager.h"

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
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();
	

	mTex = new Texture("Hello World!", "ARCADE.TTF", 64, {0,250,0});
	mTex->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT* 0.5));

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

	delete mTex;
	mTex = NULL;


}

void GameManager::Run() {
	while (!mQuit) {
 		mTimer->Update();
		while (SDL_PollEvent(&mEvents)!=0){
			if (mEvents.type == SDL_QUIT) {
				mQuit = true;
			}
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE)) {

			mInputManager->Update();

			/*if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
				mTex->Translate(Vector2(200.0f, 0.0f) * mTimer->DeltaTime());
			}*/
			if (mInputManager->KeyDown(SDL_SCANCODE_SPACE)) {
				mAudioManager->PlaySFX("KeyPress.wav");
			}

			mGraphics->ClearBackBuffer();

			mTex->Render();

			mGraphics->Render();
			
			mTimer->Reset();
		
		}

	}
}








