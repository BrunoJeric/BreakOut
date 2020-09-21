#include "Level.h"

Level::Level(int level, PlaySideBar* sideBar,Player* player) {
	
	mTimer = Timer::Instance();
	
	mSideBar = sideBar;
	mSideBar->SetLevel(level);

	mLevel = level;
	mLevelStarted = false;

	mLabelTimer = 0.0f;

	mLevelLabel = new Texture("Level", "emulogic.ttf", 24, { 75,75,200 });
	mLevelLabel->Parent(this);
	mLevelLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.6f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelNumber = new ScoreBoard({ 75,75,200 });
	mLevelNumber->Score(mLevel);
	mLevelNumber->Parent(this);
	mLevelNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.7f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevelLabelOnScreen = 0.0f;
	mLevelLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "emulogic.ttf", 24, { 75,75,200 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.62f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mLevelLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;

	mPlayer = player;
	mBallDropped = false;
	mPlayerRespawnDelay=3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;

	mGameOverLabel = new Texture("GAME OVER", "emulogic.ttf", 32, { 150,0,0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.62f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 4.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;
}

Level::~Level() {
	mTimer = NULL;
	mSideBar = NULL;

	delete mLevelLabel;
	mLevelLabel = NULL;
	delete mLevelNumber;
	mLevelNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;
}

void Level::StartLevel() {
	mLevelStarted = true;
}

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mLevelLabelOffScreen) {
		if (mLevel > 1) {
			StartLevel();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {

				StartLevel();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions() {
	if (!mBallDropped) {
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_X)) {
			mPlayer->DroppedBall();
			mSideBar->SetLifes(mPlayer->Lives());

			mBallDropped = true;
			mPlayerRespawnTimer = 0.0f;
			mPlayer->Active(false);
		}
	}
}

void Level::HandlePlayerDeath() {

	if (!mPlayer->IsAnimating()) {

		if (mPlayer->Lives() > 0) {
			
			if (mPlayerRespawnTimer == 0.0f) {
				mPlayer->Visible(false);

			}
			mPlayerRespawnTimer += mTimer->DeltaTime();

			if (mPlayerRespawnTimer >= mPlayerRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mBallDropped = false;


			}
		}
		else {
			if (mGameOver == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = gameover;
			}
		}

	}
}

Level::LEVEL_STATES Level::State() {
	return mCurrentState;
}

void Level::Update() {
	if (!mLevelStarted) {
		HandleStartLabels();
	}
	else {
		HandleCollisions();

		if (mBallDropped) {

			HandlePlayerDeath();
		} else{
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N)) {
				mCurrentState = finished;
			}
		}
		
	}
}


void Level::Render() {
	if (!mLevelStarted) {
		if (mLabelTimer > mLevelLabelOnScreen && mLabelTimer < mLevelLabelOffScreen) {
			mLevelLabel->Render();
			mLevelNumber->Render();
		} else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {

			mReadyLabel->Render();
		
		}
	}
	else
	{
		if (mBallDropped) {
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}
