#include "Execution.hpp"

std::string CExecution::compile_script(const std::string Source) {

    std::string Bytecode = Luau::compile(Source, { 2, 1, 2 }, { true, true }, &Encoder);

    size_t DataSize = Bytecode.size();
    size_t MaxSize = ZSTD_compressBound(DataSize);
    std::vector<char> Buffer(MaxSize + 8);

    memcpy(Buffer.data(), "RSB1", 4);
    memcpy(Buffer.data() + 4, &DataSize, sizeof(DataSize));

    size_t CompressedSize = ZSTD_compress(Buffer.data() + 8, MaxSize, Bytecode.data(), DataSize, ZSTD_maxCLevel());
    size_t TotalSize = CompressedSize + 8;

    uint32_t Key = XXH32(Buffer.data(), TotalSize, 42);
    uint8_t* KeyBytes = (uint8_t*)&Key;

    for (size_t i = 0; i < TotalSize; ++i) Buffer[i] ^= KeyBytes[i % 4] + i * 41;

    return std::string(Buffer.data(), TotalSize);
}

void CExecution::set_proto_capabilities(Proto* Proto) {
    Proto->userdata = &MaxCaps;
    for (int i = 0; i < Proto->sizep; i++)
    {
        set_proto_capabilities(Proto->p[i]);
    }
}

int CExecution::lua_loadstring(lua_State* L, std::string& code, std::string chunkName) {

    std::string source = "script = Instance.new('LocalScript');" + code;
    std::string compiled = compile_script(source);

    if (chunkName.empty())
        chunkName = "=";

    if (Roblox::LuaVM__Load((int64_t)L, &compiled, chunkName.c_str(), 0) != LUA_OK) {
        lua_pushnil(L);
        lua_pushvalue(L, -2);
        return 2;
    }

    Closure* closure = lua_toclosure(L, -1); 
    if (closure && closure->l.p)
        set_proto_capabilities(closure->l.p);

    return 1; 
}

bool CExecution::execute(const std::string& source) {
    std::string bytecode = this->compile_script(source);

    if (bytecode.empty() || bytecode.at(0) == 0) {
        Roblox::Print(3, bytecode.c_str() + 1);
        return false;
    }

    lua_State* mainL = task_scheduler->get_lua_state();
    lua_State* threadL = lua_newthread(mainL);
    luaL_sandboxthread(threadL);
    lua_pop(mainL, 1);  

    if (Roblox::LuaVM__Load((int64_t)threadL, &bytecode, "@XP", 0) != LUA_OK) {
        Roblox::Print(2, lua_tostring(threadL, -1));
        lua_pop(threadL, 1);
        return false;
    }

    const Closure* cl = clvalue(luaA_toobject(threadL, -1));
    if (!cl || !cl->l.p) {
        lua_pop(threadL, 1);
        return false;
    }

    set_proto_capabilities(cl->l.p);
    Roblox::Task__Defer(threadL); // you can instead use
    /*
    lua_getglobal(L, "task");
    lua_getfield(L, -1, "defer");
    lua_remove(L, -2); // remove "task" table from stack
    lua_xmove(execThread, L, 1);
    lua_pcall(L, 1, 0, 0);

    for no offsets
    */
    return true;
}
