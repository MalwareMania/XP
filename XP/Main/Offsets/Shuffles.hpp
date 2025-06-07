#include "EncryptionManager.hpp"

#define REBASE(x)(x + (uintptr_t)GetModuleHandleA(NULL))

#define LUAU_COMMA_SEP ,
#define LUAU_SEMICOLON_SEP ;

#define LUAU_SHUFFLE3(sep, a1, a2, a3) a1 sep a3 sep a2
#define LUAU_SHUFFLE4(sep, a1, a2, a3, a4) a3 sep a2 sep a4 sep a1
#define LUAU_SHUFFLE5(sep, a1, a2, a3, a4, a5) a1 sep a2 sep a5 sep a4 sep a3
#define LUAU_SHUFFLE6(sep, a1, a2, a3, a4, a5, a6) a2 sep a4 sep a3 sep a1 sep a5 sep a6
#define LUAU_SHUFFLE7(sep, a1, a2, a3, a4, a5, a6, a7) a6 sep a2 sep a7 sep a3 sep a1 sep a4 sep a5
#define LUAU_SHUFFLE8(sep, a1, a2, a3, a4, a5, a6, a7, a8) a5 sep a4 sep a8 sep a3 sep a2 sep a1 sep a7 sep a6
#define LUAU_SHUFFLE9(sep, a1, a2, a3, a4, a5, a6, a7, a8, a9) a9 sep a7 sep a3 sep a5 sep a1 sep a6 sep a2 sep a8 sep a4

#define PROTO_MEMBER2_ENC VMValue4 //updated
#define CLOSURE_DEBUGNAME_ENC VMValue4

#define PROTO_DEBUGISN_ENC VMValue3 //updated
#define CLOSURE_CONT_ENC VMValue3 //updated
#define UDATA_META_ENC VMValue3 //updated

#define PROTO_TYPEINFO_ENC VMValue2 //updated
#define LSTATE_STACKSIZE_ENC VMValue2 //updated

#define PROTO_DEBUGNAME_ENC VMValue1 //updated
#define TSTRING_HASH_ENC VMValue1 //updated

#define PROTO_MEMBER1_ENC VMValue0 // removed
#define CLOSURE_FUNC_ENC VMValue0 // removed
#define LSTATE_GLOBAL_ENC VMValue0 // removed
#define TSTRING_LEN_ENC VMValue0 // removed
#define TABLE_META_ENC VMValue0 //removed
#define TABLE_MEMBER_ENC VMValue0  // removed
#define GSTATE_TTNAME_ENC VMValue0 //removed
#define GSTATE_TMNAME_ENC VMValue0 //removed

namespace Shuffles
{
	const uintptr_t luaO_nilObject = REBASE(0x46BBE08);
	const uintptr_t luau_execute = REBASE(0x2773CE0);
	const uintptr_t luaH_dummynode = REBASE(0x46BB828);
}
