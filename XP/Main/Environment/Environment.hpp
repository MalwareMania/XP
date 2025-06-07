#include <lua.h>
#include <lapi.h>
#include <lfunc.h>
#include <lmem.h>
#include <lgc.h>
#include <memory>
#include <map>
#include <unordered_set>
#include "Execution/Execution.hpp"


class Environment
{
public:
	void initialize(lua_State* L);
};

inline auto environment = std::make_unique<Environment>();
