#pragma once
#define SDL_MAIN_HANDLED
#include "SDL.h"
namespace EngineSDL {
	class Timer {
	private:
		static Timer* sInstance;

		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float  mTimeScale;
	public:
		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();

		void TimeScale(float t = 1.0f);
		float TimeScale();

		void Update();

	private:
		Timer();
		~Timer();
	};
}