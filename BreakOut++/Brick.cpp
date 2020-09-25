#include "Brick.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"
Brick::Brick(char id,std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore) {

	mHitpoints = hitPoints;
	mBreakScore = breakScore;
	mHitSound = hitSound;
	mBreakSound=breakSound;
	mBId = id;
	mTexturePath = texturePath;

	mTexture = new Texture(texturePath);
	mTexture->Parent(this);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::BrickLayer);
}

Brick::~Brick() {
	delete mTexture;
	mTexture = NULL;
}



char Brick::Id() {
	return mBId;
}

void Brick::Hit(PhysEntity* other) {
	mHitpoints--;
}

Brick* Brick::Clone() {
	return new Brick(mId, mHitSound, mBreakSound, mTexturePath, mHitpoints, mBreakScore);
}

void Brick::Update() {
	/*if (mHitpoints == 0) {
		PhysicsManager::Instance()->UnregisterEntity(mId);
		delete this;
	}*/
}

void Brick::Render() {
	if (mHitpoints > 0) {
		mTexture->Render();
		PhysEntity::Render();
	}
	
}