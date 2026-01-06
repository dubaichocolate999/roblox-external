#pragma once
#include "framework/settings/functions.h"
#include <windows.h>
#include "oxorany/oxorany.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_freetype.h"
#include <d3d11.h>
#include <dxgi.h>
#include <thread>
#include "features/menu/menu.h"
#include "utils/color.h"
#include "configuration/config.h"
#include "game/gameloop.h"
#include <dwmapi.h>
#include "features/overlay/fonts/fonts.h"

LRESULT WINAPI wndproc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

inline ID3D11Device* device = nullptr;
inline ID3D11DeviceContext* device_context = nullptr;
inline IDXGISwapChain* swap_chain = nullptr;
inline ID3D11RenderTargetView* render_target_view = nullptr;

namespace overlay {
    inline static bool visible = true;
    inline static bool finished = false;

    // window
    void initialize();

    // imgui
    void render();
    void setup();
    void begin_render();
    void end_render();

    // devices
    bool create_device();
    void clear_device();
    void cleanup_render_target();
    void create_render_target();
}