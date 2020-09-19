#pragma once
#include "Timer.h"
#include "AudioManager.h"
#include "StartScreen.h"
namespace EngineSDL {
	class GameManager {
	private:
		static GameManager* sInstance;

		const int FRAME_RATE = 120;

		bool mQuit;

		//list of managers
		Graphics* mGraphics;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;


		Timer* mTimer;
		//catch exit event
		SDL_Event mEvents;

		StartScreen* mStartScreen;

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