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
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreboard->Score(score);
}
void PlaySideBar::SetPlayerScore(int score) {
	mPlayerScoreboard->Score(score);
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
}
