#include "AudioManager.h"
namespace EngineSDL {

	AudioManager* AudioManager::sInstance = nullptr;

	AudioManager* AudioManager::Instance() {

		if (sInstance == 0) {
			sInstance = new AudioManager();
		}
		return sInstance;
	}

	void AudioManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	AudioManager::AudioManager() {

		mAssetManager = AssetManager::Instance();

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
			std::cout << "Mixer Initialization Error: " << Mix_GetError() << std::endl;

		}
	}

	AudioManager::~AudioManager() {
		mAssetManager = nullptr;
		Mix_Quit();
	}

	void AudioManager::PlayMusic(std::string filename, int loops) {
		Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
	}

	void AudioManager::PauseMusic() {
		if (Mix_PlayingMusic() != 0) {
			Mix_PauseMusic();
		}
	}

	void AudioManager::ResumeMusic() {
		if (Mix_PausedMusic != 0) {
			Mix_ResumeMusic();
		}
	}

	void AudioManager::PlaySFX(std::string filename, int loops, int channel) {
		Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loops);
	}
}






