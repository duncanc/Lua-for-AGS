
#include "agsplugin.h"
#include "AGSLua.h"

/*
	"#define LUA_REGISTRYINDEX (-10000)" "\r\n"
	"#define LUA_ENVIRONINDEX (-10001)" "\r\n"
	"#define LUA_GLOBALSINDEX (-10002)" "\r\n"
	"import void lua_concat(int);" "\r\n"
	"import void lua_createtable(int,int);" "\r\n"
	"import bool lua_equal(int,int);" "\r\n"
	"import int lua_error();" "\r\n"
	"import void lua_getfenv(int);" "\r\n"
	"import void lua_getfield(int,String);" "\r\n"
	"import void lua_getglobal(String);" "\r\n"
	"import int lua_getmetatable(int);" "\r\n"
	"import void lua_gettable(int);" "\r\n"
	"import int lua_gettop();" "\r\n"
	"import void lua_insert(int);" "\r\n"
	"import bool lua_isboolean(int);" "\r\n"
	"import bool lua_iscfunction(int);" "\r\n"
	"import bool lua_isfunction(int);" "\r\n"
	"import bool lua_islightuserdata(int);" "\r\n"
	"import bool lua_isnil(int);" "\r\n"
	"import bool lua_isnoneornil(int);" "\r\n"
	"import bool lua_isnumber(int);" "\r\n"
	"import bool lua_isstring(int);" "\r\n"
	"import bool lua_istable(int);" "\r\n"
	"import bool lua_isthread(int);" "\r\n"
	"import bool lua_isuserdata(int);" "\r\n"
	"import bool lua_lessthan(int,int);" "\r\n"
	"import void lua_newtable();" "\r\n"
	"import void lua_newthread();" "\r\n"
	"import int lua_next(int);" "\r\n"
	"import int lua_objlen(int);" "\r\n"
	"import int lua_pcall(int,int,int);" "\r\n"
	"import void lua_pushboolean(bool);" "\r\n"
	"import void lua_pushnil();" "\r\n"
	"import void lua_pushstring(String);" "\r\n"
	"import int lua_pushthread();" "\r\n"
	"import void lua_pushvalue(int);" "\r\n"
	"import void lua_rawequal(int,int);" "\r\n"
	"import void lua_rawget(int);" "\r\n"
	"import void lua_rawgeti(int,int);" "\r\n"
	"import void lua_rawset(int);" "\r\n"
	"import void lua_rawseti(int,int);" "\r\n"
	"import void lua_remove(int);" "\r\n"
	"import void lua_replace(int);" "\r\n"
	"import int lua_resume(int);" "\r\n"
	"import int lua_setfenv(int);" "\r\n"
	"import void lua_setfield(int,String);" "\r\n"
	"import void lua_setglobal(String);" "\r\n"
	"import int lua_setmetatable(int);" "\r\n"
	"import int lua_settable(int);" "\r\n"
	"import void lua_settop(int);" "\r\n"
	"import int lua_status();" "\r\n"
	"import bool lua_toboolean(int);" "\r\n"
	"import float lua_tonumber(int);" "\r\n"
	"import String lua_tostring(int);" "\r\n"
	"import int lua_type(int);" "\r\n"
	"import String lua_typename(int);" "\r\n"
	"import void lua_yield(int);" "\r\n"

	"import int luaL_loadstring(String);" "\r\n"
	"import int luaL_loadfile(String);" "\r\n"
	"import void lua_call(int,int);" "\r\n"
	"import int lua_tointeger(int);" "\r\n"
	"import int lua_pushinteger(int);" "\r\n"
	"import void lua_pop(int);" "\r\n"
	*/


