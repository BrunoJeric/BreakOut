#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace EngineSDL;

class StartScreen : public GameEntity {

private:
	//Top bar
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHighScore;

	//Start game
	GameEntity* mPlay;
	Texture* mStartGame;

	//Bottom bar
	GameEntity* mBottomBar;
	Texture* mDate;
	Texture* mCreds;
public:
	StartScreen();
	~StartScreen();

	void Update();

	void Render(); 
	 
};
