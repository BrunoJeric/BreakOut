#pragma once
#include "Texture.h"
#include "AudioManager.h"

using namespace EngineSDL;

class Brick : public GameEntity {

public:

protected:
	Texture* mTexture;
	
	std::string mHitSound;
	std::string mBreakSound;
	std::string mTexturePath;

	int mHitpoints;
	int mBreakScore;

	char mId;


public:
	Brick(char id, std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints,int breakScore);
	~Brick();
	char Id();

	Brick* Clone();

	void Update();
	void Render();

};