
#include <windows.h>

#include "agsplugin.h"
#include "agslua.h"
#include "agslua_autogen.h"
#include "CompressedLuaChunks.h"
#include "SerializeLuaUniverse.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
	#include "pluto.h"
	#include "zlib.h"
	#include "malloc.h"
}
#include "llh.h"

IAGSEngine* engine;
lua_State* main_L;
unsigned char lscripts_guid[16];
int ags_current_room;
long long* ags_hotspot_array;
long long* ags_object_array;
long long* ags_region_array;
long long* ags_character_array;

HANDLE luaMutex;

int ags_closing = 0;

static int ags_character__tostring(lua_State *L) {
	AGSCharacter* character = *(AGSCharacter**)lua_touserdata(L,1);
	lua_pushstring(L, character->name);
	return 1;
}

#define HOTSPOTMETA_UV_LIB lua_upvalueindex(1)

static int ags_hotspot__index(lua_State *L) {
	lua_getfenv(L,1);
	lua_pushvalue(L,2);
	lua_rawget(L,-2);
	if (!lua_isnil(L,-1)) {
		return 1;
	}
	lua_pushvalue(L,2);
	lua_rawget(L, HOTSPOTMETA_UV_LIB);
	return 1;
}

static int ags_hotspot__newindex(lua_State *L) {
	lua_getfenv(L, 1);
	lua_insert(L,-3);
	lua_rawset(L,-3);
	return 0;
}

static int ags_hotspot__tostring(lua_State *L) {
	AGS_RoomThing* thing = (AGS_RoomThing*)lua_touserdata(L,1);
	if (thing->RoomID != ags_current_room) {
		lua_pushfstring(L, "(room %d hotspot %d)", thing->RoomID, thing->ThingID);
	}
	else {
		lua_pushstring(L, AGS_Hotspot_get_Name(&ags_hotspot_array[thing->ThingID]));
	}
	return 1;
}

static const luaL_Reg ags_hotspot_meta[] = {
	{"__index", ags_hotspot__index},
	{"__newindex", ags_hotspot__newindex},
	{"__tostring", ags_hotspot__tostring},
	{NULL, NULL}
};

#undef HOTSPOTMETA_UV_LIB

#define REGIONMETA_UV_LIB lua_upvalueindex(1)

static int ags_region__index(lua_State *L) {
	lua_getfenv(L,1);
	lua_pushvalue(L,2);
	lua_rawget(L,-2);
	if (!lua_isnil(L,-1)) {
		return 1;
	}
	lua_pushvalue(L,2);
	lua_rawget(L, REGIONMETA_UV_LIB);
	return 1;
}

static int ags_region__newindex(lua_State *L) {
	lua_getfenv(L, 1);
	lua_insert(L,-3);
	lua_rawset(L,-3);
	return 0;
}

static int ags_region__tostring(lua_State *L) {
	AGS_RoomThing* thing = (AGS_RoomThing*)lua_touserdata(L,1);
	lua_pushfstring(L, "(room %d region %d)", thing->RoomID, thing->ThingID);
	return 1;
}

static const luaL_Reg ags_region_meta[] = {
	{"__index", ags_region__index},
	{"__newindex", ags_region__newindex},
	{"__tostring", ags_region__tostring},
	{NULL, NULL}
};

#undef REGIONMETA_UV_LIB

#define OBJECTMETA_UV_LIB lua_upvalueindex(1)

static int ags_object__index(lua_State *L) {
	lua_getfenv(L,1);
	lua_pushvalue(L,2);
	lua_rawget(L,-2);
	if (!lua_isnil(L,-1)) {
		return 1;
	}
	lua_pushvalue(L,2);
	lua_rawget(L, OBJECTMETA_UV_LIB);
	return 1;
}

static int ags_object__newindex(lua_State *L) {
	lua_getfenv(L, 1);
	lua_insert(L,-3);
	lua_rawset(L,-3);
	return 0;
}

static int ags_object__tostring(lua_State *L) {
	AGS_RoomThing* thing = (AGS_RoomThing*)lua_touserdata(L,1);
	if (thing->RoomID != ags_current_room) {
		lua_pushfstring(L, "(room %d object %d)", thing->RoomID, thing->ThingID);
	}
	else {
		lua_pushstring(L, AGS_Object_get_Name(&ags_object_array[thing->ThingID]));
	}
	return 1;
}

static const luaL_Reg ags_object_meta[] = {
	{"__index", ags_object__index},
	{"__newindex", ags_object__newindex},
	{"__tostring", ags_object__tostring},
	{NULL, NULL}
};

#undef OBJECTMETA_UV_LIB

#define IMMORTALMETA_UV_LIB lua_upvalueindex(1)

static int ags_immortal__index(lua_State *L) {
	lua_getfenv(L,1);
	lua_pushvalue(L,2);
	lua_rawget(L,-2);
	if (!lua_isnil(L,-1)) {
		return 1;
	}
	lua_pushvalue(L,2);
	lua_rawget(L, IMMORTALMETA_UV_LIB);
	return 1;
}

static int ags_immortal__newindex(lua_State *L) {
	lua_getfenv(L, 1);
	lua_replace(L, 1);
	lua_rawset(L, 1);
	return 0;
}

static int ags_inventoryitem__tostring(lua_State *L) {
	AGS_InventoryItem* item = *(AGS_InventoryItem**)lua_touserdata(L,1);
	lua_pushstring(L, AGS_InventoryItem_get_Name(item));
	return 1;
}

static const luaL_Reg ags_immortal_meta[] = {
	/*
	{"__index", ags_immortal__index},
	{"__newindex", ags_immortal__newindex},
	*/
	{NULL, NULL}
};

static void GetLibTableForImmortalMetatable(lua_State *L, int IDX_META) {
	lua_getfield(L,IDX_META,"__index");
	if (lua_isfunction(L,-1)) {
		if (lua_getupvalue(L,lua_gettop(L),1) == NULL) {
			lua_pushnil(L);
		}
		lua_remove(L,-2);
	}
}

static void SetLibTableForImmortalMetatable(lua_State* L, int IDX_META, int IDX_NEWLIB) {
	lua_getfield(L,IDX_META,"__index");
	if (lua_isfunction(L,-1)) {
		lua_pushvalue(L,IDX_NEWLIB);
		if (lua_setupvalue(L,lua_gettop(L)-1,1) == NULL) {
			lua_pop(L,1);
			MessageBox(NULL, "wrong number of upvalues", "wrong number of upvalues", MB_OK);
		}
		lua_getfield(L,IDX_META,"__newindex");
		lua_pushvalue(L,IDX_NEWLIB);
		if (lua_setupvalue(L,lua_gettop(L)-1,1) == NULL) {
			lua_pop(L,1);
			MessageBox(NULL, "wrong number of upvalues", "wrong number of upvalues", MB_OK);
		}
		lua_pop(L,2);
	}
	else {
		lua_pop(L,1);
		lua_pushvalue(L, IDX_NEWLIB);
		lua_setfield(L, IDX_META, "__index");
	}
}

#undef IMMORTALMETA_UV_LIB

static lua_CFunction str_format;

// used for any function that takes a variable number of
// string formatting parameters
void aux_formatstring(lua_State *L, int i) {
	if (lua_gettop(L) > i) {
		luaL_checkstring(L,i);
		lua_pushcfunction(L, str_format);
		lua_insert(L,i);
		lua_call(L,lua_gettop(L) - i,1);
	}
}

int luags_Mouse_GetPosition(lua_State *L) {
	long x,y;
	engine->GetMousePosition(&x,&y);
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return 2;
}

