#pragma once
#include "Brick.h"

class SoftBrick : public Brick {

public:
	SoftBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore);
	~SoftBrick();


};