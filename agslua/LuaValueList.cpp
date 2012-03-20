
#include <windows.h>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "agsplugin.h"
#include "agslua.h"
#include "agslua_autogen.h"

static const char* LUAVALUELIST_INDEX_OUT_OF_BOUNDS = "LuaValueList index out of bounds (remember to start at 1 not 0!)";

lua_State* vlist_L;

void Init_LuaValueList(lua_State *main_L, int IDX_IMMORTALSTORE) {
	vlist_L = lua_newthread(main_L);
	lua_setfield(main_L, LUA_REGISTRYINDEX, "LuaValueList* thread");
	lua_settop(vlist_L, VLIST_STACK_MAX);
	{
		lua_pushvalue(main_L, IDX_IMMORTALSTORE);
		lua_xmove(main_L, vlist_L, 1);
		lua_replace(vlist_L, VLIST_STACK_IMMORTALSTORE);
	}
	{
		lua_newtable(vlist_L);
		lua_replace(vlist_L, VLIST_STACK_LISTSTORE);
	}
	{
		luaL_newmetatable(vlist_L, "LuaValueList*");
		lua_replace(vlist_L, VLIST_STACK_META);
	}
	{
		luaL_newmetatable(vlist_L, "Read-Only LuaValueList*");
		lua_replace(vlist_L, VLIST_STACK_READONLY_META);
	}
	{
		lua_newtable(vlist_L);
		lua_replace(vlist_L, VLIST_STACK_NIL);

		void* ptr = (void*)lua_topointer(vlist_L,VLIST_STACK_NIL);
		engine->RegisterManagedObject(ptr, &gLuaValueListInterface);
		engine->IncrementManagedObjectRefCount((const char*)ptr);
		lua_pushlightuserdata(vlist_L, ptr);
		lua_pushvalue(vlist_L, VLIST_STACK_NIL);
		lua_rawset(vlist_L, VLIST_STACK_LISTSTORE);

		lua_pushvalue(vlist_L, VLIST_STACK_READONLY_META);
		lua_setmetatable(vlist_L, VLIST_STACK_NIL);
	}
	{
		lua_newtable(vlist_L);
		lua_replace(vlist_L, VLIST_STACK_VALUECACHE);

		lua_newtable(vlist_L);
		lua_pushliteral(vlist_L, "v");
		lua_setfield(vlist_L,-2,"__mode");
		lua_setmetatable(vlist_L, VLIST_STACK_VALUECACHE);
	}
	{
		lua_newtable(vlist_L);
		lua_replace(vlist_L, VLIST_STACK_CACHE);

		lua_newtable(vlist_L);
		lua_pushliteral(vlist_L, "k");
		lua_setfield(vlist_L,-2,"__mode");
		lua_setmetatable(vlist_L,VLIST_STACK_CACHE);
	}
	lua_atpanic(vlist_L, ags_panic);
}

static int vlist_isreadonly(int idx) {
	if (!lua_getmetatable(vlist_L, idx)) {
		return 0;
	}
	if (!lua_rawequal(vlist_L,-1,VLIST_STACK_READONLY_META)){
		lua_pop(vlist_L,1);
		return 0;
	}
	lua_pop(vlist_L,1);
	return 1;
}

int aux_LuaValueList_PushValues(void* ptr, lua_State* dest_L) {
	int n, i;
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		n = 1;
	}
	else {
		lua_getfield(vlist_L,-1,"n");
		n = (int)lua_tointeger(vlist_L,-1);
		lua_pop(vlist_L,1);
	}
	for (i = 1; i <= n; i++) {
		lua_rawgeti(vlist_L,-i,i);
	}
	lua_xmove(vlist_L, dest_L, n);
	lua_pop(vlist_L, 1);
	return n;
}

int LuaValueListInterface::Dispose(const char *address, bool force) {
	// should only happen while the game is shutting down - ignore it
	if ((void*)address == lua_topointer(vlist_L,VLIST_STACK_NIL)) {
		return 1;
	}

	lua_pushlightuserdata(vlist_L, (void*)address);
	lua_pushvalue(vlist_L, -1);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	if (lua_isnil(vlist_L, -1)) {
		lua_pop(vlist_L, 2);
		return 1;
	}
	if (vlist_isreadonly(-1)) {
		lua_pop(vlist_L, 1);
	}
	else {
		lua_pushboolean(vlist_L, 1);
		lua_rawset(vlist_L, VLIST_STACK_CACHE);
	}

	lua_pushnil(vlist_L);
	lua_rawset(vlist_L, VLIST_STACK_LISTSTORE);
	return 1;
}

