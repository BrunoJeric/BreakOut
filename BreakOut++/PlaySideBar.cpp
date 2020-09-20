#include "PlaySideBar.h"

PlaySideBar::PlaySideBar() {

	mTimer = Timer::Instance();
	mAudioManager = AudioManager::Instance();
	
	mBackground = new Texture("black.png");

	mBackground->Parent(this);
	mBackground->Pos(Vector2(-55.0f,278.0f));
	mBackground->Scale(Vector2(3.0f, 10.0f));

	mHighLabel = new Texture("HIGH", "emulogic.ttf", 20, { 0,255,0 });
	mHighLabel->Parent(this);
	mHighLabel->Pos(Vector2(-30.0f, 0.0f));

	mScoreLabel = new Texture("SCORE", "emulogic.ttf", 20, { 0,255,0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Pos(Vector2(20.0f, 24.0f));

	mHighScoreboard = new  ScoreBoard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Pos(Vector2(70.0f, 48.0f));

	mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 20, { 0,255,0 });
	mPlayerOneLabel->Parent(this);
	mPlayerOneLabel->Pos(Vector2(-45.0f, 110.0f));

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mPOneLabelVisible = true;

	mPlayerScoreboard = new ScoreBoard();
	mPlayerScoreboard->Parent(this);
	mPlayerScoreboard->Pos(Vector2(70.0f, 134.0));

	mLifes = new GameEntity();
	mLifes->Parent(this);
	mLifes->Pos(Vector2(-55.0f, 200.0f));

	for (int i = 0; i < MAX_LIFES; i++) {
		mLifesTextures[i] = new Texture("heart.png");
		mLifesTextures[i]->Parent(mLifes);
		mLifesTextures[i]->Scale(Vector2(0.33f, 0.33f));
		mLifesTextures[i]->Pos(Vector2(38.0f * i, 0.0f));
	}

	mLevel = new GameEntity();
	mLevel->Parent(this);
	mLevel->Pos(Vector2(-9.0f, 600.0f));
	mLevelLabel = new Texture("LEVEL", "emulogic.ttf", 24, { 0,255,0 });
	mLevelNumber = new ScoreBoard();

	mLevelLabel->Parent(mLevel);
	mLevelNumber->Parent(mLevel);
	mLevelLabel->Pos(Vector2(-20.0f,0.0f));
	mLevelNumber->Pos(Vector2(90.0f,0.0f));
	mLevel->Scale(Vector2(0.8f, 0.8f));


}

PlaySideBar::~PlaySideBar() {
	mTimer = NULL;
	mAudioManager = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mHighLabel;
	mHighLabel = NULL;

	delete mScoreLabel;
	mScoreLabel = NULL;

	delete mHighScoreboard;
	mHighScoreboard = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mPlayerScoreboard;
	mPlayerScoreboard = NULL;

	delete mLifes;
	mLifes = NULL;

	for (int i = 0; i < MAX_LIFES; i++) {
		delete mLifesTextures[i];
		mLifesTextures[i] = NULL;
	}

	delete mLevel;
	mLevel = NULL;

	delete mLevelLabel;
	mLevelLabel = NULL;

	delete mLevelNumber;
	mLevelNumber = NULL;
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreboard->Score(score);
}
void PlaySideBar::SetPlayerScore(int score) {
	mPlayerScoreboard->Score(score);
}
void PlaySideBar::SetLifes(int lifes) {
	mTotalLifes = lifes;
}
void PlaySideBar::SetLevel(int level) {
	mLevelNumber->Score(level);
}
void PlaySideBar::Update() {
	mBlinkTimer += mTimer->DeltaTime();
	if (mBlinkTimer >= mBlinkInterval) {
		mPOneLabelVisible = !mPOneLabelVisible;
		mBlinkTimer = 0.0f;
	}
}
void PlaySideBar::Render() {

	mBackground->Render();
	
	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreboard->Render();
	
	if(mPOneLabelVisible)
		mPlayerOneLabel->Render();
	mPlayerScoreboard->Render();

	for (int i = 0; i < MAX_LIFES && i<mTotalLifes; i++) {
		mLifesTextures[i]->Render();
	}

	mLevelLabel->Render();
	mLevelNumber->Render();
}
