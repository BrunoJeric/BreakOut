#pragma once
#include "Texture.h"
#include <vector>

using namespace EngineSDL;
class ScoreBoard : public GameEntity{

private:
	std::vector<Texture*>mScore;

	SDL_Color mColor;
public:
	ScoreBoard();
	ScoreBoard(SDL_Color color);
	~ScoreBoard();

	void Score(int score);
	void Render();

private:
	void ClearBoard();
};
