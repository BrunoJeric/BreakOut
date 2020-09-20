#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.1f, Graphics::Instance()->SCREEN_HEIGHT * 0.03f));

	mStartLabel = new Texture("START", "emulogic.ttf", 32, { 0,0,150 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.6f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;
}

PlayScreen::~PlayScreen() {
	mTimer = NULL;
	mInputManager = NULL;
	mAudioManager = NULL;

	delete mSideBar;
	mSideBar = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;
}

void PlayScreen::StartNewGame() {
	mSideBar->SetHighScore(30000);
	mSideBar->SetLifes(3);
	mGameStarted = false;
	mAudioManager->PlayMusic("gameStart.wav", 0);
	mCurrentLevel = 0;
}
void PlayScreen::StartNextLevel() {

	mCurrentLevel++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	

	delete mLevel;
	mLevel = new Level(mCurrentLevel, mSideBar);
	//maybe remove sound 
	mAudioManager->PlaySFX("levelReady.wav");

}
void PlayScreen::Update(){

	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}


	}
	else {
		if (!Mix_PlayingMusic()) {
			mGameStarted = true;
		}
	}

	if (mGameStarted && mLevelStarted)
	{
		mSideBar->Update();
		mLevel->Update();
	}
	
}
void PlayScreen::Render() {
	mSideBar->Render();
	if (!mGameStarted) {
		mStartLabel->Render();
	}
	if (mGameStarted && mLevelStarted) {
		mLevel->Render();
	}
}