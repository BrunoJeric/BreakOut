#pragma once
#include "Timer.h"
#include "AudioManager.h"
#include "ScreenManager.h"
#include "PhysicsManager.h"
namespace EngineSDL {
	class GameManager {
	private:
		static GameManager* sInstance;

		const int FRAME_RATE = 60;

		bool mQuit;

		Graphics* mGraphics;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;


		Timer* mTimer;
		SDL_Event mEvents;

		ScreenManager* mScreenManager;

	public:
		static GameManager* Instance();
		static void Release();

		void Run();
	private:
		GameManager();
		~GameManager();

		void EarlyUpdate();
		//all transformations are to be done in this functions 
		void Update();
		//collision detection to be done in LateUpdate
		void LateUpdate();

		void Render();
	};
}