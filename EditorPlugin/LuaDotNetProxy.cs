using System;
using System.Reflection;
using System.Collections.Generic;
using System.Text;
using lua_State = System.IntPtr;

namespace AGS.Plugin.Lua
{
    public class LuaDotNetObjectProxy
    {
        public object ProxyObject
        {
            get { return proxy_for; }
        }
        private object proxy_for;
        private Type proxy_type;
        internal IntPtr userdata;

        internal Dictionary<object, LuaDotNetObjectProxy> proxied;
        internal Dictionary<IntPtr, LuaDotNetObjectProxy> proxiedByUserdata;
        internal Dictionary<string, LuaDotNetMethodProxy> proxiedMethods;

        public void GetMethodProxy(lua_State L, string name, MethodInfo[] methods)
        {
            proxiedMethods[name] = new LuaDotNetMethodProxy(L, this, name, methods);
        }

        public LuaDotNetObjectProxy(lua_State L, object o)
            : this(L, o, new Dictionary<object,LuaDotNetObjectProxy>(), new Dictionary<IntPtr,LuaDotNetObjectProxy>())
        {
        }
        private LuaDotNetObjectProxy(lua_State L, object o, Dictionary<object,LuaDotNetObjectProxy> proxied,
            Dictionary<IntPtr,LuaDotNetObjectProxy> proxiedByUserdata)
        {
            this.proxied = proxied;
            this.proxiedByUserdata = proxiedByUserdata;
            this.proxy_for = o;
            proxy_type = o.GetType();

            userdata = InvokeLua.lua_newuserdata(L, (UIntPtr)1);

            proxied[proxy_for] = this;
            proxiedByUserdata[userdata] = this;

            InvokeLua.lua_pushlightuserdata(L, userdata);
            InvokeLua.lua_pushvalue(L, -2);
            InvokeLua.lua_rawset(L, InvokeLua.LUA_REGISTRYINDEX);

            InvokeLua.lua_newtable(L);

            InvokeLua.lua_pushcfunction(L, __Index);
            InvokeLua.lua_setfield(L, -2, "__index");

            InvokeLua.lua_pushcfunction(L, __ToString);
            InvokeLua.lua_setfield(L, -2, "__tostring");

            InvokeLua.lua_setmetatable(L, -2);
        }

        private int __ToString(lua_State L)
        {
            InvokeLua.lua_pushstring(L, this.ToString());
            return 1;
        }

        private int __Index(lua_State L)
        {
            switch(InvokeLua.lua_type(L,1))
            {
                case InvokeLua.LUA_TSTRING:
                    string memberName = InvokeLua.lua_tostring(L, 1);
                    MemberInfo[] members = proxy_type.GetMember(memberName);
                    List<MethodInfo> methods = new List<MethodInfo>();
                    foreach (MemberInfo member in members)
                    {
                        switch (member.MemberType)
                        {
                            case MemberTypes.Field:
                                return PushField(L, (FieldInfo)member);
                            case MemberTypes.Property:
                                return PushProperty(L, (PropertyInfo)member);
                            case MemberTypes.Method:
                                LuaDotNetMethodProxy methodProxy;
                                if (proxiedMethods.TryGetValue(memberName, out methodProxy))
                                {
                                    methodProxy.Push(L);
                                    return 1;
                                }
                                MethodInfo method = (MethodInfo)member;
                                if (method.IsSpecialName || !method.IsPublic)
                                {
                                    continue;
                                }
                                methods.Add(method);
                                return 0;
                        }
                    }
                    if (methods.Count != 0)
                    {
                        GetMethodProxy(L, memberName, methods.ToArray());
                        return 1;
                    }
                    return 0;
                case InvokeLua.LUA_TNUMBER:
                    if (proxy_type.IsArray)
                    {
                        int idx = (int)InvokeLua.lua_tonumber(L,1);
                        if (idx < 0 || idx >= ((Array)proxy_for).Length) {
                            return 0;
                        }
                        PushValue(L, ((Array)proxy_for).GetValue(idx), proxied, proxiedByUserdata);
                        return 1;
                    }
                    else
                    {
                        proxy_type.GetProperty("Values");
                    }
                    return 0;
                default:
                    return 0;
            }
        }

        public static void PushValue(lua_State L, object o, Dictionary<object, LuaDotNetObjectProxy> proxied, Dictionary<IntPtr, LuaDotNetObjectProxy> proxiedByUserdata)
        {
            if (o == null)
            {
                InvokeLua.lua_pushnil(L);
                return;
            }
            if (o is char)
            {
                InvokeLua.lua_pushstring(L, new String((char)o, 1));
                return;
            }
            if (o is string)
            {
                InvokeLua.lua_pushstring(L, (string)o);
                return;
            }
            if (o is Byte || o is SByte || o is Int16 || o is UInt16 || o is Int32 || o is UInt32
                || o is Int64 || o is UInt64 || o is Single || o is Double || o is Decimal)
            {
                InvokeLua.lua_pushnumber(L, (double)o);
                return;
            }
            if (o is bool)
            {
                InvokeLua.lua_pushboolean(L, (bool)o);
                return;
            }
            if (o is byte[])
            {
                InvokeLua.lua_pushstring(L, (byte[])o);
                return;
            }
            LuaDotNetObjectProxy proxy;
            if (proxied.TryGetValue(o, out proxy))
            {
                InvokeLua.lua_pushlightuserdata(L, proxy.userdata);
                InvokeLua.lua_rawget(L, InvokeLua.LUA_REGISTRYINDEX);
            }
            else
            {
                new LuaDotNetObjectProxy(L, o, proxied, proxiedByUserdata);
            }
        }

