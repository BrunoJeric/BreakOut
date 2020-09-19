#include "StartScreen.h"

StartScreen::StartScreen() {
	//Top bar
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, 45.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 24, { 255,255,255 });
	mHighScore = new Texture("HI-SCORE", "emulogic.ttf", 24, {255,255,255 });


	mHighScore->Parent(mTopBar);
	mPlayerOne->Parent(mTopBar);

	mHighScore -> Pos(Vector2(-30.0f,0.0f));
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	
	mTopBar->Parent(this);

	//Start game
	mPlay = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mStartGame = new Texture("Start Game", "emulogic.ttf", 24, { 230,230,230 });
	mStartGame->Parent(mPlay);

	mStartGame->Pos(VEC_ZERO);

	mPlay->Parent(this);

	//Bottom Bar
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	mDate = new Texture("19.09.2020", "emulogic.ttf", 20, { 230,230,230 });
	mCreds = new Texture("Bruno Jeric", "emulogic.ttf", 16, { 100,0,0 });

	mDate->Parent(mBottomBar);
	mCreds->Parent(mBottomBar);

	mDate->Pos(Vector2(0.0f, -25.0f));
	mCreds->Pos(Vector2(0.0f, 0.0f));

	mBottomBar->Parent(this);
}

StartScreen::~StartScreen() {
	//top bar cleanup
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne= NULL;
	delete mHighScore;
	mHighScore = NULL;
	
	//game start cleanup
	delete mPlay;
	mPlay = NULL;
	delete mStartGame;
	mStartGame = NULL;

	//bottom bar cleanup
	delete mBottomBar;
	mBottomBar = NULL;
	delete mDate;
	mDate = NULL;
	delete mCreds;
	mCreds = NULL;
}

void StartScreen::Update(){}

void StartScreen::Render() {
	mHighScore->Render();
	mPlayerOne->Render();

	mStartGame->Render();

	mDate->Render();
	mCreds->Render();
};