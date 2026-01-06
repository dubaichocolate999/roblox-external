#pragma once

#include "sdk/roblox.h"
#include "globals/globals.h"
#include "features/feature.h"
#include "sdk/impl/camera.h"

class fov {
public:
	void loop();
};

extern fov fov_changer;