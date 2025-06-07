#pragma once

#include <zstd/include/zstd/zstd.h>
#include <zstd/include/zstd/xxhash.h>

#include <lua.h>
#include <lobject.h>
#include <lualib.h>
#include <lapi.h>

#include <Luau/Compiler.h>
#include <Luau/BytecodeBuilder.h>
#include <Luau/BytecodeUtils.h>
#include <Luau/Bytecode.h>

#include "TaskScheduler/TaskScheduler.hpp"

static class BytecodeEncoderClass : public Luau::BytecodeEncoder {
    inline void encode(uint32_t* data, size_t count) override
    {
        for (auto i = 0u; i < count;) {

            auto& opcode = *(uint8_t*)(data + i);

            i += Luau::getOpLength(LuauOpcode(opcode));

            opcode *= 227;
        }
    }
};

static BytecodeEncoderClass Encoder;

static uintptr_t MaxCaps = ~0ULL;

class CExecution {
private:
public:
    std::string compile_script(const std::string Source);
    int lua_loadstring(lua_State* L, std::string& code, std::string chunkName);
    bool execute(const std::string& source);
    void set_proto_capabilities(Proto* Proto);
};

inline auto execution = std::make_unique<CExecution>();
