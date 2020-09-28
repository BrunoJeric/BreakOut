#pragma once
#include "PhysEntity.h"
#include <bitset>

class PhysicsManager {

public:
	enum class CollisionLayers {
		PlatformLayer = 0,
		BallLayer,
		BrickLayer,
		//----for iteration--------- 
		MaxLayers
	};
	enum class CollisonFlags {
		None			=0x00,
		PlatformLayer	=0x01,
		BallLayer		=0x02,
		BrickLayer		=0x04

	};

private:
	static PhysicsManager* sInstance;

	std::vector<PhysEntity*>mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

public:
	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisonFlags flags);

	unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);

	void UnregisterEntity(unsigned long id);

	void Update();


private:
	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisonFlags operator|(PhysicsManager::CollisonFlags a, PhysicsManager::CollisonFlags b) {
	return static_cast<PhysicsManager::CollisonFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisonFlags operator&(PhysicsManager::CollisonFlags a, PhysicsManager::CollisonFlags b) {
	return static_cast<PhysicsManager::CollisonFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}