/*
void agslua_concat(int n) {
	lua_concat(L,n);
}

int agslua_equal(int idx1, int idx2) {
	return lua_equal(L,idx1,idx2);
}

int agslua_error() {
	return lua_error(L);
}

void agslua_getfenv(int idx) {
	lua_getfenv(L,idx);
}

void agslua_getfield(int idx, char* k) {
	lua_getfield(L, idx, k);
}

void agslua_getglobal(char* s) {
	lua_getglobal(L, s);
}

int agslua_getmetatable(int objindex) {
	return lua_getmetatable(L,objindex);
}

void agslua_gettable(int idx) {
	lua_gettable(L, idx);
}

int agslua_gettop() {
	return lua_gettop(L);
}

void agslua_insert(int idx) {
	lua_insert(L, idx);
}

int agslua_isboolean(int n) {
	return lua_isboolean(L, n);
}

int agslua_iscfunction(int n) {
	return lua_iscfunction(L, n);
}

int agslua_isfunction(int n) {
	return lua_isfunction(L, n);
}

int agslua_islightuserdata(int n) {
	return lua_islightuserdata(L, n);
}

int agslua_isnil(int n) {
	return lua_isnil(L, n);
}

int agslua_isnone(int n) {
	return lua_isnone(L, n);
}

int agslua_isnoneornil(int n) {
	return lua_isnoneornil(L, n);
}

int agslua_isnumber(int n) {
	return lua_isnumber(L, n);
}

int agslua_isstring(int n) {
	return lua_isstring(L, n);
}

int agslua_istable(int n) {
	return lua_istable(L, n);
}

int agslua_isthread(int n) {
	return lua_isthread(L, n);
}

int agslua_isuserdata(int n) {
	return lua_isuserdata(L, n);
}

int agslua_lessthan(int idx1, int idx2) {
	return lua_lessthan(L, idx1, idx2);
}

void agslua_newtable() {
	lua_newtable(L);
}

void agslua_newthread() {
	lua_newthread(L);
}

int agslua_next(int idx) {
	return lua_next(L, idx);
}

int agslua_objlen(int idx) {
	return (int)lua_objlen(L, idx);
}

int agslua_pcall(int nargs, int nresults, int errfunc) {
	return lua_pcall(L, nargs, nresults, errfunc);
}

void agslua_pushboolean(int b) {
	lua_pushboolean(L, b);
}

void agslua_pushnil() {
	lua_pushnil(L);
}

void agslua_pushstring(char* s) {
	lua_pushstring(L, s);
}

int agslua_pushthread() {
	return lua_pushthread(L);
}

void agslua_pushvalue(int idx) {
	lua_pushvalue(L, idx);
}

int agslua_rawequal(int idx1, int idx2) {
	return lua_rawequal(L, idx1, idx2);
}

void agslua_rawget(int idx) {
	lua_rawget(L, idx);
}

void agslua_rawgeti(int idx, int n) {
	lua_rawgeti(L, idx, n);
}

void agslua_rawset(int idx) {
	lua_rawset(L, idx);
}

void agslua_rawseti(int idx, int n) {
	lua_rawseti(L, idx, n);
}

void agslua_remove(int idx) {
	lua_remove(L, idx);
}

void agslua_replace(int idx) {
	lua_replace(L, idx);
}

int agslua_resume(int idx) {
	return lua_resume(L, idx);
}

int agslua_setfenv(int idx) {
	return lua_setfenv(L, idx);
}

void agslua_setfield(int idx, char* k) {
	lua_setfield(L, idx, k);
}

void agslua_setglobal(char* s) {
	lua_setglobal(L, s);
}

int agslua_setmetatable(int objindex) {
	return lua_setmetatable(L, objindex);
}

void agslua_settable(int idx) {
	lua_settable(L, idx);
}

void agslua_settop(int idx) {
	lua_settop(L, idx);
}

int agslua_status() {
	return lua_status(L);
}

int agslua_toboolean(int idx) {
	return lua_toboolean(L, idx);
}

float agslua_tonumber(int idx) {
	return (float)lua_tonumber(L, idx);
}

const char* agslua_tostring(int idx) {
	return engine->CreateScriptString(lua_tostring(L,idx));
}

int agslua_type(int idx) {
	return lua_type(L, idx);
}

const char* agslua_typename(int n) {
	return engine->CreateScriptString(lua_typename(L,n));
}

int agslua_yield(int n) {
	return lua_yield(L, n);
}

int agsluaL_loadstring(char* script) {
	return luaL_loadstring(L, script);
}

int agsluaL_loadfile(char* filename) {
	return luaL_loadfile(L, filename);
}

void agslua_call(int nargs, int nresults) {
	lua_call(L, nargs, nresults);
}

void agslua_pushinteger(int n) {
	lua_pushinteger(L, n);
}

int agslua_tointeger(int idx) {
	return (int)lua_tointeger(L,idx);
}

void agslua_pop(int n) {
	lua_pop(L, n);
}
*/

	/*
	engine->RegisterScriptFunction("luaL_loadstring", agsluaL_loadstring);
	engine->RegisterScriptFunction("luaL_loadfile", agsluaL_loadfile);
	engine->RegisterScriptFunction("lua_call", agslua_call);
	engine->RegisterScriptFunction("lua_pushinteger", agslua_pushinteger);
	engine->RegisterScriptFunction("lua_tointeger", agslua_tointeger);
	engine->RegisterScriptFunction("lua_pop", agslua_pop);

	engine->RegisterScriptFunction("lua_concat", agslua_concat);
	engine->RegisterScriptFunction("lua_equal", agslua_equal);
	engine->RegisterScriptFunction("lua_error", agslua_error);
	engine->RegisterScriptFunction("lua_getfenv", agslua_getfenv);
	engine->RegisterScriptFunction("lua_getfield", agslua_getfield);
	engine->RegisterScriptFunction("lua_getglobal", agslua_getglobal);
	engine->RegisterScriptFunction("lua_getmetatable", agslua_getmetatable);
	engine->RegisterScriptFunction("lua_gettable", agslua_gettable);
	engine->RegisterScriptFunction("lua_gettop", agslua_gettop);
	engine->RegisterScriptFunction("lua_insert", agslua_insert);
	engine->RegisterScriptFunction("lua_isboolean", agslua_isboolean);
	engine->RegisterScriptFunction("lua_iscfunction", agslua_iscfunction);
	engine->RegisterScriptFunction("lua_isfunction", agslua_isfunction);
	engine->RegisterScriptFunction("lua_islightuserdata", agslua_islightuserdata);
	engine->RegisterScriptFunction("lua_isnil", agslua_isnil);
	engine->RegisterScriptFunction("lua_isnoneornil", agslua_isnoneornil);
	engine->RegisterScriptFunction("lua_isnumber", agslua_isnumber);
	engine->RegisterScriptFunction("lua_isstring", agslua_isstring);
	engine->RegisterScriptFunction("lua_istable", agslua_istable);
	engine->RegisterScriptFunction("lua_isthread", agslua_isthread);
	engine->RegisterScriptFunction("lua_isuserdata", agslua_isuserdata);
	engine->RegisterScriptFunction("lua_lessthan", agslua_lessthan);
	engine->RegisterScriptFunction("lua_newtable", agslua_newtable);
	engine->RegisterScriptFunction("lua_newthread", agslua_newthread);
	engine->RegisterScriptFunction("lua_next", agslua_next);
	engine->RegisterScriptFunction("lua_objlen", agslua_objlen);
	engine->RegisterScriptFunction("lua_pcall", agslua_pcall);
	engine->RegisterScriptFunction("lua_pushboolean", agslua_pushboolean);
	engine->RegisterScriptFunction("lua_pushnil", agslua_pushnil);
	engine->RegisterScriptFunction("lua_pushstring", agslua_pushstring);
	engine->RegisterScriptFunction("lua_pushthread", agslua_pushthread);
	engine->RegisterScriptFunction("lua_pushvalue", agslua_pushvalue);
	engine->RegisterScriptFunction("lua_rawequal", agslua_rawequal);
	engine->RegisterScriptFunction("lua_rawget", agslua_rawget);
	engine->RegisterScriptFunction("lua_rawgeti", agslua_rawgeti);
	engine->RegisterScriptFunction("lua_rawset", agslua_rawset);
	engine->RegisterScriptFunction("lua_rawseti", agslua_rawseti);
	engine->RegisterScriptFunction("lua_remove", agslua_remove);
	engine->RegisterScriptFunction("lua_replace", agslua_replace);
	engine->RegisterScriptFunction("lua_resume", agslua_resume);
	engine->RegisterScriptFunction("lua_setfenv", agslua_setfenv);
	engine->RegisterScriptFunction("lua_setfield", agslua_setfield);
	engine->RegisterScriptFunction("lua_setglobal", agslua_setglobal);
	engine->RegisterScriptFunction("lua_setmetatable", agslua_setmetatable);
	engine->RegisterScriptFunction("lua_settable", agslua_settable);
	engine->RegisterScriptFunction("lua_settop", agslua_settop);
	engine->RegisterScriptFunction("lua_status", agslua_status);
	engine->RegisterScriptFunction("lua_toboolean", agslua_toboolean);
	engine->RegisterScriptFunction("lua_tonumber", agslua_tonumber);
	engine->RegisterScriptFunction("lua_tostring", agslua_tostring);
	engine->RegisterScriptFunction("lua_type", agslua_type);
	engine->RegisterScriptFunction("lua_typename", agslua_typename);
	engine->RegisterScriptFunction("lua_yield", agslua_yield);
	*/
