
#include "Offsets/Offsets.hpp"
#include "Globals.hpp"
#include <lua.h>
#include <vector>


class Scheduler
{
public:
	uintptr_t get_job_by_name(const std::string& name);

	uintptr_t get_data_model();
	uintptr_t get_script_context();

	lua_State* get_lua_state();

	void initialize();
};

static auto task_scheduler = std::make_unique<Scheduler>();
