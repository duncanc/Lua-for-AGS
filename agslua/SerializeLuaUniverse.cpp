
#include <windows.h>

#include "SerializeLuaUniverse.h"
#include "AGSLua.h"
#include <string.h>
#include <malloc.h>

const char META_NAME_PREFIX[] = "AGS_";
const char META_NAME_SUFFIX[] = "*";

#define charcount(n) ((sizeof(n)/sizeof(char))-1)

void push_name(lua_State *L, int IDX_PREFIX) {
	if (lua_strlen(L,IDX_PREFIX) == 0) {
		lua_pushvalue(L,-2);
		return;
	}
	if (lua_isnumber(L,-2)) {
		lua_pushvalue(L, IDX_PREFIX);
		lua_pushliteral(L,"[");
		lua_pushvalue(L,-4);
		lua_pushliteral(L,"]");
		lua_concat(L,4);
	}
	else {
		const char* c = lua_tostring(L,-2);
		size_t c_len = lua_strlen(L,-2);
		for (size_t i = 0; i < c_len; i++) {
			if ((c[i] < 'a' || c[i] > 'z') && (c[i] != '_') && (c[i] < 'A' || c[i] > 'Z') &&
					(c[i] < '0' || c[i] > '9' || i == 0)) {
				lua_pushfstring(L, "%s[\"%s\"]", lua_tostring(L,IDX_PREFIX),
					luaL_gsub(L,lua_tostring(L,-2),"\"","\\\""));
				lua_pop(L,1);
				return;
			}
		}
		lua_pushvalue(L, IDX_PREFIX);
		lua_pushliteral(L,".");
		lua_pushvalue(L,-4);
		lua_concat(L,3);
	}
}

void persist_opaque(lua_State *L, int IDX_PERSIST, int IDX_UNPERSIST, int IDX_PREFIX) {
	// Push the name
	push_name(L, IDX_PREFIX);
	lua_pushvalue(L,-2);
	lua_rawget(L, IDX_PERSIST);
	if (lua_isstring(L,-1)) {
		size_t old_len = lua_strlen(L,-1);
		size_t new_len = lua_strlen(L,-2);
		if (old_len < new_len || (old_len == new_len && strcmp(lua_tostring(L,-1), lua_tostring(L,-2)) < 0)) {
			lua_pop(L,3);
			return;
		}
	}
	lua_pop(L,1);

	// Get [value, name, name, value]
	lua_pushvalue(L,-1);
	lua_pushvalue(L,-3);
	// Add to persist and unpersist
	lua_rawset(L, IDX_UNPERSIST);
	lua_rawset(L, IDX_PERSIST);
}

int check_ancestor_loop(lua_State *L, int IDX_ANCESTRY) {
	int i;
	for (i = 1; ; i++) {
		lua_rawgeti(L, IDX_ANCESTRY, i);
		if (lua_isnil(L,-1)) {
			lua_pop(L,1);
			return 0;
		}
		if (lua_rawequal(L,-2,-1)) {
			lua_pop(L,1);
			return 1;
		}
		lua_pop(L,1);
	}
}

void push_ancestor(lua_State *L, int IDX_ANCESTRY) {
	lua_rawseti(L, IDX_ANCESTRY, (int)lua_objlen(L,IDX_ANCESTRY)+1);
}

void pop_ancestor(lua_State *L, int IDX_ANCESTRY) {
	lua_pushnil(L);
	lua_rawseti(L, IDX_ANCESTRY, (int)lua_objlen(L,IDX_ANCESTRY));
}

void persist_table(lua_State *L, int IDX_PERSIST, int IDX_UNPERSIST, int IDX_PREFIX, int IDX_ANCESTRY, int IDX_MAKEPRISTINE) {
	// make pristine
	lua_pushvalue(L, IDX_MAKEPRISTINE);
	lua_pushvalue(L, -2);
	lua_pushvalue(L, IDX_PREFIX);
	lua_call(L, 2, 0);

	// Iterate over the table
	lua_pushnil(L);
	while (lua_next(L,-2)) {
		// Work on the assumption that the key should only ever be a string or a number for now
		if (lua_isstring(L,-2)) {
			if (lua_iscfunction(L,-1) || lua_isuserdata(L,-1)) {
				persist_opaque(L, IDX_PERSIST, IDX_UNPERSIST, IDX_PREFIX);
			}
			else if (lua_istable(L,-1)) {
				if (check_ancestor_loop(L, IDX_ANCESTRY)) {
					lua_pop(L,1);
				}
				else {
					lua_pushvalue(L,-1);
					push_ancestor(L, IDX_ANCESTRY);

					size_t old_prefix_len;
					char* old_prefix;
					old_prefix = (char*)malloc(lua_strlen(L,IDX_PREFIX));
					memcpy(old_prefix, lua_tolstring(L,IDX_PREFIX,&old_prefix_len), lua_strlen(L,IDX_PREFIX));

					push_name(L, IDX_PREFIX);
					lua_replace(L, IDX_PREFIX);
					persist_table(L, IDX_PERSIST, IDX_UNPERSIST, IDX_PREFIX, IDX_ANCESTRY, IDX_MAKEPRISTINE);

					lua_pushlstring(L, old_prefix, old_prefix_len);
					lua_replace(L,IDX_PREFIX);
					free(old_prefix);

					pop_ancestor(L, IDX_ANCESTRY);
				}
			}
			else {
				// value is not a table, function or userdata
				lua_pop(L,1);
			}
		}
		else {
			// key is not a string or number
			lua_pop(L,1);
		}
	}

	// remove the table itself
	lua_pop(L,1);
}

