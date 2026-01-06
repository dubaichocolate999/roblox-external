#pragma once

#include <filesystem>
#include <string>
#include "oxorany/oxorany_include.h"
#include "nlohmann/json.hpp"
#include "features/feature.h"
#include <fstream>
#include <Windows.h>

namespace config {
    static std::vector<std::string> files_cfg;

    // gets the path as an actual path.
    static std::filesystem::path get_path() {
        std::string path;
        char* userpath = nullptr;
        size_t sz = 0;

        if (_dupenv_s(&userpath, &sz, oxorany("USERPROFILE")) == 0 && userpath != nullptr) {
            path = userpath;
            free(userpath);
        }

        // returns the path as a path...
        return std::filesystem::path(path) / oxorany("astral");
    }

    // gets the path as a string.
    static std::string get_path_string() {
        std::string path;
        char* userpath = nullptr;
        size_t sz = 0;

        if (_dupenv_s(&userpath, &sz, oxorany("USERPROFILE")) == 0 && userpath != nullptr) {
            path = userpath;
            free(userpath);
        }

        // returns the path as a string.
        return path + oxorany("\\astral");
    }

    // saves the configuration to the path.
    static void save_configuration(const std::string& name) {
        nlohmann::json json;

        // every feature and setting.
        json[oxorany("aimbot")] = features::combat::aimbot;
        json[oxorany("walkspeed")] = features::misc::walkspeed;
        json[oxorany("jump_height")] = features::misc::jump;
        json[oxorany("fov_changer")] = features::visuals::fov_changer;
        json[oxorany("streamproof")] = features::client::streamproof;
        json[oxorany("watermark")] = features::client::watermark;
        json[oxorany("esp")] = features::visuals::esp;
        json[oxorany("vsync")] = features::client::vsync;

        // settings
        json[oxorany("aimbot_fov")] = settings::aimbot::fov;
        json[oxorany("walkspeed_speed")] = settings::walkspeed::walkspeed;
        json[oxorany("fov_changer_fov")] = settings::fov_changer::fov;
        json[oxorany("jump_height_height")] = settings::jump_height::height;

        json[oxorany("name_tag")] = settings::esp::name;
        json[oxorany("name_color")] = {
                settings::esp::name_color.Value.x,
                settings::esp::name_color.Value.y,
                settings::esp::name_color.Value.z,
                settings::esp::name_color.Value.w
        };

        json[oxorany("box_outline")] = settings::esp::box;
        json[oxorany("box_color")] = {
                settings::esp::box_color.Value.x,
                settings::esp::box_color.Value.y,
                settings::esp::box_color.Value.z,
                settings::esp::box_color.Value.w
        };

        json[oxorany("health_bar")] = settings::esp::health;

        // the actual file.
        std::ofstream ofs(config::get_path() / (name + oxorany(".json")));

        // writes it to a file with an indent of 4.
        if (ofs)
            ofs << json.dump(4);
    }

    // loads the config you have chosen.
    static void load_configuration(const std::string& name) {
        nlohmann::json json;

        std::ifstream ifs(config::get_path() / (name + oxorany(".json")));

        // better checks to make sure it wont crash.
        if (!ifs.is_open())
            return;

        try {
            nlohmann::json json;
            ifs >> json;

            // every feature and setting.
            features::combat::aimbot = json[oxorany("aimbot")].get<bool>();
            features::misc::walkspeed = json[oxorany("walkspeed")].get<bool>();
            features::misc::jump = json[oxorany("jump_height")].get<bool>();
            features::visuals::fov_changer = json[oxorany("fov_changer")].get<bool>();
            features::client::streamproof = json[oxorany("streamproof")].get<bool>();
            features::client::watermark = json[oxorany("watermark")].get<bool>();
            features::visuals::esp = json[oxorany("esp")].get<bool>();
            features::client::vsync = json[oxorany("vsync")].get<bool>();

            settings::aimbot::fov = json[oxorany("aimbot_fov")].get<float>();
            settings::walkspeed::walkspeed = json[oxorany("walkspeed_speed")].get<float>();
            settings::fov_changer::fov = json[oxorany("fov_changer_fov")].get<float>();
            settings::jump_height::height = json[oxorany("jump_height_height")].get<float>();

            settings::esp::name = json[oxorany("name_tag")].get<bool>();
            settings::esp::box = json[oxorany("box_outline")].get<bool>();
            settings::esp::health = json[oxorany("health_bar")].get<bool>();

   
            auto name_color_array = json[oxorany("name_color")];
            settings::esp::name_color.Value.x = name_color_array[0].get<float>();
            settings::esp::name_color.Value.y = name_color_array[1].get<float>();
            settings::esp::name_color.Value.z = name_color_array[2].get<float>();
            settings::esp::name_color.Value.w = name_color_array[3].get<float>();

            auto box_color_array = json[oxorany("box_color")];
            settings::esp::box_color.Value.x = box_color_array[0].get<float>();
            settings::esp::box_color.Value.y = box_color_array[1].get<float>();
            settings::esp::box_color.Value.z = box_color_array[2].get<float>();
            settings::esp::box_color.Value.w = box_color_array[3].get<float>();
        }
        catch (const std::exception& e) {
            // if any errors occur, such as something not existing. this will print.
            printf(oxorany("an error has occured: %s"), e);
        }

        // closes off the file and stops reading it.
        ifs.close();
    }

    static void get_configs()
    {
        WIN32_FIND_DATAA ffd;
        std::string search_path = get_path_string() + "\\*.json";
        HANDLE hFind = FindFirstFileA(search_path.c_str(), &ffd);

        if (hFind == INVALID_HANDLE_VALUE) {
            return;
        }

        files_cfg.clear();

        do {
            if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::string file_name = ffd.cFileName;

                if (file_name.size() < 5)
                    continue;

                if (file_name.substr(file_name.size() - 5) != ".json")
                    continue;

                file_name.erase(file_name.size() - 5);
                files_cfg.push_back(file_name);
            }
        } while (FindNextFileA(hFind, &ffd)); 

        FindClose(hFind);
    }
}