void LuaValueListReader::Unserialize(int key, const char *serializedData, int dataSize) {
	lua_pushinteger(vlist_L, key);
	lua_rawget(vlist_L, VLIST_STACK_RESTORE_LISTS);
	// restored_list
	void* ptr = (void*)lua_topointer(vlist_L,-1);
	if (vlist_isreadonly(-1)) {
		lua_rawgeti(vlist_L,-1,1);
		// restored_list, value
		if (lua_isnil(vlist_L,-1)) {
			lua_pop(vlist_L,1);
			// restored_list
			ptr = (void*)lua_topointer(vlist_L,VLIST_STACK_NIL);
		}
		else {
			lua_pushvalue(vlist_L,-2);
			// restored_list, value, restored_list
			lua_rawset(vlist_L,VLIST_STACK_VALUECACHE);
			// restored_list
		}
	}
	engine->RegisterUnserializedObject(key, ptr, &gLuaValueListInterface);
	lua_pushlightuserdata(vlist_L, ptr);
	// restored_list, ptr
	lua_insert(vlist_L, -2);
	// ptr, restored_list
	lua_rawset(vlist_L, VLIST_STACK_LISTSTORE);
}

bool tryGetCachedVList() {
	lua_pushnil(vlist_L);
	if (!lua_next(vlist_L, VLIST_STACK_CACHE)) {
		return false;
	}

	// remove 'true' value
	lua_pop(vlist_L, 1);
	// remove from cache
	lua_pushvalue(vlist_L,-1);
	lua_pushnil(vlist_L);
	lua_rawset(vlist_L,VLIST_STACK_CACHE);
	// remove every value from the table
	lua_pushnil(vlist_L);
	while (lua_next(vlist_L, -2)) {
		lua_pop(vlist_L,1);
		lua_pushnil(vlist_L);
		lua_rawset(vlist_L,-3);
		lua_pushnil(vlist_L);
	}
	return true;
}

void* aux_LuaValueList_Create(int fromStackValues, int callResult) {
	void* ptr;
	if (fromStackValues > 0) {
		int IDX_LIST, i;
		if (!tryGetCachedVList()) {
			lua_createtable(vlist_L,fromStackValues,0);
		}
		IDX_LIST = lua_gettop(vlist_L) - fromStackValues;
		lua_insert(vlist_L, IDX_LIST);
		for (i = 0; i < fromStackValues; i++) {
			lua_rawseti(vlist_L, IDX_LIST, fromStackValues-i);
		}
		lua_pushinteger(vlist_L, fromStackValues);
		lua_setfield(vlist_L, IDX_LIST, "n");
	}
	else {
		if (!tryGetCachedVList()) {
			lua_newtable(vlist_L);
		}
		lua_pushinteger(vlist_L, 0);
		lua_setfield(vlist_L, -2, "n");
	}
	if (callResult != 0) {
		lua_pushinteger(vlist_L, callResult);
		lua_setfield(vlist_L, -2, "result"); 
	}
	lua_pushvalue(vlist_L,-1);
	ptr = (void*)lua_topointer(vlist_L,-1);
	lua_pushlightuserdata(vlist_L,ptr);
	lua_insert(vlist_L,-2);
	lua_settable(vlist_L, VLIST_STACK_LISTSTORE);
	engine->RegisterManagedObject(ptr, &gLuaValueListInterface);
	lua_pop(vlist_L, 1);
	return ptr;
}

