#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "framework/settings/functions.h"
#include "oxorany/oxorany.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "features/feature.h"
#include "configuration/config.h"

namespace menu {
    // config
    static int slot_cfg = 0;
    static char config_name[256];

    enum class tab {
        combat,
        misc,
        world,
        visuals,
        whitelist,
        client
    };

    inline static tab current_tab = tab::combat;
    void draw();
    void tabs();
}