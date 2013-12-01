extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <llh.h>
}
#include <string.h>
#include "AGSLua.h"
#include "agslua_autogen.h"
#include "agsplugin.h"

/*
static const char* LUA_INTERNAL_INIT =
	"local getmetatable, getstored = agsinternal.getmetatable, agsinternal.getstored;"
	"local GetManagedObjectByKey, GetKeyForManagedObject "
		"= agsinternal.GetManagedObjectByKey, agsinternal.GetKeyForManagedObject;"
	"function agsinternal.persistephemeral(self) "
		"local key, mt = GetKeyForManagedObject(self), getmetatable(self);"
		"return function() "
			"local ptr = GetManagedObjectByKey(key);"
			"return getstored(ptr, mt, mt.__store);"
		"end;"
	"end";
*/

static const char* LUA_INTERNAL_INIT =
	"local select = select;"
	"local error = error;"
	"local rawequal, pairs, type, tostring = rawequal, pairs, type, tostring;"
	"local table_concat = table.concat;"
	"local table_sort = table.sort;"

	"local getkey, getmetatable, ephemeralplaceholder "
		"= agsinternal.getkey, agsinternal.getmetatable, agsinternal.ephemeralplaceholder;"
	"function agsinternal.persistephemeral(self) "
		"local key, mt = getkey(self), getmetatable(self);"
		"return function() "
			"return ephemeralplaceholder(key, mt);"
		"end;"
	"end;"

	"local composeroomthing, decomposeroomthing "
		"= agsinternal.composeroomthing, agsinternal.decomposeroomthing;"
	"function agsinternal.persistroomthing(self) "
		"local roomid, thingid, mt = decomposeroomthing(self);"
		"return function() "
			"return composeroomthing(roomid, thingid, mt);"
		"end;"
	"end;"

	"local CallGameScriptFunction = agsinternal.CallGameScriptFunction;"
	"local type = type;"
	"function agsinternal.agsregister(name, global, numArgs) "
		"ags[name] = function(...) "
			"if (select('#',...) ~= numArgs) then "
				"error(name .. ': expecting ' .. numArgs .. ' arguments',2) "
			"end;"
			"for i = 1,numArgs do "
				"if (type(select(i,...)) ~= 'number') then "
					"error(name .. ' argument #' .. i .. ': expecting number',2)"
				"end;"
			"end;"
			"return CallGameScriptFunction(name, global, numArgs, ...);"
		"end;"
	"end;"


	"local getmetatable, setmetatable = agsinternal.getmetatable, agsinternal.setmetatable;"
	"local getpristine, setpristine = agsinternal.getpristine, agsinternal.setpristine;"
	"local MessageBox = agsinternal.MessageBox;"
	"local get_G = agsinternal.get_G;"



	"function agsinternal.makepristinepersist(name) "
		"return function(t) "
			"local pristine = getpristine(name); "
			"local diff = {};"
			// selfproxy: 
			"local selfproxy = {};"
			"for k,v in pairs(pristine) do "
				"local newv = t[k]; "
				"if (newv == nil) then "
					"diff[k] = diff;"
				"elseif not rawequal(v,newv) then "
					"diff[k] = newv;"
				"end;"
			"end;"
			"for k,newv in pairs(t) do "
				"if (newv == t) then "
					"newv = selfproxy; "
				"end;"
				"if (k == t) then "
					"k = selfproxy; "
				"end;"
				"if (pristine[k] == nil) then "
					"diff[k] = newv; "
				"end;"
			"end;"
			"local meta = getmetatable(t);"
			"return function() "
				"local pristine = getpristine(name);"
				"local new_t = {};"
				"for k,v in pairs(pristine) do "
					"if diff[k] == nil then "
						"new_t[k] = v;"
					"end;"
				"end;"
				"for k,v in pairs(diff) do "
					"if (k == selfproxy) then "
						"k = new_t;"
					"end;"
					"if (v == selfproxy) then "
						"v = new_t;"
					"end;"
					"if not rawequal(v, diff) then "
						"new_t[k] = v;"
					"end;"
				"end;"
				"return setmetatable(new_t, meta);"
			"end;"
		"end;"
	"end;"

	"function agsinternal.makepristine(my_t, name) "
		"do return end;"
		"local pristine = {};"
		"for k,v in pairs(my_t) do "
			"if type(v) ~= 'table' and type(k) ~= 'table' then "
				"pristine[k] = v; "
			"end;"
		"end;"
		"setpristine(name, pristine);"
		"setmetatable(my_t, {__persist=agsinternal.makepristinepersist(name)});"
	"end;"


	"local type, rawget, rawset, error, setmetatable"
       " = type, rawget, rawset, error, setmetatable;"
    "local getfenv = debug.getfenv;"

	"local function arrayproxy(lib, instance, expando, name) "
	  "local geti = 'geti_' .. name;"
	  "local seti = 'seti_' .. name;"
	  "if expando then "
	    "return setmetatable({}, {"
		  "__index = function(_,k)"
		               "local getter = expando[geti] or rawget(lib,geti);"
			           "if getter then  return getter(instance,k);  end;"
			  	    "end;"
		  "__newindex = function(_,k,v) "
		                 "local setter = expando[seti] or rawget(lib,seti);"
					     "if setter then  return setter(instance,k,v);  end;"
					     "error('attempt to modify readonly attribute ' .. name, 2);"
					    "end;"
	    "});"
	  "else "
	    "return setmetatable({}, {"
		  "__index = function(_,k)"
		               "local getter = rawget(lib,geti);"
			           "if getter then  return getter(instance,k);  end;"
			  	    "end;"
		  "__newindex = function(_,k,v) "
		                 "local setter = rawget(lib,seti);"
					     "if setter then  return setter(instance,k,v);  end;"
					     "error('attempt to modify readonly attribute ' .. name, 2);"
					    "end;"
	    "});"
	  "end;"
	"end;"

	"local function staticarrayproxy(lib, name) "
	  "local geti = 'geti_' .. name;"
	  "local seti = 'seti_' .. name;"
	  "return setmetatable({}, {"
		"__index = function(_,k) "
		             "local getter = rawget(lib, geti);"
					 "if getter then  return getter(k);  end;"
				   "end;"
		"__newindex = function(_,k,v) "
					   "local setter = rawget(lib, seti);"
					   "if setter then  return setter(k,v);  end;"
					   "error('attempt to modify readonly attribute ' .. name, 2);"
					  "end;"
	  "});"
	"end;"
	
	"local function lib__index(lib, k) "
	  "if (type(k) == 'string') then "
	    "local getter = rawget(lib, 'get_' .. k);"
	    "if getter then  return getter();  end;"
	    "getter = rawget(lib, 'geti_' .. k);"
	    "if getter then "
		  "local proxy = staticarrayproxy(lib, k);"
		  "rawset(lib, k, proxy);"
		  "return proxy;"
	    "end;"
	  "end;"
	"end;"

	"local function lib__newindex(lib, k, v) "
	  "if (type(k) == 'string') then "
	    "local setter = rawget(lib, 'set_' .. k);"
		"if setter then  return setter(v);  end;"
		"if rawget(lib, 'get_' .. k) or rawget(lib, 'geti_' .. k) then "
		  "error('attempt to modify read-only attribute ' .. k, 2);"
	    "end;"
	  "end;"
	  "return rawset(lib, k, v);"
	"end;"

	"local nonexpando_array_proxies = {};"
	
	"function agsinternal.initlib(lib, lib_meta, instance_meta, is_expando) "
	  "if instance_meta then "
	    "instance_meta.__metatable = true;"
		"if is_expando then "
  		  "instance_meta.__index = function(self, k) "
	        "local expando = getfenv(self);"
			"local v = expando[k] or rawget(lib, k);"
		    "if (v == nil) and (type(k) == 'string') then "
		      "local getname = 'get_' .. k;"
			  "local getter = expando[getname] or rawget(lib, getname);"
		      "if getter then  return getter(self);  end;"
			  "getname = 'geti_' .. k;"
			  "if expando[getname] or rawget(lib, getname) then "
		        "local proxy = arrayproxy(lib, self, expando, k);"
			    "rawset(expando, k, proxy);"
			    "return proxy;"
		      "end;"
		    "end;"
	        "return v;"
		  "end;"
		  "instance_meta.__newindex = function(instance, k, v) "
			"local expando = getfenv(instance);"
		    "if type(k) == 'string' then "
		      "local setname = 'set_' .. k;"
			  "local setter = expando[setname] or rawget(lib, setname);"
		      "if setter then  return setter(instance, v);  end;"
		      "local getname = 'get_' .. k;"
			  "if rawget(lib, getname) or expando[getname] then "
		        "error('attempt to set readonly attribute ' .. k,2);"
		      "end;"
              "getname = 'geti_' .. k;"
			  "if rawget(lib, getname) or expando[getname] then "
			    "error('invalid use of array attribute ' .. k,2);"
		      "end;"
		    "end;"
			"expando[k] = v;"
		  "end;"
		"else "
  		  "instance_meta.__index = function(self, k) "
		    "local v = rawget(lib, k);"
		    "if (v == nil) and (type(k) == 'string') then "
			  "local getter = rawget(lib, 'get_' .. k);"
		      "if getter then  return getter(self);  end;"
			  "if rawget(lib, 'geti_' .. k) then "
				"local proxies = nonexpando_array_proxies[self];"
				"if not proxies then "
					"proxies = {};"
					"nonexpando_array_proxies[self] = proxies;"
				"end;"
				"local proxy = proxies[k];"
				"if not proxy then "
					"proxy = arrayproxy(lib, self, nil, k);"
					"proxies[k] = proxy;"
				"end;"
			    "return proxy;"
		      "end;"
		    "end;"
	        "return v;"
		  "end;"
		  "instance_meta.__newindex = function(instance, k, v) "
		    "if type(k) == 'string' then "
		      "local setname = 'set_' .. k;"
		      "local setter = rawget(lib, setname);"
		      "if setter then  return setter(instance, v);  end;"
		      "local getname = 'get_' .. k;"
		      "if rawget(lib, getname) or rawget(instance, getname) then "
		        "error('attempt to set readonly attribute ' .. k,2);"
		      "end;"
              "getname = 'geti_' .. k;"
			  "if rawget(lib, getname) or rawget(instance, getname) then "
			    "error('attempt to set array attribute ' .. k,2);"
		      "end;"
		    "end;"
		    "error('attempt to add custom field/method to non-expando object',2);"
		  "end;"
		"end;"
	  "end;"
	  "lib_meta.__index = lib__index;"
	  "lib_meta.__newindex = lib__newindex;"
	"end;"

	"local get_r, get_g, get_b = agsinternal.get_r, agsinternal.get_g, agsinternal.get_b;"
	"local set_r, set_g, set_b = agsinternal.set_r, agsinternal.set_g, agsinternal.set_b;"

	"function agsinternal.palette__index(self, i) "
	  "if type(i) ~= 'number' or i < 0 or i > 255 then "
	    "return nil;"
	  "end;"
	  "local p = {};"
	  "rawset(self, i, p);"
	  "function p.__index(self, k) "
	    "if k == 'r' then "
  		  "return get_r(i);"
	    "elseif k == 'g' then "
		  "return get_g(i);"
	    "elseif k == 'b' then "
		  "return get_b(i);"
	    "end;"
	  "end;"
	  "function p.__newindex(self, k, v) "
	    "if k == 'r' then "
  		  "return set_r(i, v);"
	    "elseif k == 'g' then "
		  "return set_g(i, v);"
	    "elseif k == 'b' then "
		  "return set_b(i, v);"
	    "end;"
	  "end;"
	  "return setmetatable(p, p);"
	"end;"
