using AGS.Types;
using System;
using System.Collections.Generic;
using System.Text;

namespace AGS.Plugin.Lua
{
	[RequiredAGSVersion("3.2.0.0")]
	public class LuaPlugin : IAGSEditorPlugin
	{
		public LuaPlugin(IAGSEditor editor)
		{
			editor.AddComponent(new LuaForAGSEditorComponent(editor));
		}

		public void Dispose()
		{
			// We don't need any cleanup code
		}
    }
}