void* aux_LuaValueList_MakeReadOnly() {
	// value
	lua_pushvalue(vlist_L,-1);
	lua_rawget(vlist_L, VLIST_STACK_VALUECACHE);
	// value, cached
	if (lua_isnil(vlist_L,-1)) {
		lua_pop(vlist_L,1);
		// value
		lua_createtable(vlist_L,1,0);
		// value, newcache
		void* ptr = (void*)lua_topointer(vlist_L,-1);
		lua_pushlightuserdata(vlist_L, ptr);
		lua_pushvalue(vlist_L,-2);
		// value, newcache, newcacheptr, newcache
		lua_rawset(vlist_L, VLIST_STACK_LISTSTORE);
		// value, newcache
		engine->RegisterManagedObject(ptr, &gLuaValueListInterface);
		lua_pushvalue(vlist_L, VLIST_STACK_READONLY_META);
		lua_setmetatable(vlist_L,-2);
		// value, newcache
		lua_pushvalue(vlist_L,-2);
		// value, newcache, value
		lua_rawseti(vlist_L,-2,1);
		// value, newcache
		lua_rawset(vlist_L, VLIST_STACK_VALUECACHE);
		return ptr;
	}
	else {
		// value, cached
		void* ptr = (void*)lua_topointer(vlist_L,-1);
		lua_pushlightuserdata(vlist_L, ptr);
		// value, cached, cachedptr
		lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
		// value, cached, activelist
		if (lua_isnil(vlist_L, -1)) {
			lua_pop(vlist_L, 1);
			// value, cached
			engine->RegisterManagedObject(ptr, &gLuaValueListInterface);
			lua_pushlightuserdata(vlist_L, ptr);
			// value, cached, cachedptr
			lua_pushvalue(vlist_L, -2);
			// value, cached, cachedptr, cached
			lua_rawset(vlist_L, VLIST_STACK_LISTSTORE);
			// value, cached
			lua_pop(vlist_L,2);
		}
		else {
			lua_pop(vlist_L, 3);
		}
		return ptr;
	}
}

void* LuaValueList_Create() {
	return aux_LuaValueList_Create(0,LUACALL_NONE);
}

void* Lua_StringValue(const char* str) {
	if (!str) {
		return (void*)lua_topointer(vlist_L, VLIST_STACK_NIL);
	}
	lua_pushstring(vlist_L, str);
	return aux_LuaValueList_MakeReadOnly();
}

void* Lua_IntValue(int i) {
	lua_pushinteger(vlist_L, i);
	return aux_LuaValueList_MakeReadOnly();
}

void* Lua_FloatValue(SCRIPT_FLOAT(f)) {
	INIT_SCRIPT_FLOAT(f);
	lua_pushnumber(vlist_L, f);
	return aux_LuaValueList_MakeReadOnly();
}

void* Lua_BoolValue(bool b) {
	lua_pushboolean(vlist_L, b);
	return aux_LuaValueList_MakeReadOnly();
}

void* Lua_NilValue() {
	return (void*)lua_topointer(vlist_L, VLIST_STACK_NIL);
}

void* LuaValueList_geti_Values(void* list, int idx) {
	if (idx < 1) {
		engine->AbortGame(LUAVALUELIST_INDEX_OUT_OF_BOUNDS);
	}
	lua_pushlightuserdata(vlist_L, list);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L,-1,idx);
	lua_remove(vlist_L,-2);
	return aux_LuaValueList_MakeReadOnly();
}

void LuaValueList_seti_Values(void* list, int idx, void* value) {
	lua_pushlightuserdata(vlist_L, list);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		engine->AbortGame("Attempt to modify Read-Only LuaValueList");
	}
	lua_getfield(vlist_L, -1, "n");
	int n = (int)lua_tointeger(vlist_L,-1);
	lua_pop(vlist_L,1);
	for (;n < idx-1;n++) {
		lua_pushnil(vlist_L);
		lua_rawseti(vlist_L,-2,n);
	}
	if (value) {
		lua_pushlightuserdata(vlist_L, value);
		lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
		lua_rawgeti(vlist_L,-1,1);
		lua_remove(vlist_L, -2);
	}
	else {
		lua_pushnil(vlist_L);
	}
	lua_rawseti(vlist_L,-2,idx);
	lua_pop(vlist_L,1);
}

void LuaValueList_Add(void* add_to, void* add_from) {
	if (!add_from) {
		return;
	}
	int IDX_RESTORE = lua_gettop(vlist_L);
	lua_pushlightuserdata(vlist_L, add_to);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		engine->AbortGame("Attempt to modify Read-Only LuaValueList");
	}
	lua_getfield(vlist_L, -1, "n");
	int add_to_n = (int)lua_tonumber(vlist_L, -1);
	lua_pushlightuserdata(vlist_L, add_from);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	int add_from_n;
	if (vlist_isreadonly(-1)) {
		add_from_n = 1;
	}
	else {
		lua_getfield(vlist_L, -1, "n");
		add_from_n = (int)lua_tonumber(vlist_L, -1);
		lua_pop(vlist_L, 1);
	}
	// add_to, add_to_n, add_from
	for (int i = 1; i <= add_from_n; i++) {
		lua_rawgeti(vlist_L, -1, i);
		lua_rawseti(vlist_L, -4, add_to_n+i);
	}
	lua_pushinteger(vlist_L, add_to_n + add_from_n);
	lua_setfield(vlist_L,-4,"n");
	lua_settop(vlist_L, IDX_RESTORE);
}


