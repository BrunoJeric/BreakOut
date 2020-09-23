#pragma once
#include "Brick.h"

class ImpenetrableBrick : public Brick {

public:
	ImpenetrableBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore);
	~ImpenetrableBrick();


};
#pragma once
