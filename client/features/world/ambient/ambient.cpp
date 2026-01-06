#include "ambient.h"

g_ambient ambient;

void g_ambient::render() {
	if (features::world::ambience) {
		auto lighting = roblox::find_first_child_class(globals::datamodel, "Lighting");
		ImColor color = settings::ambience::color;

		write<vector_3>(lighting + offsets::OutdoorAmbient, vector_3(color.Value.x, color.Value.y, color.Value.z));
	}
}