#include "settings/functions.h"
#include <Windows.h>

void c_gui::render()
{
	gui->set_next_window_pos(ImVec2(GetIO().DisplaySize.x / 2 - var->window.width / 2, 20));
	gui->set_next_window_size(ImVec2(var->window.width, elements->section.size.y + var->window.spacing.y * 2 - 1));
	gui->push_style_var(ImGuiStyleVar_Alpha, var->gui.menu_alpha);

	gui->begin("astral", nullptr, var->window.main_flags);
	{
		const ImVec2 pos = GetWindowPos();
		const ImVec2 size = GetWindowSize();
		ImDrawList* draw_list = GetWindowDrawList();
		ImGuiStyle* style = &GetStyle();

		{
			style->WindowPadding = var->window.padding;
			style->PopupBorderSize = var->window.border_size;
			style->WindowBorderSize = var->window.border_size;
			style->ItemSpacing = var->window.spacing;
			style->ScrollbarSize = var->window.scrollbar_size;
		}

		{
			gui->set_next_window_size_constraints(ImVec2(650, 500), GetIO().DisplaySize);
			gui->begin("astral.uno", nullptr, var->window.flags);
			{
				draw->window_decorations();

				{
					static int subtabs;
					gui->set_cursor_pos(elements->content.window_padding + ImVec2(0, var->window.titlebar));
					gui->begin_group();
					{
						gui->sub_section("combat", 0, subtabs, 4);
						gui->sub_section("misc", 1, subtabs, 4);
						gui->sub_section("world", 2, subtabs, 4);
						gui->sub_section("visuals", 3, subtabs, 4);
						gui->sub_section("whitelist", 4, subtabs, 5);
						gui->sub_section("client", 5, subtabs, 6);
					}
					gui->end_group();

					gui->set_cursor_pos(elements->content.window_padding + ImVec2(0, var->window.titlebar + elements->section.height - 1));
					gui->begin_content();
					{
						gui->begin_group();
						{
							gui->begin_child("Aimbot", 2, 1);
							{
								static bool enabled = true;
								static int key;
								static int mode;
								gui->checkbox("Enabled", &enabled, &key, &mode);

								static int fov = 90;
								gui->slider_int("Field Of View", &fov, 0, 100);

								static int fov_type = 0;
								const char* fov_type_items[2] = { "Static", "Dynamic" };
								gui->dropdown("fov type", &fov_type, fov_type_items, IM_ARRAYSIZE(fov_type_items), true);

								static float horizontal = 30;
								gui->slider_float("Horizontal Smoothing", &horizontal, 0, 100);

								static float vertical = 12;
								gui->slider_float("Vertical Smoothing", &vertical, 0, 100);

								static std::vector<int> checks = { 1, 1, 1 };
								const char* checks_items[3] = { "Team Check", "Alive Check", "Enemy Check" };
								gui->multi_dropdown("Checks", checks, checks_items, IM_ARRAYSIZE(checks_items));

								static std::vector<int> hitboxes = { 1, 0, 1, 0, 1, 0 };
								const char* hitboxes_items[6] = { "Head", "Neck", "Stomach", "Body", "Arms", "Legs" };
								gui->multi_dropdown("Hitboxes", hitboxes, hitboxes_items, IM_ARRAYSIZE(hitboxes_items));

								static float menu_accent[4] = { clr->accent.Value.x, clr->accent.Value.y, clr->accent.Value.z, 1.f };
								if (gui->label_color_edit("Menu Accent", menu_accent, false))
								{
									clr->accent.Value.x = menu_accent[0];
									clr->accent.Value.y = menu_accent[1];
									clr->accent.Value.z = menu_accent[2];
								}

								static bool randomize = false;
								gui->checkbox("Randomize Position", &randomize);

								static int hitscan_type = 0;
								const char* hitscan_type_items[2] = { "Mouse", "Distance" };
								gui->dropdown("Hitscan Type", &hitscan_type, fov_type_items, IM_ARRAYSIZE(fov_type_items));

								static bool readjustment = false;
								static int rkey;
								static int rmode;
								gui->checkbox("Readjustment", &readjustment, &rkey, &rmode);

								static bool deadzone = true;
								gui->checkbox("Dead Zone", &deadzone);

								static float dzone = 44;
								gui->slider_float("dzone", &dzone, 0, 100, true);

								static bool stutter = true;
								gui->checkbox("Stutter", &stutter);

								static float stslider = 25;
								gui->slider_float("stslider", &stslider, 0, 100, true, "%.1ft");
							}
							gui->end_child();
						}
						gui->end_group();

						gui->sameline();

						gui->begin_group();
						{
							gui->begin_child("Trigger Assist", 2, 2);
							{
								static bool enabled = true;
								static int key;
								static int mode;
								gui->checkbox("Enabled", &enabled, &key, &mode);

								static int delay = 15;
								gui->slider_int("Delay", &delay, 0, 500, false, "%dms");

								static int interval = 75;
								gui->slider_int("Interval", &interval, 0, 1000, false, "%dms");

								static std::vector<int> checks = { 1, 1, 1 };
								const char* checks_items[3] = { "Team Check", "Alive Check", "Enemy Check" };
								gui->multi_dropdown("Checks", checks, checks_items, IM_ARRAYSIZE(checks_items));

								static std::vector<int> hitboxes = { 1, 0, 1, 0, 1, 0 };
								const char* hitboxes_items[6] = { "Head", "Neck", "Stomach", "Body", "Arms", "Legs" };
								gui->multi_dropdown("Hitboxes", hitboxes, hitboxes_items, IM_ARRAYSIZE(hitboxes_items));

								static bool readjustment = false;
								static int rkey;
								static int rmode;
								gui->checkbox("Readjustment", &readjustment, &rkey, &rmode);
							}
							gui->end_child();

							gui->begin_child("Misc", 2, 2);
							{
								static bool cursor = true;
								gui->checkbox("Cursor Offset", &cursor);

								static int x = 50;
								gui->slider_int("offsetx", &x, 0, 100, true, "%dpx");

								static int y = 50;
								gui->slider_int("offsety", &y, 0, 100, true, "%dpx");

								gui->label_keybind("MENU KEY", &var->gui.menu_key, 0);
							}
							gui->end_child();
						}
						gui->end_group();
					}
					gui->end_content();
				}

			}
			gui->end();
		}

		var->window.width = GetCurrentWindow()->ContentSize.x + style->ItemSpacing.x;

		if (IsMouseHoveringRect(pos, pos + size))
			SetWindowFocus();
	}
	gui->end();
	gui->pop_style_var();
}