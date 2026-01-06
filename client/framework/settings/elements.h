#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <string>
#include "imgui.h"

class c_elements
{
public:

	struct
	{
		ImVec2 window_padding{ 14, 7 };
		ImVec2 padding{ 7, 7 };
		ImVec2 spacing{ 7, 7 };
	} content;

	struct
	{
		ImVec2 checkbox_size{ 17, 17 };
		float slider_height{ 15 };
		float dropdown_height{ 17 };
		ImVec2 color_size{ 24, 14 };
		ImVec2 key_size{ 32, 16 };
		ImVec2 padding{ 4, 7 };
		ImVec2 spacing{ 7, 7 };
	} widgets;

	struct
	{
		ImVec2 size{ 30, 30 };
		float height{ 20 };
	} section;
};

inline c_elements* elements = new c_elements();