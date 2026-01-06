#pragma once

#include "sdk/roblox.h"
#include "globals/globals.h"
#include "utils/vector.h"
#include "utils/matrix.h"
#include "utils/quaternion.h"

namespace camera {
	static uintptr_t get_camera() {
		uintptr_t datamodel = globals::datamodel;
		uintptr_t workspace = roblox::find_first_child_class(datamodel, oxorany("Workspace"));

		return read<uintptr_t>(workspace + offsets::Camera);
	}

    static vector_2 world_to_screen(const vector_3& world, const matrix& matrix) {
        vector_2 screen{ 0, 0 };
        float w;

        int screen_width = GetSystemMetrics(SM_CXSCREEN), screen_height = GetSystemMetrics(SM_CYSCREEN);

        // check if it's in view first.
        // w is below 0 when world position is around -90 / +90 from the player's camera on the y axis.
        w = matrix.data[3][0] * world.x + matrix.data[3][1] * world.y + matrix.data[3][2] * world.z + matrix.data[3][3];

        if (w < 0.001f)
            return vector_2();

        // calculate x and y;
        screen.x = (matrix.data[0][0] * world.x + matrix.data[0][1] * world.y + matrix.data[0][2] * world.z + matrix.data[0][3]);
        screen.y = (matrix.data[1][0] * world.x + matrix.data[1][1] * world.y + matrix.data[1][2] * world.z + matrix.data[1][3]);

        screen.x /= w;
        screen.y /= w;

        // calculate screen position.
        screen.x = (screen_width / 2) * (screen.x + 1.0f);
        screen.y = (screen_height / 2) * (1.0f - screen.y);

        return screen;
    }
}