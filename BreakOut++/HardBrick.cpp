#include "HardBrick.h"

HardBrick::HardBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore)
	: Brick(hitSound, breakSound, texturePath, hitPoints, breakScore)
{
	mType = hard;
}

HardBrick::~HardBrick() {

}