;

static int agsinternal_getmetatable(lua_State* L) {
	if (lua_getmetatable(L,1)) {
		return 1;
	}
	return 0;
}

static int agsinternal_setmetatable(lua_State* L) {
	lua_setmetatable(L,1);
	lua_settop(L,1);
	return 1;
}

static int agsinternal_GetKeyForManagedObject(lua_State *L) {
	lua_pushinteger(L, engine->GetManagedObjectKeyByAddress((const char*)*(void**)lua_touserdata(L,1)));
	return 1;
}

static int agsinternal_getkey(lua_State *L) {
	EphemeralContainer* container = (EphemeralContainer*)lua_touserdata(L,1);
	lua_pushinteger(L, container->key);
	return 1;
}

static int agsinternal_GetManagedObjectByKey(lua_State *L) {
	void* ptr = (void*)engine->GetManagedObjectAddressByKey((int)luaL_checknumber(L,1));
	lua_pushlightuserdata(L, ptr);
	return 1;
}

static int agsinternal_getstored(lua_State *L) {
	luags_pushEphemeral(L, lua_touserdata(L,1), 2, 3);
	return 1;
}

static int agsinternal_ephemeralplaceholder(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "Ephemeral Holding Bay");
	lua_pushvalue(L,1);
	lua_gettable(L,-2);
	if (lua_isnil(L,-1)) {
		EphemeralContainer* container = (EphemeralContainer*)lua_newuserdata(L, sizeof(EphemeralContainer));
		lua_pushvalue(L,-1);
		lua_pushvalue(L,-1);
		lua_rawset(L,-5);
		container->key = (int)lua_tonumber(L,1);
		lua_pushvalue(L,2);
		lua_setmetatable(L,-2);
	}
	return 1;
}

