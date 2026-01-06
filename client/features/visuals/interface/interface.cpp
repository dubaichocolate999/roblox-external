#include "interface.h"



hud interface_render;

void hud::render() {
	if (features::client::watermark) {
		int screen_width = GetSystemMetrics(SM_CXSCREEN);
		std::string text = "astral.uno";
		std::string info = " / vasler / 93ms / 999fps";

		ImVec2 name_size = ImGui::CalcTextSize((text).c_str());
		ImVec2 size = ImGui::CalcTextSize((text + info).c_str());

		// background.
		render::render_gradient(screen_width - size.x - 20, 10, size.x + 10, size.y + 10, Color(17, 17, 17), Color(13, 13, 13));
		render::render_outline(screen_width - size.x - 20, 10, size.x + 10, size.y + 10, Color(5, 5, 5));

		// for me: -2 for height and width.
		render::render_outline(screen_width - size.x - 19, 11, size.x + 8, size.y + 8, Color(26, 26, 26));

		// text.
		render::render_text(text, screen_width - size.x - 15, 14, features::client::menu_color, 0);
		render::render_text(info, screen_width - size.x - 15 + name_size.x, 14, Color(100, 100, 100), 0);
	}

}