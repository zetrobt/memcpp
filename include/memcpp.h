#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <assert.h>
#include <vector>

namespace memcpp {

    class memcpp {
    public:
        memcpp(std::string name);
        uintptr_t get_module_from_name(std::string name);
        template<typename T> WINBOOL read(uintptr_t address, T value);
        template<typename T> WINBOOL write(uintptr_t address, T value);
        std::vector<MODULEENTRY32> list_of_modules();
        ~memcpp();
    private:
        int process_id;
        HANDLE snapshot;
    };

}
