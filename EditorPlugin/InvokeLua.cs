using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using lua_State = System.IntPtr;
using size_t = System.UIntPtr;

namespace AGS.Plugin.Lua
{
    public static class InvokeLua
    {
        // Equivalent to luaconf.h
        public static class luaconf
        {
            public const int LUA_IDSIZE = 60;
            public const int LUAL_BUFFERSIZE = 0;
        }

        /* mark for precompiled code (`<esc>Lua') */
        public static byte[] LUA_SIGNATURE = {27, 76, 117, 97};

        /* option for multiple returns in `lua_pcall' and `lua_call' */
        public const int LUA_MULTRET = -1;

        /*
        ** pseudo-indices
        */
        public const int LUA_REGISTRYINDEX  = -10000;
        public const int LUA_ENVIRONINDEX   = -10001;
        public const int LUA_GLOBALSINDEX   = -10002;
        public static int lua_upvalueindex(int i)
        {
            return LUA_GLOBALSINDEX - i;
        }

        /* thread status; 0 is OK */
        public const int LUA_OK = 0;

        public const int LUA_YIELD = 1;
        public const int LUA_ERRRUN = 2;
        public const int LUA_ERRSYNTAX = 3;
        public const int LUA_ERRMEM = 4;
        public const int LUA_ERRERR = 5;

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public delegate int lua_CFunction(lua_State L);

