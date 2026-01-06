#pragma once

#include "features/feature.h"
#include "sdk/impl/player.h"
#include "globals/globals.h"
#include "utils/matrix.h"
#include "utils/vector.h"

class g_flight {
public:
	void loop();
};

extern g_flight flight;