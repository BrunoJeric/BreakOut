#include "Ball.h"

Ball::Ball() {
	mTimer = Timer::Instance();
	mDocked = false;
	mVisible = false;
	mSpeed = 700.0f;
	mDirection = Vector2(0.0f, -1.0f);
	mBallTexture = new Texture("ball.png");
	mBallTexture->Parent(this);
	mBallTexture->Pos(VEC_ZERO);
	mUDBounds = Vector2(25.0f, 620.0f);
	mLRBounds = Vector2(181.0f, 843.0f);
}

Ball::~Ball() {
	mTimer = NULL;

	delete mBallTexture;
	mBallTexture = NULL;
}
void Ball::Visible(bool visible) {
	mVisible = visible;
}
void Ball::Docked(bool docked) {
	mDocked = docked;
}
bool Ball::Visible() {
	return mVisible;
}
bool Ball::Docked() {
	return mDocked;
}
void Ball::RotateDirVec(float  amount) {
	mDirection=RotateVector(mDirection, amount);
}

void Ball::TranslateAndHandlePlayArea() {

	if (Pos().y < mUDBounds.x || Pos().y > mUDBounds.y) {
		mDirection = Vector2(mDirection.x, -mDirection.y);
	}
	else if (Pos().x < mLRBounds.x || Pos().x > mLRBounds.y) {
		mDirection = Vector2(-mDirection.x, mDirection.y);
	}
	Translate(mDirection * mSpeed * mTimer->DeltaTime(), local);
}
void Ball::Update() {
	if (Active()) {
		if (!mDocked) {
			TranslateAndHandlePlayArea();
		}
	}
}
void Ball::Render() {
	if (Active()) {

		mBallTexture->Render();
	}
}