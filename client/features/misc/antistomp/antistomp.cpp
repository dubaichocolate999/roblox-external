#include "antistomp.h"

g_antistomp antistomp;

void g_antistomp::run() {
    if (!features::misc::antistomp)
        return;

    uintptr_t players = player::get_players();
    uintptr_t local_player = player::get_local_player();
    uintptr_t character = player::get_character();
    uintptr_t humanoid = player::get_humanoid();

    auto bodyeffects = roblox::find_first_child(character, "BodyEffects");
    if (!driver::is_valid_address(bodyeffects))
        return;

    auto find_ko = roblox::find_first_child(bodyeffects, "K.O");
    auto find_dead = roblox::find_first_child(bodyeffects, "Dead");
    auto find_sdeath = roblox::find_first_child(bodyeffects, "SDeath");

    if (!driver::is_valid_address(humanoid))
        return;

    bool ko = read<bool>(find_ko + offsets::Value);
    if (ko) {
        if (driver::is_valid_address(find_ko)) {
            write<bool>(find_ko + offsets::Value, true);
        }

        if (driver::is_valid_address(find_dead)) {
            write<bool>(find_dead + offsets::Value, true);
        }

        if (driver::is_valid_address(find_sdeath)) {
            write<bool>(find_sdeath + offsets::Value, true);
        }

        write<float>(humanoid + offsets::Health, 0.f);
    }
}
