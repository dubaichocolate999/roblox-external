#pragma once

#include <unordered_map>

#include "features/feature.h"
#include "utils/math.h"
#include "sdk/impl/player.h"
#include "utils/matrix.h"
#include "utils/vector.h"
#include "sdk/impl/camera.h"
#include "utils/render.h"
#include "utils/game.h"

class aimbot {
public:
	float fov = 0.f;
	std::unordered_map<uintptr_t, vector_3> last_positions;
public:
	float get_fov(vector_2 pos, POINT cursor);
	float get_dynamic_fov(float distance);
	void send_input(int x, int y);
	void loop();
	std::string get_hitboxes();
	uintptr_t get_bone(uintptr_t player);
};

extern aimbot aim_bot;