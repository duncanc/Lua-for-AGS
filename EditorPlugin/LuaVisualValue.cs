using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Windows.Forms;
using AGS.Types;

namespace AGS.Plugin.Lua
{
    public enum VisualLuaValueType
    {
        None, String, Number, Boolean, Table
    }
    public abstract class VisualLuaValue
    {
        public abstract void ToXml(XmlWriter output);
        protected void StartElement(XmlWriter writer, string typeName)
        {
            writer.WriteStartElement(ElementName);
            writer.WriteAttributeString("Name", Name);
            writer.WriteAttributeString("Type", typeName);
        }
        protected AGS.Types.IProjectTree ProjectTree
        {
            get
            {
                return _editorComponent.editor.GUIController.ProjectTree;
            }
        }
        public abstract void AddIcon();
        private string _elementName = "Value";
        public string ElementName
        {
            get { return _elementName; }
            set { _elementName = value; }
        }
        protected string _namespace;
        internal VisualLuaTableValue _parentTable;
        public VisualLuaTableValue ParentTable
        {
            get
            {
                return _parentTable;
            }
        }
        public abstract VisualLuaValueType Type
        {
            get;
        }
        public string Namespace
        {
            get
            {
                return _namespace;
            }
        }
        public string FullName
        {
            get
            {
                if (_parentTable == null)
                {
                    return _name ?? "";
                }
                else if (_name == null)
                {
                    return _parentTable.Name;
                }
                else
                {
                    return _parentTable.Name + "." + _name;
                }
            }
        }
        public virtual void FromXml(XmlNode node)
        {
            Name = node.Attributes["Name"].Value;
        }
        private string _name;
        public string Name
        {
            get { return _name; }
            set
            {
                if (value == _name)
                {
                    return;
                }
                if (_name != null)
                {
                    _editorComponent.visualValues.Remove(Namespace + FullName);
                }
                _name = value;
                if (value != null)
                {
                    _editorComponent.visualValues.Add(Namespace + FullName, this);
                }
            }
        }
        protected bool Editable = true;
        public virtual void GetContextMenu(IList<MenuCommand> menu)
        {
            MenuCommand editCommand = new MenuCommand(Namespace + FullName + "::Edit", "Edit");
            editCommand.Enabled = Editable;
            menu.Add(editCommand);
            MenuCommand delCommand = new MenuCommand(Namespace + FullName + "::Delete", "Delete");
            if (ParentTable == null)
            {
                delCommand.Enabled = false;
            }
            menu.Add(delCommand);
        }
        public virtual void OnCommand(string command)
        {
            switch (command)
            {
                case "Delete":
                    ParentTable.RemoveChild(this);
                    ParentTable.RefreshChildren();
                    break;
            }
        }
        internal LuaForAGSEditorComponent _editorComponent;
        protected VisualLuaValue(LuaForAGSEditorComponent editorComponent, string ns)
        {
            _editorComponent = editorComponent;
            _namespace = ns;
        }
        public static VisualLuaValue GetFromXml(LuaForAGSEditorComponent editorComponent, string ns, XmlNode node)
        {
            string name = node.Name;
            switch (node.Attributes["Type"].Value)
            {
                case "Number":
                    VisualLuaNumberValue num = new VisualLuaNumberValue(editorComponent, ns);
                    num.FromXml(node);
                    return num;
                case "String":
                    VisualLuaStringValue str = new VisualLuaStringValue(editorComponent, ns);
                    str.FromXml(node);
                    return str;
                case "Boolean":
                    VisualLuaBooleanValue bl = new VisualLuaBooleanValue(editorComponent, ns);
                    bl.FromXml(node);
                    return bl;
                case "Table":
                    VisualLuaTableValue tbl = new VisualLuaTableValue(editorComponent, ns);
                    tbl.FromXml(node);
                    return tbl;
            }
            return null;
        }
    }
    public class VisualLuaStringValue : VisualLuaValue
    {
        public override VisualLuaValueType Type
        {
            get { return VisualLuaValueType.String; }
        }
        private string _value;
        public string Value
        {
            get { return _value; }
            set { _value = value; }
        }
        public VisualLuaStringValue(LuaForAGSEditorComponent editorComponent, string ns)
            : base(editorComponent, ns)
        {
        }
        public override void FromXml(XmlNode node)
        {
            base.FromXml(node);
            _value = node.InnerText;
        }
        public override void GetContextMenu(IList<MenuCommand> menu)
        {
            base.GetContextMenu(menu);
        }
        public override void ToXml(XmlWriter writer)
        {
            base.StartElement(writer, "String");
            writer.WriteString(_value);
            writer.WriteEndElement();
        }
        public override void AddIcon()
        {
            string trimmed = _value;
            trimmed = Regex.Replace(trimmed, @"^\s+", "");
            trimmed = Regex.Replace(trimmed, @"\s+$", "");
            trimmed = Regex.Replace(trimmed, @"\s+", " ");
            if (trimmed.Length > 15)
            {
                trimmed = trimmed.Substring(1,11) + "[...]";
            }
            string preview = Name + " = \"" + trimmed.Replace("\"", "\\\"") + "\";";
            ProjectTree.AddTreeLeaf(_editorComponent, Namespace + FullName, preview, "silk:textfield", false);
        }
    }
    public class VisualLuaNumberValue : VisualLuaValue
    {
        public override VisualLuaValueType Type
        {
            get { return VisualLuaValueType.Number; }
        }
        private double _value;
        public double Value
        {
            get { return _value; }
            set { _value = value; }
        }
        public VisualLuaNumberValue(LuaForAGSEditorComponent editorComponent, string ns)
            : base(editorComponent, ns)
        {
        }
        public override void FromXml(XmlNode node)
        {
            base.FromXml(node);
            _value = double.Parse(node.InnerText);
        }
        public override void ToXml(XmlWriter output)
        {
            base.StartElement(output, "Number");
            output.WriteString(_value.ToString());
            output.WriteEndElement();
        }
        public override void AddIcon()
        {
            string preview = Name + " = " + _value + ";";
            ProjectTree.AddTreeLeaf(_editorComponent, Namespace + FullName, preview, "silk:textfield", false);
        }
    }
    public class VisualLuaBooleanValue : VisualLuaValue
    {
        public override VisualLuaValueType Type
        {
            get { return VisualLuaValueType.Boolean; }
        }
        private bool _value;
        public bool Value
        {
            get { return _value; }
            set { _value = value; }
        }
        public VisualLuaBooleanValue(LuaForAGSEditorComponent editorComponent, string ns)
            : base(editorComponent, ns)
        {
        }
        public override void AddIcon()
        {
            string preview = Name + " = " + (_value?"true":"false") + ";";
            ProjectTree.AddTreeLeaf(_editorComponent, Namespace + FullName, preview, "silk:contrast", false);
        }
        public override void FromXml(XmlNode node)
        {
            base.FromXml(node);
            _value = bool.Parse(node.InnerText);
        }
        public override void ToXml(XmlWriter output)
        {
            base.StartElement(output, "Boolean");
            output.WriteString(_value.ToString());
            output.WriteEndElement();
        }
    }
    public class VisualLuaTableValue : VisualLuaValue
    {
        public override VisualLuaValueType Type
        {
            get { return VisualLuaValueType.Table; }
        }
        public bool IsGlobalScope;
        private SortedDictionary<string, VisualLuaValue> _values
            = new SortedDictionary<string,VisualLuaValue>();
        public VisualLuaTableValue(LuaForAGSEditorComponent editorComponent, string ns)
            : base(editorComponent, ns)
        {
            this.Editable = false;
        }
        public VisualLuaValue this[string key]
        {
            get
            {
                VisualLuaValue val;
                if (!_values.TryGetValue(key, out val))
                {
                    val = null;
                }
                return val;
            }
            set
            {
                _values[key] = value;
            }
        }
        public void Clear()
        {
            _values.Clear();
        }
        public override void ToXml(XmlWriter output)
        {
            base.StartElement(output, "Table");
            foreach (VisualLuaValue value in _values.Values)
            {
                value.ToXml(output);
            }
            output.WriteEndElement();
        }
        public void RefreshChildren()
        {
            string key = Namespace + FullName;
            ProjectTree.RemoveAllChildNodes(_editorComponent, key);
            foreach (VisualLuaValue val in _values.Values)
            {
                ProjectTree.SelectNode(_editorComponent, key);
                val.AddIcon();
            }
        }
        public override void FromXml(XmlNode node)
        {
            base.FromXml(node);
            _values.Clear();
            foreach (XmlNode subnode in node.ChildNodes)
            {
                if (subnode is XmlElement)
                {
                    VisualLuaValue val = VisualLuaValue.GetFromXml(_editorComponent, _namespace, subnode);
                    val._parentTable = this;
                    _values.Add(val.Name, val);
                }
            }
        }
        public override void GetContextMenu(IList<MenuCommand> menu)
        {
            base.GetContextMenu(menu);
            menu.Add(new MenuCommand("-","-"));
            menu.Add(new MenuCommand(Namespace + FullName + "::AddString", "Add String..."));
            menu.Add(new MenuCommand(Namespace + FullName + "::AddNumber", "Add Number..."));
            menu.Add(new MenuCommand(Namespace + FullName + "::AddBoolean", "Add Boolean..."));
            menu.Add(new MenuCommand(Namespace + FullName + "::AddTable", "Add Table..."));
        }
        public override void OnCommand(string command)
        {
            switch (command)
            {
                case "AddString":
                    (new SimpleLuaValueEditor(_editorComponent, this, VisualLuaValueType.String)).ShowDialog();
                    return;
                case "AddNumber":
                    (new SimpleLuaValueEditor(_editorComponent, this, VisualLuaValueType.Number)).ShowDialog();
                    return;
                case "AddBoolean":
                    (new SimpleLuaValueEditor(_editorComponent, this, VisualLuaValueType.Boolean)).ShowDialog();
                    return;
                default:
                    base.OnCommand(command);
                    return;
            }
        }
        public bool HasField(string name)
        {
            return _values.ContainsKey(name);
        }
        public void RemoveChild(VisualLuaValue val)
        {
            _values.Remove(val.Name);
            _editorComponent.visualValues.Remove(val.Namespace + val.FullName);
        }
        public override void AddIcon()
        {
            string preview = Name + " = {";
            ProjectTree.AddTreeLeaf(_editorComponent, Namespace + FullName, preview, "silk:table", false);
            ProjectTree.AddTreeLeaf(_editorComponent, Namespace + FullName + "::Select", "}", "EmptyIcon", false);
            foreach (VisualLuaValue val in _values.Values)
            {
                ProjectTree.SelectNode(_editorComponent, Namespace + FullName);
                val.AddIcon();
            }
        }
    }
}