static int agsinternal_decomposeroomthing(lua_State *L) {
	AGS_RoomThing* roomThing = (AGS_RoomThing*)lua_touserdata(L,1);
	lua_pushinteger(L, roomThing->RoomID);
	lua_pushinteger(L, roomThing->ThingID);
	lua_getmetatable(L, 1);
	return 3;
}

static int agsinternal_composeroomthing(lua_State *L) {
	// 1: Room ID
	// 2: Thing ID
	// 3: Metatable
	AGS_RoomThing roomThing;
	roomThing.RoomID = (int)lua_tonumber(L,1);
	roomThing.ThingID = (int)lua_tonumber(L,2);
	// 4: Store
	lua_getfield(L,3,"__store");
	// 5: Store Key
	lua_pushlstring(L, (const char*)&roomThing, sizeof(roomThing));

	lua_pushvalue(L,5);
	lua_rawget(L,4);
	if (lua_isnil(L,-1)) {
		memcpy(lua_newuserdata(L, sizeof(roomThing)), &roomThing, sizeof(roomThing));

		// add metatable
		lua_pushvalue(L,3);
		lua_setmetatable(L,-2);

		// add to store
		lua_pushvalue(L,5);
		lua_pushvalue(L,-2);
		lua_rawset(L,4);
	}
	return 1;
}

