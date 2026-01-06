#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

enum class health_color {
	static_color,
	gradient,
	healthbased
};

enum class target_hitbox {
	head,
	upper_torso,
	torso
};

enum class camera_movement {
	instant,
	exponential,
	curved
};

namespace features {
	
	namespace combat {
		inline bool aimbot = false;
	}
	namespace misc {
		inline bool walkspeed = false;
		inline bool jump = false;
		inline bool desync = false;
		inline bool gravity = false;
		inline bool antistomp = false;
		inline bool noclip = false;
	}
	namespace world {
		inline bool fog_changer = false;
		inline bool ambience = false;
	}
	namespace visuals {
		inline bool fov_changer = false;
		inline bool esp = false;
		inline bool crosshair = false;
	}
	namespace client {
		inline ImColor menu_color = ImColor(150, 150, 255);
		inline bool streamproof = false;
		inline bool vsync = false;
		inline bool watermark = false;
	}
}

// need to make a new namespace for each feature.
namespace settings {
	namespace aimbot {
		inline float fov = 0.f;
		inline target_hitbox hitboxes = target_hitbox::head;
		inline bool target_teammates = false;
		inline float smoothing = 70.f;
		inline float vertical_smoothing = 70.f;
		inline float interpolation_delta = 0.6f;
		inline camera_movement movement = camera_movement::instant;

		inline bool dynamic_fov = false;

		inline bool visualize = false;
		inline ImColor fov_color = ImColor(150, 150, 255);
	}
	namespace walkspeed {
		inline float walkspeed = 20.f;
	}
	namespace fov_changer {
		inline float fov = 90.f;
	}
	namespace jump_height {
		inline float height = 50.f;
	}
	namespace esp {
		inline bool teammates = false;

		inline bool name = false;
		inline ImColor name_color = ImColor(230, 230, 230);
		
		inline bool box = false;
		inline ImColor box_color = ImColor(230, 230, 230);

		inline bool health = false;
		inline health_color health_mode = health_color::healthbased;
		inline ImColor color = ImColor(230, 230, 230);
		inline ImColor second_color = ImColor(1, 1, 1);

		inline bool dot = false;
		inline ImColor dot_color = ImColor(150, 150, 255);

		inline bool distance = false;
	}
	namespace fog_changer {
		inline ImColor color = ImColor(150, 150, 250);
	}
	namespace ambience {
		inline ImColor color = ImColor(150, 150, 250);
	}
	namespace gravity {
		inline float gravity = 196.2f;
	}
}