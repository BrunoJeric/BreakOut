#pragma once
#include "InputManager.h"
#include "PlaySideBar.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>
#include <sys/stat.h>

class Level : GameEntity {

public:
	enum LEVEL_STATES {running,finished,gameover};
private:
	Timer* mTimer;

	PlaySideBar* mSideBar;

	int mLevel;
	bool mLevelStarted;

	float mLabelTimer;

	Texture* mLevelTexture;

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

	int mRowCount;
	int	mColumnCount;
	int	mRowSpacing;
	int	mColumnSpacing;
	std::string	mBackgroundTexture;

	std::vector<Brick*> mBrickTypes;
	std::vector<Brick*> mBricks;
	
	GameEntity* mBrickContainer;
	LEVEL_STATES mCurrentState;

	Texture* mDemoOver;
	bool mDemo = true;




private:

	void StartLevel();

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	void GetBricksOnScreen();
	void ResetBall();
	void ParseXml();

public:
	Level(int level, PlaySideBar* sideBar,Player* player, Ball* ball);
	~Level();

	LEVEL_STATES State();

	void Update();
	void Render();

};
inline bool exists_test(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
