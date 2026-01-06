#include "menu.h"
#include "utils/driver/driver.h"
#include "utils/offsets.h"

void menu::draw() {
    menu::tabs();
   
    ImGui::Separator();

    // all of our tabs..
    switch (current_tab) {
        // the combat tab.
        case tab::combat: {
            if(ImGui::BeginChild("aimbot", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f - 5, 0), true)) {
                ImGui::Checkbox(oxorany("aimbot"), &features::combat::aimbot);
                ImGui::SliderFloat(oxorany("fov"), &settings::aimbot::fov, 1.0f, 180.0f, "%.1f");

                const char* target_hitboxes[] = { "head", "upper torso", "torso" };
                ImGui::Combo("hitbox", reinterpret_cast<int*>(&settings::aimbot::hitboxes),
                    target_hitboxes, IM_ARRAYSIZE(target_hitboxes));
                ImGui::Checkbox(oxorany("target teammates"), &settings::aimbot::target_teammates);
                ImGui::SliderFloat(oxorany("smoothing"), &settings::aimbot::smoothing, 1.0f, 100.0f, "%.1f");
                ImGui::SliderFloat(oxorany("vertical smoothing"), &settings::aimbot::vertical_smoothing, 1.0f, 100.0f, "%.1f");

                const char* movement[] = { "instant", "exponential", "curved" };
                ImGui::Combo("movement", reinterpret_cast<int*>(&settings::aimbot::movement),
                    movement, IM_ARRAYSIZE(movement));
                ImGui::SliderFloat(oxorany("interpolation delta"), &settings::aimbot::interpolation_delta, 0.0f, 1.0f, "%.1f");

                ImGui::Checkbox(oxorany("dynamic fov"), &settings::aimbot::dynamic_fov);

                ImGui::Checkbox(oxorany("visualize"), &settings::aimbot::visualize);
                if (settings::aimbot::visualize) {
                    ImGui::SameLine();
                    ImGui::ColorEdit3(oxorany("fov color"), (float*)&settings::aimbot::fov_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }

                ImGui::EndChild();
            }
            break;
        }
        // misc features.                
        case tab::misc: {
            ImGui::Checkbox(oxorany("walksped"), &features::misc::walkspeed);
            if (features::misc::walkspeed) {
                ImGui::SliderFloat(oxorany("speed"), &settings::walkspeed::walkspeed, 1.0f, 200.0f, "%.1f");
            }

            ImGui::Checkbox(oxorany("jump height"), &features::misc::jump); 
            if (features::misc::jump) {
                ImGui::SliderFloat(oxorany("height"), &settings::jump_height::height, 1.0f, 200.0f, "%.1f");
            }

            ImGui::Checkbox(oxorany("gravity"), &features::misc::gravity);
            if (features::misc::gravity) {
                ImGui::SliderFloat(oxorany("gravity acceleration"), &settings::gravity::gravity, 1.0f, 250.0f, "%.1f");
            }

            ImGui::Checkbox(oxorany("desync"), &features::misc::desync);
            ImGui::Checkbox(oxorany("antistomp"), &features::misc::antistomp);
            break;
        }
        // world features              
        case tab::world: {
            if(ImGui::BeginChild("world left", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f - 5, 0), true)) {
                ImGui::Checkbox(oxorany("fog changer"), &features::world::fog_changer);
                if (features::world::fog_changer) {
                    ImGui::SameLine();
                    ImGui::ColorEdit3(oxorany("color"), (float*)&settings::fog_changer::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }

                ImGui::Checkbox(oxorany("ambience"), &features::world::ambience);
                if (features::world::ambience) {
                    ImGui::SameLine();
                    ImGui::ColorEdit3(oxorany("color"), (float*)&settings::ambience::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                }

                ImGui::EndChild();
            }
            if (ImGui::BeginChild("world right", ImVec2(0, 0), true)) {
                ImGui::EndChild();
            }
            break;
        }
        // visual features.
        case tab::visuals: {
            if (ImGui::BeginChild("esp child", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f - 5, 0), true)) {
                ImGui::Checkbox(oxorany("enabled"), &features::visuals::esp);
                ImGui::Checkbox(oxorany("teammates"), &settings::esp::teammates);

                ImGui::Checkbox(oxorany("name"), &settings::esp::name);
                ImGui::SameLine();
                ImGui::ColorEdit3(oxorany("name color"), (float*)&settings::esp::name_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                ImGui::Checkbox(oxorany("box"), &settings::esp::box);
                ImGui::SameLine();
                ImGui::ColorEdit3(oxorany("box color"), (float*)&settings::esp::box_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                ImGui::Checkbox(oxorany("health"), &settings::esp::health);

                const char* color_modes[] = { "static", "gradient", "health based" };
                ImGui::Combo("health color", reinterpret_cast<int*>(&settings::esp::health_mode),
                    color_modes, IM_ARRAYSIZE(color_modes));

                switch (settings::esp::health_mode) {
                case health_color::static_color:
                    ImGui::ColorEdit3(oxorany("first color"), (float*)&settings::esp::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    break;
                case health_color::gradient:
                    ImGui::ColorEdit3(oxorany("first color"), (float*)&settings::esp::color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    ImGui::SameLine();
                    ImGui::ColorEdit3(oxorany("second color"), (float*)&settings::esp::second_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                    break;
                }

                ImGui::Checkbox(oxorany("head dot"), &settings::esp::dot);
                ImGui::SameLine();
                ImGui::ColorEdit3(oxorany("dot color"), (float*)&settings::esp::dot_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

                ImGui::EndChild();

            }

            ImGui::SameLine();

            if (ImGui::BeginChild("visuals right", ImVec2(0, 0), true)) {
                ImGui::Checkbox(oxorany("fov"), &features::visuals::fov_changer);
                ImGui::SliderFloat(oxorany("fov val"), &settings::fov_changer::fov, 1.0f, 120.0f, "%.1f");
                ImGui::EndChild();
            }
            break;
        }
        case tab::whitelist: {
            ImGui::Checkbox(oxorany("whitelist test"), &features::combat::aimbot);
            break;
        }
        case tab::client: {
            if (ImGui::BeginChild("client child", ImVec2(ImGui::GetContentRegionAvail().x * 0.5f - 5, 0), true)) {
                ImGui::ColorEdit3(oxorany("menu color"), (float*)&features::client::menu_color, ImGuiColorEditFlags_NoInputs);
                ImGui::Checkbox(oxorany("obs streamproof"), &features::client::streamproof);
                ImGui::Checkbox(oxorany("v-sync"), &features::client::vsync);
                ImGui::Checkbox(oxorany("watermark"), &features::client::watermark);
                ImGui::EndChild();
            }

            ImGui::SameLine();
            
            if (ImGui::BeginChild("config child", ImVec2(0, 0), true)) {
                config::get_configs();

                std::vector<const char*> items;
                items.reserve(config::files_cfg.size());

                for (const auto& item : config::files_cfg)
                    items.push_back(item.c_str());

                static int selected_index = -1;
                ImGui::ListBox("configs", &selected_index, items.data(), static_cast<int>(items.size()));

                ImGui::InputText("name", config_name, sizeof(config_name));

                if (ImGui::Button("save configuration", ImVec2(200, 25))) {
                    if (strlen(config_name) > 0) {
                        config::save_configuration(config_name);
                        config::get_configs();
                    }
                    else if (selected_index >= 0 && selected_index < config::files_cfg.size()) {
                        std::string config_to_load = config::files_cfg[selected_index];
                        config::save_configuration(config_to_load.c_str());
                        config::get_configs();
                    }
                }

                if (ImGui::Button("load configuration", ImVec2(200, 25))) {
                    if (selected_index >= 0 && selected_index < config::files_cfg.size()) {
                        std::string config_to_load = config::files_cfg[selected_index];
                        config::load_configuration(config_to_load.c_str());
                    }
                }

                ImGui::EndChild();
            }
            break;
        }
    }
}

void menu::tabs() {
    if (ImGui::Button(oxorany("combat"), ImVec2(100, 20)))
        current_tab = tab::combat;

    ImGui::SameLine();

    if (ImGui::Button(oxorany("misc"), ImVec2(100, 20)))
        current_tab = tab::misc;

    ImGui::SameLine();

    if (ImGui::Button(oxorany("world"), ImVec2(100, 20)))
        current_tab = tab::world;

    ImGui::SameLine();

    if (ImGui::Button(oxorany("visuals"), ImVec2(100, 20)))
        current_tab = tab::visuals;

    ImGui::SameLine();

    if (ImGui::Button(oxorany("whitelist"), ImVec2(100, 20)))
        current_tab = tab::whitelist;

    ImGui::SameLine();

    if (ImGui::Button(oxorany("client"), ImVec2(100, 20)))
        current_tab = tab::client;
}