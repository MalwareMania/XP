#include "Environment.hpp"

static TValue* index2addr(lua_State* L, int idx) {
	return (idx > 0) ? &L->base[idx - 1] : &L->top[idx];
}

inline std::map<Closure*, lua_CFunction> ExecutorClosures = {};

inline std::unordered_set<Closure*> ExecutorFunctions = {};

static int closures_handler(lua_State* L)
{
	auto found = ExecutorClosures.find(curr_func(L));

	if (found != ExecutorClosures.end())
	{
		return found->second(L);
	}

	return 0;
}

static void push_closure(lua_State* L, lua_CFunction Function, const char* debugname, int nup)
{
	lua_pushcclosurek(L, closures_handler, debugname, nup, 0);
	Closure* closure = *reinterpret_cast<Closure**>(index2addr(L, -1));
	ExecutorClosures[closure] = Function;
}

static void register_function(lua_State* L, const char* globalname, lua_CFunction function)
{
	push_closure(L, function, nullptr, 0);
	ExecutorFunctions.insert(*reinterpret_cast<Closure**>(index2addr(L, -1)));
	lua_setfield(L, LUA_GLOBALSINDEX, globalname);
}

namespace XP
{
	namespace Cache
	{

	}

	namespace Crypt
	{

	}

	namespace Closures
	{
		int loadstring(lua_State* L)
		{
			const char* src = luaL_checklstring(L, 1, nullptr);
			const char* name = luaL_optlstring(L, 2, "XP", nullptr);
			std::string source = std::string(src);
			std::string chunkname = std::string(name);
			return execution->lua_loadstring(L, source, chunkname);
		}
	}

	namespace Http
	{
		

	}
}

void Environment::initialize(lua_State* L)
{
	register_function(L, "loadstring", XP::Closures::loadstring);

	lua_newtable(L);
	lua_setglobal(L, "_G");

	lua_newtable(L);
	lua_setglobal(L, "shared");
}
