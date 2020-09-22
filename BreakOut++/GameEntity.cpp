#include "GameEntity.h"
namespace EngineSDL {
	GameEntity::GameEntity(Vector2 pos) {

		mPos = pos;
		mRotation = 0.0f;
		mActive = true;
		mParent = NULL;
		mScale = VEC_ONE;
	}

	GameEntity::~GameEntity() {
		mParent = NULL;
	}

	void GameEntity::Pos(Vector2 pos) {
		mPos = pos;
	}

	Vector2 GameEntity::Pos(SPACE space) {

		if (space == local || mParent == NULL)
			return mPos;

		Vector2 parentScale = mParent->Scale(world);
		//Vector2 rotVector = Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y);

		Vector2 rotPos = RotateVector(Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(local));

		return mParent->Pos(world) + rotPos;
	}

	void GameEntity::Rotation(float r) {
		mRotation = r;
		if (mRotation > 360.0f) {

			int mul = mRotation / 360;
			mRotation -= 360.0f * mul;

		}
		else if (mRotation < 0.0f) {

			int mul = (mRotation / 360) - 1;
			mRotation -= 360.0f * mul;
		}
	}

	float GameEntity::Rotation(SPACE space) {
		if (space == local || mParent == NULL)
			return mRotation;
		return mParent->Rotation(world) + mRotation;
	}

	void GameEntity::Scale(Vector2 scale) {
		mScale = scale;
	}

	Vector2 GameEntity::Scale(SPACE space) {
		if (space == local || mParent == NULL) {
			return mScale;
		}

		Vector2 scale = mParent->Scale(world);
		scale.x *= mScale.x;
		scale.y *= mScale.y;
		return scale;

	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}

	bool GameEntity::Active() {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {


		if (parent == NULL) {

			mPos = Pos(world);
			mScale = Scale(world);
			mRotation = Rotation(world);

		}
		else {

			//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
			if (mParent != NULL)
				Parent(NULL);

			Vector2 parentScale = parent->Scale(world);

			//Setting the local position to be relative to the new parent (while maintaining the same world position as before)
			mPos = RotateVector(Pos(world) - parent->Pos(world), -parent->Rotation(world));
			mPos.x /= parentScale.x;
			mPos.y /= parentScale.y;

			//Setting the local rotation to be relative to the new parent (while maintaining the same world rotation as before)
			mRotation = mRotation - parent->Rotation(world);

			//Setting the new scale to be relative to the new parent (while maintaining the same world scale as before)
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}

		mParent = parent;
	}

	void GameEntity::Translate(Vector2 vec,SPACE space) {
		if (space == world) {
			mPos += vec;
		}
		else {
			mPos += RotateVector(vec, Rotation());
		}	
	}

	void GameEntity::Rotate(float amount) {
		mRotation += amount;
	}

	GameEntity* GameEntity::Parent() {
		return mParent;
	}

	void GameEntity::Update() {}
	void GameEntity::Render() {}
}