#include "Level.h"

Level::Level(int level, PlaySideBar* sideBar) {
	
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
	mReadyLabelOffScreen = mReadyLabelOnScreen + 2.0f;
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
}

void Level::StartLevel() {
	mLevelStarted = true;
}

void Level::Update() {
	if (!mLevelStarted) {
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mLevelLabelOffScreen) {
			if (mLevel > 1) {
				StartLevel();
			}
			else {
				if (mLabelTimer >= mReadyLabelOffScreen) {
					StartLevel();
				}
			}
		}
	}
}

void Level::Render() {
	if (!mLevelStarted) {
		if (mLabelTimer > mLevelLabelOnScreen && mLabelTimer < mLevelLabelOffScreen) {
			mLevelLabel->Render();
			mLevelNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}
}
