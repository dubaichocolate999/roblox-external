#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <windows.h>
#include <winhttp.h>
#include <nlohmann/json.hpp>
#pragma comment(lib, "winhttp.lib")
#include "oxorany/oxorany_include.h"

namespace offsets
{
    inline uintptr_t Team = 0;
    inline uintptr_t ModelInstance = 0;
    inline uintptr_t Primitive = 0;
    inline uintptr_t Position = 0; // basepart, position
    inline uintptr_t ViewMatrix = 0;
    inline uintptr_t JumpPower = 0;
    inline uintptr_t WalkSpeed = 0;
    inline uintptr_t WalkSpeedCheck = 0;
    inline uintptr_t Health = 0;
    inline uintptr_t FOV = 0; // camera, fieldofview
    inline uintptr_t FakeDataModelPointer = 0; // fakedatamodel, pointer
    inline uintptr_t FakeDataModelToDataModel = 0;
    inline uintptr_t VisualEnginePointer = 0; // visualengine, pointer
    inline uintptr_t GameId = 0;
    inline uintptr_t Camera = 0; // workspace, currentcamera
    inline uintptr_t LocalPlayer = 0;
    inline uintptr_t TeamColor = 0; // team, brickcolor
    inline uintptr_t NameSize = 0; // bytecode size
    inline uintptr_t Name = 0;
    inline uintptr_t Children = 0; // instance, childrenstart
    inline uintptr_t ChildrenEnd = 0;
    inline uintptr_t ClassDescriptor = 0;
    inline uintptr_t Text = 0;
    inline uintptr_t FogColor = 0;
    inline uintptr_t OutdoorAmbient = 0;
    inline uintptr_t ClockTime = 0;
	inline uintptr_t GravityContainer = 0; // workspace, gravitycontainer
	inline uintptr_t Gravity = 0; // workspace, gravity
    inline uintptr_t HumanoidState = 0;
    inline uintptr_t CanCollide = 0;
    inline uintptr_t PhysicsSenderMaxBandwidthBps = 0x5f3decc;
    inline uintptr_t Value = 0;
    inline uintptr_t RigType = 0;

    inline void auto_update() {
        const std::wstring host = L"imtheo.lol";
        const std::wstring path = L"/Offsets/OffsetsHex.json";
        std::string response_string;

        HINTERNET hSession = WinHttpOpen(L"OffsetUpdater/1.0",
            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
            NULL, NULL, 0);
        if (!hSession) return;

        HINTERNET hConnect = WinHttpConnect(hSession, host.c_str(),
            INTERNET_DEFAULT_HTTPS_PORT, 0);
        if (!hConnect) {
            WinHttpCloseHandle(hSession);
            return;
        }

        HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"GET", path.c_str(),
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            WINHTTP_FLAG_SECURE);
        if (!hRequest) {
            WinHttpCloseHandle(hConnect);
            WinHttpCloseHandle(hSession);
            return;
        }

        BOOL success = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
            WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
            WinHttpReceiveResponse(hRequest, NULL);

        if (success) {
            DWORD dwSize = 0;
            do {
                if (!WinHttpQueryDataAvailable(hRequest, &dwSize) || !dwSize) break;

                std::string buffer(dwSize, 0);
                DWORD dwDownloaded = 0;

                if (!WinHttpReadData(hRequest, &buffer[0], dwSize, &dwDownloaded)) break;
                response_string.append(buffer, 0, dwDownloaded);
            } while (dwSize > 0);
        }

        WinHttpCloseHandle(hRequest);
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);

        if (response_string.empty()) return;

        try {
            auto j = nlohmann::json::parse(response_string, nullptr, false);
            if (j.is_discarded()) return;

            auto offsets = j["Offsets"];
            auto hex = [](const std::string& s) { return std::stoull(s, nullptr, 16); };

            offsets::Team = hex(offsets["Player"]["Team"]);
            offsets::ModelInstance = hex(offsets["Player"]["ModelInstance"]);
            offsets::Primitive = hex(offsets["BasePart"]["Primitive"]);
            offsets::Position = hex(offsets["BasePart"]["Position"]);
            offsets::ViewMatrix = hex(offsets["VisualEngine"]["ViewMatrix"]);
            offsets::JumpPower = hex(offsets["Humanoid"]["JumpPower"]);
            offsets::WalkSpeed = hex(offsets["Humanoid"]["Walkspeed"]);
            offsets::WalkSpeedCheck = hex(offsets["Humanoid"]["WalkspeedCheck"]);
            offsets::Health = hex(offsets["Humanoid"]["Health"]);
            offsets::FOV = hex(offsets["Camera"]["FieldOfView"]);
            offsets::FakeDataModelPointer = hex(offsets["FakeDataModel"]["Pointer"]);
            offsets::FakeDataModelToDataModel = hex(offsets["FakeDataModel"]["RealDataModel"]);
            offsets::VisualEnginePointer = hex(offsets["VisualEngine"]["Pointer"]);
            offsets::GameId = hex(offsets["DataModel"]["GameId"]);
            offsets::Camera = hex(offsets["Workspace"]["CurrentCamera"]);
            offsets::LocalPlayer = hex(offsets["Player"]["LocalPlayer"]);
            offsets::TeamColor = hex(offsets["Team"]["BrickColor"]);
            offsets::NameSize = hex(offsets["ByteCode"]["Pointer"]);
            offsets::Name = hex(offsets["Instance"]["Name"]);
            offsets::Children = hex(offsets["Instance"]["ChildrenStart"]);
            offsets::ChildrenEnd = hex(offsets["Instance"]["ChildrenEnd"]);
            offsets::ClassDescriptor = hex(offsets["Instance"]["ClassDescriptor"]);
            offsets::Text = hex(offsets["GuiObject"]["Text"]);
            offsets::FogColor = hex(offsets["Lighting"]["FogColor"]);
            offsets::OutdoorAmbient = hex(offsets["Lighting"]["OutdoorAmbient"]);
            offsets::ClockTime = hex(offsets["Lighting"]["ClockTime"]);
            offsets::GravityContainer = hex(offsets["Workspace"]["GravityContainer"]);
            offsets::Gravity = hex(offsets["Workspace"]["Gravity"]);
            offsets::HumanoidState = hex(offsets["Humanoid"]["HumanoidState"]);
            offsets::CanCollide = hex(offsets["PrimitiveFlags"]["CanCollide"]);
            offsets::Value = hex(offsets["Misc"]["Value"]);
            offsets::RigType = hex(offsets["Humanoid"]["RigType"]);
        }
        catch (const std::exception& e) {
            return;
        }
    }


}