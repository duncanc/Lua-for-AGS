using System;
using System.Collections.Generic;
using System.Text;

namespace AGS.Plugin.Lua
{
    public interface IAGSEventReceiver
    {
        void OnAGSEvent(string eventName);
    }
}
