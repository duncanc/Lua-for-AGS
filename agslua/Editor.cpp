
#include <windows.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "AGSLua.h"
#include "CompressedLuaChunks.h"

IAGSEditor *editor;

const char ourScriptHeader[] =
	"#define USE_LUA" "\r\n"

	"enum LuaCallMode {" "\r\n"
	"	eLuaUnprotectedMode = 0," "\r\n"
	"	eLuaProtectedMode = 1" "\r\n"
	"};" "\r\n"

	"enum LuaCallResult {" "\r\n"
	"	eLuaCallNone = 0," "\r\n"
	"	eLuaCallOK = 1," "\r\n"
	"	eLuaCallError = 2," "\r\n"
	"	eLuaCallFuncNotFound = 3" "\r\n"
	"};" "\r\n"

	"enum LuaValueType {" "\r\n"

	//"	eLuaTypeNone = -1," "\r\n"      -1 not a literal value...
	"	eLuaBaseTypeBoolean = 1," "\r\n"
	"	eLuaBaseTypeLightUserdata = 2," "\r\n"
	"	eLuaBaseTypeNumber = 3," "\r\n"
	"	eLuaBaseTypeString = 4," "\r\n"
	"	eLuaBaseTypeTable = 5," "\r\n"
	"	eLuaBaseTypeFunction = 6," "\r\n"
	"	eLuaBaseTypeFullUserdata = 7," "\r\n"
	"	eLuaBaseTypeThread = 8," "\r\n"

	// Immortal
	"	eLuaGameTypeCharacter = 1001," "\r\n"
	"	eLuaGameTypeDialog = 1002," "\r\n"
	"	eLuaGameTypeGUI = 1003," "\r\n"
	"	eLuaGameTypeGUIControl = 1004," "\r\n"
	"	eLuaGameTypeListBox = 1005," "\r\n"
	"	eLuaGameTypeTextBox = 1006," "\r\n"
	"	eLuaGameTypeSlider = 1007," "\r\n"
	"	eLuaGameTypeLabel = 1008," "\r\n"
	"	eLuaGameTypeButton = 1009," "\r\n"
	"	eLuaGameTypeInvWindow = 1010," "\r\n"

	// Room specific
	"	eLuaGameTypeHotspot = 1011," "\r\n"
	"	eLuaGameTypeRegion = 1012," "\r\n"
	"	eLuaGameTypeObject = 1013," "\r\n"

	// Ephemeral
	"	eLuaGameTypeViewFrame = 1014," "\r\n"
	"	eLuaGameTypeDrawingSurface = 1015," "\r\n"
	"	eLuaGameTypeFile = 1016," "\r\n"
	"	eLuaGameTypeOverlay = 1017," "\r\n"
	"	eLuaGameTypeDynamicSprite = 1018," "\r\n"
	"	eLuaGameTypeDateTime = 1019," "\r\n"
	"#ifver 3.2" "\r\n"
	"	eLuaGameTypeAudioChannel = 1020," "\r\n"
	"	eLuaGameTypeAudioClip = 1021," "\r\n"
	"#endif" "\r\n"
	"	eLuaBaseTypeNil = 0" "\r\n"

	"};" "\r\n"

	"managed struct LuaValue;" "\r\n"

	"managed struct LuaValueList {" "\r\n"

	"	/// Gets/sets the length of the LuaValueList." "\r\n"
	"	import attribute int Length; // $AUTOCOMPLETENOINHERIT$" "\r\n"

	"	/// Append one or more values to the List." "\r\n"
	"	import void Add(LuaValueList* values); // $AUTOCOMPLETENOINHERIT$" "\r\n"

	//"	/// Gets the type of a value from the list, as a LuaValueType enum value." "\r\n"
	//"	readonly import attribute LuaValueType Types[];" "\r\n"

	"	/// Gets the error message associated with this list, or null if there was no error." "\r\n"
	"	readonly import attribute String Error; // $AUTOCOMPLETENOINHERIT$" "\r\n"

	"	/// Gets the function call result type associated with this list." "\r\n"
	"	readonly import attribute LuaCallResult CallResult; // $AUTOCOMPLETENOINHERIT$" "\r\n"

	"	/// Indicates whether this LuaValueList is modifiable or not." "\r\n"
	"	readonly import attribute bool IsReadOnly; // $AUTOCOMPLETENOINHERIT$" "\r\n"

	//"	/// Gets/sets values in the list as strings." "\r\n"
	//"	import attribute String AsStrings[];" "\r\n"
	//"	/// Gets/sets values in the list as ints." "\r\n"
	//"	import attribute int AsInts[];" "\r\n"
	//"	/// Gets/sets values in the list as floats." "\r\n"
	//"	import attribute float AsFloats[];" "\r\n"
	//"	/// Gets/sets values in the list as bools." "\r\n"
	//"	import attribute bool AsBools[];" "\r\n"
	
	"	/// Extract values from the List into a new List. Does not modify the original, unlike Splice()." "\r\n"
	"	import LuaValueList* Slice(int beginning, int end=0); // $AUTOCOMPLETENOINHERIT$" "\r\n"
	"	/// Insert and/or remove elements to/from the List. Removed elements are also returned, in a new List." "\r\n"
	"	import LuaValueList* Splice(int index, int removals, LuaValueList* insertions=0); // $AUTOCOMPLETENOINHERIT$" "\r\n"

	"	/// Get/set values in the List." "\r\n"
	"	import attribute LuaValue* Values[]; // $AUTOCOMPLETENOINHERIT$" "\r\n"

