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

	//Texture* mLevelLabel;

public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);

	void Update();
	void Render();
};