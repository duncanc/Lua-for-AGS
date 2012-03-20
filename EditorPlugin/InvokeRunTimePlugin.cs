using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Text.RegularExpressions;
using lua_State = System.IntPtr;
using size_t = System.UIntPtr;

namespace AGS.Plugin.Lua
{
    static class InvokeRunTimePlugin
    {
        [DllImport("agslua.dll")]
        public static extern void PrepareForCompileTimeScripts(lua_State L);

        [DllImport("agslua.dll")]
        public static extern void RunCompileTimeScripts(lua_State L);

        [DllImport("agslua.dll")]
        public static extern void WriteInitState(lua_State L, InvokeLua.lua_Writer writer);
    }
}
