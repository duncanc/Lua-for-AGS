//#define USE_EVENT_ACTIONS
//#define USE_VISUAL_EDITOR

using AGS.Types;
using AGS.Types.AutoComplete;
using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Resources;
using System.Text;
using System.Xml;
using System.Windows.Forms;
using zlib;
using lua_State = System.IntPtr;
using size_t = System.UIntPtr;
using AGSView = AGS.Types.View;
using AGSFont = AGS.Types.Font;
using System.Reflection;
using ScriptEntry = System.Collections.Generic.KeyValuePair<
                        string,
                        AGS.Plugin.Lua.LuaScriptFileInfo
                    >;
using ScriptEntryList = System.Collections.Generic.List<
                            System.Collections.Generic.KeyValuePair<
                                string,
                                AGS.Plugin.Lua.LuaScriptFileInfo
                            >
                        >;

namespace AGS.Plugin.Lua
{
	public class LuaForAGSEditorComponent : IEditorComponent
	{
        public const string COMMAND_SEPARATOR = "::";
		internal const string COMPONENT_ID = "LuaForAGSEditorComponent";
		internal const string NEWSCRIPT_PREFIX = "NEW-SCRIPT";
        internal const string NEWFOLDER_PREFIX = "NEW-FOLDER";
        internal const string CONTROL_ID_REFRESH = "RefreshLuaScriptsMenuItem";
        internal const string CONTROL_ID_LUA = "LuaRoot";
        internal const string CONTROL_ID_ENABLE = "LuaEnable";
        internal const string CONTROL_ID_GLOBAL_VARS = "LuaGlobalVars";
        internal const string CONTROL_ID_PROPERTIES_AND_METHODS = "LuaPropertiesAndMethods";
        public const string SCRIPTS_ROOT = "<LuaScripts>/";
        internal const string EDITSCRIPT_PREFIX = "LUASCRIPT:";
        internal const string DELETESCRIPT_PREFIX = "LUASCRIPT-DELETE:";
        internal const string DELETEFOLDER_PREFIX = "SCRIPTFOLDER-DELETE:";
        internal const string RENAMESCRIPT_PREFIX = "LUASCRIPT-RENAME:";
        internal const string RENAMEFOLDER_PREFIX = "SCRIPTFOLDER-RENAME:";
        internal const string INCLUDESCRIPT_PREFIX = "LUASCRIPT-INCLUDE:";
        internal const string COMPILETIME_PREFIX = "COMPILETIME:";
        internal const string SCRIPT_ICON = "ScriptIcon";
        internal const string SCRIPTS_ICON = "ScriptsIcon";
        internal const string GLOBAL_VARS_ICON = "GlobalVarsIcon";
        internal const string COMPILE_TIME_SCRIPTS = "LuaCompileTimeScripts";
        internal const string COMPILETIMEENTRY_PREFIX = "compiletimeentry_";
        internal const string CTSCRIPT_MOVEUP_PREFIX = "CTStringMoveUp_";
        internal const string CTSCRIPT_MOVEDOWN_PREFIX = "CTStringMoveDown_";
        internal const string CTSCRIPT_REMOVE_PREFIX = "CTScriptRemove_";
        internal const string EVENT_ACTIONS = "LuaEventActions";
        internal const string VISUAL_VALUE_EDITOR = "LuaVisualValueEditor";
        internal const string VISUAL_ROOT = "<Visual>";
        internal const string LUA_MENU = "LuaMenu";
        internal const string LUA_CONVERT_MENUOPTION = "LuaCodeConvert";

        internal Dictionary<string, LuaScriptFileInfo> scripts
            = new Dictionary<string, LuaScriptFileInfo>();

        internal List<LuaScriptFileInfo> compileTimeScripts
            = new List<LuaScriptFileInfo>();

        internal Dictionary<string, LuaScriptFolderInfo> scriptFolders
            = new Dictionary<string, LuaScriptFolderInfo>();

        internal void ClearScriptFolders()
        {
            foreach (KeyValuePair<string, LuaScriptFolderInfo> folder in scriptFolders)
            {
                if (folder.Value.watcher != null)
                {
                    folder.Value.watcher.EnableRaisingEvents = false;
                }
            }
            scriptFolders.Clear();
            rootScriptFolder = null;
        }

        internal Dictionary<string, LuaScriptEditPane> editPanes
            = new Dictionary<string,LuaScriptEditPane>();

        internal Dictionary<string, VisualLuaValue> visualValues
            = new Dictionary<string, VisualLuaValue>();

        VisualLuaTableValue globalsTable;

		internal IAGSEditor editor;

        internal string lscriptsdir
        {
            get { return Path.Combine(editor.CurrentGame.DirectoryPath, "lscripts"); }
        }

        private string compiledir
        {
            get { return Path.Combine(editor.CurrentGame.DirectoryPath, "Compiled"); }
        }

        private string debugdir
        {
            get { return Path.Combine(editor.CurrentGame.DirectoryPath, "_Debug"); }
        }

        internal lua_State main_L;

        public Form MainForm;

