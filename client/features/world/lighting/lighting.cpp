#include "lighting.h"

g_lighting lighting;

void g_lighting::render() {
	if (features::world::fog_changer) {
		auto lighting = roblox::find_first_child_class(globals::datamodel, "Lighting");
		ImColor color = settings::fog_changer::color;

		write<vector_3>(lighting + offsets::FogColor, vector_3(color.Value.x, color.Value.y, color.Value.z));
	}
}