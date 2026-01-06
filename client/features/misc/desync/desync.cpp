#include "desync.h"

g_desync desync;

void g_desync::run() {
    static bool was_enabled = false;
    static int32_t original_value = -1;
    static auto restore_start_time = std::chrono::steady_clock::now();
    static bool is_restoring = false;
    static bool has_been_used = false;


    bool currently_enabled = features::misc::desync;

    if (currently_enabled && !was_enabled) {
        // saves og value and sets to 0
        if (original_value == -1) {
            original_value = read<int32_t>(driver::get_base() + offsets::PhysicsSenderMaxBandwidthBps);
            has_been_used = true; // Mark that we've used desync
        }
        write<int32_t>(driver::get_base() + offsets::PhysicsSenderMaxBandwidthBps, 0);
        is_restoring = false;
    }
    else if (!currently_enabled && was_enabled) {
        // turns off and strts restoring
        if (original_value != -1) {
            restore_start_time = std::chrono::steady_clock::now();
            is_restoring = true;
        }
    }
    else if (currently_enabled) {
        // keeps writing 0 i also ht ns
        write<int32_t>(driver::get_base() + offsets::PhysicsSenderMaxBandwidthBps, 0);
    }

    // when restoring, keeps doing it for 3 secs
    if (is_restoring && original_value != -1) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - restore_start_time);

        if (elapsed.count() < 10000) { // 3 seconds
            write<int32_t>(driver::get_base() + offsets::PhysicsSenderMaxBandwidthBps, original_value);
        }
        else {
            // stops restoring after 3 secs
            is_restoring = false;
            original_value = -1;
        }
    }

    was_enabled = currently_enabled;
}