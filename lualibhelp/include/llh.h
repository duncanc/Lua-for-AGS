
#ifndef LUALIBHELP_DOT_H
#define LUALIBHELP_DOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>

// MY_STRUCT* mystructptr = GetMyStruct();
// luaL_getmetatable(L, "MY_STRUCT*");
// llh_pushboxedptr(L, mystructptr, -1);
#define llh_pushboxedptr(L, ptr, meta_idx) \
	{ \
		lua_pushvalue(L, meta_idx); \
		*(void**)lua_newuserdata(L,sizeof(void*)) = (void*)ptr; \
		lua_insert(L, -2); \
		lua_setmetatable(L, -2); \
	}
#define llh_nullboxedptr(L, ptr_idx)	{ *(void**)lua_touserdata((L),(ptr_idx)) = NULL; }
#define llh_pushunboxedptr(L, ptr)	lua_pushlightuserdata((L), (void*)(ptr))
#define llh_unboxptr(L, ptr_idx)	(*(void**)lua_touserdata((L),(ptr_idx)))

#define llh_pushnumberarray(L, values, count) \
	{ \
		int ___i; \
		lua_createtable(L,count,0); \
		for (___i = 0; ___i < (count); ___i++) { \
			lua_pushnumber((L), (lua_Number)((values)[___i])); \
			lua_rawseti((L),-2,___i+1); \
		} \
	}

#define llh_newstoretable(L, name) \
	{ \
		lua_newtable(L); \
		lua_pushstring(L, name); \
		lua_pushvalue(L, -2); \
		lua_settable(L, LUA_REGISTRYINDEX); \
		luaL_newmetatable(L, "weak-valued store"); \
		lua_pushliteral(L,"__mode"); \
		lua_pushliteral(L,"v"); \
		lua_rawset(L,-3); \
		lua_setmetatable(L, -2); \
	}

#define llh_newstored(L, obj_ptr, meta_idx, store_idx) \
	{ \
		llh_pushboxedptr((L), (obj_ptr), (meta_idx)); \
		lua_pushvalue((L), (meta_idx)); \
		lua_setmetatable((L), -2); \
		llh_pushunboxedptr((L), (obj_ptr)); \
		lua_pushvalue((L),-2); \
		lua_rawset((L),(store_idx)); \
	}

#define llh_pushstored(L, obj_ptr, meta_idx, store_idx) \
	{ \
		if ((obj_ptr) == NULL) { \
			lua_pushnil((L)); \
		} \
		else { \
			llh_pushunboxedptr((L), (obj_ptr)); \
			lua_rawget((L), (store_idx)); \
			if (lua_isnil((L),-1)) { \
				lua_pop((L),1); \
				llh_newstored((L),(obj_ptr),(meta_idx),(store_idx)); \
			} \
		} \
	}

#define llh_checkboxedptr(L, obj_idx, meta_idx, type_name)								\
	(																					\
		luaL_argcheck(																	\
			(L),																		\
			lua_getmetatable((L),(obj_idx)) && lua_rawequal((L),-1,(meta_idx)),			\
			(obj_idx),																	\
			"expecting " type_name														\
		),																				\
		lua_pop((L),1),																	\
		llh_unboxptr((L),(obj_idx))														\
	)

#define llh_checkstruct(L, obj_idx, meta_idx, type_name)								\
	(																					\
		luaL_argcheck(																	\
			(L),																		\
			lua_getmetatable((L),(obj_idx)) && lua_rawequal((L),-1,(meta_idx)),			\
			(obj_idx),																	\
			"expecting " type_name														\
		),																				\
		lua_pop((L),1),																	\
		lua_touserdata((L),(obj_idx))													\
	)

#define llh_checkboolean(L,i)		(luaL_checktype((L),(i),LUA_TBOOLEAN), lua_toboolean((L),(i)))

#define llh_optenum(L,i,values,names,def) \
	(lua_isnoneornil((L),(i)) ? def : \
		(lua_type((L),(i))==LUA_TNUMBER ? lua_tonumber((L),(i)) : values[luaL_checkoption((L),(i),NULL,names)]))

#define llh_checkenum(L,i,values,names) \
	(lua_type((L),(i))==LUA_TNUMBER ? lua_tonumber((L),(i)) : values[luaL_checkoption((L),(i),NULL,names)])

#define llh_isabsindex(L, i)	((i) > 0 || (i) <= LUA_REGISTRYINDEX)

#define llh_absindex(L, i)		(llh_isabsindex((L),(i)) ? (i) : lua_gettop(L) + (i) + 1)

// STRUCT2TABLE

#define llh_struct2table_number(L,pstruct,propname) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_pushnumber((L), (lua_Number)((pstruct)->##propname)); \
		lua_settable((L),-3); \
	}

#define llh_struct2table_lightuserdata(L,pstruct,propname) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_pushlightuserdata((L), (void*)((pstruct)->##propname)); \
		lua_settable((L),-3); \
	}

#define llh_struct2table_boolean(L,pstruct,propname) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_pushboolean((L), (int)((pstruct)->##propname)); \
		lua_settable((L),-3); \
	}

