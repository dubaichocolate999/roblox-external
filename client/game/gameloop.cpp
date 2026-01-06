#include "gameloop.h"

void gameloop::initialization() {
	aim_bot.loop();
	esp.render();
	desync.run();
}

// to do
void gameloop::slow_loop() {
	uintptr_t fake_model = read<uintptr_t>(driver::get_base() + offsets::FakeDataModelPointer);
	uintptr_t datamodel = read<std::uint64_t>(fake_model + offsets::FakeDataModelToDataModel);
	globals::datamodel = datamodel;
	globals::visual_engine = read<uintptr_t>(driver::get_base() + offsets::VisualEnginePointer);
	globals::game_id = read<uint64_t>(datamodel + offsets::GameId);

	uintptr_t players = player::get_players();
	uintptr_t local_player = player::get_local_player();
	uintptr_t character = player::get_character();
	uintptr_t humanoid = player::get_humanoid();

	walk_speed.loop();
	fov_changer.loop();
	jump_height.loop();
	interface_render.render();

	lighting.render();
	ambient.render();

	gravity.loop();
	antistomp.run();
}

void gameloop::cache_loop() {
	while (true) {
		//player_list::update(globals::datamodel);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
