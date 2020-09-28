#include "Ball.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
#include "Player.h"
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

	AddCollider(new CircleCollider(25.0f));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::BallLayer);

}
Ball::~Ball() {
	mTimer = nullptr;

	delete mBallTexture;
	mBallTexture = nullptr;
}

bool Ball::IgnoreCollision() {
	return mDocked;
}

void Ball::Visible(bool visible) {
	mVisible = visible;
}

void Ball::ResetSpeed() {
	mSpeed = 700.0f;
}

void Ball::Hit(PhysEntity* other) {

	Player* pl = dynamic_cast<Player*>(other);
	
	if (pl != nullptr) {
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_RIGHT)) {
			RotateDirVec(-10.0f);
		}else if (InputManager::Instance()->KeyDown(SDL_SCANCODE_LEFT)) {
			RotateDirVec(10.0f);
		}
	}
	mDirection = Vector2(mDirection.x, -mDirection.y);

	
}

float Ball::Speed() {
	return mSpeed;
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

	if (Pos().y < mUDBounds.x) {
		mDirection = Vector2(mDirection.x, -mDirection.y);
		AudioManager::Instance()->PlaySFX("platform.wav");

	}
	else if (Pos().x < mLRBounds.x || Pos().x > mLRBounds.y) {
		mDirection = Vector2(-mDirection.x, mDirection.y);
		AudioManager::Instance()->PlaySFX("platform.wav");

	}
	else if (Pos().y > mUDBounds.y) {
		mSpeed = 0.0f;
	}
	Translate(mDirection * mSpeed * mTimer->DeltaTime(), local);

}

void Ball::Direction(Vector2 dir) {
	mDirection = dir;
}
Vector2 Ball::Direction(){
	return mDirection;
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
		PhysEntity::Render();
	}
}