//#include "autogen_luavaluelist_members.h"

	"};" "\r\n"

	"managed struct LuaValue extends LuaValueList {" "\r\n"
	"	/// Get the type of the value, as a LuaValueType enum value." "\r\n"
	"	readonly import attribute LuaValueType Type;" "\r\n"
	
	"	/// Get the value as a String (or null if it is not convertible)." "\r\n"
	"	readonly import attribute String AsString;" "\r\n"
	"	/// Get the value as an int (or 0 if it is not convertible)." "\r\n"
	"	readonly import attribute int AsInt;" "\r\n"
	"	/// Get the values in the list as a float (or 0 if it is not convertible)." "\r\n"
	"	readonly import attribute float AsFloat;" "\r\n"
	"	/// Get the value as a boolean (or true if it is not a boolean or nil)." "\r\n"
	"	readonly import attribute bool AsBool;" "\r\n"
	"};" "\r\n"

	"struct Lua {" "\r\n"
	"	/// Creates a new, empty LuaValueList." "\r\n"
	"	import static LuaValueList* NewValueList();   // " "\r\n"

	"	/// Get a read-only LuaValueList containing one int." "\r\n"
	"	import static LuaValue* IntValue(int value);   // " "\r\n"
	"	/// Get a read-only LuaValueList containing one float." "\r\n"
	"	import static LuaValue* FloatValue(float value);   // " "\r\n"
	"	/// Get a read-only LuaValueList containing one String." "\r\n"
	"	import static LuaValue* StringValue(String value);   // " "\r\n"
	"	/// Get a read-only LuaValueList containing one bool." "\r\n"
	"	import static LuaValue* BoolValue(bool value);   // " "\r\n"
	"	/// Get a read-only LuaValueList containing one nil value." "\r\n"
	"	readonly import static attribute LuaValue* NilValue;   // " "\r\n"

	//"	/// Gets the first value from a LuaValueList as an int." "\r\n"
	//"	import static int ToInt(LuaValueList* values);" "\r\n"
	//"	/// Gets the first value from a LuaValueList as a float." "\r\n"
	//"	import static float ToFloat(LuaValueList* values);" "\r\n"
	//"	/// Gets the first value from a LuaValueList as a String." "\r\n"
	//"	import static String ToString(LuaValueList* values);" "\r\n"
	//"	/// Gets the first value from a LuaValueList as a bool." "\r\n"
	//"	import static bool ToBool(LuaValueList* values);" "\r\n"

	"	/// Run the script from the Lua script store with the given filename." "\r\n"
	"	import static void RunScript(String script_name);" "\r\n"
	"	/// Require a Lua module. Will throw a Lua error if it cannot be found." "\r\n"
	"	import static void RequireModule(String module_name);" "\r\n"

	"	/// Call a Lua global function." "\r\n"
	"	import static LuaValueList* Call(String funcname, LuaValueList* params = 0, LuaCallMode = eLuaUnprotectedMode);" "\r\n"
	"	/// Set the value of a Lua global variable to the first value from a LuaValueList." "\r\n"
	"	import static void SetVar(String variableName, LuaValue* value);" "\r\n"
	"	/// Get the value of a Lua global variable in a LuaValueList." "\r\n"
	"	import static LuaValue* GetVar(String variableName);" "\r\n"
	"	/// Set the value of a Lua global variable to a new, empty table." "\r\n"
	"	import static void CreateTable(String variableName);" "\r\n"

	"	/// Run a short piece of Lua code and get the results." "\r\n"
	"	import static LuaValueList* Evaluate(String expression, LuaCallMode = eLuaUnprotectedMode);" "\r\n"


	/*
	"	/// Add a user-defined AGS function from the global script, that takes 'numArgs' int parameters." "\r\n"
	"	import static void RegisterGlobalScriptFunction(String func_name, int numArgs);" "\r\n"
	"	/// Add a user-defined AGS function from the room script, that takes 'numArgs' int parameters." "\r\n"
	"	import static void RegisterRoomScriptFunction(String func_name, int numArgs);" "\r\n"
	"	/// Remove a function previously added with RegisterGlobalScriptFunction or RegisterRoomScriptFunction." "\r\n"
	"	import static void UnregisterFunction(String func_name);" "\r\n"
	*/

