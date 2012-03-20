using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace AGS.Plugin.Lua
{
    static class ResourceManager
    {
        public static string GetResourceAsString(string fileName)
        {
            Stream manifestResourceStream = typeof(ResourceManager).Assembly.GetManifestResourceStream("AGS.Plugin.Lua." + fileName);
            byte[] buffer = new byte[manifestResourceStream.Length];
            manifestResourceStream.Read(buffer, 0, buffer.Length);
            manifestResourceStream.Close();
            return Encoding.ASCII.GetString(buffer);
        }
    }
}
