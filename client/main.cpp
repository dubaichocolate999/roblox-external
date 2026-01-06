#include <iostream>
#include <windows.h>
#include "main.h"

/*
* not COMMENTING ANYTHING ANYMORE!!! FUCK THAT
*/
int main()
{
    // creates a console.
    misc::initialize_console();

    // automatically updates roblox's offsets, so we don't have to do them manually.
    offsets::auto_update();

    std::string title = oxorany("astral external");

    // sets the console title.
    SetConsoleTitleA(title.c_str());

    // commented until needed.
    // just some logs for the user
    // misc::print_spinner(oxorany("initializing into roblox."), 3000, 100);

    std::string config = config::get_path_string();

    // make sure that the path doesn't already exist, creating a new folder for no reason is stupid.
    if (!std::filesystem::is_directory(config)) {
        std::filesystem::create_directories(config);
        printf(oxorany("successfully created at: %s\n"), config.c_str());
    }
    else {
        // if config already exists, don't make a new directory.
        printf(oxorany("config already exists"));
        system(oxorany("cls"));
    }

    int attempt = 0;
    
    // if the process hasn't been set, try to set it.
    while (driver::proc_id == 0) {
        printf(oxorany("waiting for roblox to start. [attempt %d]\n"), attempt);

        // tries to find roblox's process.
        driver::proc_id = driver::find_process(oxorany(L"RobloxPlayerBeta.exe"));

        // wait 2 seconds before doing this again.
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        // adds +1 to the attempt integer.
        attempt++;
        system(oxorany("cls"));
    }

    // if the driver somehow doesn't initialize. (should be impossible, unless someone is cracking.)
    if (!driver::initialize()) {
        printf(oxorany("failed to initialize driver. error: %d\n"), GetLastError());
        return 1;
    }

    auto module = driver::get_module(oxorany(L"RobloxPlayerBeta.exe"));
    if (module == 0) {
        printf(oxorany("failed to set module.\n"));
        return 1;
    }

    overlay::render();
    gameloop::cache_loop();

    return 0;
}