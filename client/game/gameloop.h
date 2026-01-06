#pragma once

#include <thread>
#include "features/misc/walkspeed/walkspeed.h"
#include "features/visuals/fovchanger/fovchanger.h"
#include "features/misc/jumpheight/jumpheight.h"
#include "features/combat/aimbot/aimbot.h"
#include "features/visuals/interface/interface.h"
#include "features/visuals/esp/esp.h"
#include "features/world/lighting/lighting.h"
#include "features/world/ambient/ambient.h"
#include "features/misc/gravity/gravity.h"
#include "features/misc/desync/desync.h"
#include "features/misc/antistomp/antistomp.h"
namespace gameloop {
	inline static bool has_finished = false;
	void initialization();
	void slow_loop();
	void cache_loop();
}