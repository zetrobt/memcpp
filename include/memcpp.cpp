#include "memcpp.h"

namespace memcpp {
    memcpp::memcpp(std::string name) {
        PROCESSENTRY32 process;
        process.dwSize = sizeof(PROCESSENTRY32);

        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (Process32First(snapshot, &process)) {
            do {
                if (process.szExeFile == name) {
                    this->process_id = process.th32ProcessID;
                    this->snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->process_id);
                    assert(this->snapshot != INVALID_HANDLE_VALUE);
                }
            } while (Process32Next(snapshot, &process));
        }

        assert(process_id != 0);
    }

    uintptr_t memcpp::get_module_from_name(std::string name) {
        MODULEENTRY32 module;
        module.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(this->snapshot, &module)) {
            do {
                if (module.szModule == name) {
                    return (uintptr_t)module.modBaseAddr;
                }
            } while(Module32Next(this->snapshot, &module));
        }

        return 0;
    }

    template<typename T>
    WINBOOL memcpp::read(uintptr_t address, T value) {
        return ReadProcessMemory(this->snapshot, (void*)address, &value, sizeof(value), 0);
    }

    template<typename T>
    WINBOOL memcpp::write(uintptr_t address, T value) {
        return WriteProcessMemory(this->snapshot, (void*)address, &value, sizeof(value), 0);
    }

    std::vector<MODULEENTRY32> memcpp::list_of_modules() {
        std::vector<MODULEENTRY32> modules;
        MODULEENTRY32 module;
        module.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(this->snapshot, &module)) {
            do {
                modules.push_back(module);
            } while(Module32Next(this->snapshot, &module));
        }

        return modules;
    }

    memcpp::~memcpp() {
        CloseHandle(this->snapshot);
    }
}
