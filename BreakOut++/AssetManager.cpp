#include "AssetManager.h"
namespace EngineSDL {
	AssetManager* AssetManager::sInstance = NULL;

	AssetManager* AssetManager::Instance() {
		if (sInstance == NULL)
			sInstance = new AssetManager();

		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	AssetManager::AssetManager() {

	}
	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != NULL) {
				SDL_DestroyTexture(tex.second);
			}
		}
		mTextures.clear();

		for (auto text : mText) {
			if (text.second != NULL) {
				SDL_DestroyTexture(text.second);
			}
		}
		mText.clear();
		for (auto font : mFonts) {
			if (font.second != NULL) {
				TTF_CloseFont(font.second);
			}
		}
		mFonts.clear();

		for (auto music : mMusic) {
			if (music.second != NULL) {
				Mix_FreeMusic(music.second);
			}
		}
		mMusic.clear();

		for (auto sfx : mSFX) {
			if (sfx.second != NULL) {
				Mix_FreeChunk(sfx.second);
			}
		}
		mSFX.clear();

		/*for (auto level : mLevels) {
			if (level.second != NULL) {
				delete level.second;
				level.second = NULL;
			}
		}
		mLevels.clear();*/
	}

	SDL_Texture* AssetManager::GetTexture(std::string filename) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mTextures[fullPath] == nullptr) {
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		}

		return mTextures[fullPath];
	}

	TTF_Font* AssetManager::GetFont(std::string filename, int size) {
		//Get the full path of the font
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		//The key takes into account the size of the font aswell since the same font can be opened with different sizes
		std::string key = fullPath + (char)size;

		//If the font has not been already loaded, load it and add it to the mFonts map
		if (mFonts[key] == nullptr) {

			mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
			//Error handling for opening the font
			if (mFonts[key] == nullptr)
				printf("Font Loading Error: Font-%s Error-%s", filename.c_str(), TTF_GetError());
		}

		//returning the cached font from the map
		return mFonts[key];
	}

	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color) {
		//Get the font from the font cache
		TTF_Font* font = GetFont(filename, size);

		//The key takes into account the font, text, size, and color to differentiate text textures
		std::string key = text + filename + (char)size + (char)color.r + (char)color.b + (char)color.g;

		//If the same text has not been rendered before, render it and add it to the mText map
		if (mText[key] == nullptr)
			mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);

		//returning the cached texture containing the text
		return mText[key];
	}

	Mix_Music* AssetManager::GetMusic(std::string filename) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + filename);

		if (mMusic[fullpath] == nullptr) {
			mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
			if (mMusic[fullpath] == NULL) {
				std::cout << "Music Loading Error: File(" << filename.c_str() << ") - Error(" << Mix_GetError() << ") " << std::endl;

			}
		}
		return mMusic[fullpath];
	}

	Mix_Chunk* AssetManager::GetSFX(std::string filename) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + filename);

		if (mSFX[fullpath] == nullptr) {
			mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
			if (mSFX[fullpath] == NULL) {
				std::cout << "SFX Loading Error: File(" << filename.c_str() << ") - Error(" << Mix_GetError() << ") " << std::endl;

			}
		}
		return mSFX[fullpath];
	}

	//XMLDocument* AssetManager::GetLevel(std::string filename) {
	//	std::string fullpath = SDL_GetBasePath();
	//	fullpath.append("Assets/Level/" + filename);
	//	XMLDocument doc;

	//	if (mLevels[fullpath] == nullptr) {
	//		doc.LoadFile(fullpath.c_str());

	//		const XMLDocument& cdoc = doc;

	//		const XMLAttribute* attrib = cdoc.FirstChildElement("Level")->FindAttribute("RowCount");

	//		std::cout << doc.ErrorIDToName(doc.ErrorID())<< attrib->Value()<<std::endl;
	//		mLevels[fullpath]=&doc;
	//		if (mLevels[fullpath] == NULL) {
	//			std::cout << "Level Loading Error: File(" << filename.c_str() << ")" << std::endl;

	//		}
	//	}
	//	return mLevels[fullpath];
	//}
}