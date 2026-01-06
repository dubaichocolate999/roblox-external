#include "overlay.h"

HWND hwnd = nullptr;

void overlay::render() {
    overlay::initialize();
    overlay::create_device();
    overlay::setup();

    bool visible = true;

    while (!overlay::finished) {

        if (GetAsyncKeyState(VK_RSHIFT) & 1)
            visible = !visible;

        // obs streamproof.
        if (features::client::streamproof)
            SetWindowDisplayAffinity(hwnd, 0x11);
        else
            SetWindowDisplayAffinity(hwnd, 0x00);

        overlay::begin_render();
        if (!visible) {
            gameloop::slow_loop();
            gameloop::initialization();
        }

        if (visible)
        {
            ImGui::SetNextWindowSize({ 650, 500 });
            ImGui::Begin(oxorany("astral"),
                nullptr,
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoResize
            );
            menu::draw();
            gui->render();

            ImGui::End();

            LONG ex_style = GetWindowLong(hwnd, GWL_EXSTYLE);
            if (ex_style & WS_EX_TRANSPARENT)
            {
                ex_style &= ~WS_EX_TRANSPARENT;
                SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }
        else
        {
            LONG ex_style = GetWindowLong(hwnd, GWL_EXSTYLE);
            if ((ex_style & WS_EX_TRANSPARENT) == 0)
            {
                ex_style |= WS_EX_TRANSPARENT | WS_EX_LAYERED;
                SetWindowLong(hwnd, GWL_EXSTYLE, ex_style);
                SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
            }
        }

        overlay::end_render();

        std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }

}

void overlay::begin_render() {
    MSG msg;

    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT) {
            overlay::finished = true;
            return;
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void overlay::create_render_target() {
    ID3D11Texture2D* back_buffer = nullptr;
    swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back_buffer);

    if (back_buffer) {
        device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
        back_buffer->Release();
    }
}

void overlay::cleanup_render_target() {
    if (render_target_view) {
        render_target_view->Release();
        render_target_view = nullptr;
    }
}

void overlay::end_render() {
    ImGui::EndFrame();

    const float clear_color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
    device_context->ClearRenderTargetView(render_target_view, clear_color);

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    swap_chain->Present(features::client::vsync ? 1 : 0, 0);
}


void overlay::initialize() {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, wndproc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, oxorany(L"Calculator"), NULL };
    RegisterClassEx(&wc);

    hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        wc.lpszClassName, oxorany(L"Calculator"),
        WS_POPUP,
        0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
        NULL, NULL, wc.hInstance, NULL
    );

    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
}

void overlay::setup() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetStyle().Alpha = 1.0f;

    ImGuiIO& io = ImGui::GetIO();
    ImFontConfig cfg;
    cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags::ImGuiFreeTypeBuilderFlags_ForceAutoHint;
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 14.0f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
	var->font.tahoma = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 14.0f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    ImFontConfig esp_cfg;
    esp_cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_Monochrome | ImGuiFreeTypeBuilderFlags_MonoHinting;
    esp_cfg.OversampleH = esp_cfg.OversampleV = 5;
    esp_cfg.PixelSnapH = false;
    esp_cfg.RasterizerMultiply = 1.2f;
    fonts::esp_health = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 11.0f, &esp_cfg, io.Fonts->GetGlyphRangesCyrillic());

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(device, device_context);
}

bool overlay::create_device() {
    IDXGIFactory* factory = nullptr;
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
        return false;

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;

    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0,
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createDeviceFlags,
        featureLevelArray,
        2,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        &featureLevel,
        &device_context
    );

    if (factory) factory->Release();

    if (FAILED(hr))
        return false;

    create_render_target();
    return true;
}


void overlay::clear_device() {
    cleanup_render_target();

    if (swap_chain) {
        swap_chain->Release();
        swap_chain = nullptr;
    }

    if (device_context) {
        device_context->Release();
        device_context = nullptr;
    }

    if (device) {
        device->Release();
        device = nullptr;
    }
}


LRESULT WINAPI wndproc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(h_wnd, msg, w_param, l_param))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (w_param == SIZE_MINIMIZED)
            return 0;

        if (device != nullptr)
        {
            overlay::cleanup_render_target();
            swap_chain->ResizeBuffers(0, (UINT)LOWORD(l_param), (UINT)HIWORD(l_param), DXGI_FORMAT_UNKNOWN, 0);
            overlay::create_render_target();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((w_param & 0xfff0) == SC_KEYMENU)
            return 0;

        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }

    return ::DefWindowProcW(h_wnd, msg, w_param, l_param);
}