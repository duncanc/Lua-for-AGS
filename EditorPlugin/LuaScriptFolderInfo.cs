using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;

namespace AGS.Plugin.Lua
{
    public class LuaScriptFolderInfo
    {
        private LuaForAGSEditorComponent component;
        internal DirectoryInfo __dir;
        internal DirectoryInfo dir
        {
            get
            {
                return __dir;
            }
            set
            {
                if (__dir != null)
                {
                    component.scriptFolders.Remove(key);
                    if (parent != null)
                    {
                        parent.SubFolders.Remove(__dir.Name.ToLower());
                    }
                }
                __dir = value;
                if (value != null)
                {
                    if (parent != null)
                    {
                        parent.SubFolders.Add(__dir.Name.ToLower(), this);
                    }
                    // NOTE: key must be assigned AFTER parent changed
                    component.scriptFolders.Add(key, this);
                }
            }
        }
        public LuaScriptFolderInfo parent;
        internal FileSystemWatcher watcher;
        string key
        {
            get
            {
                if (parent == null)
                {
                    return LuaForAGSEditorComponent.SCRIPTS_ROOT;
                }
                return parent.key + dir.Name.ToLower() + "/";
            }
        }

        public SortedDictionary<string, LuaScriptFolderInfo> SubFolders
            = new SortedDictionary<string,LuaScriptFolderInfo>();
        public SortedDictionary<string, LuaScriptFileInfo> Scripts
            = new SortedDictionary<string,LuaScriptFileInfo>();

        public string Key
        {
            get { return key; }
        }

        public LuaScriptFolderInfo AddSubFolder(string name)
        {
            LuaScriptFolderInfo theInfo = new LuaScriptFolderInfo(component, this, dir.CreateSubdirectory(name));
            SubFolders.Add(theInfo.dir.Name, theInfo);
            return theInfo;
        }

        public void EnsureExistence()
        {
            if (parent != null)
            {
                parent.EnsureExistence();
            }
            if (!dir.Exists)
            {
                dir.Create();
            }
        }

        public void Delete()
        {
            Stack<object> deleteStack = new Stack<object>();
            AddToDeleteStack(deleteStack);
            while (deleteStack.Count > 0)
            {
                object deleteMe = deleteStack.Pop();
                if (deleteMe is LuaScriptFolderInfo)
                {
                    LuaScriptFolderInfo folder = (LuaScriptFolderInfo)deleteMe;
                    component.scriptFolders.Remove(folder.key);
                    folder.dir.Delete();
                }
                else
                {
                    LuaScriptFileInfo script = (LuaScriptFileInfo)deleteMe;
                    component.scripts.Remove(script.key);
                    script.Delete();
                }
            }
        }
        internal void AddToDeleteStack(Stack<object> deleteStack)
        {
            watcher.EnableRaisingEvents = false;
            watcher.Dispose();
            watcher = null;
            deleteStack.Push(this);
            foreach (LuaScriptFileInfo script in Scripts.Values)
            {
                deleteStack.Push(script);
            }
            foreach (LuaScriptFolderInfo folder in SubFolders.Values)
            {
                folder.AddToDeleteStack(deleteStack);
            }
        }

        public void BeenDeleted()
        {
            if (watcher != null)
            {
                watcher.EnableRaisingEvents = false;
                watcher.Dispose();
                watcher = null;
            }
            dir = null;
            if (parent != null) // should never be the case anyway?
            {
                parent.RefreshIcons();
            }
        }

        public LuaScriptFolderInfo(LuaForAGSEditorComponent l4a_component, LuaScriptFolderInfo parent, DirectoryInfo actualDir)
        {
            this.component = l4a_component;
            this.parent = parent;
            this.dir = actualDir;
            EnsureExistence();

            foreach (DirectoryInfo subdir in dir.GetDirectories())
            {
                // adds self to folders automatically
                new LuaScriptFolderInfo(component, this, subdir);
            }
            foreach (FileInfo file in dir.GetFiles("*.lua"))
            {
                // adds self to Scripts automatically
                new LuaScriptFileInfo(component, this, file);
            }

            InitFileSystemWatcher();
        }

