#include "PhysEntity.h"
#include "PhysicsHelper.h"
#include "PhysicsManager.h"

PhysEntity::PhysEntity() {
	mBroadPhaseCollider = NULL;
	mId = 0;
}
PhysEntity::~PhysEntity() {
	for (int i = 0; i < mColliders.size(); i++) {
		delete mColliders[i];
		mColliders[i] = NULL;
	}
	
	mColliders.clear();

	if (mBroadPhaseCollider) {
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = NULL;
	}
	if (mId != 0) {
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}
unsigned long PhysEntity::GetId() {
	return mId;
}

bool PhysEntity::CheckCollision(PhysEntity* other) {
	
	return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);

}

void PhysEntity::Hit(PhysEntity* other) {

}

void PhysEntity::AddCollider(Collider* collider, Vector2 localPos /* =VEC_ZERO */) {
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle) {

		float furthestDist = mColliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;

		for (int i = 0; i < mColliders.size(); i++) {
			dist = mColliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDist) {
				furthestDist = dist;
			}
		}
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = new CircleCollider(furthestDist, true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Pos(VEC_ZERO);
	}
}

void PhysEntity::Render() {
	for (int i = 0; i < mColliders.size(); i++) {
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider) {
		mBroadPhaseCollider->Render();
	}
}