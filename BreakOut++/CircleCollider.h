#pragma once
#include "Collider.h"

class CircleCollider : public Collider {

private:
	float mRadius;



public:
	CircleCollider(float radius,bool broad=false);
	~CircleCollider();

	Vector2 GetFurthestPoint() override;
};