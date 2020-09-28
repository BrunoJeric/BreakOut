#include "GameManager.h"

int main(int argc, char* argv[]) {
	EngineSDL::GameManager* game = EngineSDL::GameManager::Instance();
	game->Run();
	EngineSDL::GameManager::Release();
	game = nullptr;
	return 0;

}
