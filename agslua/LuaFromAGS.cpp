
#if defined(WINDOWS_VERSION)
#include <windows.h>
#else
#include <string.h>
#include <ctype.h>
#endif

extern "C" {
#include "lua.h"
#include "lauxlib.h"
}

#include "agslua.h"
#include "agslua_autogen.h"

static void lua_pushlowerpath(lua_State *L, const char* c) {
	luaL_Buffer b;
	luaL_buffinit(L,&b);
	for (; *c; c++) {
		if (*c == '\\') {
			luaL_addchar(&b, '/');
		}
		else {
			luaL_addchar(&b, tolower(*c));
		}
	}
	luaL_pushresult(&b);
}

void LuaRun(const char* scriptname) {
	if (!scriptname) {
		return;
	}
	lua_getfield(main_L, LUA_REGISTRYINDEX, "lscripts");
	lua_pushlowerpath(main_L, scriptname);
	lua_rawget(main_L,-2);
	lua_remove(main_L,-2);
	if (lua_isfunction(main_L,-1)) {
		lua_call(main_L,0,0);
	}
	else {
		lua_pop(main_L,1);
	}
}


int Lua_ScriptCount() {
	return scriptCount;
}

const char* Lua_ScriptName(int n) {
	lua_getfield(main_L, LUA_REGISTRYINDEX, "lscriptnames");
	lua_rawgeti(main_L, -1, n+1);
	const char* name;
	if (!lua_isstring(main_L,-1)) engine->AbortGame("Lua.ScriptNames[] index out of range");
	else name = engine->CreateScriptString(lua_tostring(main_L,-1));
	lua_pop(main_L, 2);
	return name;
}

void aux_LuaGetVariable(lua_State* aux_L, const char* expr) {
	const char* c;
	for (c = expr; *c; c++) {
		if ((*c < 'a' || *c > 'z') && (*c < 'A' || *c > 'Z') && (*c != '_') && !(c != expr && *c >= '0' && *c <= '9')) {
			lua_pushliteral(aux_L, "return ");
			lua_pushstring(aux_L, expr);
			lua_concat(aux_L,2);
			luaL_loadstring(aux_L,lua_tostring(aux_L,-1));
			lua_remove(aux_L,-2);
			lua_call(aux_L,0,1);
			return;
		}
	}
	lua_getglobal(main_L, expr);
}

void aux_LuaSetVariable(const char* expr, int values) {
	const char* c;
	for (c = expr; *c; c++) {
		if ((*c < 'a' || *c > 'z') && (*c < 'A' || *c > 'Z') && (*c != '_') && !(c != expr && *c >= '0' && *c <= '9')) {
			lua_pushstring(main_L, expr);
			lua_pushliteral(main_L, "=...");
			lua_concat(main_L,2);
			luaL_loadstring(main_L,lua_tostring(main_L,-1));
			lua_remove(main_L,-2);
			lua_insert(main_L,-2);
			lua_call(main_L,values,0);
			return;
		}
	}
	lua_setglobal(main_L, expr);
}

static void LuaSetVarToNewTable(const char* expr) {
	lua_newtable(main_L);
	aux_LuaSetVariable(expr,1);
}

int aux_LuaCall_SetUp_Obj(const char* expr, void* params) {
	int IDX_OBJ = lua_gettop(main_L);
	lua_pushstring(main_L, expr);
	lua_gettable(main_L, IDX_OBJ);
	if (!lua_isfunction(main_L,-1)) {
		if (luaL_getmetafield(main_L,-1,"__call")) {
			lua_pop(main_L,1);
		}
		else {
			return -1;
		}
	}
	if (params) {
	int n;
		lua_pushvalue(main_L, IDX_OBJ);
		n = aux_LuaValueList_PushValues(params, main_L);
		return n + (IDX_OBJ?1:0);
	}
	else {
		lua_pushvalue(main_L, IDX_OBJ);
		lua_remove(main_L, IDX_OBJ);
		return 1;
	}
}

int aux_LuaCall_SetUp(void* ptr, const char* expr, void* params) {
	if (ptr) {
		lua_pushlightuserdata(main_L, ptr);
		lua_rawget(main_L, LUA_REGISTRYINDEX);
		return aux_LuaCall_SetUp_Obj(expr, params);
	}
	aux_LuaGetVariable(main_L, expr);
	if (!lua_isfunction(main_L,-1)) {
		if (luaL_getmetafield(main_L,-1,"__call")) {
			lua_pop(main_L,1);
		}
		else {
			return -1;
		}
	}
	if (params) {
		return aux_LuaValueList_PushValues(params, main_L);
	}
	else {
		return 0;
	}
}

void* aux_LuaCall_ReturnList(int numParams, int protectedMode) {
	int IDX_PRECALL = lua_gettop(main_L) - 1 - numParams;
	if (protectedMode) {
		if (0 != lua_pcall(main_L,numParams,LUA_MULTRET,0)) {
			return aux_LuaValueList_Create(0, LUACALL_ERROR);
		}
	}
	else {
		lua_call(main_L,numParams,LUA_MULTRET);
	}
	int retvalue_count = lua_gettop(main_L) - IDX_PRECALL;
	lua_xmove(main_L, vlist_L, retvalue_count);
	return aux_LuaValueList_Create(retvalue_count, LUACALL_SUCCESS);
}

