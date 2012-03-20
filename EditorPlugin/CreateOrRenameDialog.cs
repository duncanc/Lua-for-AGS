using AGS.Types;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace AGS.Plugin.Lua
{
    public partial class CreateOrRenameDialog : Form
    {
        private LuaForAGSEditorComponent component;
        private LuaScriptFolderInfo folder;
        private LuaScriptFileInfo script;
        private bool renaming;
        private bool targetingFolder;
        public CreateOrRenameDialog(LuaForAGSEditorComponent component, LuaScriptFolderInfo scriptFolder)
        {
            this.component = component;
            this.folder = scriptFolder;
            this.targetingFolder = true;
            this.renaming = true;
            InitializeComponent();
        }
        public CreateOrRenameDialog(LuaForAGSEditorComponent component, LuaScriptFolderInfo scriptFolder, bool creatingFolder)
        {
            this.component = component;
            this.folder = scriptFolder;
            this.renaming = false;
            this.targetingFolder = creatingFolder;
            InitializeComponent();
        }
        public CreateOrRenameDialog(LuaForAGSEditorComponent component, LuaScriptFileInfo script)
        {
            this.component = component;
            this.script = script;
            this.renaming = true;
            this.folder = script.parent;
            InitializeComponent();
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void NewLuaScriptDialog_Load(object sender, EventArgs e)
        {
            if (targetingFolder)
            {
                if (renaming)
                {
                    this.Text = "Rename Lua Scripts Folder";
                    label1.Text = "Enter a new name for the folder:";
                    ConfirmButton.Text = "Rename";
                    NameBox.Text = folder.dir.Name;
                }
                else
                {
                    this.Text = "Create New Lua Scripts Folder";
                    label1.Text = "Enter a name for the new folder:";
                    ConfirmButton.Text = "Create";
                    NameBox.Text = "scripts";
                }
            }
            else
            {
                if (renaming)
                {
                    this.Text = "Rename Lua Script";
                    label1.Text = "Enter a new name for the script:";
                    ConfirmButton.Text = "Rename";
                    NameBox.Text = script.file.Name;
                }
                else
                {
                    this.Text = "Add New Lua Script";
                    label1.Text = "Enter a name for the new script:";
                    ConfirmButton.Text = "Create";
                    NameBox.Text = "script.lua";
                }
            }
        }

        private void NewLuaScriptDialog_Activated(object sender, EventArgs e)
        {
        }

        private void NewLuaScriptDialog_Shown(object sender, EventArgs e)
        {
            NameBox.Focus();
            NameBox.Select(0, Path.GetFileNameWithoutExtension(NameBox.Text).Length);
        }

        private void ScriptNameBox_Validating(object sender, CancelEventArgs e)
        {
        }

        private void CreateButton_Click(object sender, EventArgs e)
        {
            string filename = NameBox.Text;
            if (targetingFolder)
            {
                if (renaming)
                {
                    if (folder.TryRename(filename))
                    {
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show(
                            "Sorry - something went wrong, and the folder could not be renamed.",
                            "Cannot Rename Folder",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                    }
                }
                else
                {
                    folder.TryCreateSubfolder(filename);
                    this.Close();
                    return;
                }
            }
            else
            {
                if (renaming)
                {
                    if (script.TryRename(filename))
                    {
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show(
                            "Sorry - something went wrong, and the script could not be renamed.",
                            "Cannot Rename Script",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                    }
                }
                else
                {
                    if (folder.TryCreateScript(filename))
                    {
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show(
                            "A script with this name already exists. Please choose another.",
                            "Script Already Exists",
                            MessageBoxButtons.OK,
                            MessageBoxIcon.Error);
                    }
                }
            }
        }
    }
}
