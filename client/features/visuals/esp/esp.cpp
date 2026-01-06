#include "esp.h"

g_esp esp;

void g_esp::render() {
	if (!features::visuals::esp)
		return;

	uintptr_t local_player = player::get_local_player();

	std::vector<uintptr_t> players = player::get_players_all(globals::datamodel);

	if (globals::game_id == static_cast<std::uint64_t>(game::phantom_forces))
		players = player::get_players_pf(globals::datamodel);

	// sooo bad bro
	for (uintptr_t player : players) {
		if (!player || player == local_player)
			continue;

		int player_team = read<int>(player + offsets::Team);
		int local_team = read<int>(local_player + offsets::Team);

		if (!settings::esp::teammates && player_team == local_team)
			continue;

		//if (get_player_health(player) <= 0.0f)
			 //continue;

		draw_player(player);
	}
}


void g_esp::draw_player(uintptr_t player) {
	uintptr_t character = read<uintptr_t>(player + offsets::ModelInstance);

	uintptr_t bone = get_bone(player);

	if (!bone) return; // no valid part found

	uintptr_t prim = read<uintptr_t>(bone + offsets::Primitive);
	vector_3 pos = read<vector_3>(prim + offsets::Position);

	vector_3 last_pos = last_positions.count(player) ? last_positions[player] : pos;

	matrix view_matrix = read<matrix>(globals::visual_engine + offsets::ViewMatrix);

	vector_3 interpolated = math::lerp_vec3(1.0f, last_pos, pos);

	vector_2 head_pos = camera::world_to_screen({ interpolated.x, interpolated.y + 1, interpolated.z }, view_matrix);
	vector_2 leg_pos = camera::world_to_screen(math::subtract_vectors(interpolated, { 0, 4, 0 }), view_matrix);

	float height = head_pos.y - leg_pos.y;
	float width = height / 1.8f;

	if (settings::esp::box) {
		render::render_outline(leg_pos.x - (width / 2.f), leg_pos.y, width, height, settings::esp::box_color);
	}

	if (settings::esp::name) {
		std::string player_name = roblox::get_name(player);
		ImColor color = settings::esp::name_color;

		if (globals::game_id == static_cast<std::uint64_t>(game::phantom_forces))
			player_name = get_pf_name(player);

		render::render_text(player_name, head_pos.x, head_pos.y - 15, settings::esp::name_color, 1);
	}

	if (settings::esp::health) {
		float health = get_player_health(player);
		if (globals::game_id == static_cast<std::uint64_t>(game::phantom_forces))
			health = 100;

		int og_health = static_cast<int>(health);
		health = std::clamp(health, 0.0f, 100.0f);

		render::render_rect((leg_pos.x + (width / 2.f)) - 6, leg_pos.y + 1, 4., height - 2, Color(5, 5, 5, 179));

		if (settings::esp::health_mode != health_color::gradient)
			render::render_rect((leg_pos.x + (width / 2.f)) - 5, leg_pos.y + 1, 2., (height * (health / 100.0f)) - 2, get_health_color(health));
		else
			render::render_gradient((leg_pos.x + (width / 2.f)) - 5, leg_pos.y + 1, 2., (height * (health / 100.0f)) - 2, settings::esp::color, settings::esp::second_color);

		if (health < 999) {
			ImGui::PushFont(fonts::esp_health);

			render::render_text(
				std::to_string(og_health),
				((leg_pos.x + (width / 2.f)) - 5),
				leg_pos.y + (height * (health / 100.0f)),
				Color(255, 255, 255),
				1,
				fonts::esp_health
			);

			ImGui::PopFont();
		}

	}

	if (settings::esp::dot) {
		ImColor& color = settings::esp::dot_color;

		ImColor circle_color(
			color.Value.x,
			color.Value.y,
			color.Value.z,
			100 / 255.f
		);

		render::render_circle(head_pos.x, head_pos.y, 5.0f, circle_color, true);
		render::render_circle(head_pos.x, head_pos.y, 5.0f, color, false);
	}

	if (settings::esp::distance) {

	}

	last_positions[player] = pos;
}

float g_esp::get_player_health(uintptr_t player) {
	uintptr_t character = read<uintptr_t>(player + offsets::ModelInstance);
	uintptr_t humanoid = roblox::find_first_child(character, "Humanoid");
	return read<float>(humanoid + offsets::Health);
}

ImColor g_esp::get_health_color(float& health) {
	switch (settings::esp::health_mode) {
	case health_color::static_color:
		return settings::esp::color;

	case health_color::healthbased:
		ImColor health_color;

		if (health >= 75)
			health_color = ImColor(0, 255, 0);
		else if (health >= 30)
			health_color = ImColor(255, 255, 0);
		else
			health_color = ImColor(255, 0, 0);

		return health_color;
	}
}

uintptr_t g_esp::get_bone(uintptr_t player) {
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

std::string g_esp::get_pf_name(uintptr_t player) {
	for (auto& part : roblox::get_children(player)) {
		if (roblox::get_class_name(part) != "Part")
			continue;

		uintptr_t billboard = roblox::find_first_child_class(part, "BillboardGui");
		if (!billboard)
			continue;

		uintptr_t label = roblox::find_first_child_class(billboard, "TextLabel");
		if (!label)
			continue;

		return roblox::read_string(label + offsets::Text);
	}

	return "";
}

bool g_esp::get_player_box_rect(uintptr_t player, rect& rect) {
	vector_2 bottom, top;


	return true;
}