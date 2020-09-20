#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "ScoreBoard.h"

using namespace EngineSDL;

class StartScreen : public GameEntity {

private:
	Timer* mTimer;
	InputManager* mInputManager;

	//Top bar
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHighScore;
	ScoreBoard* mPlayerOneScore;
	ScoreBoard* mTopScore;

	//Logo
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Start game
	GameEntity* mPlay;
	Texture* mStartGame;
	Texture* mQuitGame;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelection;


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

	void ResetAnimation();

	int SelectedScreen();
	void ChangeSelection(int change);

	void Update();

	void Render(); 
	 
};