static int agsinternal_CallGameScriptFunction(lua_State *L) {
	engine->QueueGameScriptFunction(
		lua_tostring(L,1), (long)lua_tointeger(L,2), (long)lua_tointeger(L,3), (long)lua_tointeger(L,4),
		(long)lua_tointeger(L,5));
	return 1;
}

static int agsinternal_getpristine(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "pristine");
	lua_insert(L, 1);
	lua_rawget(L, 1);
	return 1;
}

static int agsinternal_setpristine(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "pristine");
	if (!lua_istable(L,-1)) {
		lua_newtable(L);
		lua_pushvalue(L,-1);
		lua_setfield(L, LUA_REGISTRYINDEX, "pristine");
	}
	// add name->self to table
	lua_pushvalue(L,1);
	lua_pushvalue(L,2);
	lua_rawset(L,-3);
	return 0;
}

static int agsinternal_MessageBox(lua_State *L) {
#if defined(WINDOWS_VERSION)
	MessageBox(NULL, lua_tostring(L,1), "message", MB_OK);
#endif
	return 0;
}

static int agsinternal_get_G(lua_State *L) {
	lua_pushvalue(L, LUA_GLOBALSINDEX);
	return 1;
}

static int agsinternal_get_r(lua_State *L) {
	int i = luaL_checkint(L, 1);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	lua_pushinteger(L, palette[i].r);
	return 1;
}