        private int PushField(lua_State push_to_L, FieldInfo field)
        {
            if (!field.IsPublic)
            {
                return 0;
            }

            InvokeLua.lua_CFunction fieldFunc =
                delegate(lua_State L)
                {
                    if (InvokeLua.lua_touserdata(L, 1) != userdata)
                    {
                        return InvokeLua.luaL_argerror(L, 1, "bad method invocation");
                    }
                    if (InvokeLua.lua_gettop(L) == 1)
                    {
                        PushValue(L, field.GetValue(this), proxied, proxiedByUserdata);
                        return 1;
                    }

                    return 0;
                };

            InvokeLua.lua_pushcfunction(push_to_L, fieldFunc);
            return 1;
        }

        private int PushProperty(lua_State push_to_L, PropertyInfo property)
        {
            if (property.IsSpecialName)
            {
                return 0;
            }
            MethodInfo getMethod = property.GetGetMethod(false);
            if (getMethod == null)
            {
                return 0;
            }
            PushValue(push_to_L, getMethod.Invoke(proxy_for, new object[] { }), proxied, proxiedByUserdata);
            return 1;
        }
    }

    public class LuaDotNetMethodProxy
    {
        private IntPtr funcptr;
        private LuaDotNetObjectProxy proxy_object;
        private MethodInfo[] proxy_methods;
        public LuaDotNetMethodProxy(lua_State L, LuaDotNetObjectProxy obj, string name, MethodInfo[] methods)
        {
            proxy_object = obj;
            proxy_methods = methods;

            InvokeLua.lua_pushcfunction(L, __Call);

            funcptr = InvokeLua.lua_topointer(L, -1);
            InvokeLua.lua_pushlightuserdata(L, funcptr);
            InvokeLua.lua_pushvalue(L, -2);
            InvokeLua.lua_rawset(L, InvokeLua.LUA_REGISTRYINDEX);
        }

        public void Push(lua_State push_to_L)
        {
            InvokeLua.lua_pushlightuserdata(push_to_L, funcptr);
            InvokeLua.lua_rawget(push_to_L, InvokeLua.LUA_REGISTRYINDEX);
        }

        private static bool TryGetValue(Type t, lua_State L, int idx, Dictionary<IntPtr,LuaDotNetObjectProxy> proxiedByUserdata, out object value)
        {
            if (t.IsPrimitive)
            {
                if (t == typeof(Boolean))
                {
                    if (InvokeLua.lua_type(L, idx) != InvokeLua.LUA_TBOOLEAN)
                    {
                        value = null;
                        return false;
                    }
                    value = InvokeLua.lua_toboolean(L, idx);
                    return true;
                }
                if (t == typeof(Char))
                {
                    switch (InvokeLua.lua_type(L, idx))
                    {
                        case InvokeLua.LUA_TNUMBER:
                            value = (char)InvokeLua.lua_tonumber(L, idx);
                            return true;
                        case InvokeLua.LUA_TSTRING:
                            if (InvokeLua.lua_strlen(L, idx) == (UIntPtr)1)
                            {
                                value = InvokeLua.lua_tostring(L, idx)[0];
                                return true;
                            }
                            break;
                    }
                    value = null;
                    return false;
                }
                if (t == typeof(Byte) || t == typeof(SByte) || t == typeof(Int16) || t == typeof(UInt16)
                    || t == typeof(Int32) || t == typeof(UInt32) || t == typeof(Int64) || t == typeof(UInt64)
                    || t == typeof(Single) || t == typeof(Double) || t == typeof(Decimal))
                {
                    if (!InvokeLua.lua_isnumber(L, idx))
                    {
                        value = null;
                        return false;
                    }
                }
                value = null;
                return false;
            }
            else
            {
                if (InvokeLua.lua_isnil(L, idx))
                {
                    value = null;
                    return true;
                }
                if (!InvokeLua.lua_isuserdata(L, idx) || InvokeLua.lua_islightuserdata(L, idx))
                {
                    value = null;
                    return false;
                }
                LuaDotNetObjectProxy proxy;
                if (proxiedByUserdata.TryGetValue(InvokeLua.lua_touserdata(L, idx), out proxy))
                {
                    if (proxy.ProxyObject.GetType() == t)
                    {
                        value = proxy.ProxyObject; 
                        return true;
                    }
                }
                value = null;
                return false;
            }
        }

        public int __Call(lua_State L)
        {
            List<object> paramValues = new List<object>();
            if (InvokeLua.lua_touserdata(L, 1) != proxy_object.userdata)
            {
                InvokeLua.lua_pushstring(L, "attempt to call method on bad self");
                return InvokeLua.lua_error(L);
            }
            InvokeLua.lua_remove(L, 1);
            foreach (MethodInfo method in proxy_methods)
            {
                ParameterInfo[] parameters = method.GetParameters();
                if (parameters.Length != InvokeLua.lua_gettop(L))
                {
                    continue;
                }
                paramValues.Clear();
                for (int i = 0; i < parameters.Length; i++)
                {
                    object o;
                    if (TryGetValue(parameters[i].ParameterType, L, i + 1, proxy_object.proxiedByUserdata, out o))
                    {
                        paramValues.Add(o);
                    }
                    else
                    {
                        break;
                    }
                }
                if (paramValues.Count != parameters.Length)
                {
                    continue;
                }
                object result = method.Invoke(proxy_object.ProxyObject, paramValues.ToArray());
                LuaDotNetObjectProxy.PushValue(L, result, proxy_object.proxied, proxy_object.proxiedByUserdata);
                return 1;
            }
            InvokeLua.lua_pushstring(L, "invalid arguments to method");
            return InvokeLua.lua_error(L);
        }
    }
}
