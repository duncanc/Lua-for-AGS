using AGS.Types;
using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Windows.Forms;
using zlib;
using lua_State = System.IntPtr;
using size_t = System.UIntPtr;

namespace AGS.Plugin.Lua
{
    public class LuaScriptFileInfo
    {
        public const string XML_NAME = "LuaScriptFile";
        internal FileInfo __file;
        internal FileInfo file
        {
            get
            {
                return __file;
            }
            set
            {
                if (__file != null)
                {
                    component.scripts.Remove(key);
                    parent.Scripts.Remove(__file.Name.ToLower());
                }
                __file = value;
                if (value != null)
                {
                    component.scripts.Add(key, this);
                    parent.Scripts.Add(__file.Name.ToLower(), this);
                }
            }
        }
        private LuaForAGSEditorComponent component;
        internal LuaScriptFolderInfo parent;
        [Browsable(false)]
        public string key
        {
            get
            {
                return parent.Key + file.Name.ToLower();
            }
        }

        public void Save(string newContent)
        {
            parent.EnsureExistence();
            File.WriteAllText(file.FullName, newContent);
        }

        public void Delete()
        {
            LuaScriptEditPane pane;
            if (component.editPanes.TryGetValue(key, out pane))
            {
                component.editor.GUIController.RemovePaneIfExists(pane.contentDocument);
            }
            file.Delete();
        }

        public void BeenDeleted()
        {
            file = null;
            parent.RefreshIcons();
        }

        public void BeenRenamed(string newName)
        {
            file = new FileInfo(Path.Combine(parent.dir.FullName, newName));
            parent.RefreshIcons();
        }

        public LuaScriptFileInfo(LuaForAGSEditorComponent component, LuaScriptFolderInfo folder, FileInfo file)
        {
            this.component = component; // must do this before setting file
            this.parent = folder;

            // this must come after component and parent are set!
            this.file = file;
        }

        public bool IncludeAtRunTime = true;

        [Category("Referencing")]
        [Description("Path to use to run this script using Lua.RunScript() from AGS-Script or runscript() from Lua.")]
        [DisplayName("Script path")]
        [ReadOnly(true)]
        public string ScriptPath
        {
            get
            {
                string path = file.Name;
                for (LuaScriptFolderInfo ancestor = parent; ancestor.parent != null; ancestor = ancestor.parent)
                {
                    path = ancestor.dir.Name.ToLower() + "/" + path;
                }
                return path;
            }
        }

        [Category("Referencing")]
        [Description("Name to use to import this script as a Lua module using Lua.RequireModule() from AGS-Script or require() from Lua.")]
        [DisplayName("Module name")]
        [ReadOnly(true)]
        public string ModuleName
        {
            get
            {
                if (!file.Name.EndsWith(".lua", StringComparison.OrdinalIgnoreCase))
                {
                    return null;
                }
                string module_name = file.Name.Substring(0, file.Name.Length - ".lua".Length);
                if (module_name.Equals("init", StringComparison.OrdinalIgnoreCase)
                    && parent.parent != null)
                {
                    module_name = null;
                }
                for (LuaScriptFolderInfo ancestor = parent; ancestor.parent != null; ancestor = ancestor.parent)
                {
                    if (module_name == null)
                    {
                        module_name = ancestor.dir.Name.ToLower();
                    }
                    else
                    {
                        module_name = ancestor.dir.Name.ToLower() + "." + module_name;
                    }
                }
                return module_name;
            }
        }

        public void ToXml(XmlWriter output)
        {
            output.WriteStartElement(XML_NAME);
            output.WriteAttributeString("Name", file.Name.ToLower());
            output.WriteAttributeString("IncludeAtRunTime", IncludeAtRunTime.ToString());
            output.WriteEndElement();
        }

        public void AddIcon()
        {
            component.editor.GUIController.ProjectTree.AddTreeLeaf(component, key, file.Name, "ScriptIcon", false);
        }

        public void UpdateFromXml(XmlElement element)
        {
            bool.TryParse(element.GetAttribute("IncludeAtRunTime") ?? "True", out IncludeAtRunTime);
        }
        public bool TryRename(string newName)
        {
            string newPath = Path.Combine(parent.dir.FullName, newName);
            try
            {
                file.MoveTo(newPath);
            }
            catch
            {
                return false;
            }
            file = new FileInfo(newPath);
            return true;
        }
        public void Open()
        {
            LuaScriptEditPane pane;
            if (!component.editPanes.TryGetValue(key, out pane))
            {
                pane = new LuaScriptEditPane(component, component.editor, this);
                Dictionary<string, object> scriptProps = new Dictionary<string, object>();
                scriptProps.Add("Script file options", this);
                pane.contentDocument = new ContentDocument(pane, file.Name, component, scriptProps);
                pane.contentDocument.SelectedPropertyGridObject = pane.ScriptInfo;
                pane.contentDocument.ToolbarCommands = new List<MenuCommand>();
                pane.contentDocument.ToolbarCommands.Add(new MenuCommand("VERIFY", "Verify Syntax", "LuaIcon"));
                pane.contentDocument.PanelClosed +=
                    delegate(object sender, EventArgs e)
                    {
                        component.editPanes.Remove(key);
                        pane.Save();
                    };
                component.editPanes[key] = pane;
            }
            component.editor.GUIController.AddOrShowPane(pane.contentDocument);
        }
    }
}
