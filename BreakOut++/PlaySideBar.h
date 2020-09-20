#pragma once
#include "Timer.h"
#include "ScoreBoard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity{

private:
	Timer* mTimer;
	AudioManager* mAudioManager;

	Texture* mBackground;

	Texture* mHighLabel;
	Texture* mScoreLabel;
	ScoreBoard* mHighScoreboard;

	Texture* mPlayerOneLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mPOneLabelVisible;

	ScoreBoard* mPlayerScoreboard;

	static const int MAX_LIFES = 3;
	GameEntity* mLifes;
	Texture* mLifesTextures[MAX_LIFES];
	int mTotalLifes;

	GameEntity* mLevel;
	ScoreBoard* mLevelNumber;
	Texture* mLevelLabel;

public:
	PlaySideBar();
	~PlaySideBar();

	void SetLifes(int lifes);
	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetLevel(int level);

	void Update();
	void Render();
};