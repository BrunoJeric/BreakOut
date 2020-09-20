#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.1f, Graphics::Instance()->SCREEN_HEIGHT * 0.03f));
	mSideBar->SetHighScore(30000);
	mSideBar->SetPlayerScore(14758);
}

PlayScreen::~PlayScreen() {
	mTimer = NULL;
	mInputManager = NULL;

	delete mSideBar;
	mSideBar = NULL;
}

void PlayScreen::Update(){
	mSideBar->Update();
}
void PlayScreen::Render(){
	mSideBar->Render();
}