int LuaValueList_get_Length(void* ptr) {
	int len;
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		lua_pop(vlist_L,1);
		return 1;
	}
	else {
		lua_getfield(vlist_L, -1, "n");
		len = (int)lua_tointeger(vlist_L,-1);
		lua_pop(vlist_L,2);
		return len;
	}
}

const char* LuaValueList_get_Error(void* ptr) {
	const char* str;
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	lua_getfield(vlist_L, -1, "error");
	str = lua_tostring(vlist_L,-1); 
	if (str) {
		str = engine->CreateScriptString(str);
	}
	lua_pop(vlist_L, 2);
	return str;
}

int LuaValueList_get_IsReadOnly(void* ptr) {
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	int readonly = vlist_isreadonly(-1);
	lua_pop(vlist_L,1);
	return readonly;
}

int LuaValueList_get_CallResult(void* ptr) {
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	lua_getfield(vlist_L, -1, "result");
	int v = (int)lua_tonumber(vlist_L,-1); 
	lua_pop(vlist_L, 2);
	return v;
}

void LuaValueList_set_Length(void* ptr, int len) {
	int old_len, i;
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		engine->AbortGame("Attempt to modify Read-Only LuaValueList");
	}
	lua_getfield(vlist_L, 1, "n");
	old_len = (int)lua_tointeger(vlist_L,-1);
	lua_pop(vlist_L,1);
	for (i = old_len + 1; i <= len; i++) {
		lua_pushnil(vlist_L);
		lua_rawseti(vlist_L,-2,i);
	}
	lua_pushinteger(vlist_L, len);
	lua_setfield(vlist_L, -2, "n");
	lua_pop(vlist_L,1);
}