static int initdiff(lua_State *L) {
	if (lua_strlen(L,2) == 0) {
		lua_pushliteral(L,"_G");
		lua_replace(L,2);
	}
	lua_newtable(L);
	// current, name, pristine

	// add pristine to registry
	lua_getfield(L, LUA_REGISTRYINDEX, "diffpristine");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L,-1);
		lua_setfield(L, LUA_REGISTRYINDEX, "diffpristine");
	}
	int IDX_PRISTINESTORE = lua_gettop(L);

	// add current to registry
	lua_getfield(L, LUA_REGISTRYINDEX, "diffcurrent");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1);
		lua_newtable(L);
		lua_pushvalue(L,-1);
		lua_setfield(L, LUA_REGISTRYINDEX, "diffcurrent");
	}
	int IDX_CURRENTSTORE = lua_gettop(L);

	// try getting an existing name for this table
	lua_pushvalue(L,1);
	lua_rawget(L,IDX_PRISTINESTORE);
	if (lua_isstring(L,-1)) {
		size_t len_old = lua_objlen(L,-1);
		size_t len_new = lua_objlen(L,2);
		if (len_old > len_new || (len_old == len_new && strcmp(lua_tostring(L,-1),lua_tostring(L,2)) < 0)) {
			lua_pushvalue(L,2);
			lua_pushvalue(L,-2);
			lua_rawget(L, IDX_PRISTINESTORE);
			lua_rawset(L, IDX_PRISTINESTORE);

			lua_pushvalue(L,-1);
			lua_pushnil(L);
			lua_rawset(L, IDX_PRISTINESTORE);

			lua_pushvalue(L,-1);
			lua_pushnil(L);
			lua_rawset(L, IDX_CURRENTSTORE);

			lua_pushvalue(L,1);
			lua_pushvalue(L,2);
			lua_rawset(L, IDX_PRISTINESTORE);

			lua_pushvalue(L,2);
			lua_pushvalue(L,1);
			lua_rawset(L, IDX_CURRENTSTORE);
		}
		return 0;
	}
	lua_pop(L,1);

	lua_pushvalue(L, 2);
	lua_pushvalue(L, 3);
	lua_rawset(L, IDX_PRISTINESTORE);

	lua_pushvalue(L, 2);
	lua_pushvalue(L, 1);
	lua_rawset(L, IDX_CURRENTSTORE);

	lua_pushvalue(L, 1);
	lua_pushvalue(L, 2);
	lua_rawset(L, IDX_PRISTINESTORE);

	// populate pristine
	lua_pushnil(L);
	while (lua_next(L, 1)) {
		if (!lua_istable(L,-1) && !lua_istable(L,-2)) {
			lua_pushvalue(L, -2);
			lua_insert(L,-2);
			lua_rawset(L,3);
		}
		else {
			lua_pop(L,1);
		}
	}

	return 0;
}

int diff(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "diffpristine");
	lua_getfield(L, LUA_REGISTRYINDEX, "diffcurrent");
	if (!lua_istable(L,1) || !lua_istable(L,2)) {
		return 0;
	}
	lua_pushnil(L);
	while (lua_next(L,1)) {
		if (!lua_isstring(L,-2)) {
			lua_pop(L,1);
			continue;
		}
		int pairs = 0, nils = 0;
		// ... name, pristine
		lua_pushvalue(L,-2);
		lua_rawget(L,2);
		lua_insert(L,-2);
		// ... name, current, pristine
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			pairs++;
			// ... name, current, pristine, pristinekey, pristinevalue
			lua_pushvalue(L,-2);
			lua_rawget(L,-5);
			// ... name, current, pristine, pristinekey, pristinevalue, currentvalue
			if (lua_rawequal(L,-2,-1)) {
				lua_pop(L,2);
				lua_pushvalue(L,-1);
				lua_pushnil(L);
				// ... name, current, pristine, pristinekey, pristinekey, nil
				lua_rawset(L,-5);
				// ... name, current, pristine, pristinekey
			}
			else if (lua_isnil(L,-1)) {
				nils++;
				lua_pop(L,2);
				lua_pushvalue(L,-1);
				lua_pushvalue(L,-3);
				// ... name, current, pristine, pristinekey, pristinekey, pristine
				lua_rawset(L,-5);
				// ... name, current, pristine, pristinekey
			}
			else {
				lua_pop(L,2);
				// ... name, current, pristine, pristinekey
			}
		}
		// ... name, current, pristine
		lua_pop(L,2);
		// ... name
	}
	return 0;
}