        public LuaForAGSEditorComponent(IAGSEditor editor)
		{
            main_L = InvokeLua.luaL_newstate();
            InvokeLua.lua_atpanic(main_L, InvokeLua.ExceptionPanicHandler);
            this.editor = editor;
			editor.GUIController.RegisterIcon("LuaIcon", GetIcon("lua.ico"));
            editor.GUIController.RegisterIcon("LuaGreyIcon", GetIcon("luagrey.ico"));
            editor.GUIController.RegisterIcon("CogIcon", GetIcon("cog.ico"));
            editor.GUIController.RegisterIcon("EmptyIcon", GetIcon("empty.ico"));
            editor.GUIController.RegisterIcon("silk:table", GetIcon("table.ico"));
            editor.GUIController.RegisterIcon("silk:world", GetIcon("world.ico"));
            editor.GUIController.RegisterIcon("silk:wrench", GetIcon("wrench.ico"));
            editor.GUIController.RegisterIcon("silk:textfield", GetIcon("textfield.ico"));
            editor.GUIController.RegisterIcon("silk:contrast", GetIcon("contrast.ico"));
            editor.GUIController.RegisterIcon("silk:page_white_lightning", GetIcon("page_white_lightning.ico"));
            editor.GUIController.ProjectTree.AddTreeRoot(this, CONTROL_ID_LUA, "Lua", "LuaIcon");

            editor.GUIController.AddMenu(this, LUA_MENU, "Lua", editor.GUIController.FileMenuID);
            MenuCommands newCommands = new MenuCommands(LUA_MENU);
            newCommands.Commands.Add(new MenuCommand(LUA_CONVERT_MENUOPTION, "Open Code Converter..."));
            editor.GUIController.AddMenuItems(this, newCommands);

            IsPluginEnabled = false;
            globalsTable = new VisualLuaTableValue(this, VISUAL_ROOT);
            globalsTable.Name = "_G";
            globalsTable.IsGlobalScope = true;

            codeConvertPane = new CodeConvertPane(editor);
            codeConvertContentDoc = new ContentDocument(codeConvertPane, "Convert AGS->Lua Script", this);
        }

        CodeConvertPane codeConvertPane;
        ContentDocument codeConvertContentDoc;

        private bool TryDeleteFile(string name, string folder)
        {
            string path = Path.Combine(folder, name);
            if (!File.Exists(path))
            {
                return false;
            }
            try
            {
                File.Delete(path);
            }
            catch
            {
                return false;
            }
            return true;
        }

        // Copy a file from the same folder as the assembly for this type to the given folder
        // (used to send lua5.1.dll to the output directory)
        private bool TryCopySiblingFileTo(string name, string folder)
        {
            if (File.Exists(Path.Combine(folder, name)))
            {
                return false;
            }
            string thisDllPath = this.GetType().Assembly.Location;
            string fromPath = Path.Combine(Path.GetDirectoryName(thisDllPath), name);
            string toPath = Path.Combine(folder, name);
            try
            {
                File.Copy(fromPath, toPath);
            }
            catch
            {
                return false;
            }
            return true;
        }

		private Icon GetIcon(string fileName)
		{
			return new Icon(this.GetType(), fileName);
		}

		string IEditorComponent.ComponentID
		{
			get { return COMPONENT_ID; }
		}

        public bool TryRenameScript(string from, string to)
        {
            string newpath = Path.Combine(lscriptsdir, to);
            try
            {
                File.Move(from, newpath);
            }
            catch
            {
                return false;
            }
            RefreshProjectTree();
            LuaScriptEditPane editPane;
            if (editPanes.TryGetValue(from, out editPane))
            {
                editPanes.Remove(from);
                editPanes[newpath] = editPane;
                editPane.contentDocument.Visible = false;
                editPane.contentDocument.Name = to;
                editPane.contentDocument.Visible = true;
            }
            return true;
        }

        // hack...
        /*
        private LuaScriptEditPane CurrentEditor
        {
            get
            {
                PropertyInfo prop = _editor.GUIController.GetType().GetProperty("ActivePane");
                ContentDocument cdoc = prop.GetValue(_editor.GUIController, null) as ContentDocument;
                return (cdoc == null) ? null : cdoc.Control as LuaScriptEditPane;
            }
        }
        */

		IList<MenuCommand> IEditorComponent.GetContextMenu(string controlID)
		{
            List<MenuCommand> contextMenu = new List<MenuCommand>();
            if (controlID == CONTROL_ID_LUA)
            {
                MenuCommand enabled = new MenuCommand(CONTROL_ID_ENABLE, "Enable Lua features?");
                enabled.Checked = IsPluginEnabled;
                contextMenu.Add(enabled);
            }
            else if (controlID.StartsWith(COMPILETIMEENTRY_PREFIX))
            {
                int index = int.Parse(controlID.Substring(COMPILETIMEENTRY_PREFIX.Length));
                contextMenu.Add(new MenuCommand(controlID, "Go to Script"));
                contextMenu.Add(new MenuCommand("-", "-"));
                if (index > 0)
                {
                    contextMenu.Add(new MenuCommand(CTSCRIPT_MOVEUP_PREFIX + index, "Move Up (Run Earlier)"));
                }
                if (index < compileTimeScripts.Count-1)
                {
                    contextMenu.Add(new MenuCommand(CTSCRIPT_MOVEDOWN_PREFIX + index, "Move Down (Run Later)"));
                }
                contextMenu.Add(new MenuCommand(CTSCRIPT_REMOVE_PREFIX + index, "Remove Action"));
            }
            else if (controlID.StartsWith(SCRIPTS_ROOT))
            {
                if (controlID.EndsWith("/"))
                {
                    contextMenu.Add(new MenuCommand(NEWSCRIPT_PREFIX + controlID, "New Lua Script"));
                    if (controlID == SCRIPTS_ROOT)
                    {
                        contextMenu.Add(new MenuCommand(NEWFOLDER_PREFIX + controlID, "New Folder"));
                    }
                    else
                    {
                        contextMenu.Add(new MenuCommand(NEWFOLDER_PREFIX + controlID, "New Subfolder"));
                        contextMenu.Add(new MenuCommand(DELETEFOLDER_PREFIX + controlID, "Delete Folder"));
                        contextMenu.Add(new MenuCommand(RENAMEFOLDER_PREFIX + controlID, "Rename Folder"));
                    }
                }
                else
                {
                    LuaScriptFileInfo script = scripts[controlID];
                    contextMenu.Add(new MenuCommand(DELETESCRIPT_PREFIX + controlID, "Delete"));
                    contextMenu.Add(new MenuCommand(RENAMESCRIPT_PREFIX + controlID, "Rename"));
                    contextMenu.Add(new MenuCommand("-", "-"));
                    MenuCommand includeCommand = new MenuCommand(INCLUDESCRIPT_PREFIX + controlID, "Include in Run-Time Scripts Store?");
                    includeCommand.Checked = script.IncludeAtRunTime;
                    contextMenu.Add(includeCommand);
#if USE_EVENT_ACTIONS
                    contextMenu.Add(new MenuCommand("-", "-"));
                    contextMenu.Add(new MenuCommand(COMPILETIME_PREFIX + controlID, "Add Compile-Time Action: Run Script"));
#endif
                }
            }
            else if (controlID.StartsWith(VISUAL_ROOT))
            {
                VisualLuaValue val;
                if (!visualValues.TryGetValue(controlID, out val))
                {
                    MessageBox.Show("Cannot find Visual Value " + controlID + "!");
                }
                else
                {
                    val.GetContextMenu(contextMenu);
                }
            }
            return contextMenu;
        }

