#include "ImpenetrableBrick.h"

ImpenetrableBrick::ImpenetrableBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore)
	: Brick(hitSound, breakSound, texturePath, hitPoints, breakScore)
{
	mType = impenetrable;
}

ImpenetrableBrick::~ImpenetrableBrick() {

}