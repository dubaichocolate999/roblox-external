#include "fonts.h"

void fonts::load() {
	auto& io = ImGui::GetIO();
	fonts::esp_health = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 9.0f, &fonts::esp_cfg, io.Fonts->GetGlyphRangesCyrillic());
}

void fonts::cfgs() {
	fonts::esp_cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
	fonts::esp_cfg.OversampleH = fonts::esp_cfg.OversampleV = 5;
	fonts::esp_cfg.PixelSnapH = false;
	fonts::esp_cfg.RasterizerMultiply = 1.2f;
}