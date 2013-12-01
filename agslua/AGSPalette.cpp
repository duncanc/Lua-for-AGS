extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <llh.h>
}
#include <string.h>
#include "AGSLua.h"
#include "agslua_autogen.h"
#include "agsplugin.h"

int luaopen_ags_palette(lua_State* L)
{
	lua_getglobal(L, "agsinternal");
	int INDEX_AGSINTERNAL = lua_gettop(L);

	lua_newtable(L);
	int INDEX_PALETTE = lua_gettop(L);

	lua_getfield(L, INDEX_AGSINTERNAL, "palette__index");
	lua_setfield(L, INDEX_PALETTE, "__index");

	lua_pushvalue(L, INDEX_PALETTE);
	lua_setmetatable(L, INDEX_PALETTE);

	lua_settop(L, INDEX_PALETTE);
	return 1;
}
