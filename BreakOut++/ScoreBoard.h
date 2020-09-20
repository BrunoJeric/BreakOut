#pragma once
#include "Texture.h"
#include <vector>

using namespace EngineSDL;
class ScoreBoard : public GameEntity{

private:
	std::vector<Texture*>mScore;
public:
	ScoreBoard();
	~ScoreBoard();

	void Score(int score);
	void Render();

private:
	void ClearBoard();
};