int luags_Mouse_get_x(lua_State *L) {
	long x,y;
	engine->GetMousePosition(&x,&y);
	lua_pushinteger(L, x);
	return 1;
}

int luags_Mouse_get_y(lua_State *L) {
	long x,y;
	engine->GetMousePosition(&x,&y);
	lua_pushinteger(L, y);
	return 1;
}

static const char* LuaMethodSupportingTypes[] = {
	"AGS_Character*",
	"AGS_InventoryItem*",
	"AGS_Dialog*",

	"AGS_Hotspot*",
	"AGS_Object*",
	"AGS_Region*",

	"AGS_GUIControl*",

	"AGS_GUI*",
	"AGS_Label*",
	"AGS_Button*",
	"AGS_Slider*",
	"AGS_TextBox*",
	"AGS_InvWindow*",
	"AGS_ListBox*",

	"AGS_ViewFrame*",
	"AGS_DrawingSurface*",
	"AGS_File*",
	"AGS_Overlay*",
	"AGS_DynamicSprite*",
	"AGS_DateTime*",
	"AGS_AudioChannel*",
	"AGS_AudioClip*",

	NULL
};

#define OBJECTARRAY_UV_META lua_upvalueindex(1)
#define OBJECTARRAY_UV_STORE lua_upvalueindex(2)

static int object_array__index(lua_State *L) {
	int i;
	if (!lua_isnumber(L,2)) {
		return 0;
	}
	i = (int)lua_tonumber(L,2);

	// TODO: add the object limit to lscripts.dat

	luags_pushObject(L, &ags_object_array[i], OBJECTARRAY_UV_META, OBJECTARRAY_UV_STORE);
	return 1;
}

static const luaL_Reg object_array_meta[] = {
	{"__index", object_array__index},
	{NULL, NULL}
};

#undef OBJECTARRAY_UV_META
#undef OBJECTARRAY_UV_STORE

#define HOTSPOTARRAY_UV_META lua_upvalueindex(1)
#define HOTSPOTARRAY_UV_STORE lua_upvalueindex(2)

static int hotspot_array__index(lua_State *L) {
	int i;
	if (!lua_isnumber(L,2)) {
		return 0;
	}
	i = (int)lua_tonumber(L,2);

	// TODO: add the hotspot limit to lscripts.dat

	luags_pushHotspot(L, &ags_hotspot_array[i], HOTSPOTARRAY_UV_META, HOTSPOTARRAY_UV_STORE);
	return 1;
}

static const luaL_Reg hotspot_array_meta[] = {
	{"__index", hotspot_array__index},
	{NULL, NULL}
};

#undef HOTSPOTARRAY_UV_META
#undef HOTSPOTARRAY_UV_STORE

#define REGIONARRAY_UV_META lua_upvalueindex(1)
#define REGIONARRAY_UV_STORE lua_upvalueindex(2)

static int region_array__index(lua_State *L) {
	int i;
	if (!lua_isnumber(L,2)) {
		return 0;
	}
	i = (int)lua_tonumber(L,2);

	// TODO: add the region limit to lscripts.dat

	luags_pushRegion(L, &ags_region_array[i], REGIONARRAY_UV_META, REGIONARRAY_UV_STORE);
	return 1;
}

static const luaL_Reg region_array_meta[] = {
	{"__index", region_array__index},
	{NULL, NULL}
};

#undef REGIONARRAY_UV_META
#undef REGIONARRAY_UV_STORE

#define GETPLAYER_UV_CHARACTER_META	lua_upvalueindex(1)
#define GETPLAYER_UV_CHARACTER_STORE lua_upvalueindex(2)

int ags_type(lua_State *L) {
	if (lua_getmetatable(L,1)) {
		lua_gettable(L, LUA_REGISTRYINDEX);
		if (lua_isstring(L,-1)) {
			size_t len;
			const char* type_name = lua_tolstring(L,-1,&len);
			if (len > 5) {
				lua_pushlstring(L, type_name + 4, len-5);
				return 1;
			}
		}
	}
	lua_pushnil(L);
	return 1;
}

int ags_get_player(lua_State *L) {
	AGS_Character* player = (AGS_Character*)&ags_character_array[engine->GetPlayerCharacter()];
	luags_pushCharacter(L, player, GETPLAYER_UV_CHARACTER_META, GETPLAYER_UV_CHARACTER_STORE);
	return 1;
}

#undef GETPLAYER_UV_CHARACTER_META
#undef GETPLAYER_UV_CHARACTER_STORE

lua_CFunction get_string_format(lua_State *L) {
	lua_CFunction func;
	lua_getglobal(L,"string");
	lua_getfield(L,-1,"format");
	func = lua_tocfunction(L,-1);
	lua_pop(L,2);
	return func;
}

int GetLibTable(lua_State *L) {
	luaL_checkstring(L,1);
	lua_pushliteral(L,"AGS_");
	lua_pushvalue(L,1);
	lua_pushliteral(L,"*");
	lua_concat(L,3);
	lua_gettable(L, LUA_REGISTRYINDEX);
	if (lua_istable(L,-1)) {
		lua_getfield(L,-1,"__index");
		if (lua_isfunction(L,-1)) {
			lua_getupvalue(L,-1,1);
		}
	}
	return 1;
}

const char* ReadSingleString(lua_State *persist_L, void* data, size_t* size) {
	lua_State* L = (lua_State*)data;
	if (lua_isnil(L,-1)) {
		lua_pop(L,2);
		*size = 0;
		return NULL;
	}
	lua_pushnil(L);
	return lua_tolstring(L,-2,size);
}

