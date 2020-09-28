#include "Brick.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

Player* Brick::sPlayer = nullptr;

Brick::Brick(char id,std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore) {

	mHitpoints = hitPoints;
	mBreakScore = breakScore;
	mHitSound = hitSound;
	mBreakSound=breakSound;
	mBId = id;
	mTexturePath = texturePath;

	mVisible = true;

	mTexture = new Texture(texturePath);
	mTexture->Parent(this);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::BrickLayer);
}

Brick::~Brick() {
	delete mTexture;
	mTexture = nullptr;
}

void Brick::CurrentPlayer(Player* player) {
	sPlayer = player;
}

bool Brick::IgnoreCollision() {
	return !mVisible;
}

char Brick::BrickId() {
	return mBId;
}

void Brick::Hit(PhysEntity* other) {
	if (mBId != 'I') {
		mHitpoints--;
		if (mHitpoints>=1) {
			AudioManager::Instance()->PlaySFX(mHitSound);
		}
		else {
			AudioManager::Instance()->PlaySFX(mBreakSound);
		}
	}
	else {
		AudioManager::Instance()->PlaySFX(mHitSound);

	}
}


bool Brick::Visible() {
	return mVisible;
}

Brick* Brick::Clone() {
	return new Brick(mBId, mHitSound, mBreakSound, mTexturePath, mHitpoints, mBreakScore);
}

void Brick::Update() {
	if (mHitpoints == 0) {
		if(mVisible)
			sPlayer->AddScore(mBreakScore);
		mVisible = false;
	}
}

void Brick::Render() {
	if (mVisible) {
		mTexture->Render();
		PhysEntity::Render();
	}
	
}