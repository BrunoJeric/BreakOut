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

		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

		int flags = IMG_INIT_PNG;

		if (!(IMG_Init(flags) & flags)) {
			std::cout << "Image Initialization Error: " << IMG_GetError() << std::endl;
			return false;
		}

		if (TTF_Init() == -1) {
			std::cout << "Font Initialization Error: " << TTF_GetError() << std::endl;
			return false;
		}

		//mBackBuffer = SDL_GetWindowSurface(mWindow);
		return true;
	}


	SDL_Texture* Graphics::LoadTexture(std::string path) {
		SDL_Texture* tex = NULL;

		//load the image onto a surface
		SDL_Surface* surface = IMG_Load(path.c_str());
		//Handling image loading errors
		if (surface == NULL) {

			printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
			return tex;
		}

		//Converting the surface into a texture to be able to render it using the renderer
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		//Handling texture creation errors
		if (tex == NULL) {

			printf("Create Texture Error: %s\n", SDL_GetError());
			return tex;
		}

		//free the surface since only the texture is needed
		SDL_FreeSurface(surface);

		return tex;

	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {

		//Render the text onto a surface using the provided font and color
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		//Handling font rendering errors
		if (surface == NULL) {

			printf("Text Render Error: %s\n", TTF_GetError());
			return NULL;
		}

		//Converting the surface into a texture to be able to render it using the renderer
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		//Handle texture creation errors
		if (tex == NULL) {

			printf("Text Texture Creation Error: %s\n", SDL_GetError());
			return NULL;
		}

		//free the surface since only the texture is needed
		SDL_FreeSurface(surface);

		return tex;
	}

	void Graphics::ClearBackBuffer() {
		SDL_RenderClear(mRenderer);
	}

	void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

		SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
	}

	void Graphics::Render() {
		SDL_RenderPresent(mRenderer);
	}

}