int merge(lua_State *L) {
	lua_getfield(L, LUA_REGISTRYINDEX, "diffpristine");
	lua_getfield(L, LUA_REGISTRYINDEX, "diffcurrent");
	if (!lua_istable(L,1) || !lua_istable(L,2)) {
		return 0;
	}
	lua_pushnil(L);
	while (lua_next(L,1)) {
		if (!lua_isstring(L,-2)) {
			lua_pop(L,1);
			continue;
		}
		int pairs = 0, restored = 0;
		// ... name, pristine
		lua_pushvalue(L,-2);
		lua_rawget(L,2);
		lua_insert(L,-2);
		// ... name, current, pristine
		lua_pushnil(L);
		while (lua_next(L,-2)) {
			// ... name, current, pristine, pristinekey, pristinevalue
			pairs++;
			lua_pushvalue(L,-2);
			lua_rawget(L,-5);
			// ... name, current, pristine, pristinekey, pristinevalue, currentvalue
			if (lua_isnil(L,-1)) {
				restored++;
				lua_pop(L,1);
				lua_pushvalue(L,-2);
				lua_insert(L,-2);
				// ... name, current, pristine, pristinekey, pristinekey, pristinevalue
				lua_rawset(L, -5);
				// ... name, current, pristine, pristinekey
			}
			else if (lua_rawequal(L,-1,-4)) {
				lua_pop(L,2);
				lua_pushvalue(L,-1);
				lua_pushnil(L);
				// ... name, current, pristine, pristinekey, pristinevalue, currentvalue
				lua_rawset(L,-5);
				// ... name, current, pristine, pristinekey
			}
			else {
				lua_pop(L,2);
				// ... name, current, pristine, pristinekey
			}
		}
		// ... name, current, pristine
		lua_pop(L,2);
		// ... name
	}
	return 0;
}

int autopersist(lua_State *L) {
	int IDX_PERSIST, IDX_UNPERSIST, IDX_PREFIX, IDX_ANCESTRY, IDX_MAKEPRISTINE;
	lua_newtable(L);
	IDX_PERSIST = lua_gettop(L);
	lua_newtable(L);
	IDX_UNPERSIST = lua_gettop(L);
	lua_newtable(L);
	IDX_ANCESTRY = lua_gettop(L);
	lua_pushliteral(L, "");
	IDX_PREFIX = lua_gettop(L);
	//lua_getfield(L, LUA_REGISTRYINDEX, "agsinternal");
	//lua_getfield(L, -1, "makepristine");
	//lua_replace(L,-2);
	lua_pushcfunction(L, initdiff);
	IDX_MAKEPRISTINE = lua_gettop(L);

	lua_pushvalue(L, LUA_GLOBALSINDEX);
	lua_pushvalue(L,-1);
	lua_rawseti(L, IDX_ANCESTRY, 1);
	persist_table(L, IDX_PERSIST, IDX_UNPERSIST, IDX_PREFIX, IDX_ANCESTRY, IDX_MAKEPRISTINE);

	// Get AGS type metatables
	lua_pushnil(L);
	while (lua_next(L, LUA_REGISTRYINDEX)) {
		if (lua_type(L,-2) != LUA_TSTRING) {
			lua_pop(L,1);
		}
		else {
			size_t len;
			const char* str = lua_tolstring(L,-2,&len);
			if (len > (charcount(META_NAME_PREFIX) + charcount(META_NAME_SUFFIX))
					&& !strncmp(str,META_NAME_PREFIX,charcount(META_NAME_PREFIX))
					&& !strncmp(str + len - charcount(META_NAME_SUFFIX),"*",charcount(META_NAME_SUFFIX))) {
				lua_pushvalue(L,-2);
				lua_pushvalue(L,-1);
				lua_pushvalue(L,-3);
				// key, value, key, key, value
				lua_rawset(L, IDX_UNPERSIST);
				lua_rawset(L, IDX_PERSIST);
			}
			else {
				lua_pop(L,1);
			}
		}
	}

	lua_pushvalue(L, IDX_PERSIST);
	lua_setfield(L, LUA_REGISTRYINDEX, "persist");
	lua_pushvalue(L, IDX_UNPERSIST);
	lua_setfield(L, LUA_REGISTRYINDEX, "unpersist");

	return 0;
}
