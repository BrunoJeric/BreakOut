#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysEntity.h"

using namespace EngineSDL;

class Player : public PhysEntity {

private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	int mScore;
	int mLives;

	Texture* mPlatform;
	AnimatedTexture* mDeathAnimation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

private:
	void HandleMovment();
	bool IgnoreCollision();

public:
	Player();
	~Player();

	void Visible(bool visible);

	void Hit(PhysEntity* other) override;

	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

	void DroppedBall();

	void Update();
	void Render();

};