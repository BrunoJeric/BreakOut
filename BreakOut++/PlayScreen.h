#pragma once
#include "InputManager.h"
#include "GameEntity.h"
#include "Timer.h"
#include "PlaySideBar.h"
using namespace EngineSDL;
class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInputManager;

	PlaySideBar* mSideBar;
public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();
};

