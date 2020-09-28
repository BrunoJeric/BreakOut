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

	mLevel = nullptr;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;
	mBall = nullptr;
}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;

	delete mSideBar;
	mSideBar = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;

	delete mBall;
	mBall = nullptr;
}

void PlayScreen::StartNewGame() {

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(521.0f,Graphics::Instance()->SCREEN_HEIGHT*0.95f));
	mPlayer->Active(false);

	delete mBall;
	mBall = new Ball();
	mBall->Scale(Vector2(0.4f, 0.4f));
	mBall->Parent(mPlayer);
	mBall->Docked(true);
	mBall->Pos(Vector2(0.0f,-25.0f));
	mBall->Active(false);

	mSideBar->SetHighScore(30000);
	mSideBar->SetLifes(mPlayer->Lives());
	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetLevel(0);

	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;

	mCurrentLevel = 0;

	mAudioManager->PlayMusic("gameStart.wav", 0);
}
void PlayScreen::StartNextLevel() {

	mCurrentLevel++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	

	delete mLevel;
	
	delete mBall;
	mBall = new Ball();
	mBall->Scale(Vector2(0.4f, 0.4f));
	mBall->Parent(mPlayer);
	mBall->Docked(true);
	mBall->Pos(Vector2(0.0f, -25.0f));
	mBall->Active(false);

	mLevel = new Level(mCurrentLevel, mSideBar,mPlayer,mBall);
	mAudioManager->PlaySFX("levelReady.wav");

}

bool PlayScreen::GameOver() {
	if (!mLevelStarted)
		return false;

	return (mLevel->State()==Level::gameover);
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

	if (mGameStarted)
	{
		if(mCurrentLevel>0)
			mSideBar->Update();

		if (mLevelStarted) {
			
			mLevel->Update();
			
			if (mLevel->State() == Level::finished) {
				mLevelStarted = false;
			}
		}
		mPlayer->Update();
		mSideBar->SetPlayerScore(mPlayer->Score());
		mBall->Update();

	}
	
}
void PlayScreen::Render() {
	mSideBar->Render();
	if (!mGameStarted) {
		mStartLabel->Render();
	}
	if (mGameStarted) {
		if(mLevelStarted)
			mLevel->Render();
		
		mPlayer->Render();
		mBall->Render();
	}
}