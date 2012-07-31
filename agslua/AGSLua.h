
#ifndef AGSLUA_DOT_H
#define AGSLUA_DOT_H

#if defined(WINDOWS_VERSION)
#include <windows.h>
#endif

extern "C" {
	#include <lua.h>
}
#include "agsplugin.h"
#include "agslua_autogen.h"

// extern HANDLE luaMutex;

int ags_panic(lua_State* L);

//extern lua_State* L;

#define LUAVALUELIST_TYPENAME	"LuaValueList"
#define LUAGODOBJECT_TYPENAME	"LuaGodObject"

class LuaValueListInterface : public IAGSScriptManagedObject {
public:
	LuaValueListInterface() {};

	virtual const char *GetType() {
		return LUAVALUELIST_TYPENAME;
	}
	virtual int Serialize(const char *address, char *buffer, int bufsize) {
		return 0;
	}
	virtual int Dispose(const char *address, bool force);
};

static LuaValueListInterface gLuaValueListInterface;

class LuaValueListReader : public IAGSManagedObjectReader {
public:
	LuaValueListReader() {}

	virtual void Unserialize(int key, const char *serializedData, int dataSize);
};

static LuaValueListReader gLuaValueListReader;

void* LuaValueList_Create();
void* LuaValueList_SingleString(const char* str);
void* LuaValueList_SingleInt(int i);
void* LuaValueList_SingleFloat(SCRIPT_FLOAT(f));
void* LuaValueList_SingleBool(bool b);
void LuaValueList_AddInt(void* ptr, int i);
void LuaValueList_AddString(void* ptr, const char* str);
void LuaValueList_AddFloat(void* ptr, SCRIPT_FLOAT(f));
void LuaValueList_AddBool(void* ptr, bool b);
void LuaValueList_AddFromVariable(void* ptr, const char* expr);
int LuaValueList_get_Length(void* ptr);
const char* LuaValueList_get_Error(void* ptr);
void LuaValueList_set_Length(void* ptr, int len);
void LuaValueList_seti_AsStrings(void* ptr, int n, const char* s);
const char* LuaValueList_geti_AsStrings(void* ptr, int n);
void LuaValueList_seti_AsInts(void* ptr, int n, int i);
int LuaValueList_geti_AsInts(void* ptr, int n);
void LuaValueList_seti_AsFloats(void* ptr, int n, SCRIPT_FLOAT(f));
FLOAT_RETURN_TYPE LuaValueList_geti_AsFloats(void* ptr, int n);
void LuaValueList_seti_AsBools(void* ptr, int n, int b);
int LuaValueList_geti_AsBools(void* ptr, int n);
int LuaValueList_geti_Types(void* ptr, int n);
void Init_LuaValueList(lua_State *main_L, int IDX_OBJSTORE);
void aux_LuaValueList_push(lua_State* dest_L, void* ptr);
int aux_LuaValueList_PushValues(void* ptr, lua_State* dest_L);

extern unsigned char lscripts_guid[16];

void RegisterLuaModuleStruct();
void RegisterLuaValueListFunctions();
int luaopen_ags_customlua(lua_State *L);
int luaopen_agsinternal(lua_State *L);
int hide_agsinternal(lua_State *L);

class LuaGodObjectInterface : public IAGSScriptManagedObject {
public:
	LuaGodObjectInterface() {};

	virtual int Dispose(const char *address, bool force) {
		return 1;
	}
	virtual const char *GetType() {
		return LUAGODOBJECT_TYPENAME;
	}
	virtual int Serialize(const char *address, char *buffer, int bufsize) {
		return 0;
	}
};

static LuaGodObjectInterface gLuaGodObjectInterface;

class LuaGodObjectReader : public IAGSManagedObjectReader {
public:
	LuaGodObjectReader() {}

	virtual void Unserialize(int key, const char *serializedData, int dataSize);
};

static LuaGodObjectReader gLuaGodObjectReader;
void PushLuaValueListsForSerialization(lua_State* to_L, int IDX_SAVEGAMEDATA);
void DeserializeLuaValueLists(lua_State* to_L, int IDX_SAVEGAMEDATA);

int diff(lua_State *L);
int merge(lua_State *L);

#define DebugMessage(L,msg,...) \
	{ MessageBox(NULL, lua_pushfstring(L, msg, __VA_ARGS__), "mb", MB_OK); lua_pop(L,1); }

#endif

