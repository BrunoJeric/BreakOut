#pragma once
#include "Texture.h"
#include "InputManager.h"
#include "Timer.h"
#include "PhysEntity.h"
using namespace EngineSDL;
class Ball : public PhysEntity {

private:
	Timer* mTimer;

	bool mDocked;
	bool mVisible;

	float mSpeed;
	
	Vector2 mDirection;

	Vector2 mUDBounds;
	Vector2 mLRBounds;

	Texture* mBallTexture;
private:
	void TranslateAndHandlePlayArea();
public:
	Ball();
	~Ball();

	void Docked(bool docked);
	bool Docked();

	void Visible(bool visible);
	bool Visible();

	void RotateDirVec(float amount);

	void Update();
	void Render();
};