// Push your value onto the stack before calling this
void aux_LuaValueList_seti(void* ptr, int i) {
	if (i < 1) {
		engine->AbortGame(LUAVALUELIST_INDEX_OUT_OF_BOUNDS);
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	if (vlist_isreadonly(-1)) {
		engine->AbortGame("Attempt to modify Read-Only LuaValueList");
	}
	lua_getfield(vlist_L, -1, "n");
	if (lua_tointeger(vlist_L,-1) < i) {
		lua_pushinteger(vlist_L, i);
		lua_setfield(vlist_L, -3, "n");
	}
	lua_pop(vlist_L,1);
	lua_insert(vlist_L, -2);
	lua_rawseti(vlist_L, -2, i);
	lua_pop(vlist_L,1);
}

void aux_LuaValueList_geti(void* ptr, int i) {
	if (i < 1) {
		engine->AbortGame(LUAVALUELIST_INDEX_OUT_OF_BOUNDS);
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_gettable(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L,-1,i);
	lua_remove(vlist_L,-2);
}

void LuaValueList_seti_AsStrings(void* ptr, int n, const char* str) {
	lua_pushstring(vlist_L, str);
	aux_LuaValueList_seti(ptr, n);
}

const char* LuaValueList_geti_AsStrings(void* ptr, int n) {
	const char* result;
	aux_LuaValueList_geti(ptr, n);
	result = engine->CreateScriptString(lua_tostring(vlist_L,-1));
	lua_pop(vlist_L,1);
	return result;
}

void LuaValueList_seti_AsInts(void* ptr, int n, int i) {
	lua_pushinteger(vlist_L, i);
	aux_LuaValueList_seti(ptr, n);
}

int LuaValueList_geti_AsInts(void* ptr, int i) {
	int result;
	aux_LuaValueList_geti(ptr, i);
	result = (int)lua_tonumber(vlist_L,-1);
	lua_pop(vlist_L,1);
	return result;
}

void LuaValueList_seti_AsFloats(void* ptr, int n, SCRIPT_FLOAT(f)) {
	INIT_SCRIPT_FLOAT(f);
	lua_pushnumber(vlist_L, f);
	aux_LuaValueList_seti(ptr, n);
}

FLOAT_RETURN_TYPE LuaValueList_geti_AsFloats(void* ptr, int n) {
	float result;
	aux_LuaValueList_geti(ptr, n);
	result = (float)lua_tonumber(vlist_L,-1);
	lua_pop(vlist_L,1);
	RETURN_FLOAT(result);
}

void LuaValueList_seti_AsBools(void* ptr, int n, int b) {
	lua_pushboolean(vlist_L, b);
	aux_LuaValueList_seti(ptr, n);
}

int LuaValueList_geti_AsBools(void* ptr, int n) {
	int result;
	aux_LuaValueList_geti(ptr, n);
	result = lua_toboolean(vlist_L, -1);
	lua_pop(vlist_L,1);
	return result;
}

int LuaValueList_geti_Types(void* ptr, int n) {
	int t;
	aux_LuaValueList_geti(ptr, n);
	switch(t = lua_type(vlist_L,-1)) {
		case LUA_TUSERDATA:
		default:
			lua_pop(vlist_L,1);
			return t;
	}
}

int LuaValue_get_Type(void* ptr) {
	int t;
	aux_LuaValueList_geti(ptr, 1);
	switch(t = lua_type(vlist_L,-1)) {
		case LUA_TUSERDATA:
		default:
			lua_pop(vlist_L,1);
			return t;
	}
}

void aux_LuaValueList_push(lua_State* dest_L, void* ptr) {
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	lua_xmove(vlist_L, dest_L, 1);
}

int LuaValueList_ToInt(void* ptr) {
	if (!ptr) {
		return 0;
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L, -1, 1);
	int i = (int)lua_tonumber(vlist_L, -1);
	lua_pop(vlist_L,2);
	return i;
}

FLOAT_RETURN_TYPE LuaValueList_ToFloat(void* ptr) {
	if (!ptr) {
		return 0;
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L, -1, 1);
	float f = (float)lua_tonumber(vlist_L, -1);
	lua_pop(vlist_L,2);
	RETURN_FLOAT(f);
}

const char* LuaValueList_ToString(void* ptr) {
	if (!ptr) {
		return NULL;
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L, -1, 1);
	const char* str = lua_tostring(vlist_L, -1);
	if (str) {
		str = engine->CreateScriptString(str);
	}
	lua_pop(vlist_L,2);
	return str;
}

int LuaValueList_ToBool(void* ptr) {
	if (!ptr) {
		return 0;
	}
	lua_pushlightuserdata(vlist_L, ptr);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	lua_rawgeti(vlist_L, -1, 1);
	int b = lua_toboolean(vlist_L,-1);
	lua_pop(vlist_L,2);
	return b;
}

static void* StringLuaMethod(const char* str, const char* name, void* params, int protectedMode) {
	lua_pushstring(main_L, str);
	int numParams = aux_LuaCall_SetUp_Obj(name, params);
	if (numParams == -1) {
		return NULL; // LUACALL_FUNCNOTFOUND;
	}
	return aux_LuaCall_ReturnList(numParams, protectedMode);
}

static void* LuaValueList_Slice(void* list, int beginning, int end) {
	lua_pushlightuserdata(vlist_L, list);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	if (end == 0) {
		end = -1;
	}
	if (end < 1 || beginning < 1) {
		if (beginning == 0 || end == 0) {
			engine->AbortGame("invalid range to LuaValueList.Slice()");
		}
		lua_getfield(vlist_L, -1, "n");
		if (beginning < 1) {
			beginning = (int)lua_tointeger(vlist_L,-1) + 1 + beginning;
		}
		if (end < 1) {
			end = (int)lua_tointeger(vlist_L,-1) + 1 + end;
		}
		lua_pop(vlist_L,-1);
	}
	int count = 0;
	for (int i = beginning; i <= end; i++) {
		count++;
		lua_rawgeti(vlist_L, -count, i);
	}
	void* newlist = aux_LuaValueList_Create(count, LUACALL_NONE);
	lua_pop(vlist_L, 1);
	return newlist;
}

static void* LuaValueList_Splice(void* list, int index, int removals, void* newElements) {
	if (index <= 0 || removals <= 0) {
		engine->AbortGame("invalid parameters to LuaValueList.Splice()");
	}
	lua_pushlightuserdata(vlist_L, list);
	lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
	int IDX_LIST = lua_gettop(vlist_L);

	if (vlist_isreadonly(IDX_LIST)) {
		engine->AbortGame("Attempt to modify Read-Only LuaValueList");
	}

	int insertions;
	if (newElements) {
		lua_pushlightuserdata(vlist_L, list);
		lua_rawget(vlist_L, VLIST_STACK_LISTSTORE);
		lua_getfield(vlist_L, -1, "n");
		insertions = (int)lua_tointeger(vlist_L,-1);
		lua_pop(vlist_L,1);
	}
	else {
		lua_pushnil(vlist_L);
		insertions = 0;
	}
	int IDX_INSERTIONS = lua_gettop(vlist_L);

	// Get list of removed values
	for (int i = index; i <= (index+removals); i++) {
		lua_rawgeti(vlist_L, IDX_LIST, i);
	}
	void* new_list = aux_LuaValueList_Create(removals, LUACALL_NONE);

	int insertionIndex = 1;
	if (insertions > removals) {
		insertions -= removals;

		// Overwrite [number of removals]
		while (removals--) {
			lua_rawgeti(vlist_L, IDX_INSERTIONS, insertionIndex++);
			lua_rawseti(vlist_L, IDX_LIST, index++);
		}

		// Insert [number of insertions]-[number of removals]
		// (guaranteed to be at least 1 here)
		lua_getfield(vlist_L,-2,"n");
		int old_n = (int)lua_tointeger(vlist_L,-2);
		lua_pop(vlist_L,1);
		// shift values right
		for (int i = old_n; i >= index; i++) {
			lua_rawgeti(vlist_L, IDX_LIST, i);
			lua_rawseti(vlist_L, IDX_LIST, i + insertions);
		}
		int new_n = old_n + insertions;
		while (insertions--) {
			lua_rawgeti(vlist_L, IDX_INSERTIONS, insertionIndex++);
			lua_rawseti(vlist_L, IDX_LIST, index++);
		}
		index--;
		if (index > new_n) {
			new_n = index;
		}
		lua_pushinteger(vlist_L, new_n);
		lua_setfield(vlist_L, IDX_LIST, "n");
	}
	else {
		// Overwrite [number of insertions]
		removals -= insertions;
		while (insertions--) {
			lua_rawgeti(vlist_L, -1, insertionIndex++);
			lua_rawseti(vlist_L, -2, index++);
		}
		// Remove [number of removals]-[number of insertions]
		if (removals) {
			lua_getfield(vlist_L,-2,"n");
			int old_n = (int)lua_tointeger(vlist_L,-1);
			lua_pop(vlist_L,1);
			if (index+removals > old_n) {
				lua_pushinteger(vlist_L, index-1);
				lua_setfield(vlist_L, IDX_LIST, "n");
			}
			else {
				// shift values left
				for (int i = 0; i < removals; i++) {
					lua_rawgeti(vlist_L, IDX_LIST, index + removals + i);
					lua_rawseti(vlist_L, IDX_LIST, index + i);
				}
				lua_pushinteger(vlist_L, old_n - removals);
				lua_setfield(vlist_L, IDX_LIST, "n");
			}
		}
	}
	lua_pop(vlist_L,2);
	return new_list;
}

void RegisterLuaValueListFunctions() {
	engine->AddManagedObjectReader(LUAVALUELIST_TYPENAME, &gLuaValueListReader);

	engine->RegisterScriptFunction("Lua::NewValueList^0", LuaValueList_Create);

	engine->RegisterScriptFunction("Lua::StringValue^1", Lua_StringValue);
	engine->RegisterScriptFunction("Lua::IntValue^1", Lua_IntValue);
	engine->RegisterScriptFunction("Lua::FloatValue^1", Lua_FloatValue);
	engine->RegisterScriptFunction("Lua::BoolValue^1", Lua_BoolValue);
	engine->RegisterScriptFunction("Lua::get_NilValue", Lua_NilValue);

	engine->RegisterScriptFunction("LuaValueList::Add^1", LuaValueList_Add);
	engine->RegisterScriptFunction("LuaValueList::geti_Values", LuaValueList_geti_Values);
	engine->RegisterScriptFunction("LuaValueList::seti_Values", LuaValueList_seti_Values);

	engine->RegisterScriptFunction("String::AsLuaValue", Lua_StringValue);
	engine->RegisterScriptFunction("String::LuaMethod", StringLuaMethod);

	engine->RegisterScriptFunction("LuaValue::get_AsInt", LuaValueList_ToInt);
	engine->RegisterScriptFunction("LuaValue::get_AsFloat", LuaValueList_ToFloat);
	engine->RegisterScriptFunction("LuaValue::get_AsString", LuaValueList_ToString);
	engine->RegisterScriptFunction("LuaValue::get_AsBool", LuaValueList_ToBool);
	engine->RegisterScriptFunction("LuaValue::get_Type", LuaValue_get_Type);

	engine->RegisterScriptFunction("LuaValueList::get_Length", LuaValueList_get_Length);
	engine->RegisterScriptFunction("LuaValueList::set_Length", LuaValueList_set_Length);
	engine->RegisterScriptFunction("LuaValueList::get_Error", LuaValueList_get_Error);
	engine->RegisterScriptFunction("LuaValueList::get_CallResult", LuaValueList_get_CallResult);
	engine->RegisterScriptFunction("LuaValueList::get_IsReadOnly", LuaValueList_get_IsReadOnly);
	engine->RegisterScriptFunction("LuaValueList::geti_AsStrings", LuaValueList_geti_AsStrings);
	engine->RegisterScriptFunction("LuaValueList::seti_AsStrings", LuaValueList_seti_AsStrings);
	engine->RegisterScriptFunction("LuaValueList::geti_AsInts", LuaValueList_geti_AsInts);
	engine->RegisterScriptFunction("LuaValueList::seti_AsInts", LuaValueList_seti_AsInts);
	engine->RegisterScriptFunction("LuaValueList::geti_AsFloats", LuaValueList_geti_AsFloats);
	engine->RegisterScriptFunction("LuaValueList::seti_AsFloats", LuaValueList_seti_AsFloats);
	engine->RegisterScriptFunction("LuaValueList::geti_AsBools", LuaValueList_geti_AsBools);
	engine->RegisterScriptFunction("LuaValueList::seti_AsBools", LuaValueList_seti_AsBools);
	engine->RegisterScriptFunction("LuaValueList::geti_Types", LuaValueList_geti_Types);

	engine->RegisterScriptFunction("LuaValueList::Slice^2", LuaValueList_Slice);
	engine->RegisterScriptFunction("LuaValueList::Splice^3", LuaValueList_Splice);
}

void PushLuaValueListsForSerialization(lua_State* to_L, int IDX_SAVEGAMEDATA) {
	lua_newtable(vlist_L);
	int IDX_READWRITE = lua_gettop(vlist_L);
	lua_pushnil(vlist_L);
	while (lua_next(vlist_L, VLIST_STACK_LISTSTORE)) {
		void* ptr = lua_touserdata(vlist_L,-2);
		int key = engine->GetManagedObjectKeyByAddress((const char*)ptr);
		lua_pushinteger(vlist_L, key);
		lua_insert(vlist_L,-2);
		lua_rawset(vlist_L,IDX_READWRITE);
	}
	lua_pushvalue(vlist_L, VLIST_STACK_META);
	lua_pushvalue(vlist_L, VLIST_STACK_READONLY_META);
	lua_xmove(vlist_L, to_L, 3);
	lua_setfield(to_L, IDX_SAVEGAMEDATA, "LuaValueListReadOnlyMeta");
	lua_setfield(to_L, IDX_SAVEGAMEDATA, "LuaValueListMeta");
	lua_setfield(to_L, IDX_SAVEGAMEDATA, "LuaValueLists");
}

void DeserializeLuaValueLists(lua_State* from_L, int IDX_SAVEGAMEDATA) {
	// Metatables assigned to LuaValueLists must be restored properly
	lua_getfield(from_L, IDX_SAVEGAMEDATA, "LuaValueListReadOnlyMeta");
	lua_getfield(from_L, IDX_SAVEGAMEDATA, "LuaValueListMeta");
	lua_xmove(from_L, vlist_L, 2);
	lua_replace(vlist_L, VLIST_STACK_META);
	lua_replace(vlist_L, VLIST_STACK_READONLY_META);

	lua_getfield(from_L, IDX_SAVEGAMEDATA, "LuaValueLists");
	lua_xmove(from_L, vlist_L, 1);
	lua_replace(vlist_L, VLIST_STACK_RESTORE_LISTS);
}
