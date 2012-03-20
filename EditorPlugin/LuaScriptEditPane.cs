using AGS.Types;
using ScintillaNet;
using System;
using System.Media;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Xml.Serialization;
using SystemFont = System.Drawing.Font;
using lua_State = System.IntPtr;
using size_t = System.UIntPtr;

namespace AGS.Plugin.Lua
{
	public partial class LuaScriptEditPane : EditorContentPanel
	{
		private IAGSEditor editor;
        public ContentDocument contentDocument;
        public string path
        {
            get
            {
                return ScriptInfo.file.FullName;
            }
        }

        Scintilla scintillaWrapper;
        INativeScintilla scintilla;

        private static SystemFont codeFont = new SystemFont("Courier New", 10);

        public LuaScriptFileInfo ScriptInfo;

        LuaForAGSEditorComponent parentComponent;

        public LuaScriptEditPane(LuaForAGSEditorComponent parentComponent, IAGSEditor owningEditor, LuaScriptFileInfo scriptInfo)
		{
            this.parentComponent = parentComponent;
            ScriptInfo = scriptInfo;
			InitializeComponent();
			editor = owningEditor;
            textBox1.Select(0, 0);
            textBox1.Hide();

            scintillaWrapper = new Scintilla();
            scintilla = scintillaWrapper.NativeInterface;

            scintillaWrapper.Parent = this;
            scintillaWrapper.Location = textBox1.Location;
            scintillaWrapper.Size = textBox1.Size;
            scintillaWrapper.Anchor = textBox1.Anchor;

            scintilla.RegisterImage(1, ResourceManager.GetResourceAsString("table.xpm"));


            /*
            scintillaWrapper.Folding.Flags = FoldFlag.LineBeforeContracted | FoldFlag.LineAfterExpanded;

            scintilla.SetMarginWidthN(2, 16);
            scintilla.SetMarginTypeN(2, (int)MarginType.Symbol);
            scintilla.MarkerDefine((int)MarkerOutline.FolderOpen, (int)MarkerSymbol.BoxMinus);
            scintilla.MarkerDefine((int)MarkerOutline.Folder, (int)MarkerSymbol.BoxPlus);
            scintilla.MarkerDefine((int)MarkerOutline.FolderSub, (int)MarkerSymbol.VLine);
            scintilla.MarkerDefine((int)MarkerOutline.FolderTail, (int)MarkerSymbol.LCorner);
            scintilla.MarkerDefine((int)MarkerOutline.FolderEnd, (int)MarkerSymbol.BoxPlusConnected);
            scintilla.MarkerDefine((int)MarkerOutline.FolderOpenMid, (int)MarkerSymbol.BoxMinusConnected);
            scintilla.MarkerDefine((int)MarkerOutline.FolderMidTail, (int)MarkerSymbol.TCorner);
            scintilla.SetMarginSensitiveN(2, true);
             */

            scintillaWrapper.Font = codeFont;
            for (int i = 0; i <= 32; i++)
            {
                scintillaWrapper.Styles[i].Font = codeFont;
            }
            scintillaWrapper.Lexing.Lexer = Lexer.Lua;
            scintillaWrapper.Styles[0].ForeColor = Color.FromArgb(0, 0, 0);
            scintillaWrapper.Styles[1].ForeColor = Color.FromArgb(0, 127, 0);
            scintillaWrapper.Styles[2].ForeColor = Color.FromArgb(0, 127, 0);
            scintillaWrapper.Styles[3].ForeColor = Color.FromArgb(127, 127, 127);
            scintillaWrapper.Styles[4].ForeColor = Color.FromArgb(0, 150, 175);
            scintillaWrapper.Styles[5].ForeColor = Color.FromArgb(0, 0, 127);
            scintillaWrapper.Styles[5].Bold = true;
            scintillaWrapper.Styles[6].ForeColor = Color.FromArgb(170, 0, 170);
            scintillaWrapper.Styles[7].ForeColor = Color.FromArgb(170, 0, 170);
            scintillaWrapper.Styles[8].ForeColor = Color.FromArgb(170, 0, 170);
            scintillaWrapper.Styles[9].ForeColor = Color.FromArgb(0, 0, 0);

            // Standard library keywords
            scintillaWrapper.Styles[12].ForeColor = Color.FromArgb(0, 0, 0);
            scintillaWrapper.Styles[12].BackColor = Color.FromArgb(224, 192, 224);
            scintillaWrapper.Styles[12].Bold = true;
            scintillaWrapper.Styles[12].IsSelectionEolFilled = true;

            // Brace match
            scintillaWrapper.Styles[34].ForeColor = Color.FromArgb(47, 47, 255);
            scintillaWrapper.Styles[34].Bold = true;
            // Brace mismatch
            scintillaWrapper.Styles[35].ForeColor = Color.FromArgb(255, 47, 47);
            scintillaWrapper.Styles[35].Bold = true;

            scintillaWrapper.Styles[13].ForeColor = Color.FromArgb(120, 156, 124);
            scintillaWrapper.Styles[13].Bold = true;
            scintillaWrapper.Styles[13].IsSelectionEolFilled = true;

            scintilla.UpdateUI += Scintilla_UpdateUI;

            scintillaWrapper.AutoComplete.CancelAtStart = false;
            scintillaWrapper.AutoComplete.AutoHide = false;
            scintillaWrapper.AutoComplete.MaxHeight = 8;
            scintillaWrapper.AutoComplete.MaxWidth = 100;
            scintillaWrapper.AutoComplete.StopCharacters = ")}; ";

            scintillaWrapper.Indentation.UseTabs = false;
            scintillaWrapper.Indentation.TabWidth = 2;
            scintillaWrapper.Indentation.IndentWidth = 2;
            scintillaWrapper.Caret.HighlightCurrentLine = true;
            scintillaWrapper.Caret.CurrentLineBackgroundColor = Color.FromArgb(232, 232, 255);
            scintillaWrapper.Lexing.SetKeywords(0, @"
                and break do else elseif end false for function if in local
		        nil not or repeat return then true until while");
            scintillaWrapper.Lexing.SetKeywords(1, @"
                _G _VERSION assert collectgarbage dofile error getfenv getmetatable
                ipairs load loadfile loadstring module next pairs pcall print rawequal
                rawget rawset require select setfenv setmetatable tonumber tostring type
                unpack xpcall
                coroutine.create coroutine.resume coroutine.running coroutine.status coroutine.wrap
                coroutine.yield

                debug.debug debug.getfenv debug.gethook debug.getinfo debug.getlocal debug.getmetatable
                debug.getregistry debug.getupvalue debug.setfenv debug.sethook debug.setlocal
                debug.setmetatable debug.setupvalue debug.traceback

                io.close io.flush io.input io.lines io.open io.output io.popen io.read io.stderr io.stdin
                io.stdout io.tmpfile io.type io.write

                math.abs math.acos math.asin math.atan math.atan2 math.ceil math.cos math.cosh math.deg
                math.exp math.floor math.fmod math.frexp math.huge math.ldexp math.log math.log10 math.max
                math.min math.modf math.pi math.pow math.rad math.random math.randomseed math.sin
                math.sinh math.sqrt math.tan math.tanh

                os.clock os.date os.difftime os.execute os.exit os.getenv os.remove os.rename os.setlocale
                os.time os.tmpname

                package.cpath package.loaded package.loaders package.loadlib package.path package.preload
                package.seeall

                string.byte string.char string.dump string.find string.format string.gmatch string.gsub
                string.len string.lower string.match string.rep string.reverse string.sub string.upper

                table.concat table.insert table.maxn table.remove table.sort");
            scintillaWrapper.CharAdded += Scintilla_CharAdded;
            scintillaWrapper.Scrolling.HorizontalWidth = 80;

            SetText(File.ReadAllText(path));
            scintilla.SetSavePoint();
            scintillaWrapper.UndoRedo.EmptyUndoBuffer();
        }

        SystemFont autoCompleteFont = new SystemFont("Tahoma", 8);

        private void ShowAutoComplete(int charsTyped, string autoCompleteList)
        {
            if (autoCompleteList.Length > 0)
            {
                scintillaWrapper.Styles[0x20].Font = autoCompleteFont;
                scintillaWrapper.AutoComplete.Show(charsTyped, autoCompleteList);
                scintillaWrapper.Styles[0x20].Font = codeFont;
            }
        }

        bool doShowAutocomplete;

        const string LuaFuncs = @"

                    _G
                    _VERSION
                    assert
                    collectgarbage

                    coroutine

                    debug

                    dofile
                    error
                    getfenv
                    getmetatable

                    io

                    ipairs
                    load
                    loadfile
                    loadstring

                    math

                    module
                    next

                    os

                    package

                    pairs
                    pcall
                    print
                    rawequal
                    rawget
                    rawset
                    require
                    select
                    setfenv
                    setmetatable

                    string

                    table

                    tonumber
                    tostring
                    type
                    unpack xpcall
                    ";

        void Scintilla_UpdateUI(object sender, NativeScintillaEventArgs e)
        {
            DoBraceMatching();
            if (doShowAutocomplete)
            {
                string words = Regex.Replace(LuaFuncs, @"\s+", " ");
                words = Regex.Replace(words, @"^\s+", "");
                words = Regex.Replace(words, @"\s+$", "");
                words = Regex.Replace(words, @"\S+", @"${0}?1");
                ShowAutoComplete(0, words);
                doShowAutocomplete = false;
            }
        }

        void Scintilla_CharAdded(object sender, CharAddedEventArgs e)
        {
            if (e.Ch == '\n')
            {
                int pos = scintillaWrapper.CurrentPos;
                Line line = scintillaWrapper.Lines.FromPosition(pos);
                int indent = line.Previous.Indentation;
                if (indent > 0)
                {
                    line.Indentation = indent;
                    scintillaWrapper.GoTo.Position(pos + indent);
                }
            }
            else
            {
                if (!scintillaWrapper.AutoComplete.IsActive)
                {
                    //doShowAutocomplete = true;
                }
            }
        }

        void SetText(string txt)
        {
            scintillaWrapper.Text = txt;
        }

        public string GetText()
        {
            return scintillaWrapper.Text;
        }

        public void Save()
        {
            ScriptInfo.Save(scintillaWrapper.Text);
            scintilla.SetSavePoint();
        }

        private void LuaPane_Enter(object sender, EventArgs e)
        {
            textBox1.Focus();
        }

        bool NonCommentBraceCheck(int pos)
        {
            char ch = scintilla.GetCharAt(pos);
            int sty = scintilla.GetStyleAt(pos);
            if (sty == 10 && "[](){}".IndexOf(ch) != -1)
            {
                int other = scintilla.BraceMatch(pos, 10);
                if (other == -1)
                {
                    scintilla.BraceBadLight(pos);
                }
                else
                {
                    scintilla.BraceHighlight(pos, other);
                }
                return true;
            }
            return false;
        }

        bool CommentBraceCheck(int pos)
        {
            if (scintilla.GetStyleAt(pos) != 1)
            {
                return false;
            }

            int startPos, endPos;

            for (startPos = scintilla.PositionBefore(pos); ;
                startPos = scintilla.PositionBefore(startPos))
            {
                if (scintilla.GetStyleAt(startPos) != 1)
                {
                    startPos = scintilla.PositionAfter(startPos);
                    break;
                }
                if (startPos == 0)
                {
                    break;
                }
            }
            startPos = scintilla.PositionAfter(startPos);
            startPos = scintilla.PositionAfter(startPos);
            for (endPos = pos; ; )
            {
                int oldEndPos = endPos;
                endPos = scintilla.PositionAfter(endPos);
                if (scintilla.GetStyleAt(endPos) != 1)
                {
                    endPos = scintilla.PositionBefore(endPos);
                    break;
                }
            }

            int eqs = 0;
            int checkEqPos;
            for (checkEqPos = scintilla.PositionAfter(startPos);
                scintilla.GetCharAt(checkEqPos) == '=';
                checkEqPos = scintilla.PositionAfter(checkEqPos))
            {
                eqs++;
            }
            int matchEqs = 0;
            for (checkEqPos = scintilla.PositionBefore(endPos);
                scintilla.GetCharAt(checkEqPos) == '=';
                checkEqPos = scintilla.PositionBefore(checkEqPos))
            {
                matchEqs++;
            }
            if (scintilla.GetCharAt(endPos) != ']' || eqs != matchEqs || scintilla.GetCharAt(checkEqPos) != ']')
            {
                if (pos < startPos || pos > (startPos + eqs + 1))
                {
                    return false;
                }
                scintilla.BraceBadLight(startPos);
                return true;
            }
            if (pos >= startPos && pos <= (startPos + eqs + 1)
                || pos <= endPos && pos >= (endPos - eqs - 1))
            {
                scintilla.BraceHighlight(startPos, endPos);
                return true;
            }
            return false;
        }

        void DoBraceMatching()
        {
            int length = scintilla.GetLength();
            if (length == 0)
            {
                return;
            }

            int pos = scintillaWrapper.CurrentPos;

            if (pos == 0 || scintilla.PositionBefore(pos) == (pos-1))
            {
                if (NonCommentBraceCheck(pos - 1) || CommentBraceCheck(pos - 1))
                {
                    return;
                }
            }

            if (pos < length && scintilla.PositionAfter(pos) == (pos+1))
            {
                if (NonCommentBraceCheck(pos) || CommentBraceCheck(pos))
                {
                    return;
                }
            }

            scintilla.BraceHighlight(-1, -1);
            return;
        }

        void VerifySyntax()
        {
            scintillaWrapper.Enabled = false;
            try
            {
                lua_State L = parentComponent.main_L;
                int lineIndex = 0;
                int lineCount = scintillaWrapper.Lines.Count;
                InvokeLua.lua_Reader_RetString ScintillaReader =
                    delegate(lua_State _L, IntPtr _data, ref size_t sz)
                    {
                        if (lineIndex >= lineCount)
                        {
                            sz = UIntPtr.Zero;
                            return "";
                        }
                        string line = scintillaWrapper.Lines[lineIndex++].Text;
                        sz = (size_t)line.Length;
                        return line;
                    };
                if (InvokeLua.LUA_OK == InvokeLua.lua_load(L, ScintillaReader, IntPtr.Zero, ""))
                {
                    InvokeLua.lua_pop(L, 1);
                    MessageBox.Show("Syntax verified as correct!",
                        "Success",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Information);
                }
                else
                {
                    string error = InvokeLua.lua_tostring(L, -1);
                    InvokeLua.lua_pop(L, 1);
                    Match explodedError = Regex.Match(error, @"^\[[^\]]*\]\:(\d+)\:(.*)$");
                    int lineNum = int.Parse(explodedError.Groups[1].Value);
                    string message = explodedError.Groups[2].Value;
                    scintilla.GotoLine(lineNum-1);
                    SystemSounds.Exclamation.Play();
                    editor.GUIController.SetStatusBarText("[Line " + lineNum + "]: " + message);
                    /*
                    MessageBox.Show("Line " + lineNum + ":\n" + message,
                        "Syntax Error",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                     */
                }
            }
            finally
            {
                scintillaWrapper.Enabled = true;
                scintillaWrapper.Focus();
            }
        }

        protected override void OnCommandClick(string command)
        {
            switch (command)
            {
                case "VERIFY":
                    VerifySyntax();
                    break;
            }
        }
	}
}
