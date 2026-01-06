#pragma once

#include "features/feature.h"
#include "sdk/impl/player.h"

class walkspeed {
public:
	float prev_speed;
	bool enabled = false;

public:
	void loop();
};

extern walkspeed walk_speed;