
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "agslua.h"

int luags_internal_GetKeyForManagedObject(lua_State *L) {
	lua_pushinteger(L, engine->GetManagedObjectKeyByAddress((const char*)*(void**)lua_touserdata(L,1)));
	return 1;
}

int luags_internal_GetManagedObjectFromKey(lua_State *L) {
	*(void**)lua_newuserdata(L, sizeof(void*)) = engine->GetManagedObjectAddressByKey(luaL_checkint(L,1));
	return 1;
}