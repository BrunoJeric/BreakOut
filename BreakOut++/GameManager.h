#pragma once
#include "Texture.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"
class GameManager {
private:
	static GameManager* sInstance;
	
	const int FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;

	AssetManager* mAssetManager;

	InputManager* mInputManager;

	AudioManager* mAudioManager;

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

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();
};