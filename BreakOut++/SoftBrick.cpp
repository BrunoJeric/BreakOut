#include "SoftBrick.h"

SoftBrick::SoftBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore)
	: Brick(hitSound,breakSound,texturePath,hitPoints,breakScore)
{
	mType = soft;
}

SoftBrick::~SoftBrick() {

}