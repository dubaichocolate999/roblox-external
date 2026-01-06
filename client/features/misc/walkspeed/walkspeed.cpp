#include "walkspeed.h"

walkspeed walk_speed;

// ULTRA CHINESE;;;;.....
void walkspeed::loop() {
    if (features::misc::walkspeed) {
        uintptr_t players = player::get_players();
        uintptr_t local_player = player::get_local_player();
        uintptr_t character = player::get_character();
        uintptr_t humanoid = player::get_humanoid();

        if (!enabled) {
            float current_speed = read<float>(humanoid + offsets::WalkSpeed);
            prev_speed = current_speed;
            enabled = true;
        }

        write<float>(globals::humanoid + offsets::WalkSpeed, settings::walkspeed::walkspeed);
        write<float>(globals::humanoid + offsets::WalkSpeedCheck, settings::walkspeed::walkspeed);
    }
    else if (enabled) {
        enabled = false;
        write<float>(globals::humanoid + offsets::WalkSpeed, prev_speed);
        write<float>(globals::humanoid + offsets::WalkSpeedCheck, prev_speed);
    }
}