#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	//Top bar
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, 45.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 24, { 255,255,255 });
	mHighScore = new Texture("HI-SCORE", "emulogic.ttf", 24, {255,255,255 });


	mHighScore->Parent(mTopBar);
	mPlayerOne->Parent(mTopBar);

	mHighScore -> Pos(Vector2(-30.0f,0.0f));
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	
	mTopBar->Parent(this);

	//Logo
	mLogo = new Texture("Logo.png", 0, 0, 550, 107);
	mAnimatedLogo = new AnimatedTexture("Logo.png", 0, 0, 550, 107,2,1.0f,AnimatedTexture::vertical);
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));
	mAnimatedLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.4f));
	mLogo->Scale(Vector2(0.7f, 0.7f));
	mAnimatedLogo->Scale(Vector2(0.7f, 0.7f));
	mLogo->Parent(this);
	mAnimatedLogo->Parent(this);

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

	//Animation
	mAnimationStartPosition = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPosition = VEC_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPosition);
}

StartScreen::~StartScreen() {
	//top bar cleanup
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne= NULL;
	delete mHighScore;
	mHighScore = NULL;

	//logo cleanup
	delete mLogo;
	mLogo = NULL;
	delete mAnimatedLogo;
	mAnimatedLogo = NULL;
	
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

void StartScreen::Update(){
	
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPosition, mAnimationEndPosition, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
		}
	}
	else {
		mAnimatedLogo->Update();
	}

}

void StartScreen::Render() {
	mHighScore->Render();
	mPlayerOne->Render();

	if (!mAnimationDone)
		mLogo->Render();
	else
		mAnimatedLogo->Render();

	
	mStartGame->Render();

	mDate->Render();
	mCreds->Render();
};