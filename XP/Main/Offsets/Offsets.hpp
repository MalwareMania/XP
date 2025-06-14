#include <Windows.h>
#include <cstdint>
#include <string>
#include <memory>

#define REBASE(x)(x + (uintptr_t)GetModuleHandleA(NULL))

inline const uintptr_t HyperionBase = (uintptr_t)GetModuleHandle("RobloxPlayerBeta.dll");
#define Hyperion(x) (HyperionBase + (x))

struct SignalT;
struct lua_State;
struct Proto;

namespace Offsets
{
	const uintptr_t Print = REBASE(0x1563AC0);
	const uintptr_t RawScheduler = REBASE(0x681CA18);
	const uintptr_t TaskDefer = REBASE(0xFE5D80);
	const uintptr_t DecryptState = REBASE(0xB44700);
	const uintptr_t GetGlobalState = REBASE(0xDBD570);
	const uintptr_t LuaVMLoad = REBASE(0xB47780);

        const uintptr_t BitMap = Hyperion(0x2A6938); // .

	namespace LuaState
	{
		const uintptr_t DecryptState = 0x88;
		const uintptr_t GlobalState = 0x140;
	}

	namespace DataModel
	{
		const uintptr_t FakeDataModelPointer = REBASE(0x675AA38);
		const uintptr_t FakeDataModelToDataModel = 0x1B8;
		const uintptr_t Children = 0x80;
		const uintptr_t ScriptContext = 0x3B0;
	}

	namespace TaskScheduler
	{
		const uintptr_t JobStart = 0x1D0;
		const uintptr_t JobName = 0x18;
		const uintptr_t JobEnd = 0x1D8; // Not used
	}

	namespace ExtraSpace
	{
		const uintptr_t Capabilities = 0x48;
		const uintptr_t Identity = 0x30;
	}
}

namespace Roblox
{
	inline auto Print = (int(__fastcall*)(int, const char*, ...))Offsets::Print;
	inline auto DecryptState = (lua_State * (__fastcall*)(uintptr_t))Offsets::DecryptState;
	inline auto GetGlobalState = (uintptr_t(__fastcall*)(uintptr_t, int32_t*, uintptr_t*))Offsets::GetGlobalState;

	using TLuaVM__Load = uintptr_t(__fastcall*)(int64_t, std::string*, const char*, int);
	inline auto LuaVM__Load = (TLuaVM__Load)Offsets::LuaVMLoad;

	using TTask__Defer = int(__fastcall*)(lua_State*);
	inline auto Task__Defer = (TTask__Defer)Offsets::TaskDefer;
}