#include "autogen_lua_members.h"

	"};" "\r\n"

	"/// Get a Lua value list containing the String." "\r\n"
	"import LuaValue* AsLuaValue(this String*);" "\r\n"
	"/// Call a Lua method on the String." "\r\n"
	"import LuaValueList* LuaMethod(this String*, String methodName, LuaValueList* params = 0, LuaCallMode = eLuaUnprotectedMode);" "\r\n"

#include "autogen_extender_functions.h"

;

int AGS_EditorStartup(IAGSEditor* lpEditor) {
	if (lpEditor->version < 1) {
		return -1;
	}

	editor = lpEditor;
	editor->RegisterScriptHeader(ourScriptHeader);
	main_L = luaL_newstate();

	return 0; // success
}

void AGS_EditorShutdown() {
	editor->UnregisterScriptHeader(ourScriptHeader);
	if (main_L) {
		lua_close(main_L);
		main_L = NULL;
	}
}

int savegame_aux(lua_State *L) {
	int written = 0;
	FILE* f = fopen("Compiled/lscripts.dat", "rb");
	if (!f) {
		return 0;
	}
	int offset, length;
	fseek(f, -16, SEEK_END);
	fread(&offset, sizeof(offset), 1, f);
	fseek(f, -8, SEEK_END);
	fread(&length, sizeof(length), 1, f);
	fseek(f, offset, SEEK_SET);
	aux_loadcompressed(L, f, offset, length);
	lua_call(L,0,1);
	if (lua_istable(L,-1)) {
		// get guid check
		lua_getfield(L,-1,"guid");
	}
	else {
		lua_pushnil(L);
	}
	lua_remove(L,-2);
	fclose(f);
	return 1;
}

int AGS_EditorSaveGame (char *buffer, int bufsize) {
	if (!main_L)
	{
		MessageBox(NULL, "Error serializing Lua information: Lua state was not opened", "Lua Error", MB_OK);
		return 0;
	}
	lua_pushcfunction(main_L, savegame_aux);
	if (0 != lua_pcall(main_L, 0, 1, 0))
	{
		DebugMessage(main_L, "lua save error: %s", lua_tostring(main_L,-1));
		lua_pop(main_L, 1);
		return 0;
	}
	int t = lua_type(main_L, -1);
	if (t != LUA_TSTRING)
	{
		DebugMessage(main_L, "lua save returned wrong value type (expecting string, got %s)", lua_typename(main_L, t));
		lua_pop(main_L, 1);
		return 0;
	}
	int len = lua_objlen(main_L,-1);
	if (bufsize < len)
	{
		DebugMessage(main_L, "lua plugin needs %d bytes of save data (got %d)", len, bufsize);
		lua_pop(main_L, 1);
		return 0;
	}
	memcpy(buffer, lua_tostring(main_L,-1), len);
	lua_pop(main_L, 1);
	return len;
}

void AGS_EditorLoadGame (char *buffer, int bufsize) {
}
