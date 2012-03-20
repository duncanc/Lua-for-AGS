using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace AGS.Plugin.Lua.LuaCodeDom
{
    public class LuaChunk
    {
        public static LuaChunk Create(SPAGS.Script script)
        {
            LuaChunk chunk = new LuaChunk();

            foreach (SPAGS.Constant constant in script.DefinedConstants)
            {
                if (constant is SPAGS.Constant.Expression)
                {
                    SPAGS.Expression expr = ((SPAGS.Constant.Expression)constant).TheExpression;
                    chunk.Statements.Add(
                        new LuaStatement.Assignment(
                            new LuaExpression.GlobalAccess(constant.Name),
                            LuaExpression.Create(expr)));
                }
            }

            return chunk;
        }
        public List<LuaStatement> Statements = new List<LuaStatement>();
        public void WriteTo(TextWriter output, int indent)
        {
            foreach (LuaStatement statement in Statements)
            {
                statement.WriteTo(output, indent);
            }
        }
    }

    public enum LuaStatementType
    {
        Call,
        Assignment,
        LocalDeclaration,
        If,
        While
    }

    public class LuaIfClause : LuaChunk
    {
        public LuaIfClause(LuaExpression condition)
        {
            Condition = condition;
        }
        public LuaExpression Condition;
    }

    public abstract class LuaStatement
    {
        private LuaStatement(LuaStatementType type)
        {
            Type = type;
        }
        public readonly LuaStatementType Type;
        public abstract void WriteTo(TextWriter output, int indent);
        public class Assignment : LuaStatement
        {
            public Assignment()
                : base(LuaStatementType.Assignment)
            {
            }
            public Assignment(LuaExpression left, LuaExpression right)
                : this()
            {
                LeftHandSide.Add(left);
                LeftHandSide.Add(right);
            }
            public List<LuaExpression> LeftHandSide = new List<LuaExpression>();
            public List<LuaExpression> RightHandSide = new List<LuaExpression>();
            public override void WriteTo(TextWriter output, int indent)
            {
                for (int i = 0; i < LeftHandSide.Count; i++)
                {
                    if (i > 0) output.Write(", ");
                    LeftHandSide[i].WriteTo(output, indent, false);
                }
                output.Write(" = ");
                for (int i = 0; i < RightHandSide.Count; i++)
                {
                    if (i > 0) output.Write(", ");
                    RightHandSide[i].WriteTo(output, indent, false);
                }
            }
        }
        public class If : LuaStatement
        {
            public If()
                : base(LuaStatementType.If)
            {
            }
            public List<LuaIfClause> Clauses = new List<LuaIfClause>();
            public LuaChunk ElseClause;
            public override void WriteTo(TextWriter output, int indent)
            {
                for (int i = 0; i < Clauses.Count; i++)
                {
                    output.Write((i == 0) ? "if " : "elseif ");
                    if (Clauses[i].Condition is LuaExpression.BinOp)
                    {
                        output.Write("(");
                        Clauses[i].Condition.WriteTo(output, indent, false);
                        output.Write(")");
                    }
                    else
                    {
                        Clauses[i].Condition.WriteTo(output, indent, false);
                    }
                    output.WriteLine(" then");
                    Clauses[i].WriteTo(output, indent + 1);
                    if (ElseClause != null)
                    {
                        output.WriteLine("elseif");
                        ElseClause.WriteTo(output, indent + 1);
                    }
                    output.WriteLine("end");
                }
            }
        }
    }

    public enum LuaOperatorPrecedence
    {
        Or = 100,
        And = 90,
        Compare = 80,
        Concatenate = 70,
        AddSubtract = 60,
        MultiplyDivideModulus = 50,
        Unary = 40,
        RaiseToPower = 30
    }

    public enum LuaBinaryOperatorType
    {
        LogicalOr,
        LogicalAnd,
        IsLessThan,
        IsGreaterThan,
        IsLessThanOrEqualTo,
        IsGreaterThanOrEqualTo,
        IsNotEqualTo,
        IsEqualTo,
        Concatenate,
        Add,
        Subtract,
        Multiply,
        Divide,
        Modulus,
        RaiseToPower
    }

    public enum LuaUnaryOperatorType
    {
        LogicalNot,
        Minus,
        Length
    }

    [Flags]
    public enum LuaValueType
    {

        String,

        Number,
        Integer,
        Nil,
        Boolean,

        LuaThread,

        Any
    }

    public static class LuaStandardLibrary
    {
        public static LuaExpression _G;
        public static LuaExpression _VERSION;
        public static LuaExpression Assert;
        public static LuaExpression CollectGarbage;
        public static LuaExpression DoFile;
        public static LuaExpression Error;
        public static LuaExpression GetFEnv;
        public static LuaExpression GetMetatable;
        public static LuaExpression IPairs;
        public static LuaExpression Load;
        public static LuaExpression LoadFile;
        public static LuaExpression LoadString;
        public static LuaExpression Module;
        public static LuaExpression Next;
        public static LuaExpression Pairs;
        public static LuaExpression PCall;
        public static LuaExpression Print;
        public static LuaExpression RawEqual;
        public static LuaExpression RawGet;
        public static LuaExpression RawSet;
        public static LuaExpression Require;
        public static LuaExpression Select;
        public static LuaExpression SetFEnv;
        public static LuaExpression SetMetatable;
        public static LuaExpression ToNumber;
        public new static LuaExpression ToString;
        public static LuaExpression Type;
        public static LuaExpression Unpack;
        public static LuaExpression XPCall;
        public static LuaExpression Coroutine_Create;
        public static LuaExpression Coroutine_Resume;
        public static LuaExpression Coroutine_Running;
        public static LuaExpression Coroutine_Status;
        public static LuaExpression Coroutine_Wrap;
        public static LuaExpression Coroutine_Yield;
        public static LuaExpression Debug_Debug;
        public static LuaExpression Debug_GetFEnv;
        public static LuaExpression Debug_GetHook;
        public static LuaExpression Debug_GetInfo;
        public static LuaExpression Debug_GetLocal;
        public static LuaExpression Debug_GetMetatable;
        public static LuaExpression Debug_GetRegistry;
        public static LuaExpression Debug_GetUpvalue;
        public static LuaExpression Debug_SetFEnv;
        public static LuaExpression Debug_SetHook;
        public static LuaExpression Debug_SetLocal;
        public static LuaExpression Debug_SetMetatable;
        public static LuaExpression Debug_SetUpvalue;
        public static LuaExpression Debug_Traceback;
        public static LuaExpression Math;
        public static LuaExpression Math_Pi;

        static LuaStandardLibrary()
        {
            _G = new LuaExpression.GlobalAccess("_G");

            Math = new LuaExpression.GlobalAccess("math");
            Math_Pi = Math.MakeIndex("pi");

        }
    }

    public static class LuaBitLibrary
    {
        public static LuaExpression Bit;
        public static LuaExpression Bit_LShift;
        public static LuaExpression Bit_RShift;
        public static LuaExpression Bit_BXor;
        public static LuaExpression Bit_BAnd;
        public static LuaExpression Bit_BOr;

        static LuaBitLibrary()
        {
            Bit = new LuaExpression.GlobalAccess("bit");
            Bit_LShift = Bit.MakeIndex("lshift");
            Bit_RShift = Bit.MakeIndex("rshift");
            Bit_BXor = Bit.MakeIndex("bxor");
            Bit_BAnd = Bit.MakeIndex("band");
            Bit_BOr = Bit.MakeIndex("bor");

            Bit_LShift.ReturnType = LuaValueType.Integer;
        }
    }

    public class LuaExpression
    {
        public static LuaExpression Create(SPAGS.Expression agsExpr)
        {
            switch (agsExpr.Type)
            {
                case SPAGS.ExpressionType.AllocateArray:
                    break;
                case SPAGS.ExpressionType.AllocStringBuffer:
                    break;
                case SPAGS.ExpressionType.AllocStruct:
                    break;
                case SPAGS.ExpressionType.ArrayIndex:
                    break;
                case SPAGS.ExpressionType.Attribute:
                    break;
                case SPAGS.ExpressionType.BinaryOperator:
                    SPAGS.Expression.BinaryOperator binop = (SPAGS.Expression.BinaryOperator)agsExpr;
                    LuaExpression left = LuaExpression.Create(binop.Left);
                    LuaExpression right = LuaExpression.Create(binop.Right);
                    LuaBinaryOperatorType binopType;
                    switch (binop.Token.Type)
                    {
                        case SPAGS.TokenType.Add:
                            binopType = LuaBinaryOperatorType.Add;
                            break;
                        case SPAGS.TokenType.BitwiseAnd:
                            return LuaBitLibrary.Bit_BAnd.MakeCall(left, right);
                        case SPAGS.TokenType.BitwiseLeftShift:
                            return LuaBitLibrary.Bit_LShift.MakeCall(left, right);
                        case SPAGS.TokenType.BitwiseOr:
                            return LuaBitLibrary.Bit_BOr.MakeCall(left, right);
                        case SPAGS.TokenType.BitwiseRightShift:
                            return LuaBitLibrary.Bit_RShift.MakeCall(left, right);
                        case SPAGS.TokenType.BitwiseXor:
                            return LuaBitLibrary.Bit_BXor.MakeCall(left, right);
                        case SPAGS.TokenType.Divide:
                            binopType = LuaBinaryOperatorType.Divide;
                            break;
                        case SPAGS.TokenType.IsEqualTo:
                            binopType = LuaBinaryOperatorType.IsEqualTo;
                            break;
                        case SPAGS.TokenType.IsGreaterThan:
                            binopType = LuaBinaryOperatorType.IsGreaterThan;
                            break;
                        case SPAGS.TokenType.IsGreaterThanOrEqualTo:
                            binopType = LuaBinaryOperatorType.IsGreaterThanOrEqualTo;
                            break;
                        case SPAGS.TokenType.IsLessThan:
                            binopType = LuaBinaryOperatorType.IsLessThan;
                            break;
                        case SPAGS.TokenType.IsLessThanOrEqualTo:
                            binopType = LuaBinaryOperatorType.IsLessThanOrEqualTo;
                            break;
                        case SPAGS.TokenType.IsNotEqualTo:
                            binopType = LuaBinaryOperatorType.IsNotEqualTo;
                            break;
                        case SPAGS.TokenType.LogicalAnd:
                            binopType = LuaBinaryOperatorType.LogicalAnd;
                            break;
                        case SPAGS.TokenType.LogicalOr:
                            binopType = LuaBinaryOperatorType.LogicalOr;
                            break;
                        case SPAGS.TokenType.Modulus:
                            binopType = LuaBinaryOperatorType.Modulus;
                            break;
                        case SPAGS.TokenType.Multiply:
                            binopType = LuaBinaryOperatorType.Multiply;
                            break;
                        case SPAGS.TokenType.Subtract:
                            binopType = LuaBinaryOperatorType.Subtract;
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.Call:
                    break;
                case SPAGS.ExpressionType.CharLiteral:
                    break;
                case SPAGS.ExpressionType.Constant:
                    break;
                case SPAGS.ExpressionType.Custom:
                    break;
                case SPAGS.ExpressionType.EnumValue:
                    SPAGS.Expression.EnumValue enumValue = (SPAGS.Expression.EnumValue)agsExpr;
                    if (enumValue.TheValue.OwnerType.Name == "bool")
                    {
                        return (enumValue.TheValue.Value == 0) ? False : True;
                    }
                    return new GlobalAccess(enumValue.TheValue.Name);
                case SPAGS.ExpressionType.Field:
                    break;
                case SPAGS.ExpressionType.FloatLiteral:
                    return new NumberLiteral(((SPAGS.Expression.FloatLiteral)agsExpr).Value);
                case SPAGS.ExpressionType.Function:
                    break;
                case SPAGS.ExpressionType.IntegerLiteral:
                    return new IntegerLiteral(((SPAGS.Expression.IntegerLiteral)agsExpr).Value);
                case SPAGS.ExpressionType.Method:
                    break;
                case SPAGS.ExpressionType.Null:
                    return Nil;
                case SPAGS.ExpressionType.StringLiteral:
                    return new StringLiteral(((SPAGS.Expression.StringLiteral)agsExpr).Value);
                case SPAGS.ExpressionType.StructType:
                    break;
                case SPAGS.ExpressionType.UnaryOperator:
                    SPAGS.Expression.UnaryOperator unop = (SPAGS.Expression.UnaryOperator)agsExpr;
                    switch (unop.Token.Type)
                    {
                        case SPAGS.TokenType.Subtract:
                            break;
                        case SPAGS.TokenType.LogicalNot:
                            break;
                    }
                    break;
                case SPAGS.ExpressionType.Variable:
                    break;
            }
            return null;
        }
        private LuaExpression(string keyword, LuaValueType vtype)
        {
            _keyword = keyword;
            _type = vtype;
        }
        public LuaExpression MakeIndex(string index)
        {
            return new Indexing(this, index);
        }
        public LuaExpression MakeCall(params LuaExpression[] args)
        {
            Call call = new Call(this);
            foreach (LuaExpression arg in args) call.Parameters.Add(arg);
            return call;
        }
        private LuaExpression(LuaValueType vtype)
        {
            _type = vtype;
        }
        private LuaExpression()
        {
            _type = LuaValueType.Any;
        }
        private LuaValueType _type;
        public virtual LuaValueType GetType()
        {
            return _type;
        }
        private string _keyword;
        public virtual void WriteTo(TextWriter output, int indent, bool asPrefix)
        {
            if (_keyword == null) throw new NotImplementedException();
            if (asPrefix)
            {
                output.Write("(" + _keyword + ")");
            }
            else
            {
                output.Write(_keyword);
            }
        }
        public static readonly LuaExpression True = new LuaExpression("true", LuaValueType.Boolean);
        public static readonly LuaExpression False = new LuaExpression("false", LuaValueType.Boolean);
        public static readonly LuaExpression Nil = new LuaExpression("nil", LuaValueType.Nil);
        public LuaValueType ReturnType = LuaValueType.Any;
        public virtual LuaExpression CastTo(LuaValueType newType)
        {
            switch (newType)
            {
                case LuaValueType.Boolean:
                    switch (GetType())
                    {
                        case LuaValueType.Number:
                            return new LuaExpression.BinOp(
                                LuaBinaryOperatorType.IsNotEqualTo,
                                this,
                                new LuaExpression.NumberLiteral(0));
                        default: return this;
                    }
                case LuaValueType.Number:
                    switch (GetType())
                    {
                        case LuaValueType.Boolean:
                            return new LuaExpression.BinOp(
                                LuaBinaryOperatorType.LogicalOr,
                                new LuaExpression.BinOp(
                                    LuaBinaryOperatorType.LogicalAnd,
                                    this,
                                    new LuaExpression.NumberLiteral(1)),
                                new LuaExpression.NumberLiteral(0));
                        default: return this;
                    }
                default: return this;
            }
        }
        public bool IsLogicallyTrue
        {
            get { return (this != False) && (this != Nil); }
        }
        public LuaExpression LogicallyNegate()
        {
            return this.IsLogicallyTrue ? False : True;
        }
        public class StringLiteral : LuaExpression
        {
            public StringLiteral(string value)
                : base(LuaValueType.String)
            {
                Value = value;
            }
            public string Value;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                if (asPrefix)
                {
                    output.Write("(" + InvokeLua.util_quotestring(Value) + ")");
                }
                else
                {
                    output.Write(InvokeLua.util_quotestring(Value));
                }
            }
        }
        public class NumberLiteral : LuaExpression
        {
            public NumberLiteral(double value)
                : base(LuaValueType.Number)
            {
                Value = value;
            }
            public double Value;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                if (asPrefix)
                {
                    output.Write("(" + Value + ")");
                }
                else
                {
                    output.Write(Value);
                }
            }
        }
        public class IntegerLiteral : LuaExpression
        {
            public IntegerLiteral(int value)
                : base(LuaValueType.Integer)
            {
                Value = value;
            }
            public int Value;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                if (asPrefix)
                {
                    output.Write("(" + Value + ")");
                }
                else
                {
                    output.Write(Value);
                }
            }
        }
        public class Indexing : LuaExpression
        {
            public Indexing(LuaExpression target, LuaExpression index)
            {
                Target = target;
                Index = index;
            }
            public Indexing(LuaExpression target, string index)
            {
                Target = target;
                Index = new StringLiteral(index);
            }
            public LuaExpression Target;
            public LuaExpression Index;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                Target.WriteTo(output, indent, true);
                output.Write("[");
                Index.WriteTo(output, indent, false);
                output.Write("]");
            }
        }
        public class GlobalAccess : LuaExpression
        {
            public GlobalAccess(string name)
            {
                Name = name;
            }
            public static string Name;
        }
        public class Method : LuaExpression
        {
            public Method(LuaExpression target, string name)
            {
                Target = target;
                MethodName = name;
            }
            public LuaExpression Target;
            public string MethodName;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                Target.WriteTo(output, indent, true);
                output.Write(":" + MethodName);
            }
        }
        public class Call : LuaExpression
        {
            public Call(LuaExpression callingOn)
            {
                CallingOn = callingOn;
            }
            public LuaExpression CallingOn;
            public List<LuaExpression> Parameters;
            public override LuaValueType GetType()
            {
                return CallingOn.ReturnType;
            }
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                CallingOn.WriteTo(output, indent, true);
                output.Write("(");
                for (int i = 0; i < Parameters.Count; i++)
                {
                    if (i > 0) output.Write(", ");
                    Parameters[i].WriteTo(output, indent, false);
                }
            }
        }
        public class UnOp : LuaExpression
        {
            public UnOp(LuaUnaryOperatorType type, LuaExpression operand)
            {
                OpType = type;
                Operand = operand;
            }
            public LuaUnaryOperatorType OpType;
            public LuaExpression Operand;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                switch (OpType)
                {
                    case LuaUnaryOperatorType.Length: output.Write("#"); break;
                    case LuaUnaryOperatorType.LogicalNot: output.Write("not "); break;
                    case LuaUnaryOperatorType.Minus: output.Write("-"); break;
                }
                if (Operand is BinOp)
                {
                    output.Write("(");
                    Operand.WriteTo(output, indent, false);
                    output.Write(")");
                }
                else
                {
                    Operand.WriteTo(output, indent, false);
                }
            }
        }
        public class BinOp : LuaExpression
        {
            public BinOp(LuaBinaryOperatorType type, LuaExpression left, LuaExpression right)
                : base()
            {
                OpType = type;
                Left = left;
                Right = right;
            }
            public readonly LuaBinaryOperatorType OpType;
            public LuaExpression Left;
            public LuaExpression Right;
            public override void WriteTo(TextWriter output, int indent, bool asPrefix)
            {
                if (asPrefix) output.Write("(");
                Left.WriteTo(output, indent, false);
                switch (OpType)
                {
                    case LuaBinaryOperatorType.Add: output.Write(" + "); break;
                    case LuaBinaryOperatorType.Concatenate: output.Write(" .. "); break;
                    case LuaBinaryOperatorType.Divide: output.Write(" / "); break;
                    case LuaBinaryOperatorType.IsEqualTo: output.Write(" == "); break;
                    case LuaBinaryOperatorType.IsGreaterThan: output.Write(" > "); break;
                    case LuaBinaryOperatorType.IsGreaterThanOrEqualTo: output.Write(" >= "); break;
                    case LuaBinaryOperatorType.IsLessThan: output.Write(" < "); break;
                    case LuaBinaryOperatorType.IsLessThanOrEqualTo: output.Write(" <= "); break;
                    case LuaBinaryOperatorType.IsNotEqualTo: output.Write(" ~= "); break;
                    case LuaBinaryOperatorType.LogicalAnd: output.Write(" and "); break;
                    case LuaBinaryOperatorType.LogicalOr: output.Write(" or "); break;
                    case LuaBinaryOperatorType.Modulus: output.Write(" % "); break;
                    case LuaBinaryOperatorType.Multiply: output.Write(" * "); break;
                    case LuaBinaryOperatorType.RaiseToPower: output.Write(" ^ "); break;
                    case LuaBinaryOperatorType.Subtract: output.Write(" - "); break;
                }
                Right.WriteTo(output, indent, false);
                if (asPrefix) output.Write(")");
            }
            public override LuaValueType GetType()
            {
                switch (OpType)
                {
                    case LuaBinaryOperatorType.Add: return LuaValueType.Number;
                    case LuaBinaryOperatorType.Concatenate: return LuaValueType.String;
                    case LuaBinaryOperatorType.Divide: return LuaValueType.Number;

                    case LuaBinaryOperatorType.IsEqualTo:
                    case LuaBinaryOperatorType.IsGreaterThan:
                    case LuaBinaryOperatorType.IsGreaterThanOrEqualTo:
                    case LuaBinaryOperatorType.IsLessThan:
                    case LuaBinaryOperatorType.IsLessThanOrEqualTo:
                    case LuaBinaryOperatorType.IsNotEqualTo:
                        return LuaValueType.Boolean;

                    case LuaBinaryOperatorType.LogicalAnd:
                    case LuaBinaryOperatorType.LogicalOr:
                        return Left.GetType() | Right.GetType();
                    case LuaBinaryOperatorType.Modulus: return LuaValueType.Number;
                    case LuaBinaryOperatorType.Multiply: return LuaValueType.Number;
                    case LuaBinaryOperatorType.RaiseToPower: return LuaValueType.Number;
                    case LuaBinaryOperatorType.Subtract: return LuaValueType.Number;
                    default: return LuaValueType.Any;
                }
            }
        }
    }
}
