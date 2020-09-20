#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace EngineSDL;

class StartScreen : public GameEntity {

private:
	Timer* mTimer;

	//Top bar
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHighScore;

	//Logo
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Start game
	GameEntity* mPlay;
	Texture* mStartGame;

	//Bottom bar
	GameEntity* mBottomBar;
	Texture* mDate;
	Texture* mCreds;

	//Screen animation
	Vector2 mAnimationStartPosition;
	Vector2 mAnimationEndPosition;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

public:
	StartScreen();
	~StartScreen();

	void Update();

	void Render(); 
	 
};
