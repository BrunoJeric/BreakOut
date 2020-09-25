#include "Brick.h"
#include "BoxCollider.h"
Brick::Brick(char id,std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore) {

	mHitpoints = hitPoints;
	mBreakScore = breakScore;
	mHitSound = hitSound;
	mBreakSound=breakSound;
	mId = id;
	mTexturePath = texturePath;

	mTexture = new Texture(texturePath);
	mTexture->Parent(this);

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));
}

Brick::~Brick() {
	delete mTexture;
	mTexture = NULL;
}
char Brick::Id() {
	return mId;
}
Brick* Brick::Clone() {
	return new Brick(mId, mHitSound, mBreakSound, mTexturePath, mHitpoints, mBreakScore);
}

void Brick::Update() {

}
void Brick::Render() {
	mTexture->Render();
	PhysEntity::Render();
}