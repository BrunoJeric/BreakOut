#pragma once
#include "Brick.h"

class MediumBrick : public Brick {

public:
	MediumBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore);
	~MediumBrick();


};