#define llh_struct2table_numarray(L,pstruct,propname,length) \
	{ \
		int ___i; \
		lua_pushliteral((L), #propname); \
		lua_createtable((L), (length), 0); \
		for (___i = 0; ___i < (length); ___i++) { \
			lua_pushnumber((L), (lua_Number)((pstruct)->##propname##[___i])); \
			lua_rawseti((L),-2,___i+1); \
		} \
		lua_rawset((L),-3); \
	}

#define llh_table2struct_checknumber(L,i,pstruct,propname,NUM_TYPE) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_gettable((L),(i)); \
		luaL_argcheck((L),lua_isnumber((L),-1),(i),"missing or invalid " LUA_QL(#propname) " field - expecting number"); \
		(pstruct)->##propname = (NUM_TYPE)lua_tonumber((L),-1); \
		lua_pop((L),1); \
	}

#define llh_table2struct_optnumber(L,i,pstruct,propname,NUM_TYPE,def) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_gettable((L), (i)); \
		if (lua_isnil(L,-1)) { \
			(pstruct)->##propname = def; \
		} \
		else { \
			luaL_argcheck((L), lua_isnumber((L),-1), (i), "invalid " LUA_QL(#propname) " field (expecting number)"); \
			(pstruct)->##propname = (NUM_TYPE)lua_tonumber((L),-1); \
		} \
		lua_pop((L),1); \
	}

#define llh_table2struct_checkboolean(L,i,pstruct,propname,NUM_TYPE) \
	{ \
		lua_pushliteral((L), #propname); \
		lua_gettable((L),(i)); \
		luaL_argcheck((L),lua_isboolean((L),-1),(i),"missing or invalid " LUA_QL(#propname) " field - expecting boolean"); \
		(pstruct)->##propname = (NUM_TYPE)lua_toboolean((L),-1); \
		lua_pop((L),1); \
	}

#define llh_table2struct_checknumarray(L,i,pstruct,propname,TYPE,length) \
	{ \
		int ___idx = llh_absindex((L), (i)); \
		int ___i; \
		lua_pushliteral((L), #propname); \
		lua_gettable((L), (i)); \
		luaL_argcheck((L), lua_istable((L),-1), ___idx, "missing or invalid " LUA_QL(#propname) " field (expecting number array)"); \
		for (___i = 0; ___i < (length); ___i++) { \
			lua_rawgeti((L),-1,___i+1); \
			luaL_argcheck((L), lua_isnumber((L),-1), ___idx, "missing or invalid " LUA_QL(#propname) " field (expecting number array)"); \
			(pstruct)->##propname##[___i] = (TYPE)lua_tonumber((L),-1); \
			lua_pop(L,1); \
		} \
		lua_pop(L,1); \
	}

typedef struct llh_const_uint {
	const char* name;
	unsigned int value;
} llh_const_uint;

typedef struct llh_const_int {
	const char* name;
	int value;
} llh_const_int;

#define llh_addconstants_uint(L, const_array) \
	{ \
		const llh_const_uint* ___entry; \
		for (___entry = (const_array); ___entry->name; ___entry++) { \
			lua_pushnumber(L, ___entry->value); \
			lua_setfield((L), -2, ___entry->name); \
		} \
	}

#define llh_addconstants_int(L, const_array) \
	{ \
		const llh_const_int* ___entry; \
		for (___entry = (const_array); ___entry->name; ___entry++) { \
			lua_pushnumber(L, ___entry->value); \
			lua_setfield((L), -2, ___entry->name); \
		} \
	}

#define llh_iscallable(L,i) (lua_isfunction((L),(i)) || (luaL_getmetafield((L),(i),"__call") && (lua_pop((L),1),1)))

#define llh_table2struct_optcallback(L,i,pstruct,cbname,callback_L,callback_idx,wrapperfunc) \
	{ \
		lua_getfield((L),(i),#cbname); \
		if (lua_isnil(L,-1)) { \
			(pstruct)->##cbname = NULL; \
			lua_pop((L),1); \
		} \
		else { \
			luaL_argcheck((L), llh_iscallable((L),-1), (i), "invalid " LUA_QL(#cbname) " field (expecting callback function)"); \
			lua_xmove((L), (callback_L), 1); \
			lua_replace((callback_L), (callback_idx)); \
			(pstruct)->##cbname = (wrapperfunc); \
		} \
	}

#define llh_table2struct_checkcallback(L,i,pstruct,cbname,callback_L,callback_idx,wrapperfunc) \
	{ \
		lua_getfield((L),(i),#cbname); \
		luaL_argcheck((L), llh_iscallable((L),-1), (i), "invalid or missing " LUA_QL(#cbname) " field (expecting callback function)"); \
		lua_xmove((L), (callback_L), 1); \
		lua_replace((callback_L), (callback_idx)); \
		(pstruct)->##cbname = (wrapperfunc); \
	}

static const luaL_Reg llh_null_lib[] = {{NULL,NULL}};

#define llh_newmutable(L)		lua_createtable(L,0,1)

#define llh_pushmutablevalue(L,idx) \
	{ \
		lua_pushvalue((L),(idx)); \
		lua_pushnil(L); \
		if (lua_next((L),-2)) { \
			lua_pop((L),1); \
		} \
		else { \
			lua_pushnil(L); \
		} \
		lua_remove((L),-2); \
	}

#define llh_replacemutablevalue(L,idx) \
	{ \
		if (lua_isnil((L),-1)) { \
			lua_pushvalue((L),(idx)); \
			lua_insert((L),-2); \
			if (lua_next((L),-2)) { \
				lua_pop((L),1); \
				lua_pushnil(L); \
				lua_rawset((L),-3); \
			} \
			lua_pop((L),1); \
		} \
		else { \
			lua_pushvalue((L),(idx)); \
			lua_pushnil(L); \
			if (lua_next(L,-2)) { \
				lua_pop((L),1); \
				lua_pushnil(L); \
				lua_rawset((L),-3); \
			} \
			lua_insert(L,-2); \
			lua_pushboolean((L),1); \
			lua_rawset((L),-3); \
			lua_pop((L),2); \
		} \
	}

#ifdef __cplusplus
}
#endif

#endif // LUALIBHELP_DOT_H
