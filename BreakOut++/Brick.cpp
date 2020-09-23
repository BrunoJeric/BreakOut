#include "Brick.h"

Brick::Brick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore) {

	mHitpoints = hitPoints;
	mBreakScore = breakScore;
	mHitSound = hitSound;
	mBreakSound=breakSound;

	mTexture = new Texture(texturePath);
	mTexture->Parent(this);
}

Brick::~Brick() {
	delete mTexture;
	mTexture = NULL;
}

void Brick::Update() {

}
void Brick::Render() {

}