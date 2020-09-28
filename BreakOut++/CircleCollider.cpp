#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius,bool broad) 
	: Collider(ColliderType::Circle) 
{
	mRadius = radius;

	if (DEBUG_COLLIDERS) {

		if (broad)
			SetDebugTexture(new Texture("BroadPhase.png"));
		else
			SetDebugTexture(new Texture("CircleCollider.png"));

		mDebugTexture->Scale(VEC_ONE * (radius * 2 / 100.0f));
	}
}

CircleCollider::~CircleCollider(){}

Vector2 CircleCollider::GetFurthestPoint() {
	return VEC_RIGHT * (mRadius + Pos(GameEntity::local).Magnitude());
}

float CircleCollider::GetRadius() {
	return mRadius; 
}