int init_main_L(lua_State* L) {
	int IDX_AGS_LIB,
		IDX_CHARACTER_META, IDX_CHARACTER_LIB,
		IDX_INVENTORYITEM_LIB, IDX_INVENTORYITEM_META,
		IDX_GUI_META, IDX_GUI_LIB,
		IDX_GUICONTROL_META, IDX_GUICONTROL_STORE,
		IDX_INVWINDOW_META, IDX_INVWINDOW_LIB,
		IDX_BUTTON_META, IDX_BUTTON_LIB,
		IDX_TEXTBOX_META, IDX_TEXTBOX_LIB,
		IDX_SLIDER_META, IDX_SLIDER_LIB,
		IDX_LABEL_META, IDX_LABEL_LIB,
		IDX_LISTBOX_META, IDX_LISTBOX_LIB,
		IDX_DIALOG_META, IDX_DIALOG_LIB,
		IDX_AUDIOCLIP_META, IDX_AUDIOCLIP_LIB,
		IDX_HOTSPOT_META, IDX_HOTSPOT_STORE, IDX_HOTSPOT_LIB,
		IDX_OBJECT_META, IDX_OBJECT_STORE, IDX_OBJECT_LIB,
		IDX_REGION_META, IDX_REGION_STORE, IDX_REGION_LIB,
		IDX_IMMORTAL_STORE;
	FILE* f;
	int IDX_LSCRIPTS;

	luaL_openlibs(L);

	// We need string.format for functions like Display that take formatting parameters
	if (!(str_format = get_string_format(L))) {
		engine->AbortGame("[Lua] string.format cannot be found!");
	}

	luaMutex = CreateMutex(NULL, FALSE, NULL);

	// Customisations (panic handler, print replacement, runscript, loadscript, lscripts package loader)
	lua_pushcfunction(L, luaopen_ags_customlua);
	lua_call(L,0,0);

	// must be done before any luaopen_ for ephemerals
	lua_pushcfunction(L, luaopen_agsinternal);
	lua_call(L,0,0);

	lua_newtable(L);
	IDX_LSCRIPTS = lua_gettop(L);

	lua_pushvalue(L, IDX_LSCRIPTS);
	lua_setfield(L, LUA_REGISTRYINDEX, "lscripts");

	luaopen_ags(L);
	IDX_AGS_LIB = lua_gettop(L);

	//engine->GetPathToFileInCompiledFolder("lscripts.dat", buffer);
	if (f = fopen(engine->IsRunningUnderDebugger() ? "Compiled/lscripts.dat" : "lscripts.dat", "rb")) {
		int offset,length;
		fseek(f, -16, SEEK_END);
		fread(&offset, sizeof(offset), 1, f);
		fseek(f, -8, SEEK_END);
		fread(&length, sizeof(length), 1, f);
		fseek(f, offset, SEEK_SET);
		aux_loadcompressed(L, f, offset, length);
		lua_call(L,0,1);
		if (lua_istable(L,-1)) {
			// guid check
			lua_getfield(L,-1,"guid");
			if (0 != memcmp(lua_tostring(L,-1), lscripts_guid, 16)) {
				engine->AbortGame("[Lua] lscripts.dat signature mismatch!");
			}
			lua_pop(L,1);
			// inventory items
			lua_getfield(L,-1,"inventory");
			lua_setfield(L, LUA_REGISTRYINDEX, "AGSInventoryItems");
			// guis
			lua_getfield(L,-1,"gui");
			lua_setfield(L, LUA_REGISTRYINDEX, "AGSGUIs");
			// dialog
			lua_getfield(L,-1,"dialog");
			lua_setfield(L, LUA_REGISTRYINDEX, "AGSDialogs");
			// views
			lua_getfield(L,-1,"views");
			lua_pushnil(L);
			while(lua_next(L,-2)) {
				lua_pushvalue(L,-2);
				lua_rawset(L, IDX_AGS_LIB);
			}
			lua_pop(L,1);
			// fonts
			lua_getfield(L,-1,"fonts");
			lua_pushnil(L);
			while(lua_next(L,-2)) {
				lua_pushvalue(L,-2);
				lua_rawset(L, IDX_AGS_LIB);
			}
			lua_pop(L,1);
			// cursors
			lua_getfield(L,-1,"cursors");
			lua_pushnil(L);
			while(lua_next(L,-2)) {
				lua_pushvalue(L,-2);
				lua_rawset(L, IDX_AGS_LIB);
			}
			lua_pop(L,1);
			// audioclips
			lua_getfield(L,-1,"audioclips");
			lua_setfield(L, LUA_REGISTRYINDEX, "AGSAudioClips");
			// initstate
			lua_getfield(L,-1,"initstate");
			lua_setfield(L,LUA_REGISTRYINDEX,"initstate");
			// files
			lua_getfield(L,-1,"files");
			lua_pushnil(L);
			while (lua_next(L,-2)) {
				lua_getfield(L,-1,"offset");
				lua_getfield(L,-2,"length");
				aux_loadcompressed(L, f, (int)lua_tointeger(L,-2), (int)lua_tointeger(L,-1));
				lua_pushvalue(L,-5); // script name
				lua_insert(L,-2); // put before function
				lua_rawset(L, IDX_LSCRIPTS); // insert into lscripts
				lua_pop(L,3); // remove table, offset, length
			}
			lua_pop(L,1);
			// modules
			lua_getfield(L,-1,"modules");
			lua_pushnil(L);
			while (lua_next(L,-2)) {
				lua_rawget(L, IDX_LSCRIPTS);
				lua_pushvalue(L,-2);
				lua_insert(L,-2);
				lua_rawset(L,-4);
			}
			lua_setfield(L, LUA_REGISTRYINDEX, "lmodules");
		}
		lua_pop(L,1);
		fclose(f);
	}

	lua_pushcfunction(L, luaopen_ags_Game);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_System);
	lua_call(L,0,0);
	{
		lua_pushcfunction(L, luaopen_ags_Mouse);
		lua_call(L,0,1);
		// inject special custom getters
		lua_pushcfunction(L, luags_Mouse_GetPosition);
		lua_setfield(L, -2, "GetPosition");
		lua_pushcfunction(L, luags_Mouse_get_x);
		lua_setfield(L, -2, "get_x");
		lua_pushcfunction(L, luags_Mouse_get_y);
		lua_setfield(L, -2, "get_y");
		// make ags.mouse the same as ags.Mouse
		lua_setfield(L, IDX_AGS_LIB, "mouse");
	}
	lua_pushcfunction(L, luaopen_ags_ViewFrame);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_AudioChannel);
	lua_call(L,0,1);
	lua_pushcfunction(L, luaopen_ags_DrawingSurface);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_Room);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_Parser);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_File);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_Overlay);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_DynamicSprite);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_GUIControl);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_DateTime);
	lua_call(L,0,0);
	lua_pushcfunction(L, luaopen_ags_Label);
	lua_call(L,0,1);
	IDX_LABEL_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Button);
	lua_call(L,0,1);
	IDX_BUTTON_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Slider);
	lua_call(L,0,1);
	IDX_SLIDER_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_TextBox);
	lua_call(L,0,1);
	IDX_TEXTBOX_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_InvWindow);
	lua_call(L,0,1);
	IDX_INVWINDOW_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_ListBox);
	lua_call(L,0,1);
	IDX_LISTBOX_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_GUI);
	lua_call(L,0,1);
	IDX_GUI_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Hotspot);
	lua_call(L,0,1);
	IDX_HOTSPOT_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Region);
	lua_call(L,0,1);
	IDX_REGION_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Dialog);
	lua_call(L,0,1);
	IDX_DIALOG_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Object);
	lua_call(L,0,1);
	IDX_OBJECT_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_Character);
	lua_call(L,0,1);
	IDX_CHARACTER_LIB = lua_gettop(L);
	lua_pushcfunction(L, luaopen_ags_AudioClip);
	lua_call(L,0,1);
	IDX_AUDIOCLIP_LIB = lua_gettop(L);

	luaL_newmetatable(L, IMMORTAL_OBJECT_STORE);
	IDX_IMMORTAL_STORE = lua_gettop(L);

	Init_LuaValueList(L, IDX_IMMORTAL_STORE);

	luaL_newmetatable(L, "AGS_Dialog*");
	IDX_DIALOG_META = lua_gettop(L);
	
	luaL_newmetatable(L, "AGS_Character*");
	IDX_CHARACTER_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_InventoryItem*");
	IDX_INVENTORYITEM_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_GUIControl*");
	IDX_GUICONTROL_META = lua_gettop(L);
	// Considered "abstract-immortal" instead of "immortal" (no LuaMethods, etc.)
	luaL_newmetatable(L, "AGS_GUIControl* store");
	IDX_GUICONTROL_STORE = lua_gettop(L);

	luaL_newmetatable(L, "AGS_InvWindow*");
	IDX_INVWINDOW_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_Button*");
	IDX_BUTTON_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_TextBox*");
	IDX_TEXTBOX_META = lua_gettop(L);

	lua_register(L, "GetLibTable", GetLibTable);

	luaL_newmetatable(L, "AGS_Label*");
	IDX_LABEL_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_ListBox*");
	IDX_LISTBOX_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_Slider*");
	IDX_SLIDER_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_GUI*");
	IDX_GUI_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_AudioClip*");
	IDX_AUDIOCLIP_META = lua_gettop(L);

	luaL_newmetatable(L, "AGS_Hotspot*");
	IDX_HOTSPOT_META = lua_gettop(L);
	luaL_newmetatable(L, "AGS_Hotspot* store");
	IDX_HOTSPOT_STORE = lua_gettop(L);

	luaL_newmetatable(L, "AGS_Object*");
	IDX_OBJECT_META = lua_gettop(L);
	luaL_newmetatable(L, "AGS_Object* store");
	IDX_OBJECT_STORE = lua_gettop(L);

	luaL_newmetatable(L, "AGS_Region*");
	IDX_REGION_META = lua_gettop(L);
	luaL_newmetatable(L, "AGS_Region* store");
	IDX_REGION_STORE = lua_gettop(L);

	lua_pushcfunction(L, luaopen_ags_InventoryItem);
	lua_call(L,0,1);
	IDX_INVENTORYITEM_LIB = lua_gettop(L);

	lua_pushvalue(L, IDX_CHARACTER_META);
	lua_pushvalue(L, IDX_IMMORTAL_STORE);
	lua_pushcclosure(L, ags_get_player, 2);
	lua_pushvalue(L, -1);
	lua_setfield(L, IDX_AGS_LIB, "getplayer");
	lua_setfield(L, IDX_AGS_LIB, "get_player");

	{
		const luaL_Reg* lib_entry;

		// Immortal
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_CHARACTER_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_CHARACTER_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_INVENTORYITEM_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_INVENTORYITEM_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_DIALOG_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_DIALOG_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_GUI_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_GUI_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_LABEL_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_LABEL_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_BUTTON_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_BUTTON_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_TEXTBOX_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_TEXTBOX_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_INVWINDOW_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_INVWINDOW_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_LISTBOX_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_LISTBOX_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_SLIDER_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_SLIDER_META, lib_entry->name);
		}
		for (lib_entry = ags_immortal_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_AUDIOCLIP_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_AUDIOCLIP_META, lib_entry->name);
		}

		// Room-specific

		for (lib_entry = ags_hotspot_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_HOTSPOT_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_HOTSPOT_META, lib_entry->name);
		}
		for (lib_entry = ags_region_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_REGION_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_REGION_META, lib_entry->name);
		}
		for (lib_entry = ags_object_meta; lib_entry->func; lib_entry++) {
			lua_pushvalue(L, IDX_OBJECT_LIB);
			lua_pushcclosure(L, lib_entry->func, 1);
			lua_setfield(L, IDX_OBJECT_META, lib_entry->name);
		}
	}

	{
		long i;
		int IDX_CHARACTER_ARRAY;

		lua_createtable(L, engine->GetNumCharacters(), 0);
		IDX_CHARACTER_ARRAY = lua_gettop(L);

		lua_pushvalue(L, IDX_CHARACTER_ARRAY);
		lua_setfield(L, IDX_AGS_LIB, "character");

		for (i = 0; i < engine->GetNumCharacters(); i++) {
			AGSCharacter* c = engine->GetCharacter(i);
			luags_pushCharacter(L, c, IDX_CHARACTER_META, IDX_IMMORTAL_STORE);

			// put light userdata -> object into registry, for LuaMethod
			lua_pushlightuserdata(L, c);
			lua_pushvalue(L,-2);
			lua_settable(L, LUA_REGISTRYINDEX);

			// set up function environment for expando-ness
			lua_newtable(L);
			lua_setfenv(L,-2);

			// add to array
			lua_pushvalue(L, -1);
			lua_rawseti(L, IDX_CHARACTER_ARRAY, AGS_Character_get_ID(c));

			// add as script name
			lua_setfield(L, IDX_AGS_LIB, c->scrname);
		}
		lua_settop(L, IDX_CHARACTER_ARRAY - 1); // pop off
	}

	{
		int IDX_INVENTORY_ARRAY;
		long long* inventory = (long long*)engine->GetScriptFunctionAddress("inventory");

		lua_createtable(L, AGS_Game_get_InventoryItemCount(), 0);
		IDX_INVENTORY_ARRAY = lua_gettop(L);

		lua_pushvalue(L, IDX_INVENTORY_ARRAY);
		lua_setfield(L, IDX_AGS_LIB, "inventory");

		lua_getfield(L, LUA_REGISTRYINDEX, "AGSInventoryItems");
		lua_pushnil(L);
		while (lua_next(L,-2))
		{
			AGS_InventoryItem* item = (AGS_InventoryItem*)(inventory + lua_tointeger(L,-2));
			luags_pushInventoryItem(L, item, IDX_INVENTORYITEM_META, IDX_IMMORTAL_STORE);

			// add to registry for LuaMethod
			lua_pushlightuserdata(L, item);
			lua_pushvalue(L,-2);
			lua_settable(L, LUA_REGISTRYINDEX);

			// add expando table
			lua_newtable(L);
			lua_setfenv(L,-2);

			// add to inventory array
			lua_pushvalue(L,-1);
			lua_rawseti(L, IDX_INVENTORY_ARRAY, AGS_InventoryItem_get_ID(item));

			// add as script name
			lua_settable(L, IDX_AGS_LIB);
		}

		lua_settop(L, IDX_INVENTORY_ARRAY-1);
	}

	{
		lua_getfield(L, LUA_REGISTRYINDEX, "AGSAudioClips");
		int IDX_AUDIOCLIP_NAMES = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, -2))
		{
			AGS_AudioClip* clip = (AGS_AudioClip*)engine->GetScriptFunctionAddress(lua_tostring(L,-1));
			luags_pushAudioClip(L, clip, IDX_AUDIOCLIP_META, IDX_IMMORTAL_STORE);

			// set up function environment for expando-ness
			lua_newtable(L);
			lua_setfenv(L,-2);

			lua_settable(L, IDX_AGS_LIB);
		}
		lua_settop(L, IDX_AUDIOCLIP_NAMES - 1);
	}

	{
		int IDX_DIALOG_ARRAY;
		long long* dialog_array = (long long*)engine->GetScriptFunctionAddress("dialog");

		lua_createtable(L, AGS_Game_get_DialogCount(), 0);
		IDX_DIALOG_ARRAY = lua_gettop(L);

		lua_pushvalue(L, IDX_DIALOG_ARRAY);
		lua_setfield(L, IDX_AGS_LIB, "dialog");

		lua_getfield(L, LUA_REGISTRYINDEX, "AGSDialogs");
		lua_pushnil(L);

		while (lua_next(L,-2))
		{
			AGS_Dialog* dialog = (AGS_Dialog*)(dialog_array + lua_tointeger(L,-2));
			luags_pushDialog(L, dialog, IDX_DIALOG_META, IDX_IMMORTAL_STORE);

			// add to registry for LuaMethod
			lua_pushlightuserdata(L, dialog);
			lua_pushvalue(L,-2);
			lua_settable(L, LUA_REGISTRYINDEX);

			// add expando table
			lua_newtable(L);
			lua_setfenv(L,-2);

			// add to dialog array
			lua_pushvalue(L,-1);
			lua_rawseti(L, IDX_DIALOG_ARRAY, AGS_Dialog_get_ID(dialog));

			// add as script name
			lua_settable(L, IDX_AGS_LIB);
		}

		lua_settop(L, IDX_DIALOG_ARRAY-1);
	}

	{
		long long* gui_array = (long long*)engine->GetScriptFunctionAddress("gui");
		int IDX_GUI_ARRAY;

		lua_createtable(L, AGS_Game_get_GUICount(), 0);
		IDX_GUI_ARRAY = lua_gettop(L);

		lua_pushvalue(L, IDX_GUI_ARRAY);
		lua_setfield(L, IDX_AGS_LIB, "gui");

		lua_getfield(L, LUA_REGISTRYINDEX, "AGSGUIs");
		lua_pushnil(L);
		while (lua_next(L,-2))
		{
			int i;
			AGS_GUI* gui = (AGS_GUI*)(gui_array + lua_tointeger(L,-2));
			luags_pushGUI(L, gui, IDX_GUI_META, IDX_IMMORTAL_STORE);
			// ID, table, ud

			// add to registry for LuaMethod
			lua_pushlightuserdata(L, gui);
			lua_pushvalue(L,-2);
			lua_settable(L, LUA_REGISTRYINDEX);

			// add expando table
			lua_newtable(L);
			lua_setfenv(L,-2);

			for (i = 0; i < AGS_GUI_get_ControlCount(gui); i++) {
				const char* type;
				AGS_GUIControl* control = AGS_GUI_geti_Controls(gui,i);
				lua_rawgeti(L, -2, i);
				lua_getfield(L, -1, "type");
				type = lua_tostring(L,-1);
				lua_getfield(L, -2, "name");
				if (!lua_isstring(L,-1) || lua_objlen(L,-1) == 0) {
					lua_pop(L,3);
					continue;
				}
				if (!strcmp(type,"InventoryWindow")) {
					AGS_InvWindow* invWindow = AGS_GUIControl_get_AsInvWindow(control);
					luags_pushInvWindow(L, invWindow, IDX_INVWINDOW_META, IDX_IMMORTAL_STORE);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_pushlightuserdata(L, invWindow);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else if (!strcmp(type,"Button")) {
					AGS_Button* button = AGS_GUIControl_get_AsButton(control);
					luags_pushButton(L, button, IDX_BUTTON_META, IDX_IMMORTAL_STORE);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_pushlightuserdata(L, button);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else if (!strcmp(type,"TextBox")) {
					AGS_TextBox* textBox = AGS_GUIControl_get_AsTextBox(control);
					luags_pushTextBox(L, textBox, IDX_TEXTBOX_META, IDX_IMMORTAL_STORE);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_pushlightuserdata(L, textBox);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else if (!strcmp(type,"Slider")) {
					AGS_Slider* slider = AGS_GUIControl_get_AsSlider(control);
					luags_pushSlider(L, slider, IDX_SLIDER_META, IDX_IMMORTAL_STORE);

					lua_pushlightuserdata(L, slider);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else if (!strcmp(type,"Label")) {
					AGS_Label* label = AGS_GUIControl_get_AsLabel(control);
					luags_pushLabel(L, label, IDX_LABEL_META, IDX_IMMORTAL_STORE);

					lua_pushlightuserdata(L, label);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else if (!strcmp(type,"ListBox")) {
					AGS_ListBox* listBox = AGS_GUIControl_get_AsListBox(control);
					luags_pushListBox(L, listBox, IDX_LISTBOX_META, IDX_IMMORTAL_STORE);

					lua_pushlightuserdata(L, listBox);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
				else {
					luags_pushGUIControl(L, control, IDX_GUICONTROL_META, IDX_IMMORTAL_STORE);

					lua_pushlightuserdata(L, control);
					lua_pushvalue(L,-2);
					lua_rawset(L,LUA_REGISTRYINDEX);

					lua_newtable(L);
					lua_setfenv(L,-2);

					lua_rawset(L, IDX_AGS_LIB);
					lua_pop(L,2);
				}
			}

			// add to gui array
			lua_pushvalue(L,-1);
			lua_rawseti(L, IDX_GUI_ARRAY, AGS_GUI_get_ID(gui));

			// add as script name
			lua_getfield(L, -2, "name");
			lua_replace(L, -3);
			lua_settable(L, IDX_AGS_LIB);
		}

		lua_settop(L, IDX_GUI_ARRAY-1);
	}

	{
		*(long long**)lua_newuserdata(L, sizeof(long long*)) = ags_hotspot_array;
		lua_newtable(L);
		{
			const luaL_Reg* lib_entry;
			for (lib_entry = hotspot_array_meta; lib_entry->func; lib_entry++) {
				lua_pushstring(L, lib_entry->name);
				lua_pushvalue(L, IDX_HOTSPOT_META);
				lua_pushvalue(L, IDX_HOTSPOT_STORE);
				lua_pushcclosure(L, lib_entry->func, 2);
				lua_rawset(L, -3);
			}
		}
		lua_setmetatable(L,-2);
		lua_setfield(L, IDX_AGS_LIB, "hotspot");
	}

	{
		*(long long**)lua_newuserdata(L, sizeof(long long*)) = ags_region_array;
		lua_newtable(L);
		{
			const luaL_Reg* lib_entry;
			for (lib_entry = region_array_meta; lib_entry->func; lib_entry++) {
				lua_pushstring(L, lib_entry->name);
				lua_pushvalue(L, IDX_REGION_META);
				lua_pushvalue(L, IDX_REGION_STORE);
				lua_pushcclosure(L, lib_entry->func, 2);
				lua_rawset(L, -3);
			}
		}
		lua_setmetatable(L,-2);
		lua_setfield(L, IDX_AGS_LIB, "region");
	}

	{
		*(long long**)lua_newuserdata(L, sizeof(long long*)) = ags_object_array;
		lua_newtable(L);
		{
			const luaL_Reg* lib_entry;
			for (lib_entry = object_array_meta; lib_entry->func; lib_entry++) {
				lua_pushstring(L, lib_entry->name);
				lua_pushvalue(L, IDX_OBJECT_META);
				lua_pushvalue(L, IDX_OBJECT_STORE);
				lua_pushcclosure(L, lib_entry->func, 2);
				lua_rawset(L, -3);
			}
		}
		lua_setmetatable(L,-2);
		lua_setfield(L, IDX_AGS_LIB, "object");
	}

	lua_pushcfunction(L, ags_type);
	lua_setfield(L, IDX_AGS_LIB, "type");

#define INJECT_EVENT_CONSTANT(name)	{ lua_pushnumber(L, AGS##name); lua_setfield(L, -2, #name); }
	INJECT_EVENT_CONSTANT(E_KEYPRESS);
	INJECT_EVENT_CONSTANT(E_MOUSECLICK);
	INJECT_EVENT_CONSTANT(E_POSTSCREENDRAW);
	INJECT_EVENT_CONSTANT(E_SAVEGAME);
	INJECT_EVENT_CONSTANT(E_RESTOREGAME);
	INJECT_EVENT_CONSTANT(E_PREGUIDRAW);
	INJECT_EVENT_CONSTANT(E_LEAVEROOM);
	INJECT_EVENT_CONSTANT(E_ENTERROOM);
	INJECT_EVENT_CONSTANT(E_TRANSITIONOUT);
	INJECT_EVENT_CONSTANT(E_TRANSITIONIN);
	INJECT_EVENT_CONSTANT(E_FINALSCREENDRAW);
	INJECT_EVENT_CONSTANT(E_TRANSLATETEXT);
	INJECT_EVENT_CONSTANT(E_SCRIPTDEBUG);
	INJECT_EVENT_CONSTANT(E_SPRITELOAD);
	INJECT_EVENT_CONSTANT(E_PRERENDER);
#undef INJECT_EVENT_CONSTANT

	main_L = L;

	lua_pushcfunction(L, autopersist);
	lua_call(L,0,0);

	lua_getfield(L, LUA_REGISTRYINDEX, "initstate");
	if (lua_isstring(L,-1)) {
		lua_State* persist_L = lua_newthread(L);
		lua_getfield(persist_L, LUA_REGISTRYINDEX, "unpersist");
		pluto_unpersist(persist_L, ReadSingleString, L);
		lua_xmove(persist_L, L, 1);
		lua_setfield(L, LUA_GLOBALSINDEX, "compiletime");
		lua_pop(L,1);
		return 0;
	}
	else {
		// THIS MUST BE CALLED *AFTER* AUTOPERSIST
		lua_pushcfunction(L, hide_agsinternal);
		lua_call(L,0,0);
	}

	return 0;
}

int need_restoration;

void AGS_EngineStartup(IAGSEngine *lpEngine) {
	lua_State* new_L;
	engine = lpEngine;
	if (16 != engine->GetSavedData((char*)lscripts_guid, 16)) {
		main_L = NULL;
		return;
	}
	if (engine->version < 24) {
		engine->AbortGame("Lua for AGS requires AGS 3.2");
	}
	GetScriptFunctionAddresses(engine);
	RegisterLuaInterop(engine);
	RegisterLuaModuleStruct();
	RegisterLuaValueListFunctions();

	engine->AddManagedObjectReader(LUAGODOBJECT_TYPENAME, &gLuaGodObjectReader);
	engine->RegisterManagedObject(&gLuaGodObjectInterface, &gLuaGodObjectInterface);
	engine->IncrementManagedObjectRefCount((const char*)&gLuaGodObjectInterface);
	
	need_restoration = 0;

	// Request event hooks
	engine->RequestEventHook(AGSE_SAVEGAME);
	engine->RequestEventHook(AGSE_RESTOREGAME);
	engine->RequestEventHook(AGSE_ENTERROOM);
	engine->RequestEventHook(AGSE_PRESAVEGAME);
	engine->RequestEventHook(AGSE_POSTRESTOREGAME);

	// Immortal arrays
	ags_hotspot_array = (long long*)engine->GetScriptFunctionAddress("hotspot");
	ags_object_array = (long long*)engine->GetScriptFunctionAddress("object");
	ags_region_array = (long long*)engine->GetScriptFunctionAddress("region");
	ags_character_array = (long long*)engine->GetScriptFunctionAddress("character");

	// Create and initialise Lua state
	new_L = luaL_newstate();

	lua_pushcfunction(new_L, init_main_L);
	lua_call(new_L,0,0);
}

void AGS_EngineShutdown() {

	// Unfortunately, it looks like some things (e.g. DynamicSprite.Delete())
	// can cause a shutdown crash if called at this point...

	/*
	if (main_L) {
		ags_closing = 1;
		lua_close(main_L);
	}
	*/
}

#define USE_DIFF

int aux_SaveGame(lua_State *L, int compileTime, lua_Writer output) {
	int handle = compileTime ? 0 : (int)lua_tonumber(L,1);
	int IDX_SAVEGAMEDATA;
	// create the save game data table
	lua_newtable(L);
	IDX_SAVEGAMEDATA = lua_gettop(L);
	// add the global variable scope to it
	lua_pushvalue(L, LUA_GLOBALSINDEX);
	lua_setfield(L, IDX_SAVEGAMEDATA, "_G");
	// add the "loaded" table to it
	lua_getfield(L, LUA_REGISTRYINDEX, "_LOADED");
	lua_setfield(L, IDX_SAVEGAMEDATA, "_LOADED");
#ifdef USE_DIFF
	// run diff
	lua_pushcfunction(main_L, diff);
	lua_call(main_L,0,0);
	// add the diff persist table to it
	lua_getfield(L, LUA_REGISTRYINDEX, "diffcurrent");
	lua_setfield(L, IDX_SAVEGAMEDATA, "diffcurrent");
#endif
	// add the string metatable
	lua_pushliteral(L, "");
	if (lua_getmetatable(L, -1)) {
		lua_setfield(L, IDX_SAVEGAMEDATA, "string meta");
	}
	lua_pop(L,1);
	if (!compileTime) {
		// add the Lua Value Lists
		PushLuaValueListsForSerialization(L, IDX_SAVEGAMEDATA);
	}
	// add a mapping from meta to lib table for immortals
	lua_newtable(L);
	for (const char** entry = LuaMethodSupportingTypes; *entry; entry++) {
		lua_pushstring(L, *entry);
		lua_getfield(L, LUA_REGISTRYINDEX, *entry);
		GetLibTableForImmortalMetatable(L, lua_gettop(L));
		lua_remove(L,-2);
		lua_rawset(L,-3);
	}
	lua_setfield(L, IDX_SAVEGAMEDATA, "Meta2Lib");
	// add a mapping from immortal objects to their fenvs
	// (nil for empty ones)
	lua_newtable(L);
	lua_getfield(L, LUA_REGISTRYINDEX, IMMORTAL_OBJECT_STORE);
	lua_pushnil(L);
	while (lua_next(L,-2)) {
		lua_getfenv(L,-1);
		lua_pushnil(L);
		if (lua_next(L,-2)) {
			lua_pop(L,2);
			// mapping, store, light userdata key, full userdata value, fenv
			lua_rawset(L,-5);
		}
		else {
			lua_pop(L,2);
		}
	}
	lua_pop(L,1);
	lua_setfield(L, IDX_SAVEGAMEDATA, IMMORTAL_OBJECT_STORE);
	{
		// add a mapping from hotspots to their fenvs
		// (nil for empty ones)
		lua_newtable(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Hotspot* store");
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			lua_getfenv(L,-1);
			lua_pushnil(L);
			if (lua_next(L,-2)) {
				lua_pop(L,2);
				// mapping, store, light userdata key, full userdata value, fenv
				lua_rawset(L,-5);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_pop(L,1);
		lua_setfield(L, IDX_SAVEGAMEDATA, "AGS_Hotspot* store");
	}
	{
		// add a mapping from regions to their fenvs
		// (nil for empty ones)
		lua_newtable(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Region* store");
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			lua_getfenv(L,-1);
			lua_pushnil(L);
			if (lua_next(L,-2)) {
				lua_pop(L,2);
				// mapping, store, light userdata key, full userdata value, fenv
				lua_rawset(L,-5);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_pop(L,1);
		lua_setfield(L, IDX_SAVEGAMEDATA, "AGS_Region* store");
	}
	{
		// add a mapping from room objects to their fenvs
		// (nil for empty ones)
		lua_newtable(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Object* store");
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			lua_getfenv(L,-1);
			lua_pushnil(L);
			if (lua_next(L,-2)) {
				lua_pop(L,2);
				// mapping, store, light userdata key, full userdata value, fenv
				lua_rawset(L,-5);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_pop(L,1);
		lua_setfield(L, IDX_SAVEGAMEDATA, "AGS_Object* store");
	}
	// Create persist state
	lua_State* persist_L = lua_newthread(L);
	//lua_pushvalue(L, LUA_GLOBALSINDEX);
	//int IDX_OLDGLOBALS = lua_gettop(L);
	if (compileTime) {
		lua_getfield(persist_L, LUA_REGISTRYINDEX, "persist");
		lua_pushvalue(L, IDX_SAVEGAMEDATA);
		lua_xmove(L, persist_L, 1);

		lua_newtable(persist_L);
		lua_replace(persist_L, LUA_GLOBALSINDEX);
		pluto_persist(persist_L, output, NULL);

		//lua_pushvalue(L, IDX_OLDGLOBALS);
		//lua_replace(L, LUA_GLOBALSINDEX);

	}
	else {
		AGSLuaPersistState state;
		state.handle = handle;
		state.finished = 0;
		state.count = 0;
		luaL_buffinit(L, &state.b);
		state.z_stream.zalloc = Z_NULL;
		state.z_stream.zfree = Z_NULL;
		state.z_stream.opaque = NULL;
		state.z_stream.next_out = (Bytef*)luaL_prepbuffer(&state.b);
		state.z_stream.avail_out = LUAL_BUFFERSIZE;
		deflateInit(&state.z_stream, ZLIB_DEFLATE_LEVEL);

		lua_getfield(persist_L, LUA_REGISTRYINDEX, "persist");
		lua_pushvalue(L, IDX_SAVEGAMEDATA);
		lua_xmove(L, persist_L, 1);

		// Complicated! Pluto will check the function environment of any Lua functions, see if they are the same
		// as the globals table, and if so, not bother to persist it (instead it will just set the environment
		// to whatever LUA_GLOBALSINDEX is when the function gets unpersisted)... but we WANT the environment to
		// be persisted! because we are intending to immediately *replace* the globals table.
		// to get around this, I am setting the globals table to a new, empty table just before persisting, then
		// setting it back afterwards...
		lua_newtable(persist_L);
		lua_replace(persist_L, LUA_GLOBALSINDEX);
		pluto_persist(persist_L, AGSLuaPersistWriter, &state);

		//lua_pushvalue(L, IDX_OLDGLOBALS);
		//lua_replace(L, LUA_GLOBALSINDEX);

		state.z_stream.avail_in = 0;
		deflate(&state.z_stream, Z_FINISH);
		while (state.z_stream.avail_out < LUAL_BUFFERSIZE) {
			luaL_addsize(&state.b, LUAL_BUFFERSIZE - state.z_stream.avail_out);
			state.z_stream.avail_out = LUAL_BUFFERSIZE;
			state.z_stream.next_out = (Bytef*)luaL_prepbuffer(&state.b);
			deflate(&state.z_stream, Z_FINISH);
		}
		deflateEnd(&state.z_stream);

		int len;
		const char* data;
		const char* data_end;
		luaL_pushresult(&state.b);
		len = (int)lua_objlen(L,-1);
		lua_pushlstring(L, (const char*)&len, sizeof(int));

		data = lua_tostring(L,-1);
		data_end = data + sizeof(int);
		while (data < data_end) {
			data += engine->FWrite((void*)data, (long)(data_end - data), state.handle);
		}

		data = lua_tostring(L,-2);
		data_end = data + len;
		while (data < data_end) {
			data += engine->FWrite((void*)data, (long)(data_end - data), state.handle);
		}

#ifdef USE_DIFF
		// Restore diff-merged tables
		lua_pushcfunction(main_L, merge);
		lua_call(main_L,0,0);
#endif
		// Turn garbage collector back on
		lua_gc(L, LUA_GCRESTART, 0);
	}
	return 0;
}

int ags_SaveGame(lua_State *L) {
	return aux_SaveGame(L, 0, NULL);
}

int aux_LoadGame(lua_State *L, int handle, lua_Reader input, void* ud) {
	int IDX_SAVEGAMEDATA;
	luaL_Buffer b;
	int to_read;
	lua_State* persist_L = lua_newthread(L);
	luaL_buffinit(main_L, &b);

	if (input) {
		lua_getfield(persist_L, LUA_REGISTRYINDEX, "unpersist");
		pluto_unpersist(persist_L, input, ud);

		lua_xmove(persist_L, L, 1);
		lua_setfield(L, LUA_GLOBALSINDEX, "compiletime");
		lua_pop(L,1);
		return 0;
	}
	else {
		AGSLuaUnpersistState state;
		engine->FRead(&to_read, sizeof(int), handle);
		while (to_read > 0) {
			int read = engine->FRead(
				(void*)luaL_prepbuffer(&b),
				(to_read > LUAL_BUFFERSIZE) ? LUAL_BUFFERSIZE : to_read,
				handle);
			luaL_addsize(&b, read);
			to_read -= read;
		}
		luaL_pushresult(&b);
		state.z_stream.avail_in = (uInt)lua_objlen(L,-1);
		state.z_stream.next_in = (Bytef*)lua_tostring(L,-1);
		state.z_stream.avail_out = ZLIB_INFLATE_BUFSIZE;
		state.z_stream.next_out = state.buf;
		state.z_stream.zalloc = Z_NULL;
		state.z_stream.zfree = Z_NULL;
		state.z_stream.opaque = NULL;
		inflateInit(&state.z_stream);
		lua_getfield(persist_L, LUA_REGISTRYINDEX, "unpersist");

		pluto_unpersist(persist_L, AGSLuaPersistReader, &state);

		inflateEnd(&state.z_stream);
	}

	lua_xmove(persist_L, L, 1);

	IDX_SAVEGAMEDATA = lua_gettop(L);
	if (!lua_istable(L,-1)) {
		engine->AbortGame("[Lua] Invalid save game data");
	}

	lua_getfield(L, IDX_SAVEGAMEDATA, "_G");
	int IDX_NEW_G = lua_gettop(L);

	if (!lua_istable(L,-1)) {
		engine->AbortGame("[Lua] Save game data contains no _G");
	}

	lua_getfield(L, IDX_SAVEGAMEDATA, "_LOADED");
	int IDX_NEW_LOADED = lua_gettop(L);

	if (!lua_istable(L,-1)) {
		engine->AbortGame("[Lua] Save game data contains no _LOADED");
	}

	lua_pushvalue(L,IDX_NEW_G);
	lua_xmove(L,vlist_L,1);
	lua_replace(vlist_L,LUA_GLOBALSINDEX);
	
	lua_pushvalue(L,IDX_NEW_G);
	lua_replace(L, LUA_GLOBALSINDEX);

	lua_pushvalue(L, IDX_NEW_LOADED);
	lua_setfield(L, LUA_REGISTRYINDEX, "_LOADED");

	// fix environments of functions in lscripts
	lua_getfield(L, LUA_REGISTRYINDEX, "lscripts");
	if (lua_istable(L,-1)) {
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			lua_pushvalue(L,IDX_NEW_G);
			lua_setfenv(L,-2);
			lua_pop(L,1);
		}
	}
	lua_pop(L,1);

#ifdef USE_DIFF
	lua_getfield(L, IDX_SAVEGAMEDATA, "diffcurrent");
	lua_setfield(L, LUA_REGISTRYINDEX, "diffcurrent");

	lua_pushcfunction(L, merge);
	lua_call(L,0,0);
#endif

	lua_pushliteral(L,"");
	lua_getfield(L, IDX_SAVEGAMEDATA, "string meta");
	lua_setmetatable(L,-2);
	lua_pop(L,1);

	DeserializeLuaValueLists(L, IDX_SAVEGAMEDATA);

	lua_getfield(L, IDX_SAVEGAMEDATA, "Meta2Lib");
	if (lua_istable(L,-1)) {
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			lua_pushvalue(L,-2);
			lua_gettable(L, LUA_REGISTRYINDEX);
			SetLibTableForImmortalMetatable(L, lua_gettop(L), lua_gettop(L)-1);
			lua_pop(L,2);
		}
	}
	lua_pop(L,1);

	lua_getfield(L, IDX_SAVEGAMEDATA, IMMORTAL_OBJECT_STORE);
	if (lua_istable(L,-1)) {
		int IDX_IMMORTAL_FENVS = lua_gettop(L);
		lua_getfield(L, LUA_REGISTRYINDEX, IMMORTAL_OBJECT_STORE);
		int IDX_IMMORTAL_STORE = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, IDX_IMMORTAL_STORE)) {
			lua_pushvalue(L,-1);
			lua_gettable(L, IDX_IMMORTAL_FENVS);
			if (lua_istable(L,-1)) {
				lua_setfenv(L,-2);
				lua_pop(L,1);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_settop(L, IDX_IMMORTAL_FENVS);
	}
	lua_pop(L,1);

	lua_getfield(L, IDX_SAVEGAMEDATA, "AGS_Hotspot* store");
	if (lua_istable(L,-1)) {
		int IDX_HOTSPOT_FENVS = lua_gettop(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Hotspot* store");
		int IDX_HOTSPOT_STORE = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, IDX_HOTSPOT_STORE)) {
			lua_pushvalue(L,-1);
			lua_gettable(L, IDX_HOTSPOT_FENVS);
			if (lua_istable(L,-1)) {
				lua_setfenv(L,-2);
				lua_pop(L,1);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_settop(L, IDX_HOTSPOT_FENVS);
	}
	lua_pop(L,1);

	lua_getfield(L, IDX_SAVEGAMEDATA, "AGS_Region* store");
	if (lua_istable(L,-1)) {
		int IDX_REGION_FENVS = lua_gettop(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Region* store");
		int IDX_REGION_STORE = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, IDX_REGION_STORE)) {
			lua_pushvalue(L,-1);
			lua_gettable(L, IDX_REGION_FENVS);
			if (lua_istable(L,-1)) {
				lua_setfenv(L,-2);
				lua_pop(L,1);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_settop(L, IDX_REGION_FENVS);
	}
	lua_pop(L,1);

	lua_getfield(L, IDX_SAVEGAMEDATA, "AGS_Object* store");
	if (lua_istable(L,-1)) {
		int IDX_OBJECT_FENVS = lua_gettop(L);
		lua_getfield(L, LUA_REGISTRYINDEX, "AGS_Object* store");
		int IDX_OBJECT_STORE = lua_gettop(L);
		lua_pushnil(L);
		while (lua_next(L, IDX_OBJECT_STORE)) {
			lua_pushvalue(L,-1);
			lua_gettable(L, IDX_OBJECT_FENVS);
			if (lua_istable(L,-1)) {
				lua_setfenv(L,-2);
				lua_pop(L,1);
			}
			else {
				lua_pop(L,2);
			}
		}
		lua_settop(L, IDX_OBJECT_FENVS);
	}
	lua_pop(L,1);

	return 0;
}

int ags_LoadGame(lua_State *L) {
	int handle = (int)lua_tointeger(L,1);
	return aux_LoadGame(L, handle, NULL, NULL);
}

int AGS_EngineOnEvent(int evt, int data) {
	switch(evt) {
		case AGSE_ENTERROOM: {
			ags_current_room = data;
			// Take advantage of the slight delay by adding a bit of Lua-universe cleanup to it
			lua_gc(main_L, LUA_GCCOLLECT, 0);
			break;
		}
		// Before saving the game:
		// Attempt to call presave()
	    // Do a full garbage collection sweep
		// Turn off garbage collection
		case AGSE_PRESAVEGAME: {
			/*
			lua_getglobal(main_L, "presave");
			if (lua_isfunction(main_L, -1) || (luaL_getmetafield(main_L,-1,"__call") && (lua_pop(main_L,1), 1))) {
				lua_call(main_L, 0, 0);
			}
			else {
				lua_pop(main_L, 1);
			}
			*/
			int old_count = lua_gc(main_L, LUA_GCCOUNT, 0);
			int old_countb = lua_gc(main_L, LUA_GCCOUNTB, 0);
			int inc_count = 0;
			for (;;) {
				lua_gc(main_L, LUA_GCCOLLECT, 0);
				int new_count = lua_gc(main_L, LUA_GCCOUNT, 0);
				int new_countb = lua_gc(main_L, LUA_GCCOUNTB, 0);
				if (new_count > old_count || (new_count == old_count && new_countb > old_countb)) {
					if (inc_count++ > 1000) {
						engine->AbortGame("[Lua] Pre-save garbage collection error: memory use increasing");
					}
				}
				if (new_count == old_count && new_count == old_count) {
					break;
				}
				old_count = new_count;
				old_countb = new_countb;
			}
			lua_gc(main_L, LUA_GCSTOP, 0);
			break;
		}
		case AGSE_SAVEGAME: {
			lua_pushcfunction(main_L, ags_SaveGame);
			lua_pushinteger(main_L, data);
			lua_call(main_L,1,0);
			break;
		}
		case AGSE_RESTOREGAME: {
			lua_gc(main_L, LUA_GCSTOP, 0);
			// Close the whole state and start anew
			ags_closing = 1;
			lua_close(main_L);
			ags_closing = 0;
			lua_State* new_L = luaL_newstate();
			lua_gc(new_L, LUA_GCSTOP, 0);
			init_main_L(new_L);
			lua_newtable(new_L);
			lua_setfield(new_L, LUA_REGISTRYINDEX, "Ephemeral Holding Bay");
			lua_pushcfunction(new_L, ags_LoadGame);
			lua_pushinteger(new_L, data);
			lua_call(new_L,1,0);
			break;
		}
		case AGSE_POSTRESTOREGAME: {
			/*
			lua_getglobal(main_L, "postrestore");
			if (lua_isfunction(main_L, -1) || (luaL_getmetafield(main_L,-1,"__call") && (lua_pop(main_L,1), 1))) {
				lua_call(main_L, 0, 0);
			}
			else {
				lua_pop(main_L, 1);
			}
			*/
			_RestoreLuaReliability();
		}
	}
	return 0;
}

void LuaGodObjectReader::Unserialize(int key, const char *serializedData, int dataSize) {
	return;
}

void _RestoreLuaReliability() {
	lua_pushnil(vlist_L);
	lua_replace(vlist_L, VLIST_STACK_RESTORE_LISTS);

	lua_getfield(main_L, LUA_REGISTRYINDEX, "Ephemeral Holding Bay");

	lua_pushnil(main_L);
	while (lua_next(main_L,-2)) {
		EphemeralContainer* container = (EphemeralContainer*)lua_touserdata(main_L,-1);
		container->ptr = (const char*)engine->GetManagedObjectAddressByKey(container->key);
		if (container->ptr) {
			lua_getmetatable(main_L,-2);
			lua_getfield(main_L,-1,"__store");
			lua_remove(main_L,-2);
			lua_insert(main_L,-2);
			lua_pushlightuserdata(main_L, (void*)container->ptr);
			lua_insert(main_L,-2);
			lua_rawset(main_L,-3);
			lua_pop(main_L,1);
		}
		else {
			lua_pop(main_L,2);
		}
	}

	lua_pop(main_L, 1);

	lua_pushnil(main_L);
	lua_setfield(main_L, LUA_REGISTRYINDEX, "Ephemeral Holding Bay");

	lua_gc(main_L, LUA_GCRESTART, 0);
	need_restoration = 0;
}

DLLEXPORT void PrepareForCompileTimeScripts(lua_State* L) {
	luaL_openlibs(L);
	// TODO: add dummies in for every function and variable here
	// TODO: add working versions of require, runscript, and doscript
	autopersist(L);
}

DLLEXPORT void WriteInitState(lua_State *L, lua_Writer output) {
	aux_SaveGame(L, 1, output);
}
