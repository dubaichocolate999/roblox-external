#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "utils/color.h"
#include <string>

namespace render {

    enum text_flags {
        align_right,
        align_center
    };

    static void render_rect(double x, double y, double width, double height, const Color& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilled(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255)
        );
    }

    static void render_outline(double x, double y, double width, double height, const Color& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255)
        );
    }

    static void render_glow(double x, double y, double width, double height, const Color& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddShadowRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            15.f, ImVec2(0, 0),
            ImDrawFlags_ShadowCutOutShapeBackground, 0
        );
    }

    static void render_rect_rounded(double x, double y, double width, double height, const Color& color, int roundness) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilled(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255)
        );


    }

    static void render_outline_rounded(double x, double y, double width, double height, const Color& color, int roundness) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            roundness
        );
    }

    static void render_text(std::string text, double x, double y, const Color& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            text.c_str());
    }


    static void render_text(std::string text, double x, double y, const Color& color, int flags) {
        auto draw_list = ImGui::GetBackgroundDrawList();
        float width = ImGui::CalcTextSize(text.c_str()).x;

        // right
        if (flags & 0)
            x -= width;

        // center
        if (flags & 1)
            x -= width / 2;


        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            text.c_str());
    }

    static void render_text(std::string text, double x, double y, const Color& color, ImFont* font) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->PushTextureID(font->ContainerAtlas->TexID);

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            text.c_str());

        draw_list->PopTextureID();
    }


    static void render_text(std::string text, double x, double y, const Color& color, int flags, ImFont* font) {
        auto draw_list = ImGui::GetBackgroundDrawList();
        float width = ImGui::CalcTextSize(text.c_str()).x;

        // right
        if (flags & 0)
            x -= width;

        // center
        if (flags & 1)
            x -= width / 2;

        draw_list->PushTextureID(font->ContainerAtlas->TexID);


        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            text.c_str());

		draw_list->PopTextureID();
    }

    static void render_circle(double x, double y, float radius, const Color& color, bool filled) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        if (!filled) {
            draw_list->AddCircle(ImVec2(static_cast<float>(x), static_cast<float>(y)),
                radius,
                ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255));
        }
        else {
            draw_list->AddCircleFilled(ImVec2(static_cast<float>(x), static_cast<float>(y)),
                radius,
                ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255));
        }
    }

    static void render_gradient(double x, double y, double width, double height, const Color& color, const Color& second_color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilledMultiColor(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            ImColor(second_color.r / 255, second_color.g / 255, second_color.b / 255, second_color.a / 255),
            ImColor(second_color.r / 255, second_color.g / 255, second_color.b / 255, second_color.a / 255),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255),
            ImColor(color.r / 255, color.g / 255, color.b / 255, color.a / 255)
        );
    }


    static void render_rect(double x, double y, double width, double height, const ImColor& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilled(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            color
        );
    }

    static void render_outline(double x, double y, double width, double height, const ImColor& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            color
        );
    }

    static void render_glow(double x, double y, double width, double height, const ImColor& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddShadowRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            color,
            15.f, ImVec2(0, 0), 0.0f
        );
    }


    static void render_gradient(double x, double y, double width, double height, const ImColor& color, const ImColor& second_color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilledMultiColor(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            second_color,
            second_color,
            color, 
            color
        );
    }


    static void render_rect_rounded(double x, double y, double width, double height, const ImColor& color, int roundness) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRectFilled(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            color
        );
    }

    static void render_outline_rounded(double x, double y, double width, double height, const ImColor& color, int roundness) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddRect(
            ImVec2(static_cast<float>(x), static_cast<float>(y)),
            ImVec2(static_cast<float>(x + width), static_cast<float>(y + height)),
            color,
            roundness
        );
    }

    static void render_text(std::string text, double x, double y, const ImColor& color) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            color,
            text.c_str());
    }

    static void render_text(std::string text, double x, double y, const ImColor& color, int flags) {
        auto draw_list = ImGui::GetBackgroundDrawList();
        float width = ImGui::CalcTextSize(text.c_str()).x;

        // right
        if (flags & 0)
            x -= width;

        // center
        if (flags & 1)
            x -= width / 2;

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            color,
            text.c_str());
    }

    static void render_text(std::string text, double x, double y, const ImColor& color, ImFont* font) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        draw_list->PushTextureID(font->ContainerAtlas->TexID);

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            color,
            text.c_str());

		draw_list->PopTextureID();
    }

    static void render_text(std::string text, double x, double y, const ImColor& color, int flags, ImFont* font) {
        auto draw_list = ImGui::GetBackgroundDrawList();
        float width = ImGui::CalcTextSize(text.c_str()).x;

        // right
        if (flags & 0)
            x -= width;

        // center
        if (flags & 1)
            x -= width / 2;

        draw_list->PushTextureID(font->ContainerAtlas->TexID);

        draw_list->AddText(ImVec2(static_cast<float>(x + 1), static_cast<float>(y + 1)),
            ImColor(0.1f, 0.1f, 0.1f),
            text.c_str());

        draw_list->AddText(ImVec2(static_cast<float>(x), static_cast<float>(y)),
            color,
            text.c_str());

        draw_list->PopTextureID();
    }


    static void render_circle(double x, double y, float radius, const ImColor& color, bool filled) {
        auto draw_list = ImGui::GetBackgroundDrawList();

        if (!filled) {
            draw_list->AddCircle(ImVec2(static_cast<float>(x), static_cast<float>(y)),
                radius,
                color);
        }
        else {
            draw_list->AddCircleFilled(ImVec2(static_cast<float>(x), static_cast<float>(y)),
                radius,
                color);
        }
    }
}

struct rect {
    int x;
    int y;
    int w;
    int h;
};