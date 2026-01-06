#include "aimbot.h"

aimbot aim_bot;

void aimbot::loop() {
    if (!features::combat::aimbot) return;

    std::vector<uintptr_t> players = player::get_players_all(globals::datamodel);

    if (globals::game_id == static_cast<std::uint64_t>(game::phantom_forces))
        players = player::get_players_pf(globals::datamodel);

    POINT cursor;
    if (!GetCursorPos(&cursor))
        return;

    fov = settings::aimbot::fov;
    
    render::render_circle(cursor.x, cursor.y, fov, settings::aimbot::fov_color, false);

    if (!(GetAsyncKeyState(VK_RBUTTON) & 0x8000))
        return;

    uintptr_t local_player = player::get_local_player();

    uintptr_t target = 0;
    for (uintptr_t player : players) {
        if (!player || player == local_player)
            continue;

        int player_team = read<int>(player + offsets::Team);
        int local_team = read<int>(globals::local_player + offsets::Team);

        if (!settings::aimbot::target_teammates && player_team == local_team)
            continue;

        uintptr_t character = read<uintptr_t>(player + offsets::ModelInstance);
        uintptr_t bone = aimbot::get_bone(player);
        if (!bone) continue;

        uintptr_t prim = read<uintptr_t>(bone + offsets::Primitive);
        if (!prim) continue;

        vector_3 pos = read<vector_3>(prim + offsets::Position);

        vector_3 last_pos = last_positions.count(player) ? last_positions[player] : pos;
        matrix view_matrix = read<matrix>(globals::visual_engine + offsets::ViewMatrix);

        vector_3 interpolated = math::lerp_vec3(settings::aimbot::interpolation_delta, last_pos, pos);

        vector_2 screen_pos = camera::world_to_screen(interpolated, view_matrix);

        if (settings::aimbot::dynamic_fov) {
            float world_distance = math::distance(player::get_position(local_player), pos);
            fov = aimbot::get_dynamic_fov(world_distance);
        }

        float fov_distance = aimbot::get_fov(screen_pos, cursor);
        if (fov_distance > fov)
            continue;

        target = player;
        last_positions[player] = pos;
    }

    if (target != 0) {
        uintptr_t character = read<uintptr_t>(target + offsets::ModelInstance);
        uintptr_t bone = aimbot::get_bone(target);
        uintptr_t prim = read<uintptr_t>(bone + offsets::Primitive);
        vector_3 pos = read<vector_3>(prim + offsets::Position);

        matrix view_matrix = read<matrix>(globals::visual_engine + offsets::ViewMatrix);
        vector_2 screen_pos = camera::world_to_screen(pos, view_matrix);

        float move_x = screen_pos.x - static_cast<float>(cursor.x);
        float move_y = screen_pos.y - static_cast<float>(cursor.y);

        aimbot::send_input(static_cast<int>(move_x), static_cast<int>(move_y));

    }
}

float aimbot::get_fov(vector_2 pos, POINT cursor) {
    return sqrtf(
        powf(pos.x - static_cast<float>(cursor.x), 2) +
        powf(pos.y - static_cast<float>(cursor.y), 2)
    );
}

float aimbot::get_dynamic_fov(float distance) {
    float min_fov = settings::aimbot::fov * 0.5f;
    float max_fov = settings::aimbot::fov * 1.5f;

    float scale = 500 / (distance + 1.f);

    float dyn_fov = settings::aimbot::fov * scale;
    return std::clamp(dyn_fov, min_fov, max_fov);
}

void aimbot::send_input(int x, int y) {
    INPUT input{};

    x *= 0.6f - (settings::aimbot::smoothing / 100.f) * (0.6f - 0.1f);
    y *= 0.6f - (settings::aimbot::vertical_smoothing / 100.f) * (0.6f - 0.1f);

    input.type = INPUT_MOUSE;
    input.mi.dx = x;
    input.mi.dy = y;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    SendInput(1, &input, sizeof(input));
}

uintptr_t aimbot::get_bone(uintptr_t player) {
    uintptr_t bone = 0;
    uintptr_t character = read<uintptr_t>(player + offsets::ModelInstance);

    if (globals::game_id != static_cast<std::uint64_t>(game::phantom_forces))
        bone = roblox::find_first_child(character, "Head");
    else {
        // get head on pf
        for (const auto& part : roblox::get_children(player)) {
            if (roblox::get_class_name(part) != "Part")
                continue;

            uintptr_t billboard = roblox::find_first_child_class(part, "BillboardGui");
            if (billboard) {
                bone = part;
                break;
            }
        }
    }

    return bone;
}

std::string aimbot::get_hitboxes() {
    if (settings::aimbot::hitboxes == target_hitbox::upper_torso)
        return "UpperTorso";
    else if (settings::aimbot::hitboxes == target_hitbox::torso)
        return "Torso";

    return "Head";
}