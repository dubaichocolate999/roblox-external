#include "gravity.h"

g_gravity gravity;

void g_gravity::loop() {
	if (features::misc::gravity) {
		auto workspace = roblox::find_first_child_class(globals::datamodel, "Workspace");
		auto container = read<uintptr_t>(workspace + offsets::GravityContainer);

		write<float>(container + offsets::Gravity, settings::gravity::gravity);
	}
}