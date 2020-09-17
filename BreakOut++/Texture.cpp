#include "Texture.h"

Texture::Texture(std::string fileName) {
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetTexture(fileName);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

}

Texture::~Texture() {
	mTex = NULL;
	mGraphics = NULL;
}

void Texture::Render() {
	Vector2 pos = Pos(world);
	mRenderRect.x = (int)(pos.x - mWidth * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * 0.5f);
	mGraphics->DrawTexture(mTex,&mRenderRect);
}