		void IEditorComponent.CommandClick(string controlID)
		{
            if (controlID.StartsWith(DELETESCRIPT_PREFIX))
            {
                string path = controlID.Substring(DELETESCRIPT_PREFIX.Length);
                LuaScriptFileInfo script;
                if (!scripts.TryGetValue(path, out script))
                {
                    MessageBox.Show("Cannot find " + path + "!");
                }
                else
                {
                    if (MessageBox.Show("'" + script.file.Name + "' will be deleted permanently.",
                        "Are you sure?", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation) == DialogResult.OK)
                    {
                        LuaScriptEditPane pane;
                        if (editPanes.TryGetValue(path, out pane))
                        {
                            editor.GUIController.RemovePaneIfExists(pane.contentDocument);
                        }
                        script.Delete();
                        // Cannot delete the node individually, so reload the whole lot
                        //fileInfo.parent.RefreshIcons();
                        //RefreshProjectTree();
                    }
                }
                return;
            }
            if (controlID.StartsWith(INCLUDESCRIPT_PREFIX))
            {
                string key = controlID.Substring(INCLUDESCRIPT_PREFIX.Length);
                LuaScriptFileInfo script = scripts[key];
                script.IncludeAtRunTime = !script.IncludeAtRunTime;
                return;
            }
            if (controlID.StartsWith(RENAMESCRIPT_PREFIX))
            {
                string key = controlID.Substring(RENAMESCRIPT_PREFIX.Length);
                LuaScriptFileInfo selectedScript;
                if (!scripts.TryGetValue(key, out selectedScript))
                {
                    MessageBox.Show("Cannot find " + key + "!");
                }
                else
                {
                    new CreateOrRenameDialog(this, selectedScript).ShowDialog();
                }
                return;
            }
            if (controlID.StartsWith(DELETEFOLDER_PREFIX))
            {
                string path = controlID.Substring(DELETEFOLDER_PREFIX.Length);
                LuaScriptFolderInfo folder;
                if (!scriptFolders.TryGetValue(path, out folder))
                {
                    MessageBox.Show("Cannot find " + path + "!");
                }
                else
                {
                    if (MessageBox.Show("'" + folder.dir.Name + "', and all files and subfolders contained within it, will be deleted permanently.",
                        "Are you sure?", MessageBoxButtons.OKCancel, MessageBoxIcon.Exclamation) == DialogResult.OK)
                    {
                        folder.Delete();
                    }
                }
                return;
            }
            if (controlID.StartsWith(RENAMEFOLDER_PREFIX))
            {
                string key = controlID.Substring(RENAMEFOLDER_PREFIX.Length);
                LuaScriptFolderInfo folder;
                if (!scriptFolders.TryGetValue(key, out folder))
                {
                    MessageBox.Show("Cannot find " + key + "!");
                }
                else
                {
                    new CreateOrRenameDialog(this, folder).ShowDialog();
                }
                return;
            }
            if (controlID.StartsWith(CTSCRIPT_MOVEDOWN_PREFIX))
            {
                int index = int.Parse(controlID.Substring(CTSCRIPT_MOVEDOWN_PREFIX.Length));
                LuaScriptFileInfo this_script = compileTimeScripts[index];
                LuaScriptFileInfo swap_with = compileTimeScripts[index+1];
                compileTimeScripts[index + 1] = this_script;
                compileTimeScripts[index] = swap_with;
                RefreshCompileTimeScripts();
                editor.GUIController.ProjectTree.SelectNode(this, COMPILETIMEENTRY_PREFIX + (index + 1));
                return;
            }
            if (controlID.StartsWith(CTSCRIPT_MOVEUP_PREFIX))
            {
                int index = int.Parse(controlID.Substring(CTSCRIPT_MOVEUP_PREFIX.Length));
                LuaScriptFileInfo this_script = compileTimeScripts[index];
                LuaScriptFileInfo swap_with = compileTimeScripts[index - 1];
                compileTimeScripts[index - 1] = this_script;
                compileTimeScripts[index] = swap_with;
                RefreshCompileTimeScripts();
                editor.GUIController.ProjectTree.SelectNode(this, COMPILETIMEENTRY_PREFIX + (index - 1));
                return;
            }
            if (controlID.StartsWith(CTSCRIPT_REMOVE_PREFIX))
            {
                if (DialogResult.Yes != MessageBox.Show("Are you sure you want to Remove this Action?",
                    "Are you sure?",
                    MessageBoxButtons.YesNo,
                    MessageBoxIcon.Exclamation))
                {
                    return;
                }
                int index = int.Parse(controlID.Substring(CTSCRIPT_REMOVE_PREFIX.Length));
                compileTimeScripts.RemoveAt(index);
                RefreshCompileTimeScripts();
                if (index < compileTimeScripts.Count)
                {
                    editor.GUIController.ProjectTree.SelectNode(this, COMPILETIMEENTRY_PREFIX + index);
                }
                return;
            }
            if (controlID.StartsWith(COMPILETIME_PREFIX))
            {
                LuaScriptFileInfo script = scripts[controlID.Substring(COMPILETIME_PREFIX.Length)];
                if (compileTimeScripts.Contains(script))
                {
                    if (DialogResult.Yes != MessageBox.Show(
                        "This script is already run at compile time at least once. "
                        + "Are you sure want to run it multiple times?",
                        "Script Already Runs At Compile-Time",
                        MessageBoxButtons.YesNo,
                        MessageBoxIcon.Question))
                    {
                        return;
                    }
                }
                string new_entry_id = COMPILETIMEENTRY_PREFIX + compileTimeScripts.Count;
                compileTimeScripts.Add(script);
                editor.GUIController.ProjectTree.StartFromNode(this, COMPILE_TIME_SCRIPTS);
                editor.GUIController.ProjectTree.AddTreeLeaf(this, new_entry_id, compileTimeScripts.Count + ". Run: " + script.ScriptPath, SCRIPT_ICON, false);
                editor.GUIController.ProjectTree.SelectNode(this, new_entry_id);
                return;
            }
            if (controlID.StartsWith(SCRIPTS_ROOT))
            {
                if (!controlID.EndsWith("/"))
                {
                    string key = controlID;
                    LuaScriptFileInfo script;
                    if (!scripts.TryGetValue(key, out script))
                    {
                        MessageBox.Show("Cannot find " + key + "!");
                    }
                    else
                    {
                        script.Open();
                    }
                }
                else
                {
                    // Double click on folder = do nothing
                }
                return;
            }
            if (controlID.StartsWith(NEWSCRIPT_PREFIX))
            {
                string path = controlID.Substring(NEWSCRIPT_PREFIX.Length);
                LuaScriptFolderInfo folder;
                if (!scriptFolders.TryGetValue(path, out folder))
                {
                    MessageBox.Show("Cannot find " + path + "!");
                }
                else
                {
                    new CreateOrRenameDialog(this, folder, false).ShowDialog();
                }
                return;
            }
            if (controlID.StartsWith(COMPILETIMEENTRY_PREFIX))
            {
                int index = int.Parse(controlID.Substring(COMPILETIMEENTRY_PREFIX.Length));
                LuaScriptFileInfo script = compileTimeScripts[index];
                editor.GUIController.ProjectTree.SelectNode(this, script.key);
                return;
            }
            if (controlID.StartsWith(NEWFOLDER_PREFIX))
            {
                string path = controlID.Substring(NEWFOLDER_PREFIX.Length);
                LuaScriptFolderInfo folder;
                if (!scriptFolders.TryGetValue(path, out folder))
                {
                    MessageBox.Show("Cannot find " + path + "!");
                }
                else
                {
                    new CreateOrRenameDialog(this, folder, true).ShowDialog();
                }
                return;
            }
            if (controlID.StartsWith(VISUAL_ROOT))
            {
                string[] split = controlID.Split(new string[] { "::" }, StringSplitOptions.None);
                VisualLuaValue val;
                if (split.Length == 2)
                {
                    if (!visualValues.TryGetValue(split[0], out val))
                    {
                        MessageBox.Show("Cannot find Visual Value " + split[0]);
                        return;
                    }
                    val.OnCommand(split[1]);
                }
                else
                {
                    if (!visualValues.TryGetValue(controlID, out val))
                    {
                        MessageBox.Show("Cannot find Visual Value " + controlID);
                        return;
                    }
                    val.OnCommand(null);
                }
            }
            switch (controlID)
            {
                case LUA_CONVERT_MENUOPTION:
                    editor.GUIController.AddOrShowPane(codeConvertContentDoc);
                    break;
                case CONTROL_ID_ENABLE:
                    IsPluginEnabled = !IsPluginEnabled;
                    if (IsPluginEnabled)
                    {
                        if (!ShownEnableMessage)
                        {
                            ShownEnableMessage = true;
                            MessageBox.Show("Remember to also activate the Lua Run-Time Component in the \"Plugins\" section.",
                                "Run-Time Component Reminder", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                        rootScriptFolder = new LuaScriptFolderInfo(this, null, new DirectoryInfo(lscriptsdir));
                        RefreshProjectTree();
                    }
                    else
                    {
                        if (!ShownDisableMessage)
                        {
                            ShownDisableMessage = true;
                            MessageBox.Show("Remember to also deactivate the Lua Run-Time Component in the \"Plugins\" section.",
                                "Run-Time Component Reminder", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                        scripts.Clear();
                        compileTimeScripts.Clear();
                        ClearScriptFolders();
                    }
                    break;
                default:
                    //_editor.GUIController.ShowMessage(controlID, MessageBoxIconType.Information);
                    break;
			}
		}

		void IEditorComponent.PropertyChanged(string propertyName, object oldValue)
		{
            /*
            LuaScriptEditPane scriptEdit = CurrentEditor;
            if (scriptEdit != null)
            {
               // MessageBox.Show(scriptEdit.ScriptInfo.AutomaticRunMode.ToString());
            }
             */
		}

        delegate void ProcessViewFolder(IViewFolder folder);


       void IEditorComponent.BeforeSaveGame()
		{
            if (!IsPluginEnabled)
            {
                if (!File.Exists(Path.Combine(compiledir, "agslua.dll")))
                {
                    TryDeleteFile("lua5.1.dll", compiledir);
                }
                if (!File.Exists(Path.Combine(debugdir, "agslua.dll")))
                {
                    TryDeleteFile("lua5.1.dll", debugdir);
                }
                TryDeleteFile("lscripts.dat", compiledir);
                return;
            }
            foreach (LuaScriptEditPane pane in editPanes.Values)
            {
                pane.Save();
            }
            if (!Directory.Exists(compiledir))
            {
                Directory.CreateDirectory(compiledir);
            }
            TryCopySiblingFileTo("lua5.1.dll", compiledir);
            if (!Directory.Exists(debugdir))
            {
                Directory.CreateDirectory(debugdir);
            }
            TryCopySiblingFileTo("lua5.1.dll", debugdir);
            string lscripts_dat_path = Path.Combine(compiledir, "lscripts.dat");
            using (FileStream lscripts_dat = File.Open(lscripts_dat_path, FileMode.Create))
            {
                lscripts_dat.WriteByte(27);
                lscripts_dat.Write(Encoding.ASCII.GetBytes("lscripts:"), 0, "lscripts:".Length);
                Queue<string> codeQ = new Queue<string>();
                codeQ.Enqueue("return {");
                /*
                codeQ.Enqueue("rooms = {");
                foreach (UnloadedRoom room in _editor.CurrentGame.Rooms)
                {
                    codeQ.Enqueue("[" + room.Number + "]={");
                    codeQ.Enqueue("objects = {");
                    _editor.RoomController.
                    foreach (RoomObject obj in )
                    {
                        codeQ.Enqueue("[" + obj.ID + "]=" + InvokeLua.util_quotestring(obj.Name) + ";");
                    }
                    codeQ.Enqueue("};"); // rooms[i].objects
                    codeQ.Enqueue("hotspots = {");
                    foreach (RoomHotspot hotspot in room.Hotspots)
                    {
                        codeQ.Enqueue("[" + hotspot.ID + "]=" + InvokeLua.util_quotestring(hotspot.Name) + ";");
                    }
                    codeQ.Enqueue("};"); // rooms[i].hotspots
                    codeQ.Enqueue("};"); // rooms[i]
                }
                codeQ.Enqueue("};"); // rooms
                 */
                codeQ.Enqueue("dialog={");
                foreach (Dialog dialog in editor.CurrentGame.Dialogs)
                {
                    codeQ.Enqueue("[" + dialog.ID + "]=" + InvokeLua.util_quotestring(dialog.Name) + ";");
                }
                codeQ.Enqueue("};"); // dialog
                codeQ.Enqueue("audioclips={");
                foreach (string clipname in HacksAndKludges.YieldAudioClipScriptNames(editor.CurrentGame))
                {
                    codeQ.Enqueue(InvokeLua.util_quotestring(clipname) + ";");
                }
                codeQ.Enqueue("};");
                codeQ.Enqueue("fonts={");
                foreach (AGSFont font in editor.CurrentGame.Fonts)
                {
                    codeQ.Enqueue("[" + font.ID + "]=" + InvokeLua.util_quotestring(font.ScriptID) + ";");
                }
                codeQ.Enqueue("};"); // fonts
                codeQ.Enqueue("views={");
                ProcessViewFolder readViews = null;
                readViews =
                    delegate(IViewFolder folder)
                    {
                        foreach (AGSView view in folder.Views)
                        {
                            codeQ.Enqueue("[" + view.ID + "] = " + InvokeLua.util_quotestring(view.Name) + ";");
                        }
                        foreach (IViewFolder subfolder in folder.SubFolders)
                        {
                            readViews(subfolder);
                        }
                    };
                readViews(editor.CurrentGame.Views);
                codeQ.Enqueue("};"); // views
                codeQ.Enqueue("cursors = {");
                foreach (MouseCursor cursor in editor.CurrentGame.Cursors)
                {
                    codeQ.Enqueue("[" + cursor.ID + "]=" + InvokeLua.util_quotestring(cursor.ScriptID) + ";");
                }
                codeQ.Enqueue("};"); // cursor
                codeQ.Enqueue("gui = {");
                foreach (GUI gui in editor.CurrentGame.GUIs)
                {
                    codeQ.Enqueue("[" + gui.ID + "]={name=" + InvokeLua.util_quotestring(gui.Name) + ";");
                    foreach (GUIControl cnt in gui.Controls)
                    {
                        codeQ.Enqueue("[" + cnt.ID + "]={" +
                            "name=" + InvokeLua.util_quotestring(cnt.Name) + ";" +
                            "type=" + InvokeLua.util_quotestring(cnt.ControlType) + ";" +
                            "};");
                    }
                    codeQ.Enqueue("};"); // gui[i]
                }
                codeQ.Enqueue("};"); // gui
                codeQ.Enqueue("inventory = {");
                foreach (InventoryItem item in editor.CurrentGame.InventoryItems)
                {
                    codeQ.Enqueue("[" + item.ID + "]=" + InvokeLua.util_quotestring(item.Name) + ";");
                }
                codeQ.Enqueue("};"); // inventory
                codeQ.Enqueue("guid='");
                Guid signature = Guid.NewGuid();
                foreach (byte b in signature.ToByteArray())
                {
                    codeQ.Enqueue(String.Format("\\{0}", b));
                }
                codeQ.Enqueue("';"); // end of guid
                codeQ.Enqueue("files={");
                foreach (ScriptEntry scriptEntry in scripts)
                {
                    string path = scriptEntry.Value.file.FullName;
                    string key = scriptEntry.Key.Substring(SCRIPTS_ROOT.Length);
                    byte[] buf = File.ReadAllBytes(path);
                    if (InvokeLua.LUA_OK != InvokeLua.luaL_loadbuffer(main_L, buf, (size_t)buf.Length, scriptEntry.Value.ScriptPath))
                    {
                        string errorMessage = InvokeLua.lua_tostring(main_L, -1);
                        InvokeLua.lua_pop(main_L, 1);
                        InvokeLua.luaL_loadstring(main_L, "error(" + InvokeLua.util_quotestring(errorMessage) + ",2)");
                    }
                    byte[] compressedCompiled;
                    using (MemoryStream memStream = new MemoryStream())
                    using (ZOutputStream z_out = new ZOutputStream(memStream, 9))
                    {
                        InvokeLua.lua_Writer ZOutWriter =
                            delegate(lua_State _L, byte[] data, size_t _sz, lua_State _ud)
                            {
                                z_out.Write(data, 0, data.Length);
                                return 0;
                            };
                        InvokeLua.lua_dump(main_L, ZOutWriter, lua_State.Zero);
                        z_out.finish();
                        compressedCompiled = memStream.ToArray();
                    }
                    codeQ.Enqueue(String.Format("[{0}]=", InvokeLua.util_quotestring(key)));
                    codeQ.Enqueue("{");
                    codeQ.Enqueue(String.Format("offset={0};length={1};", lscripts_dat.Position, compressedCompiled.Length));
                    codeQ.Enqueue("};");
                    lscripts_dat.Write(compressedCompiled, 0, compressedCompiled.Length);
                    InvokeLua.lua_pop(main_L, 1);
                }
                codeQ.Enqueue("};"); // end of files
                codeQ.Enqueue("modules={");
                foreach (ScriptEntry scriptEntry in scripts)
                {
                    string key = scriptEntry.Key.Substring(SCRIPTS_ROOT.Length);

                    codeQ.Enqueue("[" + InvokeLua.util_quotestring(scriptEntry.Value.ModuleName.ToLower()) + "]="
                        + InvokeLua.util_quotestring(key) + ";");
                }
                codeQ.Enqueue("};"); // end of modules
                if (compileTimeScripts.Count != 0)
                {
                    lua_State temp_L = InvokeLua.luaL_newstate();
                    InvokeLua.lua_atpanic(temp_L, InvokeLua.ExceptionPanicHandler);
                    try
                    {
                        InvokeRunTimePlugin.PrepareForCompileTimeScripts(temp_L);
                        /*
                        InvokeLua.lua_getfield(temp_L, InvokeLua.LUA_REGISTRYINDEX, "lscripts");
                        int IDX_LSCRIPTS = InvokeLua.lua_gettop(temp_L);
                        InvokeLua.lua_getfield(temp_L, InvokeLua.LUA_REGISTRYINDEX, "lmodules");
                        int IDX_LMODULES = InvokeLua.lua_gettop(temp_L);
                        foreach (ScriptEntry scriptEntry in scripts)
                        {
                            InvokeLua.lua_pushstring(temp_L, scriptEntry.Value.ScriptPath.ToLower());
                            InvokeLua.lua_pushstring(temp_L, scriptEntry.Value.file.FullName);
                            InvokeLua.lua_rawset(temp_L, IDX_LSCRIPTS);

                            string moduleName = scriptEntry.Value.ModuleName;
                            if (moduleName != null)
                            {
                                InvokeLua.lua_pushstring(temp_L, moduleName);
                                InvokeLua.lua_pushstring(temp_L, scriptEntry.Value.file.FullName);
                                InvokeLua.lua_rawset(temp_L, IDX_LMODULES);
                            }
                        }
                        InvokeLua.lua_pop(temp_L, 2); // remove lscripts, lmodules
                         */
                        foreach (LuaScriptFileInfo script in compileTimeScripts)
                        {
                            if (InvokeLua.LUA_OK != InvokeLua.luaL_loadfile(temp_L, script.file.FullName))
                            {
                                MessageBox.Show(script.ScriptPath + " Compile Error:\n\n" + InvokeLua.lua_tostring(temp_L, -1));
                                InvokeLua.lua_pop(temp_L, -1);
                            }
                            else
                            {
                                if (InvokeLua.LUA_OK != InvokeLua.lua_pcall(temp_L, 0, 0, 0))
                                {
                                    MessageBox.Show(script.ScriptPath + " Run Error:\n\n" + InvokeLua.lua_tostring(temp_L, -1));
                                    InvokeLua.lua_pop(temp_L, 1);
                                }
                            }
                        }

                        codeQ.Enqueue("initstate=\"");

                        InvokeLua.lua_Writer initStateWrite =
                            delegate(lua_State _L, byte[] data, size_t _sz, lua_State _ud)
                            {
                                foreach (byte b in data)
                                {
                                    codeQ.Enqueue(String.Format("\\{0}", b));
                                }
                                return 0;
                            };
                        InvokeRunTimePlugin.WriteInitState(temp_L, initStateWrite);

                        codeQ.Enqueue("\";");
                    }
                    finally
                    {
                        InvokeLua.lua_close(temp_L);
                    }
                }
                codeQ.Enqueue("};"); // end of data

                InvokeLua.lua_Reader_RetString CodeQReader =
                    delegate(lua_State _L, IntPtr _data, ref size_t sz)
                    {
                        if (codeQ.Count == 0)
                        {
                            sz = size_t.Zero;
                            return "";
                        }
                        else
                        {
                            string fragment = codeQ.Dequeue();
                            sz = (size_t)fragment.Length;
                            return fragment;
                        }
                    };

                if (InvokeLua.LUA_OK == InvokeLua.lua_load(main_L, CodeQReader, lua_State.Zero, "lscripts.dat"))
                {
                    byte[] compressedCompiled;
                    using (MemoryStream memStream = new MemoryStream())
                    using (ZOutputStream z_out = new ZOutputStream(memStream, 9))
                    {
                        InvokeLua.lua_Writer Z_OutWriter =
                            delegate(lua_State _L, byte[] data, size_t _sz, lua_State _ud)
                            {
                                z_out.Write(data, 0, data.Length);
                                return 0;
                            };
                        InvokeLua.lua_dump(main_L, Z_OutWriter, lua_State.Zero);
                        z_out.finish();
                        compressedCompiled = memStream.ToArray();
                    }
                    byte[] offset_buf = BitConverter.GetBytes((long)lscripts_dat.Position);
                    byte[] length_buf = BitConverter.GetBytes((long)compressedCompiled.Length);
                    lscripts_dat.Write(compressedCompiled, 0, compressedCompiled.Length);
                    lscripts_dat.Write(offset_buf, 0, offset_buf.Length);
                    lscripts_dat.Write(length_buf, 0, length_buf.Length);
                }
                else
                {
                    MessageBox.Show("Error compiling lscripts.dat");
                }
            }
        }

        LuaScriptFolderInfo rootScriptFolder;

        void RefreshProjectTree()
        {
            editor.GUIController.ProjectTree.RemoveAllChildNodes(this, SCRIPTS_ROOT);
            editor.GUIController.ProjectTree.StartFromNode(this, SCRIPTS_ROOT);
            if (!Directory.Exists(lscriptsdir))
            {
                Directory.CreateDirectory(lscriptsdir);
            }
            rootScriptFolder.RefreshIcons();
            /*
            if (Directory.Exists(lscriptsdir))
            {
                foreach (string s in Directory.GetFiles(lscriptsdir, "*.lua"))
                {
                    string fullpath = Path.Combine(lscriptsdir, s);
                    string filename = Path.GetFileName(fullpath);
                    _editor.GUIController.ProjectTree.AddTreeLeaf(this, EDITSCRIPT_PREFIX + fullpath, filename, SCRIPT_ICON, false);
                }
            }
            */
        }

        void RefreshCompileTimeScripts()
        {
#if USE_EVENT_ACTIONS
            editor.GUIController.ProjectTree.RemoveAllChildNodes(this, COMPILE_TIME_SCRIPTS);
            editor.GUIController.ProjectTree.StartFromNode(this, COMPILE_TIME_SCRIPTS);
            int i = 0;
            foreach (LuaScriptFileInfo script in compileTimeScripts)
            {
                editor.GUIController.ProjectTree.AddTreeLeaf(this, COMPILETIMEENTRY_PREFIX + i, (i+1) + ". Run: " + script.ScriptPath, SCRIPT_ICON, false);
                i++;
            }
#endif
        }

        List<string> restoredCompileScripts;
        XmlElement restoredScriptsInfo;

		void IEditorComponent.RefreshDataFromGame()
		{
            MainForm = Application.OpenForms[0];
            // Copy to new list because something else may be modifying editPanes in another thread(?)
            foreach (LuaScriptEditPane pane in new List<LuaScriptEditPane>(editPanes.Values))
            {
                editor.GUIController.RemovePaneIfExists(pane.contentDocument);
            }
            editPanes.Clear();
            if (IsPluginEnabled)
            {
                scripts.Clear();
                compileTimeScripts.Clear();
                ClearScriptFolders();
                rootScriptFolder = new LuaScriptFolderInfo(this, null, new DirectoryInfo(lscriptsdir));
                rootScriptFolder.EnsureExistence();
                RefreshProjectTree();
                if (restoredScriptsInfo != null)
                {
                    rootScriptFolder.UpdateFromXml(restoredScriptsInfo);
                    restoredScriptsInfo = null;
                }
                if (restoredCompileScripts != null)
                {
                    foreach (string key in restoredCompileScripts)
                    {
                        LuaScriptFileInfo script;
                        if (scripts.TryGetValue(key, out script))
                        {
                            compileTimeScripts.Add(script);
                        }
                        else
                        {
                            MessageBox.Show("Cannot find script " + key + " for Compile-Time Action");
                        }
                    }
                    restoredCompileScripts = null;
                }
                RefreshCompileTimeScripts();
            }
        }

        DateTime RoomLastModified(IRoom room)
        {
            return File.GetLastWriteTimeUtc(Path.Combine(editor.CurrentGame.DirectoryPath, room.FileName));
        }

        void GetRoomUpdates()
        {
            foreach (UnloadedRoom room in editor.CurrentGame.Rooms)
            {
                CachedRoomInfo cache;
                if (RoomInfoCache.TryGetValue(room.Number, out cache)
                    && cache.LastModified == RoomLastModified(room))
                {
                    continue;
                }
                if (editor.RoomController.LoadRoom(room))
                {
                    RoomInfoCache[room.Number] = new CachedRoomInfo(editor, editor.RoomController.CurrentRoom);
                }
            }
        }

		void IEditorComponent.GameSettingsChanged()
		{
		}

        bool? _isPluginEnabled = null;
        bool IsPluginEnabled
        {
            get { return (_isPluginEnabled == null) ? false : (bool)_isPluginEnabled; }
            set
            {
                if (_isPluginEnabled == value)
                {
                    return;
                }
                _isPluginEnabled = value;
                if ((bool)_isPluginEnabled)
                {
                    editor.GUIController.ProjectTree.RemoveAllChildNodes(this, CONTROL_ID_LUA);
                    editor.GUIController.ProjectTree.StartFromNode(this, CONTROL_ID_LUA);
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, SCRIPTS_ROOT, "Lua Scripts", SCRIPTS_ICON, false);

#if USE_EVENT_ACTIONS
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, EVENT_ACTIONS, "Event Actions", "CogIcon", false);
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, VISUAL_VALUE_EDITOR, "Variables, Fields and Methods", "silk:wrench", false);

                    editor.GUIController.ProjectTree.StartFromNode(this, EVENT_ACTIONS);
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, COMPILE_TIME_SCRIPTS, "Compile-Time Actions", "CogIcon", false);
#endif

#if USE_VISUAL_EDITOR
                    editor.GUIController.ProjectTree.StartFromNode(this, VISUAL_VALUE_EDITOR);
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, VISUAL_ROOT + "_G", "Global Variables", "silk:world", false);
#endif
                }
                else
                {
                    // Copy to a list as I once got an error claiming the editPanes collection
                    // had been modified during the iteration
                    foreach (LuaScriptEditPane pane in new List<LuaScriptEditPane>(editPanes.Values))
                    {
                        editor.GUIController.RemovePaneIfExists(pane.contentDocument);
                    }
                    editPanes.Clear();
                    editor.GUIController.ProjectTree.RemoveAllChildNodes(this, CONTROL_ID_LUA);
                    editor.GUIController.ProjectTree.StartFromNode(this, CONTROL_ID_LUA);
                    editor.GUIController.ProjectTree.AddTreeLeaf(this, CONTROL_ID_ENABLE,
                        "(Disabled. Double-click here to enable.)", "LuaGreyIcon", true); 
                }
            }
        }
        bool ShownEnableMessage = false;
        bool ShownDisableMessage = false;

