#include "AssetManager.h"

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
		if (text.second !=NULL ) {
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
	std::string fullpath = SDL_GetBasePath();
	fullpath.append("Assets/" + filename);
	std::string key = fullpath + (char)size;

	if (mFonts[key] == nullptr) {
		mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);
		if (mFonts[key] == nullptr) {
			std::cout << "Font Loading Error: Font(" << filename.c_str() << ") - Error(" << TTF_GetError() << ") " << std::endl;

		}
	}
	return mFonts[key];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size,SDL_Color color) {
	TTF_Font* font = GetFont(filename, size);
	std::string key = text + filename + (char)size;
	if (mText[key] == nullptr) {
		mText[key] = Graphics::Instance()->CreateTextTexture(font, text,color);
	}
	return mText[key];
}