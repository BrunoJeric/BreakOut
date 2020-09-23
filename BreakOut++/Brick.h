#pragma once
#include "Texture.h"
#include "AudioManager.h"

using namespace EngineSDL;

class Brick : GameEntity {

public:
	enum TYPES {soft,medium,hard,impenetrable};

protected:
	Texture* mTexture;
	
	std::string mHitSound;
	std::string mBreakSound;
	std::string mTexturePath;

	int mHitpoints;
	int mBreakScore;

	TYPES mType;

public:
	Brick( std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints,int breakScore);
	virtual ~Brick();

	void Update();
	void Render();

};