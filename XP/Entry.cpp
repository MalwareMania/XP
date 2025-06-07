
#include <Windows.h>
#include <lua.h>
#include <lualib.h>
#include "Execution/Execution.hpp"
#include "Environment/Environment.hpp"
#include <thread>

void Exploit()
{
    auto lua_state = task_scheduler->get_lua_state();

    lua_state->userdata->Identity = 8;
    lua_state->userdata->Capabilities = ~0ULL;

    environment->initialize(lua_state);

	luaL_sandboxthread(lua_state);

    execution->execute("print('INITIALIZED')");

    while (true) {}
}

int __stdcall DllMain(HMODULE hModule, unsigned long ul_reason_for_call, void* lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        std::thread(Exploit).detach();
    }

    return TRUE;
}