static int agsinternal_get_g(lua_State *L) {
	int i = luaL_checkint(L, 1);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	lua_pushinteger(L, palette[i].g);
	return 1;
}

static int agsinternal_get_b(lua_State *L) {
	int i = luaL_checkint(L, 1);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	lua_pushinteger(L, palette[i].b);
	return 1;
}

static int agsinternal_set_r(lua_State *L) {
	int i = luaL_checkint(L, 1);
	unsigned char v = (unsigned char)luaL_checkint(L, 2);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	palette[i].r = v;
	return 0;
}

static int agsinternal_set_g(lua_State *L) {
	int i = luaL_checkint(L, 1);
	unsigned char v = (unsigned char)luaL_checkint(L, 2);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	palette[i].g = v;
	return 0;
}

static int agsinternal_set_b(lua_State *L) {
	int i = luaL_checkint(L, 1);
	unsigned char v = (unsigned char)luaL_checkint(L, 2);
	luaL_argcheck(L, i >= 0 && i <= 255, 1, "index out of range");
	AGSColor* palette = engine->GetPalette();
	palette[i].b = v;
	return 0;
}

static const luaL_Reg agsinternal_lib[] = {
	{"ephemeralplaceholder", agsinternal_ephemeralplaceholder},
	{"getmetatable", agsinternal_getmetatable},
	{"setmetatable", agsinternal_setmetatable},
	{"getstored", agsinternal_getstored},
	{"GetKeyForManagedObject", agsinternal_GetKeyForManagedObject},
	{"GetManagedObjectByKey", agsinternal_GetManagedObjectByKey},
	{"getkey", agsinternal_getkey},
	{"decomposeroomthing", agsinternal_decomposeroomthing},
	{"composeroomthing", agsinternal_composeroomthing},
	{"CallGameScriptFunction", agsinternal_CallGameScriptFunction},
	{"getpristine", agsinternal_getpristine},
	{"setpristine", agsinternal_setpristine},
	{"get_G", agsinternal_get_G},
	{"MessageBox", agsinternal_MessageBox},
	{"get_r", agsinternal_get_r},
	{"get_g", agsinternal_get_g},
	{"get_b", agsinternal_get_b},
	{"set_r", agsinternal_set_r},
	{"set_g", agsinternal_set_g},
	{"set_b", agsinternal_set_b},
	{NULL, NULL}
};

int luaopen_agsinternal(lua_State *L) {
	lua_newtable(L);
	luaL_register(L, NULL, agsinternal_lib);
	lua_pushvalue(L,-1);
	lua_setglobal(L,"agsinternal");
	lua_pushvalue(L,-1);
	lua_setfield(L,LUA_REGISTRYINDEX,"agsinternal");
	if (0 != luaL_loadstring(L, LUA_INTERNAL_INIT)) {
		lua_error(L);
	}
	lua_call(L,0,0);
	return 0;
}

int hide_agsinternal(lua_State *L) {
	lua_pushnil(L);
	lua_setglobal(L,"agsinternal");
	return 0;
}
