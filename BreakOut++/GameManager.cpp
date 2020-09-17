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

	mTimer = Timer::Instance();
	

	mTex = new Texture("platform.png");
	mTex->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5, Graphics::SCREEN_HEIGHT* 0.9));

}

GameManager::~GameManager() {
	Graphics::Release();
	mGraphics = NULL;

	AssetManager::Release();
	mAssetManager = NULL;

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

			mGraphics->ClearBackBuffer();

			mTex->Render();

			mGraphics->Render();
			
			mTimer->Reset();
		
		}

	}
}








