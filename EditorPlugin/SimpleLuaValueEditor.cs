using AGS.Types;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

namespace AGS.Plugin.Lua
{
    public partial class SimpleLuaValueEditor : Form
    {
        private LuaForAGSEditorComponent component;
        VisualLuaValueType creatingType = VisualLuaValueType.None;
        VisualLuaTableValue parentTable;
        VisualLuaValue editValue;

        public SimpleLuaValueEditor(LuaForAGSEditorComponent component, VisualLuaTableValue parentTable, VisualLuaValueType newValueType)
        {
            this.component = component;
            this.creatingType = newValueType;
            this.parentTable = parentTable;
            InitializeComponent();
        }

        private void SimpleLuaValueEditor_Load(object sender, EventArgs e)
        {
            if (editValue == null)
            {
                this.Text = "Add Lua " + creatingType.ToString() + " Value";
                ConfirmButton.Text = "Add";
            }
            else
            {
                this.Text = "Edit Lua " + editValue.Type.ToString() + " Value";
                ConfirmButton.Text = "Update";
            }
        }

        private void CancelyButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ConfirmButton_Click(object sender, EventArgs e)
        {
            if (editValue == null)
            {
                string name = NameBox.Text;
                if (!Regex.Match(name, @"^[a-zA-Z_][a-zA-Z_0-9]*$").Success
                    || InvokeLua.util_iskeyword(name))
                {
                    MessageBox.Show("Invalid name. Please choose another.");
                    NameBox.Focus();
                    return;
                }
                if (parentTable.HasField(name))
                {
                    MessageBox.Show("This variable name is already in use. Please choose another.");
                    NameBox.Focus();
                    return;
                }
                VisualLuaValue newValue;
                switch (creatingType)
                {
                    case VisualLuaValueType.String:
                        VisualLuaStringValue newString = new VisualLuaStringValue(component, parentTable.Namespace);
                        newString.Value = InitialValueBox.Text;
                        newValue = newString;
                        break;
                    default:
                        throw new Exception("Unsupported type");
                }
                newValue.Name = name;
                parentTable[name] = newValue;
                parentTable.RefreshChildren();
                this.Close();
                return;
            }
        }
    }
}
