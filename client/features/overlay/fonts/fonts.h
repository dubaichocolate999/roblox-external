#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui.h"
#include "imgui_freetype.h"

namespace fonts {
	// cfgs
	static ImFontConfig esp_cfg;

	inline ImFont* esp_health = nullptr;

	void load();
	void cfgs();
}