#pragma once
#include "Graphics.h"
#include <map>

class AssetManager {
public:
	static AssetManager* sInstance;

	std::map<std::string, SDL_Texture*>mTextures;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename);
private:
	AssetManager();
	~AssetManager();
};