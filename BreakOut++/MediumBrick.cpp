#include "MediumBrick.h"

MediumBrick::MediumBrick(std::string hitSound, std::string breakSound, std::string texturePath, int hitPoints, int breakScore)
	: Brick(hitSound, breakSound, texturePath, hitPoints, breakScore)
{
	mType = medium;
}

MediumBrick::~MediumBrick() {

}