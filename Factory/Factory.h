#pragma once
#include "../Contracts/JEntity.h"

class Factory {
public:
	JEntity* createEntity(const char* key, const char* value, JEntity* parent);
};
