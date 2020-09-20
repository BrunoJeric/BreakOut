#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	//Top bar
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.5f, 45.0f));
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 24, { 251,35,35});
	mHighScore = new Texture("HI-SCORE", "emulogic.ttf", 24, {251,35,35});
	mPlayerOneScore = new ScoreBoard();
	mTopScore = new ScoreBoard();


	mHighScore->Parent(mTopBar);
	mPlayerOne->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mHighScore -> Pos(Vector2(30.0f,0.0f));
	mPlayerOne->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));

	mPlayerOneScore->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH * 0.23f, 35.0f));
	mTopScore->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.15f, 35.0f));
	mPlayerOneScore->Score(15236);
	mTopScore->Score(30000);
	
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
	mQuitGame = new Texture("Quit Game", "emulogic.ttf", 24, { 230,230,230 });
	mCursor = new Texture("cursor.png");
	mStartGame->Parent(mPlay);
	mQuitGame->Parent(mPlay);
	mCursor->Parent(mPlay);
	mCursor->Scale(Vector2(0.5f, 0.35f));

	mCursor->Pos(Vector2(-135.0f, 18.0f));
	mStartGame->Pos(Vector2(0.0f, 15.0f));
	mQuitGame->Pos(Vector2(-11.0f, 60.0f));

	mPlay->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f,45.0f);
	mSelection = 0;

	//Bottom Bar
	mBottomBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	mDate = new Texture("19.09.2020", "emulogic.ttf", 20, { 230,230,230 });
	mCreds = new Texture("Bruno Jeric", "emulogic.ttf", 16, { 251,35,35 });

	mDate->Parent(mBottomBar);
	mCreds->Parent(mBottomBar);

	mDate->Pos(Vector2(0.0f, -25.0f));
	mCreds->Pos(Vector2(0.0f, 0.0f));

	mBottomBar->Parent(this);

	//Animation
	ResetAnimation();
}

StartScreen::~StartScreen() {
	//top bar cleanup
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayerOne;
	mPlayerOne= NULL;
	delete mHighScore;
	mHighScore = NULL;
	delete mTopScore;
	mTopScore = NULL;
	delete mPlayerOneScore;
	mPlayerOneScore = NULL;

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
	delete mQuitGame;
	mQuitGame = NULL;
	delete mCursor;
	mCursor = NULL;

	//bottom bar cleanup
	delete mBottomBar;
	mBottomBar = NULL;
	delete mDate;
	mDate = NULL;
	delete mCreds;
	mCreds = NULL;
}

void StartScreen::ChangeSelection(int change) {
	mSelection += change;
	if (mSelection <= 0)
		mSelection = 0;
	else if (mSelection > 1)
		mSelection = 1;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelection);
}
void StartScreen::ResetAnimation() {
	mAnimationStartPosition = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPosition = VEC_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPosition);
}

int StartScreen::SelectedScreen() {
	return mSelection;
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

		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelection(1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelection(-1);
		}
	}

}

void StartScreen::Render() {
	mHighScore->Render();
	mPlayerOne->Render();
	mPlayerOneScore->Render();
	mTopScore->Render();

	if (!mAnimationDone)
		mLogo->Render();
	else
		mAnimatedLogo->Render();

	
	mStartGame->Render();
	mQuitGame->Render();
	mCursor->Render();

	mDate->Render();
	mCreds->Render();
};