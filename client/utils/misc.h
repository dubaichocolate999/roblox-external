#pragma once

// Everything miscellaneous.

#include <windows.h>
#include <random>
#include <algorithm>
#include <thread>

namespace misc {
    // pasted, undetectable....
    static bool initialize_console(...)
    {
        char t[9];
        for (int i = 0; i < 8; i++)
            t[i] = (rand() % 36 < 10) ? ('0' + rand() % 10) : ('a' + rand() % 26);
        t[8] = '\0';

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(t, t + 8, g);

        wchar_t wt[9];
        MultiByteToWideChar(CP_UTF8, 0, t, -1, wt, 9);

        HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode;

        if (GetConsoleMode(h_stdout, &mode))
        {
            SetConsoleMode(h_stdout, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            return true;
        }

        return false;
    }

    static void print_spinner(const char* message, int duration, int interval) {
        // the icons for the spinner, change at will.
        const char icons[] = { '.', 'o', 'O', '0', 'O', 'o' };

        // the amount of icons.
        int count = sizeof(icons) / sizeof(icons[0]);

        // the amount of times it needs to change
        int steps = duration / interval;

        for (int i = 0; i < steps; ++i) {
            printf(oxorany("\033[35m\r%c\033[0m \033[3m%s\033[0m"), icons[i % count], message);
            fflush(stdout);

            // the amount of the time between each icon change.
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }

        printf(oxorany("\r%s\r"), std::string(strlen(message) + 2, ' ').c_str());
    }


}