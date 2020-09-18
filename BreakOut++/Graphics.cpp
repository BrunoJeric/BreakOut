#pragma once
#include"Graphics.h"
namespace EngineSDL {
	Graphics* Graphics::sInstance = NULL;
	bool Graphics::sInitialized = false;

	Graphics* Graphics::Instance() {
		if (sInstance == NULL) {
			sInstance = new Graphics();
		}
		return sInstance;
	}

	void Graphics::Release() {
		delete sInstance;
		sInstance = NULL;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	Graphics::Graphics() {
		mBackBuffer = NULL;
		sInitialized = Init();
	}

	Graphics::~Graphics() {
		SDL_DestroyWindow(mWindow);
		mWindow = NULL;

		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	bool Graphics::Init() {
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
			std::cout << "SDL Initialization Error: " << SDL_GetError() << std::endl;
			return false;
		}
		mWindow = SDL_CreateWindow("Start", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
			return false;
		}

		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == NULL) {
			std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

		int flags = IMG_INIT_PNG;

		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Image Initialization Error: " << IMG_GetError() << std::endl;
			return false;
		}

		if (TTF_Init() == -1) {
			std::cout << "Font Initialization Error: " << TTF_GetError() << std::endl;
			return false;
		}

		mBackBuffer = SDL_GetWindowSurface(mWindow);
		return true;
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

	SDL_Texture* Graphics::LoadTexture(std::string path) {
		SDL_Texture* tex = NULL;
		SDL_Surface* surface = IMG_Load(path.c_str());
		if (surface == NULL) {
			std::cout << "Image Load Error: Path(" << path.c_str() << ") - Error(" << SDL_GetError() << ") " << std::endl;
			return tex;
		}
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == NULL) {
			std::cout << "Create Texture Error: " << SDL_GetError() << std::endl;
			return tex;
		}
		SDL_FreeSurface(surface);
		return tex;

	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		if (surface == NULL) {
			std::cout << "Text Render Error:" << SDL_GetError() << std::endl;
			return NULL;
		}
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (tex == NULL) {
			std::cout << "Text Texture Creation Error:" << SDL_GetError() << std::endl;
			return NULL;
		}

		SDL_FreeSurface(surface);
		return tex;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

		SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
	}

}






