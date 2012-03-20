using AGS.Types;
using System.Windows.Forms;
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace AGS.Plugin.Lua
{
    class CachedRoomInfo
    {
        public CachedRoomInfo(IAGSEditor editor, ILoadedRoom room)
        {
            IRoom iroom = room as IRoom;
            if (iroom == null)
            {
                MessageBox.Show("Cannot convert " + iroom.ToString() + " to IRoom!");
            }
            Number = iroom.Number;
            string scriptPath = Path.Combine(editor.CurrentGame.DirectoryPath, iroom.FileName);
            LastModified = File.GetLastWriteTimeUtc(scriptPath);
            Description = iroom.Description;
            HotspotScriptNames = new string[room.Hotspots.Count];
            ObjectScriptNames = new string[room.Objects.Count];
            for (int i = 0; i < room.Hotspots.Count; i++)
            {
                HotspotScriptNames[i] = room.Hotspots[i].Name;
            }
            for (int i = 0; i < room.Objects.Count; i++)
            {
                ObjectScriptNames[i] = room.Objects[i].Name;
            }
        }
        public CachedRoomInfo(XmlElement element)
        {
            Number = int.Parse(element.GetAttribute("Number"));
            LastModified = DateTime.FromFileTimeUtc(long.Parse(element.GetAttribute("LastModified")));
            Description = element.GetAttribute("Description");
            HotspotScriptNames = element.GetAttribute("Hotspots").Split(',');
            ObjectScriptNames = element.GetAttribute("Objects").Split(',');
        }
        public void ToXml(XmlWriter output)
        {
            output.WriteStartElement("Room");
            output.WriteAttributeString("Number", Number.ToString());
            output.WriteAttributeString("LastModified", LastModified.ToFileTimeUtc().ToString());
            output.WriteAttributeString("Description", Description);
            output.WriteAttributeString("Hotspots", String.Join(",", HotspotScriptNames));
            output.WriteAttributeString("Objects", String.Join(",", ObjectScriptNames));
            output.WriteEndElement();
        }
        public int Number;
        public DateTime LastModified;
        public string Description;
        public string[] HotspotScriptNames;
        public string[] ObjectScriptNames;
    }
}
