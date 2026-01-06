#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

class c_colors
{
public:
	ImColor accent{ 255, 100, 150 };

	struct
	{
		ImColor background_one{ 13, 13, 13 };
		ImColor background_two{ 17, 17, 17 };
		ImColor stroke{ 26, 26, 26 };
	} window;

	struct
	{
		ImColor stroke_two{ 36, 36, 36 };
		ImColor text{ 230, 230, 230 };
		ImColor text_inactive{ 150, 150, 150 };
	} widgets;
};

inline c_colors* clr = new c_colors();