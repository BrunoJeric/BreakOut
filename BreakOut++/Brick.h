#pragma once
#include "Texture.h"
#include "AudioManager.h"

using namespace EngineSDL;

class Brick : GameEntity {

public:
	enum TYPES {soft,medium,hard,impenetrable};

private:
	Texture* mTexture;
	
	char mId;
	
	std::string mHitSound;
	std::string mBreakSound;
	std::string mTexturePath;

	int mHitpoints;
	int mBreakScore;

public:
	Brick();
	~Brick();

};