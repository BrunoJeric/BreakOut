#pragma once
#include "InputManager.h"
#include "PlaySideBar.h"
#include "Player.h"

class Level : GameEntity {

public:
	enum LEVEL_STATES {running,finished,gameover};
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

	Player* mPlayer;

	bool mBallDropped;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float  mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;	

private:

	void StartLevel();

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();

public:
	Level(int level, PlaySideBar* sideBar,Player* player);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();

};
