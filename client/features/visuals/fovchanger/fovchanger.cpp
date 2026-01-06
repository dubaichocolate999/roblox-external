#include "fovchanger.h"

fov fov_changer;

void fov::loop() {
	if (features::visuals::fov_changer) {
		uintptr_t camera = camera::get_camera();
		write<float>(camera + offsets::FOV, settings::fov_changer::fov / 60);
	}
}