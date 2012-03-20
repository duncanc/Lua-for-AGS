using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using SystemFont = System.Drawing.Font;
using System.Data;
using System.Text;
using System.Windows.Forms;
using ScintillaNet;

namespace AGS.Plugin.Lua
{
    public partial class CodeConvertPane : AGS.Types.EditorContentPanel
    {
        AGS.Types.IAGSEditor editor;
        public CodeConvertPane(AGS.Types.IAGSEditor editor)
        {
            this.editor = editor;
            InitializeComponent();
        }

        Scintilla agsEditWrapper;
        INativeScintilla agsEdit;

        Scintilla luaOutputWrapper;
        INativeScintilla luaOutput;

        private static SystemFont codeFont = new SystemFont("Courier New", 10);

        private void CodeConvertPane_Load(object sender, EventArgs e)
        {
            agsEditWrapper = new Scintilla();
            agsEdit = agsEditWrapper.NativeInterface;
            luaOutputWrapper = new Scintilla();
            luaOutput = luaOutputWrapper.NativeInterface;

            agsCodeEntry.Hide();
            agsEditWrapper.Parent = agsCodeEntry.Parent;
            agsEditWrapper.Location = agsCodeEntry.Location;
            agsEditWrapper.Size = agsCodeEntry.Size;
            agsEditWrapper.Anchor = agsCodeEntry.Anchor;
            agsEditWrapper.Font = codeFont;
            agsEditWrapper.Lexing.Lexer = Lexer.Cpp;
            agsEditWrapper.Text = "// AGS Code Entry";
            agsEditWrapper.UndoRedo.EmptyUndoBuffer();

            luaCodeOutput.Hide();
            luaOutputWrapper.Parent = luaCodeOutput.Parent;
            luaOutputWrapper.Location = luaCodeOutput.Location;
            luaOutputWrapper.Size = luaCodeOutput.Size;
            luaOutputWrapper.Anchor = luaCodeOutput.Anchor;
            luaOutputWrapper.Font = codeFont;
            luaOutputWrapper.Lexing.Lexer = Lexer.Lua;
            luaOutputWrapper.Text = "-- Converted Lua Code Output";
            luaOutputWrapper.IsReadOnly = true;

            agsEditWrapper.Styles[0].ForeColor = Color.FromArgb(0, 0, 0);
            agsEditWrapper.Styles[1].ForeColor = Color.FromArgb(0, 127, 0);
            agsEditWrapper.Styles[2].ForeColor = Color.FromArgb(0, 127, 0);
            agsEditWrapper.Styles[3].ForeColor = Color.FromArgb(127, 127, 127);
            agsEditWrapper.Styles[4].ForeColor = Color.FromArgb(0, 150, 175);
            agsEditWrapper.Styles[5].ForeColor = Color.FromArgb(0, 0, 127);
            agsEditWrapper.Styles[5].Bold = true;
            agsEditWrapper.Styles[6].ForeColor = Color.FromArgb(170, 0, 170);
            agsEditWrapper.Styles[7].ForeColor = Color.FromArgb(170, 0, 170);
            agsEditWrapper.Styles[8].ForeColor = Color.FromArgb(170, 0, 170);
            agsEditWrapper.Styles[9].ForeColor = Color.FromArgb(0, 0, 0);
            agsEditWrapper.Styles[13].ForeColor = Color.FromArgb(120, 156, 124);
            agsEditWrapper.Styles[13].Bold = true;
            agsEditWrapper.Styles[13].IsSelectionEolFilled = true;
            agsEditWrapper.Lexing.SetKeywords(0, @"
                if while int float bool char true false short else return this noloopcheck new null");

            // Standard library keywords
            agsEditWrapper.Styles[12].ForeColor = Color.FromArgb(0, 0, 0);
            agsEditWrapper.Styles[12].BackColor = Color.FromArgb(224, 192, 224);
            agsEditWrapper.Styles[12].Bold = true;
            agsEditWrapper.Styles[12].IsSelectionEolFilled = true;

            luaOutputWrapper.Styles[0].ForeColor = Color.FromArgb(0, 0, 0);
            luaOutputWrapper.Styles[1].ForeColor = Color.FromArgb(0, 127, 0);
            luaOutputWrapper.Styles[2].ForeColor = Color.FromArgb(0, 127, 0);
            luaOutputWrapper.Styles[3].ForeColor = Color.FromArgb(127, 127, 127);
            luaOutputWrapper.Styles[4].ForeColor = Color.FromArgb(0, 150, 175);
            luaOutputWrapper.Styles[5].ForeColor = Color.FromArgb(0, 0, 127);
            luaOutputWrapper.Styles[5].Bold = true;
            luaOutputWrapper.Styles[6].ForeColor = Color.FromArgb(170, 0, 170);
            luaOutputWrapper.Styles[7].ForeColor = Color.FromArgb(170, 0, 170);
            luaOutputWrapper.Styles[8].ForeColor = Color.FromArgb(170, 0, 170);
            luaOutputWrapper.Styles[9].ForeColor = Color.FromArgb(0, 0, 0);
            luaOutputWrapper.Styles[13].ForeColor = Color.FromArgb(120, 156, 124);
            luaOutputWrapper.Styles[13].Bold = true;
            luaOutputWrapper.Styles[13].IsSelectionEolFilled = true;

            // Standard library keywords
            luaOutputWrapper.Styles[12].ForeColor = Color.FromArgb(0, 0, 0);
            luaOutputWrapper.Styles[12].BackColor = Color.FromArgb(224, 192, 224);
            luaOutputWrapper.Styles[12].Bold = true;
            luaOutputWrapper.Styles[12].IsSelectionEolFilled = true;

            for (int i = 0; i < luaOutputWrapper.Margins.Count; i++)
            {
                luaOutputWrapper.Margins[i].Width = 0;
            }

            for (int i = 0; i < agsEditWrapper.Margins.Count; i++)
            {
                agsEditWrapper.Margins[i].Width = 0;
            }

            luaOutputWrapper.Indentation.UseTabs = false;
            luaOutputWrapper.Indentation.TabWidth = 2;
            luaOutputWrapper.Indentation.IndentWidth = 2;
            luaOutputWrapper.Lexing.SetKeywords(0, @"
                and break do else elseif end false for function if in local
		        nil not or repeat return then true until while");

            for (int i = 0; i <= 32; i++)
            {
                agsEditWrapper.Styles[i].Font = codeFont;
                luaOutputWrapper.Styles[i].Font = codeFont;
            }
        }

        private void luaCodeOutput_TextChanged(object sender, EventArgs e)
        {

        }

        private SPAGS.Util.NameDictionary agsTable;

        private void convertButton_Click(object sender, EventArgs e)
        {
            string agsScript = agsEditWrapper.Text;

            SPAGS.ScriptCollection scripts = new SPAGS.ScriptCollection(editor.Version);

            scripts.SetStandardConstants(editor.CurrentGame.Settings);
            IList<AGS.Types.Script> allHeaders = editor.GetAllScriptHeaders();
            scripts.AddHeader(allHeaders[0].FileName, allHeaders[0].Text);
            agsTable = new SPAGS.Util.NameDictionary(scripts.GlobalNamespace);
            for (int i = 1; i < allHeaders.Count; i++)
            {
                scripts.AddHeader(allHeaders[i].FileName, allHeaders[i].Text);
            }
            
            SPAGS.Script deconstructed;
            bool anonFunction = false;
            try
            {
                deconstructed = scripts.CompileScript("ConvertingScript.asc", agsScript);
            }
            catch
            {
                try
                {
                    deconstructed = scripts.CompileScript("ConvertingScript.asc", "int __AnonymousFunction__(){" + agsScript + "}");
                    anonFunction = true;
                }
                catch
                {
                    deconstructed = null;
                    anonFunction = false;
                }
                if (deconstructed == null) throw;
            }

            StringBuilder luaSB = new StringBuilder();

            if (anonFunction)
            {
                SPAGS.Function func = deconstructed.DefinedFunctions[0];
                AddBlockContent(luaSB, 0, func.Body);
            }
            else
            {
                foreach (SPAGS.Constant constant in deconstructed.DefinedConstants)
                {
                    luaSB.AppendLine();
                    SPAGS.Constant.Expression constantExpr = constant as SPAGS.Constant.Expression;
                    if (constantExpr != null)
                    {
                        luaSB.Append(constant.Name + " = ");
                        AddExpression(luaSB, 0, constantExpr.TheExpression);
                        luaSB.AppendLine();
                    }
                    else if (((SPAGS.Constant.TokenSequence)constant).Tokens.Count == 0)
                    {
                        luaSB.AppendLine(constant.Name + " = true");
                    }
                }

                foreach (SPAGS.ValueType.Enum enumType in deconstructed.DefinedEnums)
                {
                    luaSB.AppendLine();
                    luaSB.AppendLine("-- " + enumType.Name);
                    foreach (SPAGS.EnumValue enumValue in enumType.Entries)
                    {
                        luaSB.AppendLine(enumValue.Name + " = " + enumValue.Value);
                    }
                }

                foreach (SPAGS.ValueType.Struct structType in deconstructed.DefinedStructs)
                {
                    if (structType.IsManaged) continue;
                    luaSB.AppendLine();
                    luaSB.AppendLine(structType.Name + " = ags.struct{");
                    foreach (SPAGS.StructMember member in structType.Members.EachOf<SPAGS.StructMember>())
                    {
                        switch (member.MemberType)
                        {
                            case SPAGS.StructMemberType.Attribute:
                                SPAGS.StructMember.Attribute attr = (SPAGS.StructMember.Attribute)member;
                                luaSB.Append("  -- ");
                                if (attr.IsReadOnly) luaSB.Append("readonly ");
                                if (attr.IsStatic) luaSB.Append("static ");
                                luaSB.Append("attribute " + attr.Name);
                                if (attr.IsArray) luaSB.Append("[]");
                                luaSB.AppendLine();
                                break;
                            case SPAGS.StructMemberType.Field:
                                SPAGS.StructMember.Field field = (SPAGS.StructMember.Field)member;
                                luaSB.Append("  " + field.Name + " = ");
                                AddExpression(luaSB, 0, field.Type.CreateDefaultValueExpression());
                                luaSB.AppendLine(";");
                                break;
                            case SPAGS.StructMemberType.Method:
                                SPAGS.StructMember.Method method = (SPAGS.StructMember.Method)member;
                                if (!method.IsExtender)
                                {
                                    luaSB.Append("  -- ");
                                    if (method.IsStatic) luaSB.Append("static ");
                                    luaSB.AppendLine(method.Name + "()");
                                }
                                break;
                        }
                    }
                    luaSB.AppendLine("}");
                }

                foreach (SPAGS.ScriptVariable variable in deconstructed.DefinedVariables)
                {
                    luaSB.AppendLine();
                    if (!variable.Exported)
                    {
                        luaSB.Append("local ");
                    }
                    luaSB.Append(variable.Name + " = ");
                    if (variable.InitialValue != null)
                    {
                        AddExpression(luaSB, 0, variable.InitialValue);
                    }
                    else
                    {
                        AddExpression(luaSB, 0, variable.Type.CreateDefaultValueExpression());
                    }
                    luaSB.AppendLine();
                }

                foreach (SPAGS.Function function in deconstructed.DefinedFunctions)
                {
                    luaSB.AppendLine();
                    luaSB.Append("function ");
                    luaSB.Append(function.Name.Replace("::",":"));
                    luaSB.Append("(");
                    for (int i = 0; i < function.ParameterVariables.Count; i++)
                    {
                        if (i > 0) luaSB.Append(", ");
                        luaSB.Append(function.ParameterVariables[i].Name);
                    }
                    luaSB.AppendLine(")");
                    AddBlockContent(luaSB, 1, function.Body);
                    luaSB.AppendLine("end");
                }
            }
            luaOutputWrapper.IsReadOnly = false;
            luaOutputWrapper.Text = luaSB.ToString();
            luaOutputWrapper.IsReadOnly = true;
            agsEditWrapper.Selection.End = agsEditWrapper.Selection.Start = 0;
            agsEditWrapper.Scrolling.ScrollToCaret();
        }

        string GetName(string name)
        {
            switch (name)
            {
                case "this": return "self";

                case "self":
                case "in":
                case "function":
                case "then":
                case "elseif":
                case "do":
                case "end":
                case "for":
                case "local":
                case "nil":
                case "repeat":
                case "until":
                case "and":
                case "or":
                case "not":
                    return "__" + name + "__";
                case "true":
                case "false":
                    return name;
            }
            if (agsTable.ContainsKey(name))
            {
                return "ags." + name;
            }
            return name;
        }

        string GetName(SPAGS.Util.INameHolder named)
        {
            return GetName(named.Name);
        }

        void AddExpression(StringBuilder luaSB, int indent, SPAGS.Expression expression)
        {
            switch (expression.Type)
            {
                case SPAGS.ExpressionType.AllocateArray:
                    SPAGS.Expression.AllocateArray allocArray = (SPAGS.Expression.AllocateArray)expression;
                    switch (allocArray.ElementType.Category)
                    {
                        case SPAGS.ValueTypeCategory.StringValue:
                            luaSB.Append("{}");
                            break;
                        case SPAGS.ValueTypeCategory.Struct:
                            SPAGS.ValueType.Struct structType = (SPAGS.ValueType.Struct)allocArray.ElementType;
                            if (structType.IsManaged)
                            {
                                luaSB.Append("{}");
                                break;
                            }
                            else
                            {
                                goto default;
                            }
                        default:
                            luaSB.Append("ags.array(--[[ TODO ]])");
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.AllocStringBuffer:
                    luaSB.Append("ags.string()");
                    break;
                case SPAGS.ExpressionType.AllocStruct:
                    SPAGS.Expression.AllocateStruct allocStruct = (SPAGS.Expression.AllocateStruct)expression;
                    luaSB.Append(GetName(allocStruct.TheStructType) + "()");
                    break;
                case SPAGS.ExpressionType.ArrayIndex:
                    SPAGS.Expression.ArrayIndex arrayIndex = (SPAGS.Expression.ArrayIndex)expression;
                    AddExpression(luaSB, 0, arrayIndex.Target);
                    luaSB.Append("[");
                    AddExpression(luaSB, 0, arrayIndex.Index);
                    luaSB.Append("]");
                    break;
                case SPAGS.ExpressionType.Attribute:
                    SPAGS.Expression.Attribute attr = (SPAGS.Expression.Attribute)expression;
                    switch (attr.TheAttribute.Getter.Name)
                    {
                        case "Maths::get_Pi":
                            luaSB.Append("math.pi");
                            break;
                        default:
                            if (attr.Target != null)
                            {
                                AddExpression(luaSB, indent, attr.Target);
                            }
                            else
                            {
                                luaSB.Append(GetName(attr.TheStructType));
                            }
                            luaSB.Append("." + attr.TheAttribute.Name);
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.BinaryOperator:
                    SPAGS.Expression.BinaryOperator binop = (SPAGS.Expression.BinaryOperator)expression;
                    switch (binop.Token.Type)
                    {
                        case SPAGS.TokenType.Add:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" + ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.BitwiseAnd:
                            luaSB.Append("bit.band(");
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(", ");
                            AddExpression(luaSB, indent, binop.Right);
                            luaSB.Append(")");
                            break;
                        case SPAGS.TokenType.BitwiseLeftShift:
                            luaSB.Append("bit.lshift(");
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(", ");
                            AddExpression(luaSB, indent, binop.Right);
                            luaSB.Append(")");
                            break;
                        case SPAGS.TokenType.BitwiseOr:
                            luaSB.Append("bit.bor(");
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(", ");
                            AddExpression(luaSB, indent, binop.Right);
                            luaSB.Append(")");
                            break;
                        case SPAGS.TokenType.BitwiseRightShift:
                            luaSB.Append("bit.rshift(");
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(", ");
                            AddExpression(luaSB, indent, binop.Right);
                            luaSB.Append(")");
                            break;
                        case SPAGS.TokenType.BitwiseXor:
                            luaSB.Append("bit.bxor(");
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(", ");
                            AddExpression(luaSB, indent, binop.Right);
                            luaSB.Append(")");
                            break;
                        case SPAGS.TokenType.Divide:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" / ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsEqualTo:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" == ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsGreaterThan:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" > ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsGreaterThanOrEqualTo:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" >= ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsLessThan:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" < ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsLessThanOrEqualTo:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" <= ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.IsNotEqualTo:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" ~= ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.LogicalAnd:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" and ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.LogicalOr:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" or ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.Modulus:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" % ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.Multiply:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" * ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                        case SPAGS.TokenType.Subtract:
                            AddExpression(luaSB, indent, binop.Left);
                            luaSB.Append(" - ");
                            AddExpression(luaSB, indent, binop.Right);
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.Call:
                    SPAGS.Expression.Call call = (SPAGS.Expression.Call)expression;
                    AddExpression(luaSB, indent, call.CallingOn);
                    luaSB.Append("(");
                    for (int j = 0; j < call.Parameters.Count; j++)
                    {
                        if (j > 0) luaSB.Append(", ");
                        AddExpression(luaSB, indent, call.Parameters[j]);
                    }
                    luaSB.Append(")");
                    break;
                case SPAGS.ExpressionType.Method:
                    SPAGS.Expression.Method methodExpr = (SPAGS.Expression.Method)expression;
                    switch (methodExpr.TheMethod.Function.Name)
                    {
                        case "String::Format": luaSB.Append("string.format"); break;
                        case "Maths::ArcCos": luaSB.Append("math.acos"); break;
                        case "Maths::ArcSin": luaSB.Append("math.asin"); break;
                        case "Maths::ArcTan": luaSB.Append("math.atan"); break;
                        case "Maths::ArcTan2": luaSB.Append("math.atan2"); break;
                        case "Maths::Cos": luaSB.Append("math.cos"); break;
                        case "Maths::Cosh": luaSB.Append("math.cosh"); break;
                        case "Maths::DegreesToRadians": luaSB.Append("math.rad"); break;
                        case "Maths::Exp": luaSB.Append("math.exp"); break;
                        case "Maths::Log": luaSB.Append("math.log"); break;
                        case "Maths::Log10": luaSB.Append("math.log10"); break;
                        case "Maths::RadiansToDegrees": luaSB.Append("math.deg"); break;
                        case "Maths::RaiseToPower": luaSB.Append("math.pow"); break; // todo: binop?
                        case "Maths::Sin": luaSB.Append("math.sin"); break;
                        case "Maths::Sinh": luaSB.Append("math.sinh"); break;
                        case "Maths::Sqrt": luaSB.Append("math.sqrt"); break;
                        case "Maths::Tan": luaSB.Append("math.tan"); break;
                        case "Maths::Tanh": luaSB.Append("maths.tanh"); break;
                        default:
                            if (methodExpr.TheMethod.IsStatic)
                            {
                                luaSB.Append(GetName(methodExpr.TheStructType));
                                luaSB.Append(".");
                            }
                            else
                            {
                                AddExpression(luaSB, indent, methodExpr.Target);
                                luaSB.Append(":");
                            }
                            luaSB.Append(methodExpr.TheMethod.Name);
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.Function:
                    SPAGS.Expression.Function funcExpr = (SPAGS.Expression.Function)expression;
                    switch (funcExpr.TheFunction.Name)
                    {
                        case "IntToFloat": luaSB.Append("tonumber"); break; // todo: completely eliminate
                        default:
                            luaSB.Append(GetName(funcExpr.TheFunction));
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.CharLiteral:
                    SPAGS.Expression.CharLiteral charLiteral = (SPAGS.Expression.CharLiteral)expression;
                    luaSB.Append("string.byte('" + charLiteral.Value + "')");
                    break;
                case SPAGS.ExpressionType.Constant:
                    SPAGS.Expression.Constant constant = (SPAGS.Expression.Constant)expression;
                    luaSB.Append(GetName(constant.TheConstant));
                    break;
                case SPAGS.ExpressionType.EnumValue:
                    SPAGS.Expression.EnumValue enumValue = (SPAGS.Expression.EnumValue)expression;
                    luaSB.Append(GetName(enumValue.TheValue));
                    break;
                case SPAGS.ExpressionType.Field:
                    SPAGS.Expression.Field field = (SPAGS.Expression.Field)expression;
                    AddExpression(luaSB, indent, field.Target);
                    luaSB.Append("." + field.TheField.Name);
                    break;
                case SPAGS.ExpressionType.FloatLiteral:
                    SPAGS.Expression.FloatLiteral floatLiteral = (SPAGS.Expression.FloatLiteral)expression;
                    luaSB.Append(floatLiteral.Value.ToString());
                    break;
                case SPAGS.ExpressionType.IntegerLiteral:
                    luaSB.Append(((SPAGS.Expression.IntegerLiteral)expression).Value.ToString());
                    break;
                case SPAGS.ExpressionType.Null:
                    luaSB.Append("nil");
                    break;
                case SPAGS.ExpressionType.StringLiteral:
                    SPAGS.Expression.StringLiteral stringLiteral = (SPAGS.Expression.StringLiteral)expression;
                    luaSB.Append(InvokeLua.util_quotestring(stringLiteral.Value));
                    break;
                case SPAGS.ExpressionType.UnaryOperator:
                    SPAGS.Expression.UnaryOperator unop = (SPAGS.Expression.UnaryOperator)expression;
                    switch (unop.Token.Type)
                    {
                        case SPAGS.TokenType.LogicalNot:
                            luaSB.Append("not ");
                            AddExpression(luaSB, indent, unop.Operand);
                            break;
                        case SPAGS.TokenType.Subtract:
                            luaSB.Append("-");
                            AddExpression(luaSB, indent, unop.Operand);
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.Variable:
                    SPAGS.Expression.Variable variable = (SPAGS.Expression.Variable)expression;
                    luaSB.Append(GetName(variable.TheVariable));
                    break;
                default:
                    luaSB.Append("--[[" + expression.Type.ToString() + "]] nil");
                    break;
            }
        }

        void AddIndent(StringBuilder luaSB, int indent)
        {
            for (int i = 0; i < indent; i++) luaSB.Append("  ");
        }

        void AddBlockContent(StringBuilder luaSB, int indent, SPAGS.Statement.Block block)
        {
            foreach (SPAGS.Statement stmt in block.ChildStatements)
            {
                AddIndent(luaSB, indent);
                AddStatement(luaSB, indent, stmt);
            }
        }

        SPAGS.Statement.Block Enblock(SPAGS.Statement statement)
        {
            if (statement is SPAGS.Statement.Block) return (SPAGS.Statement.Block)statement;
            SPAGS.Statement.Block newBlock = new SPAGS.Statement.Block(new SPAGS.Util.NameDictionary());
            newBlock.ChildStatements.Add(statement);
            return newBlock;
        }

        void AddStatement(StringBuilder luaSB, int indent, SPAGS.Statement statement)
        {
            switch (statement.Type)
            {
                case SPAGS.StatementType.Assign:
                    SPAGS.Statement.Assign assign = (SPAGS.Statement.Assign)statement;
                    AddExpression(luaSB, 0, assign.Target);
                    luaSB.Append(" = ");
                    AddExpression(luaSB, 0, assign.SimpleAssignValue());
                    luaSB.AppendLine();
                    break;
                case SPAGS.StatementType.Block:
                    luaSB.AppendLine("do");
                    AddBlockContent(luaSB, indent + 1, (SPAGS.Statement.Block)statement);
                    AddIndent(luaSB, indent);
                    luaSB.AppendLine("end");
                    break;
                case SPAGS.StatementType.Call:
                    SPAGS.Statement.Call call = (SPAGS.Statement.Call)statement;
                    if (call.CallExpression.Parameters.Count == 1
                        && call.CallExpression.Parameters[0] is SPAGS.Expression.StringLiteral)
                    {
                        AddExpression(luaSB, indent, call.CallExpression.CallingOn);
                        luaSB.Append(" ");
                        AddExpression(luaSB, indent, call.CallExpression.Parameters[0]);
                    }
                    else
                    {
                        AddExpression(luaSB, indent, call.CallExpression);
                    }
                    luaSB.AppendLine();
                    break;
                case SPAGS.StatementType.If:
                    SPAGS.Statement.If conditional = (SPAGS.Statement.If)statement;
                    luaSB.Append("if ");
                    AddExpression(luaSB, indent, conditional.IfThisIsTrue);
                    luaSB.AppendLine(" then");
                    AddBlockContent(luaSB, indent+1, Enblock(conditional.ThenDoThis));
                    while (conditional.ElseDoThis is SPAGS.Statement.If)
                    {
                        conditional = (SPAGS.Statement.If)conditional.ElseDoThis;
                        AddIndent(luaSB, indent);
                        luaSB.Append("elseif ");
                        AddExpression(luaSB, indent, conditional.IfThisIsTrue);
                        luaSB.AppendLine(" then");
                        AddBlockContent(luaSB, indent+1, Enblock(conditional.ThenDoThis));
                    }
                    if (conditional.ElseDoThis != null)
                    {
                        AddIndent(luaSB, indent);
                        luaSB.AppendLine("else");
                        AddBlockContent(luaSB, indent+1, Enblock(conditional.ElseDoThis));
                    }
                    AddIndent(luaSB, indent);
                    luaSB.AppendLine("end");
                    break;
                case SPAGS.StatementType.Return:
                    SPAGS.Statement.Return ret = (SPAGS.Statement.Return)statement;
                    if (ret.Value == null)
                    {
                        luaSB.AppendLine("return");
                    }
                    else
                    {
                        luaSB.Append("return ");
                        AddExpression(luaSB, indent, ret.Value);
                        luaSB.AppendLine();
                    }
                    break;
                case SPAGS.StatementType.VariableDeclaration:
                    SPAGS.Statement.VariableDeclaration vardef = (SPAGS.Statement.VariableDeclaration)statement;
                    luaSB.Append("local ");
                    for (int i = 0; i < vardef.Variables.Count; i++)
                    {
                        if (i > 0) luaSB.Append(", ");
                        luaSB.Append(vardef.Variables[i].Name);
                    }
                    luaSB.Append(" = ");
                    for (int i = 0; i < vardef.Variables.Count; i++)
                    {
                        if (i > 0) luaSB.Append(", ");
                        if (vardef.Variables[i].InitialValue != null)
                        {
                            AddExpression(luaSB, indent, vardef.Variables[i].InitialValue);
                        }
                        else
                        {
                            AddExpression(luaSB, indent, vardef.Variables[i].Type.CreateDefaultValueExpression());
                        }
                    }
                    luaSB.AppendLine();
                    break;
                case SPAGS.StatementType.While:
                    SPAGS.Statement.While loop = (SPAGS.Statement.While)statement;
                    luaSB.Append("while ");
                    AddExpression(luaSB, indent, loop.WhileThisIsTrue);
                    luaSB.AppendLine(" do");
                    AddBlockContent(luaSB, indent+1, Enblock(loop.KeepDoingThis));
                    AddIndent(luaSB, indent);
                    luaSB.AppendLine("end");
                    break;
                default:
                    luaSB.AppendLine("-- " + statement.Type.ToString());
                    break;
            }
        }
    }
}
