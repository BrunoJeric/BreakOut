#include "Player.h"
#include "BoxCollider.h"
#include "Ball.h"
#include "PhysicsManager.h"

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

	AddCollider(new BoxCollider(Vector2(200.0f, 11.0f)), Vector2(0.0f, -6.0f));
	AddCollider(new BoxCollider(Vector2(195.0f,12.0f)),Vector2(0.0f,6.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::PlatformLayer);
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
		Translate(VEC_RIGHT * mMoveSpeed * mTimer->DeltaTime(),world);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		Translate(-VEC_RIGHT * mMoveSpeed * mTimer->DeltaTime(),world);

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

void Player::Hit(PhysEntity* other) {
	Ball* ball = static_cast<Ball*>(other);
	Vector2 dir = ball->Direction();
	ball->Direction(Vector2(dir.x, -dir.y));
}

void Player::DroppedBall() {
	//mLives--;
	//mDeathAnimation->ResetAnimation();
	//mAnimating = true;
	//mAudio->PlaySFX("death.wav");
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
			PhysEntity::Render();

		}

	}

}