void aux_LuaCall_ReturnValue(int numParams, int protectedMode) {
	if (protectedMode) {
		if (0 != lua_pcall(main_L,numParams,1,0)) {
			lua_pop(main_L,1);
			lua_pushnil(main_L);
		}
	}
	else {
		lua_call(main_L,numParams,1);
	}
}

static void* LuaCall(const char* expr, void* params, int protectedMode) {
	if (strcmp(expr,"on_key_press") == 0) {
		int x = 1;
	}
	int numParams = aux_LuaCall_SetUp(NULL, expr, params);
	if (numParams == -1) {
		return aux_LuaValueList_Create(0, LUACALL_FUNCNOTFOUND);
	}
	void* list = aux_LuaCall_ReturnList(numParams, protectedMode);
	return list;
}

static void LuaSetVar(const char* expr, void* values) {
	int nvalues = values ? aux_LuaValueList_PushValues(values, main_L) : 0;
	aux_LuaSetVariable(expr, nvalues);
}

static void* LuaGetVar(const char* expr) {
	aux_LuaGetVariable(vlist_L, expr);
	return aux_LuaValueList_MakeReadOnly();
}

static void* LuaEvaluate(const char* expr, int protectedMode) {
	if (expr == NULL) {
		lua_pushnil(vlist_L);
		return aux_LuaValueList_Create(1, LUACALL_FUNCNOTFOUND);
	}
	lua_pushstring(vlist_L, "return ");
	lua_pushstring(vlist_L, expr);
	lua_concat(vlist_L,2);
	int top = lua_gettop(vlist_L);
	if (luaL_loadstring(vlist_L, lua_tostring(vlist_L,-1))) {
		lua_remove(vlist_L, -2);
	}
	else {
		lua_pop(vlist_L,2);
		if (!luaL_loadstring(vlist_L, expr)) {
			engine->AbortGame(lua_pushfstring(vlist_L, "[Lua] %s", lua_tostring(vlist_L,-1)));
		}
	}
	if (protectedMode) {
		if (0 != lua_pcall(vlist_L,0,LUA_MULTRET,0)) {
			return aux_LuaValueList_Create(0, LUACALL_ERROR);
		}
	}
	else {
		lua_call(vlist_L,0,LUA_MULTRET);
	}
	return aux_LuaValueList_Create(lua_gettop(vlist_L) - top, LUACALL_SUCCESS);
}

static void LuaRequireModule(const char* name) {
	lua_getglobal(main_L, "require");
	lua_pushstring(main_L, name);
	lua_call(main_L,1,0);
}

static void aux_RegisterFunction(const char* name, int globalScript, int numArgs) {
	if (numArgs < 0 || numArgs > 3) {
		engine->AbortGame("Number of arguments must be between 0 and 3 inclusive");
	}
	lua_getfield(main_L, LUA_REGISTRYINDEX, "agsinternal");
	lua_getfield(main_L, -1, "agsregister");
	lua_pushstring(main_L, name);
	lua_pushinteger(main_L, globalScript);
	lua_pushinteger(main_L, numArgs);
	lua_call(main_L,3,0);
	lua_pop(main_L,1);
}

static void RegisterGlobalFunction(const char* name, int numArgs) {
	aux_RegisterFunction(name, 1, numArgs);
}

static void RegisterRoomFunction(const char* name, int numArgs) {
	aux_RegisterFunction(name, 0, numArgs);
}

static void UnregisterFunction(const char* name) {
	lua_getglobal(main_L, "ags");
	lua_pushstring(main_L, name);
	lua_pushnil(main_L);
	lua_rawset(main_L,-3);
	lua_pop(main_L,1);
}

void RegisterLuaModuleStruct() {
	engine->RegisterScriptFunction("Lua::RunScript^1", (void*)LuaRun);

	engine->RegisterScriptFunction("Lua::RequireModule^1", (void*)LuaRequireModule);

	engine->RegisterScriptFunction("Lua::RegisterGlobalScriptFunction^2", (void*)RegisterGlobalFunction);
	engine->RegisterScriptFunction("Lua::RegisterRoomScriptFunction^2", (void*)RegisterRoomFunction);
	engine->RegisterScriptFunction("Lua::UnregisterFunction^1", (void*)UnregisterFunction);

	engine->RegisterScriptFunction("Lua::SetVar^2", (void*)LuaSetVar);
	engine->RegisterScriptFunction("Lua::GetVar^1", (void*)LuaGetVar);
	engine->RegisterScriptFunction("Lua::Evaluate^1", (void*)LuaEvaluate);
	engine->RegisterScriptFunction("Lua::Call^3", (void*)LuaCall);

	engine->RegisterScriptFunction("Lua::CreateTable^1", (void*)LuaSetVarToNewTable);

	engine->RegisterScriptFunction("Lua::get_ScriptCount", (void*)Lua_ScriptCount);
	engine->RegisterScriptFunction("Lua::geti_ScriptNames", (void*)Lua_ScriptName);
}
