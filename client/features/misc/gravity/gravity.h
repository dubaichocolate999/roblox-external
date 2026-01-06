#pragma once

#include "features/feature.h"
#include "sdk/impl/player.h"
#include "globals/globals.h"

class g_gravity {
public:
	void loop();
};

extern g_gravity gravity;