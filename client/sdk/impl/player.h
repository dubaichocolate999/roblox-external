#pragma once

#include "sdk/roblox.h"
#include "globals/globals.h"
#include "oxorany/oxorany_include.h"
#include "utils/vector.h"
#include "sdk/utils/brick_color.h"

namespace player {
	static uintptr_t get_players() {
		uintptr_t datamodel = globals::datamodel;
		uintptr_t players = roblox::find_first_child(datamodel, "Players");

		if (!players)
			players = roblox::find_first_child_class(datamodel, "Players");

		globals::players = players;
		return players;
	}

	static uintptr_t get_local_player() {
		uintptr_t players = globals::players;
		uintptr_t local_player = read<uintptr_t>(players + offsets::LocalPlayer);

		globals::local_player = local_player;
		return local_player;
	}

	static uintptr_t get_character() {
		uintptr_t local_player = globals::local_player;
		uintptr_t character = read<uintptr_t>(local_player + offsets::ModelInstance);

		globals::character = character;
		return character;
	}

	static uintptr_t get_humanoid() {
		uintptr_t character = globals::character;
		uintptr_t humanoid = roblox::find_first_child(character, oxorany("Humanoid"));

		globals::humanoid = humanoid;
		return humanoid;
	}

	static std::vector<uintptr_t> get_players_all(uintptr_t datamodel) {
		std::vector< uintptr_t > player;

		auto players = roblox::find_first_child_class(datamodel, "Players");
		if (!players)
			return player;

		auto children = roblox::get_children(players);

		player.reserve(children.size());

		for (const auto& child : children) {
			if (roblox::get_class_name(child) == "Player")
				player.push_back(child);
		}

		return player;
	}

	static vector_3 get_position(uintptr_t player) {
		vector_3 pos = read<vector_3>(player + offsets::Position);
		return pos;
	}


	static std::vector<uintptr_t> get_players_pf(uintptr_t datamodel) {
		std::vector<uintptr_t> players;

		auto workspace = roblox::find_first_child_class(datamodel, "Workspace");
		if (!workspace) return players;

		auto players_folder = roblox::find_first_child(workspace, "Players");
		if (!players_folder) return players;

		for (const auto& child : roblox::get_children(players_folder)) {
			for (const auto& character : roblox::get_children(child)) {
				if (roblox::get_class_name(character) == "Model") {
					players.push_back(character);
				}
			}
		}

		return players;
	}


	static std::unordered_map<uintptr_t, uintptr_t> get_players_map(uintptr_t datamodel) {
		std::unordered_map<uintptr_t, uintptr_t> map; 
		auto workspace = roblox::find_first_child_class(datamodel, "Workspace");
		if (!workspace) return map; 

		auto players_folder = roblox::find_first_child(workspace, "Players");
		if (!players_folder) return map; 

		for (const auto& child : roblox::get_children(players_folder)) { 
			for (const auto& character : roblox::get_children(child)) { 
				for (const auto& part : roblox::get_children(character)) { 
					std::string className = roblox::get_class_name(part); 
					if (className != "Part" && className != "MeshPart") 
						continue; 

					uintptr_t billboard = roblox::find_first_child_class(part, "BillboardGui"); 
					if (!billboard) continue;

					uintptr_t label = roblox::find_first_child_class(billboard, "TextLabel");
					if (!label) continue;

					std::string playerName = roblox::read_string(label + offsets::Text);

					for (uintptr_t player : player::get_players_all(datamodel)) {
						if (playerName == roblox::get_name(player)) { 
							map[player] = character;
							break;
						}
					}
				}
			}
		}
		return map;
	}


	static brick_color team_color(uintptr_t player) {
		uintptr_t player_team = read<uintptr_t>(player + offsets::Team);
		return read<brick_color::brick_number>(player_team + offsets::TeamColor);
	}

	static int get_rig_type(uintptr_t player) {
		uintptr_t character = read<uintptr_t>(player + offsets::ModelInstance);
		uintptr_t humanoid = roblox::find_first_child(character, oxorany("Humanoid"));

		return read<int>(humanoid + offsets::RigType);
	}


}