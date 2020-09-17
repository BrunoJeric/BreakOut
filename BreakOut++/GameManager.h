#pragma once
#include "Texture.h"
#include "Timer.h"
class GameManager {
private:
	static GameManager* sInstance;
	
	const int FRAME_RATE = 120;

	bool mQuit;
	Graphics* mGraphics;

	AssetManager* mAssetManager;

	Timer* mTimer;
	
	SDL_Event mEvents;

	Texture* mTex;

public:
	static GameManager* Instance();
	static void Release();

	void Run();
private:
	GameManager();
	~GameManager();
};