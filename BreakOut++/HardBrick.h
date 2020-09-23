#pragma once
#include "Brick.h"

class HardBrick : public Brick {

public:
	HardBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore);
	~HardBrick();


};
#pragma once