		void IEditorComponent.ToXml(XmlTextWriter writer)
		{
            writer.WriteStartElement("Lua");
            writer.WriteAttributeString("Enabled", IsPluginEnabled.ToString());
            writer.WriteAttributeString("ShownEnableMessage", ShownEnableMessage.ToString());
            writer.WriteAttributeString("ShownDisableMessage", ShownDisableMessage.ToString());
            writer.WriteStartElement("Rooms");
            foreach (CachedRoomInfo roomInfo in RoomInfoCache.Values)
            {
                roomInfo.ToXml(writer);
            }
            writer.WriteEndElement(); // Rooms

            writer.WriteStartElement("ScriptsRootFolder");
            writer.WriteEndElement(); // Scripts

            writer.WriteStartElement("CompileTimeScripts");
            foreach (LuaScriptFileInfo script in compileTimeScripts)
            {
                writer.WriteElementString("Script", script.key);
            }
            writer.WriteEndElement(); // CompileTimeScripts

            globalsTable.ToXml(writer);

            writer.WriteEndElement(); // Lua
		}

        Dictionary<int, CachedRoomInfo> RoomInfoCache = new Dictionary<int, CachedRoomInfo>();

		void IEditorComponent.FromXml(XmlNode node)
		{
            globalsTable.Clear();
            if (node != null)
			{
                XmlElement xmlLua = node["Lua"];
                if (xmlLua != null)
                {
                    /*
                    XmlElement rooms = lua["Rooms"];
                    if (rooms != null)
                    {
                        foreach (XmlNode roomNode in rooms.ChildNodes)
                        {
                            if (roomNode is XmlElement && roomNode.Name == "Room")
                            {
                                CachedRoomInfo roomInfo = new CachedRoomInfo((XmlElement)roomNode);
                                RoomInfoCache[roomInfo.Number] = roomInfo;
                            }
                        }
                    }
                    */
                    if (xmlLua.HasAttribute("Enabled"))
                    {
                        IsPluginEnabled = bool.Parse(xmlLua.GetAttribute("Enabled"));
                    }
                    if (xmlLua.HasAttribute("ShownEnableMessage"))
                    {
                        ShownEnableMessage = bool.Parse(xmlLua.GetAttribute("ShownEnableMessage"));
                    }
                    if (xmlLua.HasAttribute("ShownDisableMessage"))
                    {
                        ShownDisableMessage = bool.Parse(xmlLua.GetAttribute("ShownDisableMessage"));
                    }
                    XmlElement xmlLuaScriptFolderRoot = xmlLua["LuaScriptFolderRoot"];
                    if (xmlLuaScriptFolderRoot != null)
                    {
                        restoredScriptsInfo = xmlLuaScriptFolderRoot;
                    }
                    XmlElement xmlCompileTimeScripts = xmlLua["CompileTimeScripts"];
                    if (xmlCompileTimeScripts != null)
                    {
                        restoredCompileScripts = new List<string>();
                        foreach (XmlNode xmlScript in xmlCompileTimeScripts)
                        {
                            if (xmlScript.NodeType == XmlNodeType.Element && xmlScript.Name == "Script")
                            {
                                restoredCompileScripts.Add(xmlScript.InnerText);
                            }
                        }
                    }
                    else
                    {
                        restoredCompileScripts = null;
                    }
                    XmlElement xml_G = xmlLua["_G"];
                    if (xml_G != null)
                    {
                        MessageBox.Show(xml_G.OuterXml);
                        globalsTable.FromXml(xml_G);
                    }
                }
			}
		}

		void IEditorComponent.EditorShutdown()
		{
		}
	}
}
