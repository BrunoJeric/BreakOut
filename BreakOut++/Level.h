#pragma once
#include "InputManager.h"
#include "PlaySideBar.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>

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
	Ball* mBall;

	bool mBallDropped;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float  mGameOverLabelOnScreen;

	//int mBrickTypes;
	int mRowCount;
	int	mColumnCount;
	int	mRowSpacing;
	int	mColumnSpacing;
	std::string	mBackgroundTexture;

	std::vector<Brick*> mBrickTypes;
	std::vector<Brick*> mBricks;
	
	GameEntity* mBrickContainer;
	LEVEL_STATES mCurrentState;	




private:

	void StartLevel();

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	void GetBricksOnScreen();
	void ParseXml();

public:
	Level(int level, PlaySideBar* sideBar,Player* player, Ball* ball);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();

};
