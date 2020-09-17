#pragma once
#include "GameEntity.h"
#include "AssetManager.h"
class Texture : public GameEntity{

private:
	SDL_Texture* mTex;
	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	SDL_Rect mRenderRect;
public:
	Texture(std::string fileName);
	~Texture();

	virtual void Render();

};