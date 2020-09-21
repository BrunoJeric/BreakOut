#include "Player.h"

Player::Player(){
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	
	mScore = 0;
	mLives = 3;

	mPlatform = new Texture("platform.png");
	mPlatform->Parent(this);
	mPlatform->Pos(VEC_ZERO);

	mMoveSpeed = 300.0f;
	mMoveBounds = Vector2(281.0f, 760.0f);

	mDeathAnimation = new AnimatedTexture("deathAnimation.png", 0, 0, 200, 23, 4, 1.0f, AnimatedTexture::vertical);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);
}

Player::~Player(){
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mPlatform;
	mPlatform = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;
}

void Player::HandleMovment() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(VEC_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-VEC_RIGHT * mMoveSpeed * mTimer->DeltaTime());

	}

	Vector2 pos = Pos(local);
	if (pos.x < mMoveBounds.x) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Pos(pos);
}

void Player::Visible(bool visible) {
	mVisible = visible;
}
bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

void Player::DroppedBall() {
	mLives--;
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("death.wav");
}

void Player::Update(){
	if (mAnimating) {
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {

		if (Active()) {
			HandleMovment();
		}
	}
}
void Player::Render() {

	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mPlatform->Render();

		}

	}

}