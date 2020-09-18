#pragma once
#include "GameEntity.h"
#include "AssetManager.h"
class Texture : public GameEntity{

protected:
	SDL_Texture* mTex;
	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mClipRect;
	SDL_Rect mRenderRect;
public:
	Texture(std::string fileName);
	Texture(std::string fileName, int x, int y, int w, int h);
	Texture(std::string text, std::string fontpath, int size);
	~Texture();

	virtual void Render();

};