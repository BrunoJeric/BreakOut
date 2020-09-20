#pragma once
#include "InputManager.h"
#include "GameEntity.h"
#include "Timer.h"
#include "PlaySideBar.h"
#include "AudioManager.h"
#include "Level.h"

using namespace EngineSDL;
class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	PlaySideBar* mSideBar;

	Texture* mStartLabel;
	
	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	Level* mLevel;

	bool mLevelStarted;
	int mCurrentLevel;

private:
	void StartNextLevel();
public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();
};

