#pragma once

#include "features/feature.h"
#include "utils/math.h"
#include "sdk/impl/player.h"
#include "utils/matrix.h"
#include "utils/vector.h"
#include "sdk/impl/camera.h"
#include "utils/render.h"
#include "features/overlay/fonts/fonts.h"
#include "utils/game.h"
#include "features/overlay/fonts/fonts.h"

class g_esp {
public:
	std::unordered_map<uintptr_t, vector_3> last_positions;
public:
	uintptr_t get_bone(uintptr_t player);
	void render();
	void draw_player(uintptr_t player);
	float get_player_health(uintptr_t player);
	ImColor get_health_color(float& health);
	std::string get_pf_name(uintptr_t player);
	bool get_player_box_rect(uintptr_t player, rect& rect);
};

extern g_esp esp;