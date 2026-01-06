#include "driver.h"
#include <iostream>
#include <memory>

namespace driver {
    INT32 proc_id = 0;
    HANDLE handle = nullptr;
}

bool driver::initialize() {
    if (driver::proc_id == 0)
        return false;

    driver::handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, driver::proc_id);
    return driver::handle != nullptr;
}

void driver::read_mem(PVOID address, PVOID buffer, DWORD size) {
    SIZE_T bytes = 0;
    if (!driver::handle)
        return;

    ReadProcessMemory(driver::handle, address, buffer, size, &bytes);
}

void driver::write_mem(PVOID address, PVOID buffer, DWORD size) {
    SIZE_T bytes = 0;
    if (!driver::handle)
        return;

    WriteProcessMemory(driver::handle, address, buffer, size, &bytes);
}

uintptr_t driver::get_base() {
    uintptr_t base_address = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, driver::proc_id);

    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 me32;
        me32.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(snapshot, &me32))
            base_address = reinterpret_cast<uintptr_t>(me32.modBaseAddr);

        CloseHandle(snapshot);
    }

    return base_address;
}

INT32 driver::find_process(LPCTSTR process_name) {
    PROCESSENTRY32 process_entry;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    process_entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &process_entry)) {
        do {
            if (!lstrcmpi(process_entry.szExeFile, process_name)) {
                CloseHandle(snapshot);
                driver::proc_id = process_entry.th32ProcessID;
                return process_entry.th32ProcessID;
            }
        } while (Process32Next(snapshot, &process_entry));
    }

    CloseHandle(snapshot);
    return 0;
}

std::uintptr_t driver::get_module(const wchar_t* name) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, driver::proc_id);
    if (snapshot == INVALID_HANDLE_VALUE)
        return 0;

    MODULEENTRY32W me32;
    me32.dwSize = sizeof(MODULEENTRY32W);

    if (Module32FirstW(snapshot, &me32)) {
        do {
            if (!_wcsicmp(me32.szModule, name)) {
                CloseHandle(snapshot);
                return reinterpret_cast<std::uintptr_t>(me32.modBaseAddr);
            }

        } while (Module32NextW(snapshot, &me32));
    }

    CloseHandle(snapshot);
    return 0;
}

bool driver::is_valid_address(uintptr_t address) {
    return address != 0 && address >= 0x10000 && address < 0x7FFFFFFFFFFF;
}