        void InitFileSystemWatcher()
        {
            watcher = new FileSystemWatcher(dir.FullName);
            watcher.Changed += OnFileSystemEvent;
            watcher.Created += OnFileSystemEvent;
            watcher.Deleted += OnFileSystemEvent;
            watcher.Renamed += OnFileSystemEvent;
            watcher.EnableRaisingEvents = true;
        }

        void AddIcon()
        {
            component.editor.GUIController.ProjectTree.AddTreeLeaf(component, key, dir.Name, "ViewFolderIcon", false);
            RefreshIcons();
        }

        internal void RefreshIcons()
        {
            component.editor.GUIController.ProjectTree.RemoveAllChildNodes(component, Key);
            foreach (LuaScriptFolderInfo subfolder in SubFolders.Values)
            {
                // each subfolder will take over the StartFromNode to recursively add its own children
                component.editor.GUIController.ProjectTree.StartFromNode(component, key);
                subfolder.AddIcon();
            }
            component.editor.GUIController.ProjectTree.StartFromNode(component, key);
            foreach (LuaScriptFileInfo scriptfile in Scripts.Values)
            {
                scriptfile.AddIcon();
            }
        }

        public delegate void OnWatchedChangeDelegate(WatcherChangeTypes change, string name, string oldName);
        private void OnWatchedChange(WatcherChangeTypes change, string name, string oldName)
        {
            switch (change)
            {
                case WatcherChangeTypes.Created:
                    string path = Path.Combine(dir.FullName, name);
                    if (Directory.Exists(path))
                    {
                        LuaScriptFolderInfo newFolder
                            = new LuaScriptFolderInfo(component, this, new DirectoryInfo(path));
                        RefreshIcons();
                        if (name == creating)
                        {
                            component.editor.GUIController.ProjectTree.SelectNode(component, newFolder.key);
                        }
                    }
                    else
                    {
                        LuaScriptFileInfo newScript
                            = new LuaScriptFileInfo(component, this, new FileInfo(path));
                        RefreshIcons();
                        if (name == creating)
                        {
                            component.editor.GUIController.ProjectTree.SelectNode(component, newScript.key);
                            newScript.Open();
                        }
                    }
                    creating = null;
                    break;
                case WatcherChangeTypes.Deleted:
                {
                    LuaScriptFileInfo script;
                    LuaScriptFolderInfo folder;
                    if (Scripts.TryGetValue(name.ToLower(), out script))
                    {
                        script.BeenDeleted();
                    }
                    else if (SubFolders.TryGetValue(name.ToLower(), out folder))
                    {
                        folder.BeenDeleted();
                    }
                    break;
                }
                case WatcherChangeTypes.Changed:
                    break;
                case WatcherChangeTypes.Renamed:
                    if (SubFolders.ContainsKey(oldName.ToLower()))
                    {
                        SubFolders[oldName.ToLower()].BeenRenamed(name);
                    }
                    else if (Scripts.ContainsKey(oldName.ToLower()))
                    {
                        Scripts[oldName.ToLower()].BeenRenamed(name);
                    }
                    break;
            }
        }
        void OnFileSystemEvent(object sender, FileSystemEventArgs e)
        {
            WatcherChangeTypes change = e.ChangeType;
            string name = e.Name;
            string oldName;
            if (change == WatcherChangeTypes.Renamed)
            {
                oldName = ((RenamedEventArgs)e).OldName;
            }
            else
            {
                oldName = null;
            }
            component.MainForm.BeginInvoke(new OnWatchedChangeDelegate(OnWatchedChange), change, name, oldName);
        }
        public void UpdateFromXml(XmlElement element)
        {
            foreach (LuaScriptFolderInfo folder in SubFolders.Values)
            {
                XmlElement folderElement = element.SelectSingleNode("LuaScriptFolder[@name=\"" + folder.dir.Name.ToLower() + "\"]") as XmlElement;
                if (folderElement != null)
                {
                    folder.UpdateFromXml(folderElement);
                }
            }
            foreach (LuaScriptFileInfo script in Scripts.Values)
            {
                XmlElement fileElement = element.SelectSingleNode("LuaScriptFile[@name=\"" + script.file.Name.ToLower() + "\"]") as XmlElement;
                if (fileElement != null)
                {
                    script.UpdateFromXml(fileElement);
                }
            }
        }
        string creating;
        public void ToXml(XmlWriter output)
        {
            output.WriteStartElement(parent==null ? "LuaScriptFolderRoot" : "LuaScriptFolder");
            if (parent != null)
            {
                output.WriteAttributeString("Name", dir.Name.ToLower());
            }
            foreach (LuaScriptFolderInfo subfolder in SubFolders.Values)
            {
                subfolder.ToXml(output);
            }
            foreach (LuaScriptFileInfo scriptfile in Scripts.Values)
            {
                scriptfile.ToXml(output);
            }
            output.WriteEndElement();
        }
        public bool TryCreateSubfolder(string name)
        {
            if (Scripts.ContainsKey(name.ToLower()) || SubFolders.ContainsKey(name.ToLower()))
            {
                return false;
            }
            creating = name;
            Directory.CreateDirectory(Path.Combine(dir.FullName, name));
            return true;
        }
        public bool TryCreateScript(string name)
        {
            if (Scripts.ContainsKey(name.ToLower()) || SubFolders.ContainsKey(name.ToLower()))
            {
                return false;
            }
            creating = name;
            File.CreateText(Path.Combine(dir.FullName, name)).Close();
            return true;
        }
        private string ParentPath
        {
            get
            {
                return (parent == null) ? component.lscriptsdir : parent.dir.FullName;
            }
        }
        void DisableAllWatchers()
        {
            if (parent != null && parent.watcher != null)
            {
                parent.watcher.EnableRaisingEvents = false;
            }
            if (watcher != null)
            {
                watcher.EnableRaisingEvents = false;
            }
            foreach (LuaScriptFolderInfo folder in SubFolders.Values)
            {
                folder.DisableAllWatchers();
            }
        }
        void EnableAllWatchers()
        {
            if (parent != null && parent.watcher != null)
            {
                parent.watcher.EnableRaisingEvents = true;
            }
            if (watcher != null)
            {
                watcher.Path = dir.FullName;
            }
            foreach (LuaScriptFolderInfo folder in SubFolders.Values)
            {
                folder.EnableAllWatchers();
            }
        }
        void UpdateChildren()
        {
            foreach (LuaScriptFileInfo script in new List<LuaScriptFileInfo>(Scripts.Values))
            {
                script.file = new FileInfo(Path.Combine(dir.FullName, script.file.Name));
            }
            foreach (LuaScriptFolderInfo subfolder in new List<LuaScriptFolderInfo>(SubFolders.Values))
            {
                subfolder.dir = new DirectoryInfo(Path.Combine(dir.FullName, subfolder.dir.Name));
                subfolder.UpdateChildren();
            }
        }
        public bool TryRename(string newName)
        {
            if (newName == dir.Name)
            {
                return true;
            }
            string newPath = Path.Combine(ParentPath, newName);
            bool caseChange = newName.Equals(dir.Name, StringComparison.OrdinalIgnoreCase);
            if (Directory.Exists(newPath) && !caseChange)
            {
                return false;
            }
            DisableAllWatchers();
            DirectoryInfo oldPath = dir;
            dir = new DirectoryInfo(newPath);
            if (!caseChange)
            {
                this.UpdateChildren();
            }
            try
            {
                if (caseChange)
                {
                    string crazyPath = Path.Combine(ParentPath, Path.GetRandomFileName());
                    oldPath.MoveTo(crazyPath);
                    Directory.Move(crazyPath, newPath);
                }
                else
                {
                    oldPath.MoveTo(newPath);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message + "\n" + e.StackTrace);
                dir = oldPath;
                if (!caseChange)
                {
                    this.UpdateChildren();
                }
                EnableAllWatchers();
                return false;
            }
            EnableAllWatchers();
            parent.RefreshIcons();
            return true;
        }
        public void BeenRenamed(string newName)
        {
            dir = new DirectoryInfo(Path.Combine(ParentPath, newName));
            parent.RefreshIcons();
        }
    }
}