        /*
        ** functions that read/write blocks when loading/dumping Lua chunks
        */

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPArray, ArraySubType=UnmanagedType.U1)]
        public delegate byte[] lua_Reader_RetBytes(lua_State L,
            IntPtr data,
            [MarshalAs(UnmanagedType.SysUInt)] ref size_t size);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public delegate string lua_Reader_RetString(lua_State L,
            lua_State data,
            [MarshalAs(UnmanagedType.SysUInt)] ref size_t size);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public delegate int lua_Writer(lua_State L,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1, SizeParamIndex = 2)] byte[] data,
            [MarshalAs(UnmanagedType.SysUInt)] size_t sz,
            IntPtr ud);

        /*
        ** prototype for memory-allocation functions
        */

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr lua_Alloc(IntPtr ud, IntPtr ptr, size_t osize, size_t nsize);

        /*
        ** basic types
        */

        public const int LUA_TNONE          = -1;

        public const int LUA_TNIL           = 0;
        public const int LUA_TBOOLEAN       = 1;
        public const int LUA_TLIGHTUSERDATA = 2;
        public const int LUA_TNUMBER        = 3;
        public const int LUA_TSTRING        = 4;
        public const int LUA_TTABLE         = 5;
        public const int LUA_TFUNCTION      = 6;
        public const int LUA_TUSERDATA      = 7;
        public const int LUA_TTHREAD        = 8;

        /* minimum Lua stack available to a C function */

        public const int LUA_MINSTACK = 20;

        /*
        ** state manipulation
        */
        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_State lua_newstate(
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_Alloc L,
            IntPtr ud);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_close(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_State lua_newthread(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.FunctionPtr)]
        public static extern lua_CFunction lua_atpanic(lua_State L,
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_CFunction panicf);

        /*
        ** basic stack manipulation
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_gettop(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_settop(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushvalue(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_remove(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_insert(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_replace(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_checkstack(lua_State L, int sz);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_xmove(lua_State from, lua_State to, int n);

        /*
        ** access functions (stack -> C)
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_isnumber(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_isstring(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_iscfunction(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_isuserdata(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_type(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string lua_typename(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_equal(lua_State L, int idx1, int idx2);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_rawequal(lua_State L, int idx1, int idx2);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_lessthan(lua_State L, int idx1, int idx2);


        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.R8)]
        public static extern double lua_tonumber(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_tointeger(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_toboolean(lua_State L, int idx);

        [DllImport("lua5.1.dll", EntryPoint = "lua_tolstring", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2, ArraySubType = UnmanagedType.U1)]
        private static extern byte[] lua_tolstring_bytes(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int idx,
            [MarshalAs(UnmanagedType.SysUInt)] out size_t len);

        [DllImport("lua5.1.dll", EntryPoint = "lua_tolstring", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        private static extern string lua_tostring_aux(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int idx,
            [MarshalAs(UnmanagedType.SysUInt)] size_t ptr);

        public static string lua_tostring(lua_State L, int idx)
        {
            return lua_tostring_aux(L, idx, size_t.Zero);
        }

        public static byte[] lua_tobytestring(lua_State L, int idx)
        {
            size_t l;
            return lua_tolstring_bytes(L, idx, out l);
        }

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.SysUInt)]
        public static extern size_t lua_objlen(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.FunctionPtr)]
        public static extern lua_CFunction lua_tocfunction(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr lua_touserdata(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_State lua_tothread(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr lua_topointer(lua_State L, int idx);

        /*
        ** push functions (C -> stack)
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushnil(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushnumber(lua_State L,
            [MarshalAs(UnmanagedType.R8)] double n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushinteger(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushstring(lua_State L,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1)] byte[] bytestring);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushstring(lua_State L,
            [MarshalAs(UnmanagedType.LPStr)] string str);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushcclosure(lua_State L,
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_CFunction fn,
            [MarshalAs(UnmanagedType.I4)] int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushboolean(lua_State L,
            [MarshalAs(UnmanagedType.I4)] bool b);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushlightuserdata(lua_State L, lua_State p);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_pushthread(lua_State L);

        /*
        ** get functions (Lua -> stack)
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_gettable(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_getfield(lua_State L, int idx, string k);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_rawget(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_rawgeti(lua_State L, int idx, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_createtable(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int narr,
            [MarshalAs(UnmanagedType.I4)] int nrec);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr lua_newuserdata(lua_State L, size_t sz);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_getmetatable(lua_State L, int objindex);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_getfenv(lua_State L, int idx);

        /*
        ** set functions (stack -> Lua)
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_settable(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_setfield(lua_State L, int idx, string k);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_rawset(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_rawseti(lua_State L, int idx, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_setmetatable(lua_State L, int objindex);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_setfenv(lua_State L, int idx);

        /*
        ** `load' and `call' functions (load and run Lua code)
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_call(lua_State L, int nargs, int nresults);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_pcall(lua_State L, int nargs, int nresults, int errfunc);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_cpcall(lua_State L, lua_CFunction func, IntPtr ud);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_load(lua_State L,
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_Reader_RetBytes reader,
            lua_State data,
            [MarshalAs(UnmanagedType.LPStr)] string chunkname);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int lua_load(lua_State L,
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_Reader_RetString reader,
            lua_State data,
            [MarshalAs(UnmanagedType.LPStr)] string chunkname);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_dump(lua_State L,
            [MarshalAs(UnmanagedType.FunctionPtr)] lua_Writer writer,
            lua_State data);

        /*
        ** coroutine functions
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_yield(lua_State L, int nresults);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_resume(lua_State L, int narg);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_status(lua_State L);

        /*
        ** garbage-collection function and options
        */

        public const int LUA_GCSTOP         = 0;
        public const int LUA_GCRESTART      = 1;
        public const int LUA_GCCOLLECT      = 2;
        public const int LUA_GCCOUNT	    = 3;
        public const int LUA_GCCOUNTB	    = 4;
        public const int LUA_GCSTEP		    = 5;
        public const int LUA_GCSETPAUSE		= 6;
        public const int LUA_GCSETSTEPMUL   = 7;

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_gc(lua_State L, int what, int data);

        /*
        ** miscellaneous functions
        */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_error(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern bool lua_next(lua_State L, int idx);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_concat(lua_State L, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_Alloc lua_getallocf(lua_State L, ref IntPtr ud);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_setallocf(lua_State L, lua_Alloc f, IntPtr ud);

        /* 
        ** ===============================================================
        ** some useful macros
        ** ===============================================================
        */

        public static void lua_pop(lua_State L, int n)
        {
            lua_settop(L, -n - 1);
        }

        public static void lua_newtable(lua_State L)
        {
            lua_createtable(L, 0, 0);
        }

        public static void lua_register(lua_State L, string n, lua_CFunction f)
        {
            lua_pushcfunction(L, f);
            lua_setglobal(L, n);
        }

        public static void lua_pushcfunction(lua_State L, lua_CFunction fn)
        {
            lua_pushcclosure(L, fn, 0);
        }

        [DllImport("lua5.1.dll", EntryPoint = "lua_objlen", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.SysUInt)]
        public static extern size_t lua_strlen(lua_State L, int idx);

        public static bool lua_isfunction(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TFUNCTION);
        }

        public static bool lua_istable(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TTABLE);
        }

        public static bool lua_islightuserdata(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TLIGHTUSERDATA);
        }

        public static bool lua_isnil(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TNIL);
        }

        public static bool lua_isboolean(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TBOOLEAN);
        }

        public static bool lua_isthread(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TTHREAD);
        }

        public static bool lua_isnone(lua_State L, int n)
        {
            return (lua_type(L, n) == LUA_TNONE);
        }

        public static bool lua_isnoneornil(lua_State L, int n)
        {
            return (lua_type(L, n) <= 0);
        }

        public static void lua_setglobal(lua_State L, string s)
        {
            lua_setfield(L, LUA_GLOBALSINDEX, s);
        }

        public static void lua_getglobal(lua_State L, string s)
        {
            lua_getfield(L, LUA_GLOBALSINDEX, s);
        }

        /*
        ** compatibility macros and functions
        */

        [DllImport("lua5.1.dll", EntryPoint = "luaL_newstate", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_State lua_open();

        public static void lua_getregistry(lua_State L)
        {
            lua_pushvalue(L, LUA_REGISTRYINDEX);
        }

        public static int lua_getgccount(lua_State L)
        {
            return lua_gc(L, LUA_GCCOUNT, 0);
        }

        /* hack */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_setlevel(lua_State from, lua_State to);

        /*
        ** {======================================================================
        ** Debug API
        ** =======================================================================
        */

        /*
        ** Event codes
        */

        public const int LUA_HOOKCALL       = 0;
        public const int LUA_HOOKRET        = 1;
        public const int LUA_HOOKLINE	    = 2;
        public const int LUA_HOOKCOUNT	    = 3;
        public const int LUA_HOOKTAILRET    = 4;

        /*
        ** Event masks
        */

        public const int LUA_MASKCALL   = (1 << LUA_HOOKCALL);
        public const int LUA_MASKRET	= (1 << LUA_HOOKRET);
        public const int LUA_MASKLINE	= (1 << LUA_HOOKLINE);
        public const int LUA_MASKCOUNT	= (1 << LUA_HOOKCOUNT);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void lua_Hook(lua_State L, lua_Debug ar);

        /* Functions to be called by the debuger in specific events */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_getstack(lua_State L, int level, lua_Debug ar);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_getinfo(lua_State L, string what, lua_Debug ar);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string lua_getlocal(lua_State L, lua_Debug ar, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string lua_setlocal(lua_State L, lua_Debug ar, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string lua_getupvalue(lua_State L, int funcindex, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern string lua_setupvalue(lua_State L, int funcindex, int n);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_sethook(lua_State L, lua_Hook func, int mask, int count);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_Hook lua_gethook(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_gethookmask(lua_State L);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int lua_gethookcount(lua_State L);

        [StructLayout(LayoutKind.Sequential)]
        public struct lua_Debug
        {
            [MarshalAs(UnmanagedType.I4)]
            public int event_type; // renamed from event as it is a reserved keyword
            [MarshalAs(UnmanagedType.LPStr)]
            public string name;	    /* (n) */
            [MarshalAs(UnmanagedType.LPStr)]
            public string namewhat;	/* (n) `global', `local', `field', `method' */
            [MarshalAs(UnmanagedType.LPStr)]
            public string what;	    /* (S) `Lua', `C', `main', `tail' */
            [MarshalAs(UnmanagedType.LPStr)]
            public string source;	/* (S) */
            [MarshalAs(UnmanagedType.I4)]
            public int currentline;	/* (l) */
            [MarshalAs(UnmanagedType.I4)]
            public int nups;		/* (u) number of upvalues */
            [MarshalAs(UnmanagedType.I4)]
            public int linedefined;	/* (S) */
            [MarshalAs(UnmanagedType.I4)]
            public int lastlinedefined;	/* (S) */
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = luaconf.LUA_IDSIZE)]
            public string short_src; /* (S) */
            /* private part */
            [MarshalAs(UnmanagedType.I4)]
            private int i_ci;           /* active function */
        };

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern lua_State luaL_newstate();

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_loadfile(lua_State L,
            [MarshalAs(UnmanagedType.LPStr)] string filename);

        public static string luaL_typename(lua_State L, int n)
        {
            return lua_typename(L, lua_type(L, n));
        }

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_loadbuffer(lua_State L,
            [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U1)] byte[] buff,
            [MarshalAs(UnmanagedType.SysUInt)] size_t sz,
            [MarshalAs(UnmanagedType.LPStr)] string name);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_loadstring(lua_State L,
            [MarshalAs(UnmanagedType.LPStr)] string str);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void lua_pushfstring(lua_State L,
            [MarshalAs(UnmanagedType.LPStr)] string format,
            __arglist);

        [StructLayout(LayoutKind.Sequential)]
        public struct luaL_Reg
        {
            [MarshalAs(UnmanagedType.LPStr)]
            public string name;
            [MarshalAs(UnmanagedType.FunctionPtr)]
            public lua_CFunction func;
        };

        /*
        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void luaI_openlib(lua_State L,
            [MarshalAs(UnmanagedType.LPStr)] string libname,
            [MarshalAs(UnmanagedType.LPArray, SizeParamIndex=3)] luaL_Reg[] l,
            [MarshalAs(UnmanagedType.I4)] int nup);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void 
         */

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_getmetafield(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int obj,
            [MarshalAs(UnmanagedType.LPStr)] string e);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_callmeta(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int obj,
            [MarshalAs(UnmanagedType.LPStr)] string e);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_typerror(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int narg,
            [MarshalAs(UnmanagedType.LPStr)] string tname);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I4)]
        public static extern int luaL_argerror(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int numarg,
            [MarshalAs(UnmanagedType.LPStr)] string extramsg);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string luaL_checklstring(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int numArg,
            [MarshalAs(UnmanagedType.SysInt)] out size_t l);

        [DllImport("lua5.1.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string luaL_optlstring(lua_State L,
            [MarshalAs(UnmanagedType.I4)] int numArg,
            [MarshalAs(UnmanagedType.SysInt)] out size_t l);

        /*
        ** {======================================================
        ** Generic Buffer manipulation
        ** =======================================================
        */

        [StructLayout(LayoutKind.Sequential)]
        public struct luaL_Buffer
        {
            public IntPtr p; /* current position in buffer */
            [MarshalAs(UnmanagedType.I4)]
            public int lvl;
            public lua_State L;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = luaconf.LUAL_BUFFERSIZE)]
            public string buffer;
        };

        public static string util_quotestring(string s)
        {
            return "\"" + Regex.Replace(s, @"[\\\r\n\t""\0]",
                delegate(Match m)
                {
                    switch (m.Value[0])
                    {
                        case '\r':
                            return @"\r";
                        case '\n':
                            return @"\n";
                        case '\t':
                            return @"\t";
                        case '"':
                            return @"\""";
                        case '\\':
                            return @"\\";
                        default:
                            return string.Format(@"\{0:000}", (int)m.Value[0]);
                    }
                }) + "\"";
        }

        // Use this with InvokeLua.lua_atpanic() to add exception-based error handling
        public static int ExceptionPanicHandler(lua_State L)
        {
            throw new LuaException(L, InvokeLua.lua_tostring(L, -1));
        }

        static Dictionary<string, bool> reservedWordCheck;

        public static bool util_iskeyword(string checkWord)
        {
            if (reservedWordCheck == null)
            {
                string[] reservedWords =
                    new string[] {
                        "and",      "break",    "do",   "else",     "elseif",
                        "end",      "false",    "for",  "function", "if",
                        "in",       "local",    "nil",  "not",      "or",
                        "repeat",   "return",   "then", "true",     "until",    "while"
                    };
                reservedWordCheck = new Dictionary<string,bool>();
                foreach (string word in reservedWords)
                {
                    reservedWordCheck[word] = true;
                }
            }
            return reservedWordCheck.ContainsKey(checkWord);
        }

    }
    public class LuaException : System.Exception
    {
        public readonly lua_State L;
        public LuaException(lua_State L, string message)
            : base(message)
        {
            this.L = L;
        }
    }
}
