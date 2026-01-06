#include "jumpheight.h"

jumpheight jump_height;

void jumpheight::loop() {
    if (features::misc::jump) {
        write<float>(globals::humanoid + offsets::JumpPower, settings::jump_height::height);
    }
}