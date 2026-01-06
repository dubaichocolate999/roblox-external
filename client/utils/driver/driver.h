#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <cstdint>

namespace driver {
    extern INT32 proc_id;
    extern HANDLE handle;

    bool initialize();
    void read_mem(PVOID address, PVOID buffer, DWORD size);
    void write_mem(PVOID address, PVOID buffer, DWORD size);
    bool is_valid_address(uintptr_t address);
    uintptr_t get_base();
    INT32 find_process(LPCTSTR process_name);
    std::uintptr_t get_module(const wchar_t* name);
}

template <typename T>
T read(uint64_t address) {
    T buffer{};
    driver::read_mem((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

template <typename T>
T write(uint64_t address, T buffer) {
    driver::write_mem((PVOID)address, &buffer, sizeof(T));
    return buffer;
}

inline void write_bytes(uint64_t address, const void* buffer, size_t size) {
    driver::write_mem((PVOID)address, &buffer, size);
}
