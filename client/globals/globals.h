#pragma once
#include <cstdint>
#include "utils/driver/driver.h"
#include "utils/offsets.h"

namespace globals
{
	extern uintptr_t datamodel;
	extern uintptr_t character;
	extern uintptr_t local_player;
	extern uintptr_t mouse_service;
	extern uintptr_t players;
	extern uintptr_t humanoid;
	extern uintptr_t visual_engine;
	extern uint64_t game_id;

	void setup();
}