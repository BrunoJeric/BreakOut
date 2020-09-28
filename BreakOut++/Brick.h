#pragma once
#include "Texture.h"
#include "AudioManager.h"
#include "PhysEntity.h"
#include "Player.h"
using namespace EngineSDL;

class Brick : public PhysEntity {


protected:

	static Player* sPlayer;

	Texture* mTexture;
	
	std::string mHitSound;
	std::string mBreakSound;
	std::string mTexturePath;

	bool mVisible;

	int mHitpoints;
	int mBreakScore;

	char mBId;

private:
	bool IgnoreCollision() override;


public:

	static void CurrentPlayer(Player* player);


	Brick(char id, std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints,int breakScore);
	~Brick();

	char BrickId();

	bool Visible();

	void Hit(PhysEntity* other) override;

	Brick* Clone();

	void Update();
	void Render();

};