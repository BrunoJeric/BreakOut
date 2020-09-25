#pragma once
#include "Texture.h"
#include "AudioManager.h"
#include "PhysEntity.h"

using namespace EngineSDL;

class Brick : public PhysEntity {

public:

protected:
	Texture* mTexture;
	
	std::string mHitSound;
	std::string mBreakSound;
	std::string mTexturePath;

	int mHitpoints;
	int mBreakScore;

	char mBId;


public:
	Brick(char id, std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints,int breakScore);
	~Brick();
	char Id();

	void Hit(PhysEntity* other) override;

	Brick* Clone();

	void Update();
	void Render();

};