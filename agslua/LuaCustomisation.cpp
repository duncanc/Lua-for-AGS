
#if defined(WINDOWS_VERSION)
#include <windows.h>
#endif

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <ctype.h>
}
#include "AGSLua.h"

int ags_panic(lua_State* L) {
	lua_pushstring(L, "[Lua] ");
	lua_insert(L,-2);
	lua_concat(L,2);
	engine->AbortGame(lua_tostring(L,-1));
	return 0;
}

static void lua_tolower(lua_State *L, int idx) {
	luaL_Buffer b;
	const char* c;
	luaL_buffinit(L,&b);
	for (c = luaL_checkstring(L, idx); *c; c++) {
		luaL_addchar(&b, tolower(*c));
	}
	luaL_pushresult(&b);
	lua_replace(L, idx);
}

static void lua_tolowerpath(lua_State *L, int idx) {
	luaL_Buffer b;
	const char* c;
	luaL_buffinit(L,&b);
	for (c = luaL_checkstring(L, idx); *c; c++) {
		if (*c == '\\') {
			luaL_addchar(&b, '/');
		}
		else {
			luaL_addchar(&b, tolower(*c));
		}
	}
	luaL_pushresult(&b);
	lua_replace(L, idx);
}

static int ags_print(lua_State *L) {
	luaL_Buffer b;
	int NUM_PARAMS = lua_gettop(L);
	luaL_buffinit(L, &b);
	lua_getglobal(L, "tostring");
	for (int i = 1; i <= NUM_PARAMS; i++) {
		lua_pushvalue(L, -1);
		lua_pushvalue(L, i);
		lua_call(L, 1, 1);
		if (i != 1) {
			luaL_addstring(&b, ", ");
		}
		luaL_addvalue(&b);		
	}
	luaL_pushresult(&b);
	AGS_Display(lua_tostring(L,-1));
	return 0;
}

int ags_loadscript(lua_State *L) {
	lua_tolower(L,1);
	lua_getfield(L, LUA_REGISTRYINDEX, "lscripts");
	lua_pushvalue(L, 1);
	lua_gettable(L, -2);
	return 1;
}

int ags_runscript(lua_State *L) {
	lua_tolowerpath(L,1);
	lua_getfield(L, LUA_REGISTRYINDEX, "lscripts");
	lua_pushvalue(L, 1);
	lua_gettable(L, -2);
	if (!lua_isfunction(L,-1)) {
		return 0;
	}
	// replace name with function
	lua_replace(L,1);
	// remove lscripts table
	lua_pop(L,1);
	// call with any extra parameters, get any number of return values
	lua_call(L,lua_gettop(L) - 1,LUA_MULTRET);
	// return all return values
	return lua_gettop(L);
}

int ags_lscript_packageloader(lua_State *L) {
	lua_tolower(L,1);
	lua_settop(L,1);
	lua_getfield(L,LUA_REGISTRYINDEX,"lmodules");
	lua_insert(L,-2);
	lua_gettable(L,-2);
	return 1;
}

static const char* LUA_ADD_LSCRIPT_PACKAGELOADER = "table.insert(package.loaders, 2, (...))";

static const char LUA_COROUTINE_WRAP[] =
	"local select, assert, cocreate, coresume = select, assert, coroutine.create, coroutine.resume;"
	"function coroutine.wrap(f) "
		"local th = cocreate(f);"
		"return function(...) "
			"return select(2, assert(coresume(th, ...)));"
		"end;"
	"end";

static int ags_newproxy (lua_State *L) {
  lua_settop(L, 1);
  lua_newuserdata(L, 0);  /* create proxy */

  if (lua_toboolean(L, 1) == 0) {
	  lua_pushvalue(L, lua_upvalueindex(1));
	  lua_setmetatable(L, -2);
    return 1;  /* no metatable */
  }
  else if (lua_isboolean(L, 1)) {
    lua_newtable(L);  /* create a new metatable `m' ... */
	lua_pushboolean(L, 1);
	lua_setfield(L, -2, "__persist");
    lua_pushvalue(L, -1);  /* ... and mark `m' as a valid metatable */
    lua_pushboolean(L, 1);
    lua_rawset(L, lua_upvalueindex(1));  /* weaktable[m] = true */
  }
  else {
    int validproxy = 0;  /* to check if weaktable[metatable(u)] == true */
    if (lua_getmetatable(L, 1)) {
		if (lua_rawequal(L,-1,lua_upvalueindex(1))) {
			validproxy = 1;
		}
		else {
			lua_rawget(L, lua_upvalueindex(1));
			validproxy = lua_toboolean(L, -1);
		}
		lua_pop(L, 1);  /* remove value */
    }
    luaL_argcheck(L, validproxy, 1, "boolean or proxy expected");
    lua_getmetatable(L, 1);  /* metatable is valid; get it */
  }
  lua_setmetatable(L, 2);
  return 1;
}

static const luaL_Reg ags_customlua_globals[] = {
	{"print", ags_print},
	{"loadscript", ags_loadscript},
	{"runscript", ags_runscript},
	{NULL, NULL}
};

int luaopen_ags_customlua(lua_State *L) {
	// TODO: inject __persist into FILE* metatable (just create a dud closed file?)
	lua_atpanic(L, ags_panic);
	
	// Inject our custom global functions
	lua_pushvalue(L, LUA_GLOBALSINDEX);
	luaL_register(L, NULL, ags_customlua_globals);

	// Add our custom newproxy
	lua_createtable(L, 0, 1);  /* new table `w' */
	lua_pushvalue(L, -1);  /* `w' will be its own metatable */
	lua_setmetatable(L, -2);
	lua_pushboolean(L, 1);
	lua_setfield(L, -2, "__persist");
	lua_pushboolean(L, 0);
	lua_setfield(L, -2, "__metatable");
	lua_pushliteral(L, "kv");
	lua_setfield(L, -2, "__mode");  /* metatable(w).__mode = "kv" */
	lua_pushcclosure(L, ags_newproxy, 1);
	lua_setglobal(L, "newproxy");  /* set global `newproxy' */

	// Add our custom package loader
	luaL_loadstring(L, LUA_ADD_LSCRIPT_PACKAGELOADER);
	lua_pushcfunction(L, ags_lscript_packageloader);
	lua_call(L,1,0);

	// Replace coroutine.wrap with one that creates a Lua function
	// rather than a C function. (For serialization)
	luaL_dostring(L, LUA_COROUTINE_WRAP);

	// Just return true
	lua_pushboolean(L,1);
	return 1;
}
