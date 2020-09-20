#pragma once
#include "InputManager.h"
#include "PlaySideBar.h"

class Level : GameEntity {

private:
	Timer* mTimer;

	PlaySideBar* mSideBar;

	int mLevel;
	bool mLevelStarted;

	float mLabelTimer;

	Texture* mLevelLabel;
	ScoreBoard* mLevelNumber;
	float mLevelLabelOnScreen;
	float mLevelLabelOffScreen;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;


private:
	void StartLevel();
public:
	Level(int level, PlaySideBar* sideBar);
	~Level();

	void Update();
	void Render();

};
