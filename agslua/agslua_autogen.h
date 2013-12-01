
#ifndef AGSLUA_AUTOGEN_H
#define AGSLUA_AUTOGEN_H

#include "agsplugin.h"
extern "C" {
	#include <lua.h>
}

extern int need_restoration;
void _RestoreLuaReliability();

extern lua_State* main_L;
extern lua_State* vlist_L;

void GetScriptFunctionAddresses(IAGSEngine* engine);
void RegisterLuaInterop(IAGSEngine* engine);

extern IAGSEngine* engine;
extern int ags_closing;

#define IMMORTAL_OBJECT_STORE "AGS Immortal Object store"

#define LUACALL_NONE			0
#define LUACALL_SUCCESS			1
#define LUACALL_ERROR			2
#define LUACALL_FUNCNOTFOUND	3
#define LUACALL_UNCALLABLE      4

typedef struct EphemeralContainer {
	const char* ptr;
	int key;
} EphemeralContainer;

#define VLIST_STACK_IMMORTALSTORE	 1
#define VLIST_STACK_LISTSTORE		 2
#define VLIST_STACK_CACHE			 3
#define VLIST_STACK_VALUECACHE		 4
#define VLIST_STACK_META			 5
#define VLIST_STACK_READONLY_META	 6
#define VLIST_STACK_RESTORE_LISTS    7
#define VLIST_STACK_RESTORE_READONLY 8
#define VLIST_STACK_NIL              9
#define VLIST_STACK_MAX				 VLIST_STACK_NIL

extern lua_State* vlist_L;

void aux_LuaGetVariable(lua_State* aux_L, const char* expr);
void aux_LuaSetVariable(const char* expr, int values);
void aux_LuaValueList_geti(void* ptr, int i);
void aux_LuaValueList_seti(void* ptr, int i);
int aux_LuaCall_SetUp(lua_State* aux_L, void* ptr, const char* expr, void* params);
void aux_LuaCall_ReturnValue(int numParams, int protectedMode);
void* aux_LuaValueList_Create(int fromStackValues, int callResult);
void* aux_LuaCall_ReturnList(lua_State* aux_L, int numParams, int protectedMode);
int aux_LuaCall_SetUp_Obj(const char* expr, void* params);
void* aux_LuaValueList_MakeReadOnly();



// Integer constants
#define AGS_MAX_INV 301
#define AGS_FOLLOW_EXACTLY 32766
#define AGS_NARRATOR -1
#define AGS_OPT_WALKONLOOK 2
#define AGS_OPT_DIALOGOPTIONSGUI 3
#define AGS_OPT_ANTIGLIDE 4
#define AGS_OPT_DIALOGOPTIONSGAP 6
#define AGS_OPT_WHENGUIDISABLED 8
#define AGS_OPT_ALWAYSSPEECH 9
#define AGS_OPT_PIXELPERFECT 11
#define AGS_OPT_NOWALKMODE 12
#define AGS_OPT_FIXEDINVCURSOR 14
#define AGS_OPT_DONTLOSEINV 15
#define AGS_OPT_TURNBEFOREWALK 18
#define AGS_OPT_HANDLEINVCLICKS 20
#define AGS_OPT_MOUSEWHEEL 21
#define AGS_OPT_DIALOGNUMBERED 22
#define AGS_OPT_DIALOGUPWARDS 23
#define AGS_OPT_CROSSFADEMUSIC 24
#define AGS_OPT_ANTIALIASFONTS 25
#define AGS_OPT_THOUGHTGUI 26
#define AGS_OPT_TURNWHENFACING 27
#define AGS_OPT_RIGHTTOLEFT 28
#define AGS_OPT_MULTIPLEINV 29
#define AGS_OPT_SAVEGAMESCREENSHOTS 30
#define AGS_OPT_PORTRAITPOSITION 31
#define AGS_OPT_LIPSYNCTEXT 99
#define AGS_COLOR_TRANSPARENT -1
#define AGS_DIALOG_PARSER_SELECTED -3053
#define AGS_RUN_DIALOG_RETURN -1
#define AGS_RUN_DIALOG_STOP_DIALOG -2
#define AGS_RUN_DIALOG_GOTO_PREVIOUS -4
#define AGS_SCR_NO_VALUE 31998
#define AGS_false 0
#define AGS_true 1
#define AGS_eOSDOS 1
#define AGS_eOSWindows 2
#define AGS_eOSLinux 3
#define AGS_eOSMacOS 4
#define AGS_eTransitionFade 0
#define AGS_eTransitionInstant 1
#define AGS_eTransitionDissolve 2
#define AGS_eTransitionBoxout 3
#define AGS_eTransitionCrossfade 4
#define AGS_eMouseLeft 1
#define AGS_eMouseRight 2
#define AGS_eMouseMiddle 3
#define AGS_eMouseLeftInv 5
#define AGS_eMouseRightInv 6
#define AGS_eMouseMiddleInv 7
#define AGS_eMouseWheelNorth 8
#define AGS_eMouseWheelSouth 9
#define AGS_eRoundDown 0
#define AGS_eRoundNearest 1
#define AGS_eRoundUp 2
#define AGS_eOnce 0
#define AGS_eRepeat 1
#define AGS_eAlignLeft 1
#define AGS_eAlignCentre 2
#define AGS_eAlignRight 3
#define AGS_eLocationNothing 0
#define AGS_eLocationHotspot 1
#define AGS_eLocationCharacter 2
#define AGS_eLocationObject 3
#define AGS_eSkipESCOnly 1
#define AGS_eSkipAnyKey 2
#define AGS_eSkipMouseClick 3
#define AGS_eSkipAnyKeyOrMouseClick 4
#define AGS_eSkipESCOrRightButton 5
#define AGS_eOptionOff 0
#define AGS_eOptionOn 1
#define AGS_eOptionOffForever 2
#define AGS_eSpeechLucasarts 0
#define AGS_eSpeechSierra 1
#define AGS_eSpeechSierraWithBackground 2
#define AGS_eSpeechFullScreen 3
#define AGS_eSpeechTextOnly 0
#define AGS_eSpeechVoiceAndText 1
#define AGS_eSpeechVoiceOnly 2
#define AGS_eFlipLeftToRight 1
#define AGS_eFlipUpsideDown 2
#define AGS_eFlipBoth 3
#define AGS_eCDIsDriverPresent 0
#define AGS_eCDGetPlayingStatus 1
#define AGS_eCDPlayTrack 2
#define AGS_eCDPausePlayback 3
#define AGS_eCDResumePlayback 4
#define AGS_eCDGetNumTracks 5
#define AGS_eCDEject 6
#define AGS_eCDCloseTray 7
#define AGS_eCDGetCDDriveCount 8
#define AGS_eCDSelectActiveCDDrive 9
#define AGS_eSayUseOptionSetting 1
#define AGS_eSayAlways 2
#define AGS_eSayNever 3
#define AGS_eVideoSkipNotAllowed 0
#define AGS_eVideoSkipEscKey 1
#define AGS_eVideoSkipAnyKey 2
#define AGS_eVideoSkipAnyKeyOrMouse 3
#define AGS_eKeyCtrlA 1
#define AGS_eKeyCtrlB 2
#define AGS_eKeyCtrlC 3
#define AGS_eKeyCtrlD 4
#define AGS_eKeyCtrlE 5
#define AGS_eKeyCtrlF 6
#define AGS_eKeyCtrlG 7
#define AGS_eKeyCtrlH 8
#define AGS_eKeyBackspace 8
#define AGS_eKeyCtrlI 9
#define AGS_eKeyTab 9
#define AGS_eKeyCtrlJ 10
#define AGS_eKeyCtrlK 11
#define AGS_eKeyCtrlL 12
#define AGS_eKeyCtrlM 13
#define AGS_eKeyReturn 13
#define AGS_eKeyCtrlN 14
#define AGS_eKeyCtrlO 15
#define AGS_eKeyCtrlP 16
#define AGS_eKeyCtrlQ 17
#define AGS_eKeyCtrlR 18
#define AGS_eKeyCtrlS 19
#define AGS_eKeyCtrlT 20
#define AGS_eKeyCtrlU 21
#define AGS_eKeyCtrlV 22
#define AGS_eKeyCtrlW 23
#define AGS_eKeyCtrlX 24
#define AGS_eKeyCtrlY 25
#define AGS_eKeyCtrlZ 26
#define AGS_eKeyEscape 27
#define AGS_eKeySpace 32
#define AGS_eKeyExclamationMark 33
#define AGS_eKeyDoubleQuote 34
#define AGS_eKeyHash 35
#define AGS_eKeyDollar 36
#define AGS_eKeyPercent 37
#define AGS_eKeyAmpersand 38
#define AGS_eKeySingleQuote 39
#define AGS_eKeyOpenParenthesis 40
#define AGS_eKeyCloseParenthesis 41
#define AGS_eKeyAsterisk 42
#define AGS_eKeyPlus 43
#define AGS_eKeyComma 44
#define AGS_eKeyHyphen 45
#define AGS_eKeyPeriod 46
#define AGS_eKeyForwardSlash 47
#define AGS_eKey0 48
#define AGS_eKey1 49
#define AGS_eKey2 50
#define AGS_eKey3 51
#define AGS_eKey4 52
#define AGS_eKey5 53
#define AGS_eKey6 54
#define AGS_eKey7 55
#define AGS_eKey8 56
#define AGS_eKey9 57
#define AGS_eKeyColon 58
#define AGS_eKeySemiColon 59
#define AGS_eKeyLessThan 60
#define AGS_eKeyEquals 61
#define AGS_eKeyGreaterThan 62
#define AGS_eKeyQuestionMark 63
#define AGS_eKeyAt 64
#define AGS_eKeyA 65
#define AGS_eKeyB 66
#define AGS_eKeyC 67
#define AGS_eKeyD 68
#define AGS_eKeyE 69
#define AGS_eKeyF 70
#define AGS_eKeyG 71
#define AGS_eKeyH 72
#define AGS_eKeyI 73
#define AGS_eKeyJ 74
#define AGS_eKeyK 75
#define AGS_eKeyL 76
#define AGS_eKeyM 77
#define AGS_eKeyN 78
#define AGS_eKeyO 79
#define AGS_eKeyP 80
#define AGS_eKeyQ 81
#define AGS_eKeyR 82
#define AGS_eKeyS 83
#define AGS_eKeyT 84
#define AGS_eKeyU 85
#define AGS_eKeyV 86
#define AGS_eKeyW 87
#define AGS_eKeyX 88
#define AGS_eKeyY 89
#define AGS_eKeyZ 90
#define AGS_eKeyOpenBracket 91
#define AGS_eKeyBackSlash 92
#define AGS_eKeyCloseBracket 93
#define AGS_eKeyUnderscore 95
#define AGS_eKeyF1 359
#define AGS_eKeyF2 360
#define AGS_eKeyF3 361
#define AGS_eKeyF4 362
#define AGS_eKeyF5 363
#define AGS_eKeyF6 364
#define AGS_eKeyF7 365
#define AGS_eKeyF8 366
#define AGS_eKeyF9 367
#define AGS_eKeyF10 368
#define AGS_eKeyHome 371
#define AGS_eKeyUpArrow 372
#define AGS_eKeyPageUp 373
#define AGS_eKeyLeftArrow 375
#define AGS_eKeyNumPad5 376
#define AGS_eKeyRightArrow 377
#define AGS_eKeyEnd 379
#define AGS_eKeyDownArrow 380
#define AGS_eKeyPageDown 381
#define AGS_eKeyInsert 382
#define AGS_eKeyDelete 383
#define AGS_eKeyF11 433
#define AGS_eKeyF12 434
#define AGS_eAudioFileOGG 1
#define AGS_eAudioFileMP3 2
#define AGS_eAudioFileWAV 3
#define AGS_eAudioFileVOC 4
#define AGS_eAudioFileMIDI 5
#define AGS_eAudioFileMOD 6
#define AGS_eAudioPriorityVeryLow 1
#define AGS_eAudioPriorityLow 25
#define AGS_eAudioPriorityNormal 50
#define AGS_eAudioPriorityHigh 75
#define AGS_eAudioPriorityVeryHigh 100
#define AGS_eFileRead 1
#define AGS_eFileWrite 2
#define AGS_eFileAppend 3
#define AGS_eEventLeaveRoom 1
#define AGS_eEventEnterRoomBeforeFadein 2
#define AGS_eEventGotScore 4
#define AGS_eEventGUIMouseDown 5
#define AGS_eEventGUIMouseUp 6
#define AGS_eEventAddInventory 7
#define AGS_eEventLoseInventory 8
#define AGS_eEventRestoreGame 9
#define AGS_eBlock 919
#define AGS_eNoBlock 920
#define AGS_eForwards 1062
#define AGS_eBackwards 1063
#define AGS_eAnywhere 304
#define AGS_eWalkableAreas 305

// Enum labels
#define AGS_eVoiceMode int
#define luags_pusheVoiceMode lua_pushinteger
#define luags_checkeVoiceMode luaL_checkint
#define AGS_RepeatStyle int
#define luags_pushRepeatStyle lua_pushinteger
#define luags_checkRepeatStyle luaL_checkint
#define AGS_RoundDirection int
#define luags_pushRoundDirection lua_pushinteger
#define luags_checkRoundDirection luaL_checkint
#define AGS_eFlipDirection int
#define luags_pusheFlipDirection lua_pushinteger
#define luags_checkeFlipDirection luaL_checkint
#define AGS_EventType int
#define luags_pushEventType lua_pushinteger
#define luags_checkEventType luaL_checkint
#define AGS_LocationType int
#define luags_pushLocationType lua_pushinteger
#define luags_checkLocationType luaL_checkint
#define AGS_function int
#define luags_pushfunction lua_pushinteger
#define luags_checkfunction luaL_checkint
#define AGS_eKeyCode int
#define luags_pusheKeyCode lua_pushinteger
#define luags_checkeKeyCode luaL_checkint
#define AGS_eSpeechStyle int
#define luags_pusheSpeechStyle lua_pushinteger
#define luags_checkeSpeechStyle luaL_checkint
#define AGS_WalkWhere int
#define luags_pushWalkWhere lua_pushinteger
#define luags_checkWalkWhere luaL_checkint
#define AGS_Direction int
#define luags_pushDirection lua_pushinteger
#define luags_checkDirection luaL_checkint
#define AGS_DialogOptionSayStyle int
#define luags_pushDialogOptionSayStyle lua_pushinteger
#define luags_checkDialogOptionSayStyle luaL_checkint
#define AGS_CursorMode int
#define luags_pushCursorMode lua_pushinteger
#define luags_checkCursorMode luaL_checkint
#define AGS_bool int
#define luags_pushbool lua_pushinteger
#define luags_checkbool luaL_checkint
#define AGS_DialogOptionState int
#define luags_pushDialogOptionState lua_pushinteger
#define luags_checkDialogOptionState luaL_checkint
#define AGS_AudioFileType int
#define luags_pushAudioFileType lua_pushinteger
#define luags_checkAudioFileType luaL_checkint
#define AGS_AudioType int
#define luags_pushAudioType lua_pushinteger
#define luags_checkAudioType luaL_checkint
#define AGS_CHARID int
#define luags_pushCHARID lua_pushinteger
#define luags_checkCHARID luaL_checkint
#define AGS_MouseButton int
#define luags_pushMouseButton lua_pushinteger
#define luags_checkMouseButton luaL_checkint
#define AGS_BlockingStyle int
#define luags_pushBlockingStyle lua_pushinteger
#define luags_checkBlockingStyle luaL_checkint
#define AGS_eCDAudioFunction int
#define luags_pusheCDAudioFunction lua_pushinteger
#define luags_checkeCDAudioFunction luaL_checkint
#define AGS_eOperatingSystem int
#define luags_pusheOperatingSystem lua_pushinteger
#define luags_checkeOperatingSystem luaL_checkint
#define AGS_FileMode int
#define luags_pushFileMode lua_pushinteger
#define luags_checkFileMode luaL_checkint
#define AGS_Alignment int
#define luags_pushAlignment lua_pushinteger
#define luags_checkAlignment luaL_checkint
#define AGS_TransitionStyle int
#define luags_pushTransitionStyle lua_pushinteger
#define luags_checkTransitionStyle luaL_checkint
#define AGS_AudioPriority int
#define luags_pushAudioPriority lua_pushinteger
#define luags_checkAudioPriority luaL_checkint
#define AGS_VideoSkipStyle int
#define luags_pushVideoSkipStyle lua_pushinteger
#define luags_checkVideoSkipStyle luaL_checkint
#define AGS_CutsceneSkipType int
#define luags_pushCutsceneSkipType lua_pushinteger
#define luags_checkCutsceneSkipType luaL_checkint
#define AGS_FontType int
#define luags_pushFontType lua_pushinteger
#define luags_checkFontType luaL_checkint

// Struct labels
#define AGS_ViewFrame void
#define AGS_DrawingSurface void
#define AGS_File void
#define AGS_InventoryItem void
#define AGS_Overlay void
#define AGS_DynamicSprite void
#define AGS_GUIControl void
#define AGS_Label void
#define AGS_Button void
#define AGS_Slider void
#define AGS_TextBox void
#define AGS_InvWindow void
#define AGS_ListBox void
#define AGS_GUI void
#define AGS_Hotspot void
#define AGS_Region void
#define AGS_Dialog void
#define AGS_DateTime void
#define AGS_AudioChannel void
#define AGS_AudioClip void
#define AGS_Object void
#define AGS_Character void

void luags_pushEphemeral(lua_State *L, void* eph, int META_IDX, int STORE_IDX);

#define luags_pushViewFrame(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkViewFrame(L,idx,META_IDX) ((AGS_ViewFrame*)llh_checkboxedptr(L,idx,META_IDX,"ViewFrame"))
#define luags_pushDrawingSurface(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkDrawingSurface(L,idx,META_IDX) ((AGS_DrawingSurface*)llh_checkboxedptr(L,idx,META_IDX,"DrawingSurface"))
#define luags_pushFile(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkFile(L,idx,META_IDX) ((AGS_File*)llh_checkboxedptr(L,idx,META_IDX,"File"))
#define luags_pushInventoryItem(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkInventoryItem(L,idx,META_IDX) ((AGS_InventoryItem*)llh_checkboxedptr(L,idx,META_IDX,"InventoryItem"))
#define luags_pushOverlay(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkOverlay(L,idx,META_IDX) ((AGS_Overlay*)llh_checkboxedptr(L,idx,META_IDX,"Overlay"))
#define luags_pushDynamicSprite(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkDynamicSprite(L,idx,META_IDX) ((AGS_DynamicSprite*)llh_checkboxedptr(L,idx,META_IDX,"DynamicSprite"))
#define luags_pushGUIControl(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkGUIControl(L,idx,META_IDX) ((AGS_GUIControl*)llh_checkboxedptr(L,idx,META_IDX,"GUIControl"))
#define luags_pushLabel(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkLabel(L,idx,META_IDX) ((AGS_Label*)llh_checkboxedptr(L,idx,META_IDX,"Label"))
#define luags_pushButton(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkButton(L,idx,META_IDX) ((AGS_Button*)llh_checkboxedptr(L,idx,META_IDX,"Button"))
#define luags_pushSlider(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkSlider(L,idx,META_IDX) ((AGS_Slider*)llh_checkboxedptr(L,idx,META_IDX,"Slider"))
#define luags_pushTextBox(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkTextBox(L,idx,META_IDX) ((AGS_TextBox*)llh_checkboxedptr(L,idx,META_IDX,"TextBox"))
#define luags_pushInvWindow(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkInvWindow(L,idx,META_IDX) ((AGS_InvWindow*)llh_checkboxedptr(L,idx,META_IDX,"InvWindow"))
#define luags_pushListBox(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkListBox(L,idx,META_IDX) ((AGS_ListBox*)llh_checkboxedptr(L,idx,META_IDX,"ListBox"))
#define luags_pushGUI(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkGUI(L,idx,META_IDX) ((AGS_GUI*)llh_checkboxedptr(L,idx,META_IDX,"GUI"))
extern void luags_pushHotspot(lua_State* L, AGS_Hotspot* hotspot,int META_IDX,int STORE_IDX);
extern AGS_Hotspot* luags_checkHotspot(lua_State* L, int idx,int META_IDX);
extern void luags_pushRegion(lua_State* L, AGS_Region* region,int META_IDX,int STORE_IDX);
extern AGS_Region* luags_checkRegion(lua_State* L, int idx,int META_IDX);
#define luags_pushDialog(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkDialog(L,idx,META_IDX) ((AGS_Dialog*)llh_checkboxedptr(L,idx,META_IDX,"Dialog"))
#define luags_pushDateTime(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkDateTime(L,idx,META_IDX) ((AGS_DateTime*)llh_checkboxedptr(L,idx,META_IDX,"DateTime"))
#define luags_pushAudioChannel(L,ptr,META_IDX,STORE_IDX) luags_pushEphemeral(L,ptr,META_IDX,STORE_IDX)
#define luags_checkAudioChannel(L,idx,META_IDX) ((AGS_AudioChannel*)llh_checkboxedptr(L,idx,META_IDX,"AudioChannel"))
#define luags_pushAudioClip(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkAudioClip(L,idx,META_IDX) ((AGS_AudioClip*)llh_checkboxedptr(L,idx,META_IDX,"AudioClip"))
extern void luags_pushObject(lua_State* L, AGS_Object* object,int META_IDX,int STORE_IDX);
extern AGS_Object* luags_checkObject(lua_State* L, int idx,int META_IDX);
#define luags_pushCharacter(L,ptr,META_IDX,STORE_IDX) llh_pushstored(L,ptr,META_IDX,STORE_IDX)
#define luags_checkCharacter(L,idx,META_IDX) ((AGS_Character*)llh_checkboxedptr(L,idx,META_IDX,"Character"))
// Global function signatures
typedef void (*_AGS_DISPLAY)(const char* message, ...);
typedef void (*_AGS_DISPLAYAT)(int x, int y, int width, const char* message, ...);
typedef void (*_AGS_DISPLAYATY)(int y, const char* message);
typedef void (*_AGS_DISPLAYMESSAGE)(int messageNumber);
typedef void (*_AGS_DISPLAYMESSAGEATY)(int messageNumber, int y);
typedef void (*_AGS_DISPLAYTOPBAR)(int y, int textColor, int backColor, const char* title, const char* text, ...);
typedef void (*_AGS_DISPLAYMESSAGEBAR)(int y, int textColor, int backColor, const char* title, int message);
typedef void (*_AGS_RESETROOM)(int roomNumber);
typedef int (*_AGS_HASPLAYERBEENINROOM)(int roomNumber);
typedef void (*_AGS_PROCESSCLICK)(int x, int y, AGS_CursorMode param3);
typedef void (*_AGS_ABORTGAME)(const char* message, ...);
typedef void (*_AGS_QUITGAME)(int promptUser);
typedef void (*_AGS_SETGAMESPEED)(int framesPerSecond);
typedef int (*_AGS_GETGAMESPEED)();
typedef int (*_AGS_SETGAMEOPTION)(int option, int value);
typedef int (*_AGS_GETGAMEOPTION)(int option);
typedef void (*_AGS_DEBUG)(int command, int data);
typedef void (*_AGS_CALLROOMSCRIPT)(int value);
typedef int (*_AGS_RUNAGSGAME)(const char* filename, int mode, int data);
typedef const char* (*_AGS_GETTRANSLATION)(const char* originalText);
typedef int (*_AGS_ISTRANSLATIONAVAILABLE)();
typedef void (*_AGS_RESTOREGAMEDIALOG)();
typedef void (*_AGS_SAVEGAMEDIALOG)();
typedef void (*_AGS_RESTARTGAME)();
typedef void (*_AGS_SAVEGAMESLOT)(int slot, const char* description);
typedef void (*_AGS_RESTOREGAMESLOT)(int slot);
typedef void (*_AGS_DELETESAVESLOT)(int slot);
typedef void (*_AGS_SETRESTARTPOINT)();
typedef AGS_LocationType (*_AGS_GETLOCATIONTYPE)(int x, int y);
typedef int (*_AGS_GETWALKABLEAREAAT)(int screenX, int screenY);
typedef int (*_AGS_GETSCALINGAT)(int x, int y);
typedef int (*_AGS_GETROOMPROPERTY)(const char* property);
typedef void (*_AGS_SETVIEWPORT)(int x, int y);
typedef void (*_AGS_RELEASEVIEWPORT)();
typedef int (*_AGS_GETVIEWPORTX)();
typedef int (*_AGS_GETVIEWPORTY)();
typedef AGS_bool (*_AGS_ISGAMEPAUSED)();
typedef int (*_AGS_GETGRAPHICALVARIABLE)(const char* variableName);
typedef void (*_AGS_SETGRAPHICALVARIABLE)(const char* variableName, int value);
typedef void (*_AGS_DISABLEINTERFACE)();
typedef void (*_AGS_ENABLEINTERFACE)();
typedef int (*_AGS_ISINTERFACEENABLED)();
typedef int (*_AGS_SAID)(const char* text);
typedef int (*_AGS_GETTEXTWIDTH)(const char* text, AGS_FontType param2);
typedef int (*_AGS_GETTEXTHEIGHT)(const char* text, AGS_FontType param2, int width);
typedef void (*_AGS_GIVESCORE)(int points);
typedef void (*_AGS_UPDATEINVENTORY)();
typedef void (*_AGS_STOPDIALOG)();
typedef int (*_AGS_ARETHINGSOVERLAPPING)(int thing1, int thing2);
typedef void (*_AGS_SETVOICEMODE)(AGS_eVoiceMode param1);
typedef void (*_AGS_SETSKIPSPEECH)(int skipFlag);
typedef void (*_AGS_SETSPEECHSTYLE)(AGS_eSpeechStyle param1);
typedef void (*_AGS_SETTIMER)(int timerID, int timeout);
typedef AGS_bool (*_AGS_ISTIMEREXPIRED)(int timerID);
typedef void (*_AGS_SETMULTITASKINGMODE)(int mode);
typedef int (*_AGS_FLOATTOINT)(SCRIPT_FLOAT(value), AGS_RoundDirection param2);
typedef FLOAT_RETURN_TYPE (*_AGS_INTTOFLOAT)(int value);
typedef void (*_AGS_FADEIN)(int speed);
typedef void (*_AGS_FADEOUT)(int speed);
typedef void (*_AGS_CYCLEPALETTE)(int start, int end);
typedef void (*_AGS_SETPALRGB)(int slot, int r, int g, int b);
typedef void (*_AGS_UPDATEPALETTE)();
typedef void (*_AGS_TINTSCREEN)(int red, int green, int blue);
typedef void (*_AGS_SETAMBIENTTINT)(int red, int green, int blue, int saturation, int luminance);
typedef int (*_AGS_RANDOM)(int max);
typedef void (*_AGS_SETBACKGROUNDFRAME)(int frame);
typedef int (*_AGS_GETBACKGROUNDFRAME)();
typedef void (*_AGS_SHAKESCREEN)(int amount);
typedef void (*_AGS_SHAKESCREENBACKGROUND)(int delay, int amount, int length);
typedef void (*_AGS_SETSCREENTRANSITION)(AGS_TransitionStyle param1);
typedef void (*_AGS_SETNEXTSCREENTRANSITION)(AGS_TransitionStyle param1);
typedef void (*_AGS_SETFADECOLOR)(int red, int green, int blue);
typedef int (*_AGS_ISINTERACTIONAVAILABLE)(int x, int y, AGS_CursorMode param3);
typedef void (*_AGS_REMOVEWALKABLEAREA)(int area);
typedef void (*_AGS_RESTOREWALKABLEAREA)(int area);
typedef void (*_AGS_SETAREASCALING)(int area, int min, int max);
typedef void (*_AGS_DISABLEGROUNDLEVELAREAS)(int disableTints);
typedef void (*_AGS_ENABLEGROUNDLEVELAREAS)();
typedef void (*_AGS_SETWALKBEHINDBASE)(int area, int baseline);
typedef int (*_AGS_CDAUDIO)(AGS_eCDAudioFunction param1, int data);
typedef void (*_AGS_PLAYFLIC)(int flcNumber, int options);
typedef void (*_AGS_PLAYVIDEO)(const char* filename, AGS_VideoSkipStyle param2, int flags);
typedef void (*_AGS_PLAYMUSIC)(int musicNumber);
typedef void (*_AGS_PLAYMUSICQUEUED)(int musicNumber);
typedef void (*_AGS_PLAYSILENTMIDI)(int musicNumber);
typedef void (*_AGS_PLAYMP3FILE)(const char* filename);
typedef int (*_AGS_PLAYSOUND)(int soundNumber);
typedef void (*_AGS_PLAYSOUNDEX)(int soundNumber, int channel);
typedef void (*_AGS_PLAYAMBIENTSOUND)(int channel, int sound, int volume, int x, int y);
typedef void (*_AGS_STOPAMBIENTSOUND)(int channel);
typedef int (*_AGS_GETCURRENTMUSIC)();
typedef void (*_AGS_SETMUSICREPEAT)(int repeat);
typedef void (*_AGS_SETMUSICVOLUME)(int volume);
typedef void (*_AGS_SETSOUNDVOLUME)(int volume);
typedef void (*_AGS_SETMUSICMASTERVOLUME)(int volume);
typedef void (*_AGS_SETDIGITALMASTERVOLUME)(int volume);
typedef void (*_AGS_SEEKMODPATTERN)(int pattern);
typedef int (*_AGS_ISCHANNELPLAYING)(int channel);
typedef int (*_AGS_ISSOUNDPLAYING)();
typedef int (*_AGS_ISMUSICPLAYING)();
typedef int (*_AGS_GETMIDIPOSITION)();
typedef void (*_AGS_SEEKMIDIPOSITION)(int position);
typedef int (*_AGS_GETMP3POSMILLIS)();
typedef void (*_AGS_SEEKMP3POSMILLIS)(int offset);
typedef void (*_AGS_SETCHANNELVOLUME)(int channel, int volume);
typedef void (*_AGS_STOPCHANNEL)(int channel);
typedef void (*_AGS_STOPMUSIC)();
typedef int (*_AGS_ISVOXAVAILABLE)();
typedef void (*_AGS_SETSPEECHVOLUME)(int volume);
typedef int (*_AGS_ISMUSICVOXAVAILABLE)();
typedef int (*_AGS_SAVESCREENSHOT)(const char* filename);
typedef void (*_AGS_PAUSEGAME)();
typedef void (*_AGS_UNPAUSEGAME)();
typedef void (*_AGS_WAIT)(int waitLoops);
typedef int (*_AGS_WAITKEY)(int waitLoops);
typedef int (*_AGS_WAITMOUSEKEY)(int waitLoops);
typedef AGS_bool (*_AGS_ISKEYPRESSED)(AGS_eKeyCode param1);
typedef void (*_AGS_SETGLOBALINT)(int globalInt, int value);
typedef int (*_AGS_GETGLOBALINT)(int globalInt);
typedef void (*_AGS_FLIPSCREEN)(int way);
typedef void (*_AGS_SKIPUNTILCHARACTERSTOPS)(AGS_CHARID param1);
typedef void (*_AGS_STARTCUTSCENE)(AGS_CutsceneSkipType param1);
typedef int (*_AGS_ENDCUTSCENE)();
typedef void (*_AGS_CLAIMEVENT)();
typedef void (*_AGS_SETTEXTWINDOWGUI)(int gui);
typedef int (*_AGS_FINDGUIID)(const char* param1);

// ViewFrame method signatures
typedef AGS_bool (*_AGS_VIEWFRAME_GET_FLIPPED)(AGS_ViewFrame* self);
typedef int (*_AGS_VIEWFRAME_GET_FRAME)(AGS_ViewFrame* self);
typedef int (*_AGS_VIEWFRAME_GET_GRAPHIC)(AGS_ViewFrame* self);
typedef void (*_AGS_VIEWFRAME_SET_GRAPHIC)(AGS_ViewFrame* self, int new_value);
typedef AGS_AudioClip* (*_AGS_VIEWFRAME_GET_LINKEDAUDIO)(AGS_ViewFrame* self);
typedef void (*_AGS_VIEWFRAME_SET_LINKEDAUDIO)(AGS_ViewFrame* self, AGS_AudioClip* new_value);
typedef int (*_AGS_VIEWFRAME_GET_LOOP)(AGS_ViewFrame* self);
typedef int (*_AGS_VIEWFRAME_GET_SOUND)(AGS_ViewFrame* self);
typedef void (*_AGS_VIEWFRAME_SET_SOUND)(AGS_ViewFrame* self, int new_value);
typedef int (*_AGS_VIEWFRAME_GET_SPEED)(AGS_ViewFrame* self);
typedef int (*_AGS_VIEWFRAME_GET_VIEW)(AGS_ViewFrame* self);

// DrawingSurface method signatures
typedef void (*_AGS_DRAWINGSURFACE_CLEAR)(AGS_DrawingSurface* self, int colour);
typedef AGS_DrawingSurface* (*_AGS_DRAWINGSURFACE_CREATECOPY)(AGS_DrawingSurface* self);
typedef void (*_AGS_DRAWINGSURFACE_DRAWCIRCLE)(AGS_DrawingSurface* self, int x, int y, int radius);
typedef void (*_AGS_DRAWINGSURFACE_DRAWIMAGE)(AGS_DrawingSurface* self, int x, int y, int spriteSlot, int transparency, int width, int height);
typedef void (*_AGS_DRAWINGSURFACE_DRAWLINE)(AGS_DrawingSurface* self, int x1, int y1, int x2, int y2, int thickness);
typedef void (*_AGS_DRAWINGSURFACE_DRAWMESSAGEWRAPPED)(AGS_DrawingSurface* self, int x, int y, int width, AGS_FontType param4, int messageNumber);
typedef void (*_AGS_DRAWINGSURFACE_DRAWPIXEL)(AGS_DrawingSurface* self, int x, int y);
typedef void (*_AGS_DRAWINGSURFACE_DRAWRECTANGLE)(AGS_DrawingSurface* self, int x1, int y1, int x2, int y2);
typedef void (*_AGS_DRAWINGSURFACE_DRAWSTRING)(AGS_DrawingSurface* self, int x, int y, AGS_FontType param3, const char* text, ...);
typedef void (*_AGS_DRAWINGSURFACE_DRAWSTRINGWRAPPED)(AGS_DrawingSurface* self, int x, int y, int width, AGS_FontType param4, AGS_Alignment param5, const char* text);
typedef void (*_AGS_DRAWINGSURFACE_DRAWSURFACE)(AGS_DrawingSurface* self, AGS_DrawingSurface* surfaceToDraw, int transparency);
typedef void (*_AGS_DRAWINGSURFACE_DRAWTRIANGLE)(AGS_DrawingSurface* self, int x1, int y1, int x2, int y2, int x3, int y3);
typedef int (*_AGS_DRAWINGSURFACE_GETPIXEL)(AGS_DrawingSurface* self, int x, int y);
typedef void (*_AGS_DRAWINGSURFACE_RELEASE)(AGS_DrawingSurface* self);
typedef int (*_AGS_DRAWINGSURFACE_GET_DRAWINGCOLOR)(AGS_DrawingSurface* self);
typedef void (*_AGS_DRAWINGSURFACE_SET_DRAWINGCOLOR)(AGS_DrawingSurface* self, int new_value);
typedef int (*_AGS_DRAWINGSURFACE_GET_HEIGHT)(AGS_DrawingSurface* self);
typedef AGS_bool (*_AGS_DRAWINGSURFACE_GET_USEHIGHRESCOORDINATES)(AGS_DrawingSurface* self);
typedef void (*_AGS_DRAWINGSURFACE_SET_USEHIGHRESCOORDINATES)(AGS_DrawingSurface* self, AGS_bool new_value);
typedef int (*_AGS_DRAWINGSURFACE_GET_WIDTH)(AGS_DrawingSurface* self);

// Room method signatures
typedef const char* (*_AGS_ROOM_GETTEXTPROPERTY)(const char* property);
typedef AGS_DrawingSurface* (*_AGS_ROOM_GETDRAWINGSURFACEFORBACKGROUND)(int backgroundNumber);
typedef int (*_AGS_ROOM_GET_BOTTOMEDGE)();
typedef int (*_AGS_ROOM_GET_COLORDEPTH)();
typedef int (*_AGS_ROOM_GET_HEIGHT)();
typedef int (*_AGS_ROOM_GET_LEFTEDGE)();
typedef const char* (*_AGS_ROOM_GETI_MESSAGES)(int i);
typedef int (*_AGS_ROOM_GET_MUSICONLOAD)();
typedef int (*_AGS_ROOM_GET_OBJECTCOUNT)();
typedef int (*_AGS_ROOM_GET_RIGHTEDGE)();
typedef int (*_AGS_ROOM_GET_TOPEDGE)();
typedef int (*_AGS_ROOM_GET_WIDTH)();

// Game method signatures
typedef AGS_bool (*_AGS_GAME_CHANGETRANSLATION)(const char* newTranslationFileName);
typedef AGS_bool (*_AGS_GAME_DOONCEONLY)(const char* token);
typedef int (*_AGS_GAME_GETCOLORFROMRGB)(int red, int green, int blue);
typedef int (*_AGS_GAME_GETFRAMECOUNTFORLOOP)(int view, int loop);
typedef const char* (*_AGS_GAME_GETLOCATIONNAME)(int x, int y);
typedef int (*_AGS_GAME_GETLOOPCOUNTFORVIEW)(int view);
typedef int (*_AGS_GAME_GETMODPATTERN)();
typedef AGS_bool (*_AGS_GAME_GETRUNNEXTSETTINGFORLOOP)(int view, int loop);
typedef const char* (*_AGS_GAME_GETSAVESLOTDESCRIPTION)(int saveSlot);
typedef AGS_ViewFrame* (*_AGS_GAME_GETVIEWFRAME)(int view, int loop, int frame);
typedef const char* (*_AGS_GAME_INPUTBOX)(const char* prompt);
typedef AGS_bool (*_AGS_GAME_ISAUDIOPLAYING)(AGS_AudioType audioType);
typedef AGS_bool (*_AGS_GAME_SETSAVEGAMEDIRECTORY)(const char* directory);
typedef void (*_AGS_GAME_STOPAUDIO)(AGS_AudioType audioType);
typedef void (*_AGS_GAME_STOPSOUND)(AGS_bool includeAmbientSounds);
typedef int (*_AGS_GAME_GET_CHARACTERCOUNT)();
typedef int (*_AGS_GAME_GET_DIALOGCOUNT)();
typedef const char* (*_AGS_GAME_GET_FILENAME)();
typedef int (*_AGS_GAME_GET_FONTCOUNT)();
typedef const char* (*_AGS_GAME_GETI_GLOBALMESSAGES)(int i);
typedef const char* (*_AGS_GAME_GETI_GLOBALSTRINGS)(int i);
typedef void (*_AGS_GAME_SETI_GLOBALSTRINGS)(int i, const char* new_value);
typedef int (*_AGS_GAME_GET_GUICOUNT)();
typedef int (*_AGS_GAME_GET_IGNOREUSERINPUTAFTERTEXTTIMEOUTMS)();
typedef void (*_AGS_GAME_SET_IGNOREUSERINPUTAFTERTEXTTIMEOUTMS)(int new_value);
typedef AGS_bool (*_AGS_GAME_GET_INSKIPPABLECUTSCENE)();
typedef int (*_AGS_GAME_GET_INVENTORYITEMCOUNT)();
typedef int (*_AGS_GAME_GET_MINIMUMTEXTDISPLAYTIMEMS)();
typedef void (*_AGS_GAME_SET_MINIMUMTEXTDISPLAYTIMEMS)(int new_value);
typedef int (*_AGS_GAME_GET_MOUSECURSORCOUNT)();
typedef const char* (*_AGS_GAME_GET_NAME)();
typedef void (*_AGS_GAME_SET_NAME)(const char* new_value);
typedef AGS_FontType (*_AGS_GAME_GET_NORMALFONT)();
typedef void (*_AGS_GAME_SET_NORMALFONT)(AGS_FontType new_value);
typedef AGS_bool (*_AGS_GAME_GET_SKIPPINGCUTSCENE)();
typedef AGS_FontType (*_AGS_GAME_GET_SPEECHFONT)();
typedef void (*_AGS_GAME_SET_SPEECHFONT)(AGS_FontType new_value);
typedef int (*_AGS_GAME_GETI_SPRITEHEIGHT)(int i);
typedef int (*_AGS_GAME_GETI_SPRITEWIDTH)(int i);
typedef int (*_AGS_GAME_GET_TEXTREADINGSPEED)();
typedef void (*_AGS_GAME_SET_TEXTREADINGSPEED)(int new_value);
typedef const char* (*_AGS_GAME_GET_TRANSLATIONFILENAME)();
typedef AGS_bool (*_AGS_GAME_GET_USENATIVECOORDINATES)();
typedef int (*_AGS_GAME_GET_VIEWCOUNT)();

// Parser method signatures
typedef int (*_AGS_PARSER_FINDWORDID)(const char* wordToFind);
typedef void (*_AGS_PARSER_PARSETEXT)(const char* text);
typedef AGS_bool (*_AGS_PARSER_SAID)(const char* text);
typedef const char* (*_AGS_PARSER_SAIDUNKNOWNWORD)();

// Mouse method signatures
typedef void (*_AGS_MOUSE_CHANGEMODEGRAPHIC)(AGS_CursorMode param1, int slot);
typedef void (*_AGS_MOUSE_CHANGEMODEHOTSPOT)(AGS_CursorMode param1, int x, int y);
typedef void (*_AGS_MOUSE_CHANGEMODEVIEW)(AGS_CursorMode param1, int view);
typedef void (*_AGS_MOUSE_DISABLEMODE)(AGS_CursorMode param1);
typedef void (*_AGS_MOUSE_ENABLEMODE)(AGS_CursorMode param1);
typedef int (*_AGS_MOUSE_GETMODEGRAPHIC)(AGS_CursorMode param1);
typedef AGS_bool (*_AGS_MOUSE_ISBUTTONDOWN)(AGS_MouseButton param1);
typedef void (*_AGS_MOUSE_SAVECURSORUNTILITLEAVES)();
typedef void (*_AGS_MOUSE_SELECTNEXTMODE)();
typedef void (*_AGS_MOUSE_SETBOUNDS)(int left, int top, int right, int bottom);
typedef void (*_AGS_MOUSE_SETPOSITION)(int x, int y);
typedef void (*_AGS_MOUSE_UPDATE)();
typedef void (*_AGS_MOUSE_USEDEFAULTGRAPHIC)();
typedef void (*_AGS_MOUSE_USEMODEGRAPHIC)(AGS_CursorMode param1);
typedef AGS_CursorMode (*_AGS_MOUSE_GET_MODE)();
typedef void (*_AGS_MOUSE_SET_MODE)(AGS_CursorMode new_value);
typedef AGS_bool (*_AGS_MOUSE_GET_VISIBLE)();
typedef void (*_AGS_MOUSE_SET_VISIBLE)(AGS_bool new_value);

// File method signatures
typedef AGS_bool (*_AGS_FILE_DELETE)(const char* filename);
typedef AGS_bool (*_AGS_FILE_EXISTS)(const char* filename);
typedef AGS_File* (*_AGS_FILE_OPEN)(const char* filename, AGS_FileMode param2);
typedef void (*_AGS_FILE_CLOSE)(AGS_File* self);
typedef int (*_AGS_FILE_READINT)(AGS_File* self);
typedef int (*_AGS_FILE_READRAWCHAR)(AGS_File* self);
typedef int (*_AGS_FILE_READRAWINT)(AGS_File* self);
typedef const char* (*_AGS_FILE_READRAWLINEBACK)(AGS_File* self);
typedef const char* (*_AGS_FILE_READSTRINGBACK)(AGS_File* self);
typedef void (*_AGS_FILE_WRITEINT)(AGS_File* self, int value);
typedef void (*_AGS_FILE_WRITERAWCHAR)(AGS_File* self, int value);
typedef void (*_AGS_FILE_WRITERAWLINE)(AGS_File* self, const char* text);
typedef void (*_AGS_FILE_WRITESTRING)(AGS_File* self, const char* text);
typedef AGS_bool (*_AGS_FILE_GET_EOF)(AGS_File* self);
typedef AGS_bool (*_AGS_FILE_GET_ERROR)(AGS_File* self);

// InventoryItem method signatures
typedef AGS_InventoryItem* (*_AGS_INVENTORYITEM_GETATSCREENXY)(int x, int y);
typedef int (*_AGS_INVENTORYITEM_GETPROPERTY)(AGS_InventoryItem* self, const char* property);
typedef const char* (*_AGS_INVENTORYITEM_GETTEXTPROPERTY)(AGS_InventoryItem* self, const char* property);
typedef int (*_AGS_INVENTORYITEM_ISINTERACTIONAVAILABLE)(AGS_InventoryItem* self, AGS_CursorMode param1);
typedef void (*_AGS_INVENTORYITEM_RUNINTERACTION)(AGS_InventoryItem* self, AGS_CursorMode param1);
typedef int (*_AGS_INVENTORYITEM_GET_CURSORGRAPHIC)(AGS_InventoryItem* self);
typedef void (*_AGS_INVENTORYITEM_SET_CURSORGRAPHIC)(AGS_InventoryItem* self, int new_value);
typedef int (*_AGS_INVENTORYITEM_GET_GRAPHIC)(AGS_InventoryItem* self);
typedef void (*_AGS_INVENTORYITEM_SET_GRAPHIC)(AGS_InventoryItem* self, int new_value);
typedef int (*_AGS_INVENTORYITEM_GET_ID)(AGS_InventoryItem* self);
typedef const char* (*_AGS_INVENTORYITEM_GET_NAME)(AGS_InventoryItem* self);
typedef void (*_AGS_INVENTORYITEM_SET_NAME)(AGS_InventoryItem* self, const char* new_value);

// Overlay method signatures
typedef AGS_Overlay* (*_AGS_OVERLAY_CREATEGRAPHICAL)(int x, int y, int slot, AGS_bool transparent);
typedef AGS_Overlay* (*_AGS_OVERLAY_CREATETEXTUAL)(int x, int y, int width, AGS_FontType param4, int colour, const char* text, ...);
typedef void (*_AGS_OVERLAY_SETTEXT)(AGS_Overlay* self, int width, AGS_FontType param2, int colour, const char* text, ...);
typedef void (*_AGS_OVERLAY_REMOVE)(AGS_Overlay* self);
typedef AGS_bool (*_AGS_OVERLAY_GET_VALID)(AGS_Overlay* self);
typedef int (*_AGS_OVERLAY_GET_X)(AGS_Overlay* self);
typedef void (*_AGS_OVERLAY_SET_X)(AGS_Overlay* self, int new_value);
typedef int (*_AGS_OVERLAY_GET_Y)(AGS_Overlay* self);
typedef void (*_AGS_OVERLAY_SET_Y)(AGS_Overlay* self, int new_value);

// DynamicSprite method signatures
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATE)(int width, int height, AGS_bool hasAlphaChannel);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMBACKGROUND)(int frame, int x, int y, int width, int height);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMDRAWINGSURFACE)(AGS_DrawingSurface* surface, int x, int y, int width, int height);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMEXISTINGSPRITE)(int slot, AGS_bool preserveAlphaChannel);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMFILE)(const char* filename);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMSAVEGAME)(int slot, int width, int height);
typedef AGS_DynamicSprite* (*_AGS_DYNAMICSPRITE_CREATEFROMSCREENSHOT)(int width, int height);
typedef void (*_AGS_DYNAMICSPRITE_CHANGECANVASSIZE)(AGS_DynamicSprite* self, int width, int height, int x, int y);
typedef void (*_AGS_DYNAMICSPRITE_COPYTRANSPARENCYMASK)(AGS_DynamicSprite* self, int fromSpriteSlot);
typedef void (*_AGS_DYNAMICSPRITE_CROP)(AGS_DynamicSprite* self, int x, int y, int width, int height);
typedef void (*_AGS_DYNAMICSPRITE_DELETE)(AGS_DynamicSprite* self);
typedef void (*_AGS_DYNAMICSPRITE_FLIP)(AGS_DynamicSprite* self, AGS_eFlipDirection param1);
typedef AGS_DrawingSurface* (*_AGS_DYNAMICSPRITE_GETDRAWINGSURFACE)(AGS_DynamicSprite* self);
typedef void (*_AGS_DYNAMICSPRITE_RESIZE)(AGS_DynamicSprite* self, int width, int height);
typedef void (*_AGS_DYNAMICSPRITE_ROTATE)(AGS_DynamicSprite* self, int angle, int width, int height);
typedef int (*_AGS_DYNAMICSPRITE_SAVETOFILE)(AGS_DynamicSprite* self, const char* filename);
typedef void (*_AGS_DYNAMICSPRITE_TINT)(AGS_DynamicSprite* self, int red, int green, int blue, int saturation, int luminance);
typedef int (*_AGS_DYNAMICSPRITE_GET_COLORDEPTH)(AGS_DynamicSprite* self);
typedef int (*_AGS_DYNAMICSPRITE_GET_GRAPHIC)(AGS_DynamicSprite* self);
typedef int (*_AGS_DYNAMICSPRITE_GET_HEIGHT)(AGS_DynamicSprite* self);
typedef int (*_AGS_DYNAMICSPRITE_GET_WIDTH)(AGS_DynamicSprite* self);

// GUIControl method signatures
typedef void (*_AGS_GUICONTROL_BRINGTOFRONT)(AGS_GUIControl* self);
typedef AGS_GUIControl* (*_AGS_GUICONTROL_GETATSCREENXY)(int x, int y);
typedef void (*_AGS_GUICONTROL_SENDTOBACK)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SETPOSITION)(AGS_GUIControl* self, int x, int y);
typedef void (*_AGS_GUICONTROL_SETSIZE)(AGS_GUIControl* self, int width, int height);
typedef AGS_Button* (*_AGS_GUICONTROL_GET_ASBUTTON)(AGS_GUIControl* self);
typedef AGS_InvWindow* (*_AGS_GUICONTROL_GET_ASINVWINDOW)(AGS_GUIControl* self);
typedef AGS_Label* (*_AGS_GUICONTROL_GET_ASLABEL)(AGS_GUIControl* self);
typedef AGS_ListBox* (*_AGS_GUICONTROL_GET_ASLISTBOX)(AGS_GUIControl* self);
typedef AGS_Slider* (*_AGS_GUICONTROL_GET_ASSLIDER)(AGS_GUIControl* self);
typedef AGS_TextBox* (*_AGS_GUICONTROL_GET_ASTEXTBOX)(AGS_GUIControl* self);
typedef AGS_bool (*_AGS_GUICONTROL_GET_CLICKABLE)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_CLICKABLE)(AGS_GUIControl* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_GUICONTROL_GET_ENABLED)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_ENABLED)(AGS_GUIControl* self, AGS_bool new_value);
typedef int (*_AGS_GUICONTROL_GET_HEIGHT)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_HEIGHT)(AGS_GUIControl* self, int new_value);
typedef int (*_AGS_GUICONTROL_GET_ID)(AGS_GUIControl* self);
typedef AGS_GUI* (*_AGS_GUICONTROL_GET_OWNINGGUI)(AGS_GUIControl* self);
typedef AGS_bool (*_AGS_GUICONTROL_GET_VISIBLE)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_VISIBLE)(AGS_GUIControl* self, AGS_bool new_value);
typedef int (*_AGS_GUICONTROL_GET_WIDTH)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_WIDTH)(AGS_GUIControl* self, int new_value);
typedef int (*_AGS_GUICONTROL_GET_X)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_X)(AGS_GUIControl* self, int new_value);
typedef int (*_AGS_GUICONTROL_GET_Y)(AGS_GUIControl* self);
typedef void (*_AGS_GUICONTROL_SET_Y)(AGS_GUIControl* self, int new_value);

// Label method signatures
typedef AGS_FontType (*_AGS_LABEL_GET_FONT)(AGS_Label* self);
typedef void (*_AGS_LABEL_SET_FONT)(AGS_Label* self, AGS_FontType new_value);
typedef const char* (*_AGS_LABEL_GET_TEXT)(AGS_Label* self);
typedef void (*_AGS_LABEL_SET_TEXT)(AGS_Label* self, const char* new_value);
typedef int (*_AGS_LABEL_GET_TEXTCOLOR)(AGS_Label* self);
typedef void (*_AGS_LABEL_SET_TEXTCOLOR)(AGS_Label* self, int new_value);

// Button method signatures
typedef void (*_AGS_BUTTON_ANIMATE)(AGS_Button* self, int view, int loop, int delay, AGS_RepeatStyle param4);
typedef AGS_bool (*_AGS_BUTTON_GET_CLIPIMAGE)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_CLIPIMAGE)(AGS_Button* self, AGS_bool new_value);
typedef AGS_FontType (*_AGS_BUTTON_GET_FONT)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_FONT)(AGS_Button* self, AGS_FontType new_value);
typedef int (*_AGS_BUTTON_GET_GRAPHIC)(AGS_Button* self);
typedef int (*_AGS_BUTTON_GET_MOUSEOVERGRAPHIC)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_MOUSEOVERGRAPHIC)(AGS_Button* self, int new_value);
typedef int (*_AGS_BUTTON_GET_NORMALGRAPHIC)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_NORMALGRAPHIC)(AGS_Button* self, int new_value);
typedef int (*_AGS_BUTTON_GET_PUSHEDGRAPHIC)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_PUSHEDGRAPHIC)(AGS_Button* self, int new_value);
typedef int (*_AGS_BUTTON_GET_TEXTCOLOR)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_TEXTCOLOR)(AGS_Button* self, int new_value);
typedef const char* (*_AGS_BUTTON_GET_TEXT)(AGS_Button* self);
typedef void (*_AGS_BUTTON_SET_TEXT)(AGS_Button* self, const char* new_value);

// Slider method signatures
typedef int (*_AGS_SLIDER_GET_BACKGROUNDGRAPHIC)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_BACKGROUNDGRAPHIC)(AGS_Slider* self, int new_value);
typedef int (*_AGS_SLIDER_GET_HANDLEGRAPHIC)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_HANDLEGRAPHIC)(AGS_Slider* self, int new_value);
typedef int (*_AGS_SLIDER_GET_HANDLEOFFSET)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_HANDLEOFFSET)(AGS_Slider* self, int new_value);
typedef int (*_AGS_SLIDER_GET_MAX)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_MAX)(AGS_Slider* self, int new_value);
typedef int (*_AGS_SLIDER_GET_MIN)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_MIN)(AGS_Slider* self, int new_value);
typedef int (*_AGS_SLIDER_GET_VALUE)(AGS_Slider* self);
typedef void (*_AGS_SLIDER_SET_VALUE)(AGS_Slider* self, int new_value);

// TextBox method signatures
typedef AGS_FontType (*_AGS_TEXTBOX_GET_FONT)(AGS_TextBox* self);
typedef void (*_AGS_TEXTBOX_SET_FONT)(AGS_TextBox* self, AGS_FontType new_value);
typedef const char* (*_AGS_TEXTBOX_GET_TEXT)(AGS_TextBox* self);
typedef void (*_AGS_TEXTBOX_SET_TEXT)(AGS_TextBox* self, const char* new_value);
typedef int (*_AGS_TEXTBOX_GET_TEXTCOLOR)(AGS_TextBox* self);
typedef void (*_AGS_TEXTBOX_SET_TEXTCOLOR)(AGS_TextBox* self, int new_value);

// InvWindow method signatures
typedef void (*_AGS_INVWINDOW_SCROLLDOWN)(AGS_InvWindow* self);
typedef void (*_AGS_INVWINDOW_SCROLLUP)(AGS_InvWindow* self);
typedef AGS_Character* (*_AGS_INVWINDOW_GET_CHARACTERTOUSE)(AGS_InvWindow* self);
typedef void (*_AGS_INVWINDOW_SET_CHARACTERTOUSE)(AGS_InvWindow* self, AGS_Character* new_value);
typedef AGS_InventoryItem* (*_AGS_INVWINDOW_GETI_ITEMATINDEX)(AGS_InvWindow* self, int i);
typedef int (*_AGS_INVWINDOW_GET_ITEMCOUNT)(AGS_InvWindow* self);
typedef int (*_AGS_INVWINDOW_GET_ITEMHEIGHT)(AGS_InvWindow* self);
typedef void (*_AGS_INVWINDOW_SET_ITEMHEIGHT)(AGS_InvWindow* self, int new_value);
typedef int (*_AGS_INVWINDOW_GET_ITEMWIDTH)(AGS_InvWindow* self);
typedef void (*_AGS_INVWINDOW_SET_ITEMWIDTH)(AGS_InvWindow* self, int new_value);
typedef int (*_AGS_INVWINDOW_GET_TOPITEM)(AGS_InvWindow* self);
typedef void (*_AGS_INVWINDOW_SET_TOPITEM)(AGS_InvWindow* self, int new_value);
typedef int (*_AGS_INVWINDOW_GET_ITEMSPERROW)(AGS_InvWindow* self);
typedef int (*_AGS_INVWINDOW_GET_ROWCOUNT)(AGS_InvWindow* self);

// ListBox method signatures
typedef AGS_bool (*_AGS_LISTBOX_ADDITEM)(AGS_ListBox* self, const char* text);
typedef void (*_AGS_LISTBOX_CLEAR)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_FILLDIRLIST)(AGS_ListBox* self, const char* fileMask);
typedef int (*_AGS_LISTBOX_FILLSAVEGAMELIST)(AGS_ListBox* self);
typedef int (*_AGS_LISTBOX_GETITEMATLOCATION)(AGS_ListBox* self, int x, int y);
typedef AGS_bool (*_AGS_LISTBOX_INSERTITEMAT)(AGS_ListBox* self, int listIndex, const char* text);
typedef void (*_AGS_LISTBOX_REMOVEITEM)(AGS_ListBox* self, int listIndex);
typedef void (*_AGS_LISTBOX_SCROLLDOWN)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SCROLLUP)(AGS_ListBox* self);
typedef AGS_FontType (*_AGS_LISTBOX_GET_FONT)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SET_FONT)(AGS_ListBox* self, AGS_FontType new_value);
typedef AGS_bool (*_AGS_LISTBOX_GET_HIDEBORDER)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SET_HIDEBORDER)(AGS_ListBox* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_LISTBOX_GET_HIDESCROLLARROWS)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SET_HIDESCROLLARROWS)(AGS_ListBox* self, AGS_bool new_value);
typedef int (*_AGS_LISTBOX_GET_ITEMCOUNT)(AGS_ListBox* self);
typedef const char* (*_AGS_LISTBOX_GETI_ITEMS)(AGS_ListBox* self, int i);
typedef void (*_AGS_LISTBOX_SETI_ITEMS)(AGS_ListBox* self, int i, const char* new_value);
typedef int (*_AGS_LISTBOX_GET_ROWCOUNT)(AGS_ListBox* self);
typedef int (*_AGS_LISTBOX_GETI_SAVEGAMESLOTS)(AGS_ListBox* self, int i);
typedef int (*_AGS_LISTBOX_GET_SELECTEDINDEX)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SET_SELECTEDINDEX)(AGS_ListBox* self, int new_value);
typedef int (*_AGS_LISTBOX_GET_TOPITEM)(AGS_ListBox* self);
typedef void (*_AGS_LISTBOX_SET_TOPITEM)(AGS_ListBox* self, int new_value);

// GUI method signatures
typedef void (*_AGS_GUI_CENTRE)(AGS_GUI* self);
typedef AGS_GUI* (*_AGS_GUI_GETATSCREENXY)(int x, int y);
typedef void (*_AGS_GUI_SETPOSITION)(AGS_GUI* self, int x, int y);
typedef void (*_AGS_GUI_SETSIZE)(AGS_GUI* self, int width, int height);
typedef int (*_AGS_GUI_GET_BACKGROUNDGRAPHIC)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_BACKGROUNDGRAPHIC)(AGS_GUI* self, int new_value);
typedef AGS_bool (*_AGS_GUI_GET_CLICKABLE)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_CLICKABLE)(AGS_GUI* self, AGS_bool new_value);
typedef AGS_GUIControl* (*_AGS_GUI_GETI_CONTROLS)(AGS_GUI* self, int i);
typedef int (*_AGS_GUI_GET_CONTROLCOUNT)(AGS_GUI* self);
typedef int (*_AGS_GUI_GET_HEIGHT)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_HEIGHT)(AGS_GUI* self, int new_value);
typedef int (*_AGS_GUI_GET_ID)(AGS_GUI* self);
typedef int (*_AGS_GUI_GET_TRANSPARENCY)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_TRANSPARENCY)(AGS_GUI* self, int new_value);
typedef AGS_bool (*_AGS_GUI_GET_VISIBLE)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_VISIBLE)(AGS_GUI* self, AGS_bool new_value);
typedef int (*_AGS_GUI_GET_WIDTH)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_WIDTH)(AGS_GUI* self, int new_value);
typedef int (*_AGS_GUI_GET_X)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_X)(AGS_GUI* self, int new_value);
typedef int (*_AGS_GUI_GET_Y)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_Y)(AGS_GUI* self, int new_value);
typedef int (*_AGS_GUI_GET_ZORDER)(AGS_GUI* self);
typedef void (*_AGS_GUI_SET_ZORDER)(AGS_GUI* self, int new_value);

// Hotspot method signatures
typedef AGS_Hotspot* (*_AGS_HOTSPOT_GETATSCREENXY)(int x, int y);
typedef int (*_AGS_HOTSPOT_GETPROPERTY)(AGS_Hotspot* self, const char* property);
typedef const char* (*_AGS_HOTSPOT_GETTEXTPROPERTY)(AGS_Hotspot* self, const char* property);
typedef void (*_AGS_HOTSPOT_RUNINTERACTION)(AGS_Hotspot* self, AGS_CursorMode param1);
typedef AGS_bool (*_AGS_HOTSPOT_GET_ENABLED)(AGS_Hotspot* self);
typedef void (*_AGS_HOTSPOT_SET_ENABLED)(AGS_Hotspot* self, AGS_bool new_value);
typedef int (*_AGS_HOTSPOT_GET_ID)(AGS_Hotspot* self);
typedef const char* (*_AGS_HOTSPOT_GET_NAME)(AGS_Hotspot* self);
typedef int (*_AGS_HOTSPOT_GET_WALKTOX)(AGS_Hotspot* self);
typedef int (*_AGS_HOTSPOT_GET_WALKTOY)(AGS_Hotspot* self);

// Region method signatures
typedef AGS_Region* (*_AGS_REGION_GETATROOMXY)(int x, int y);
typedef void (*_AGS_REGION_RUNINTERACTION)(AGS_Region* self, int event);
typedef void (*_AGS_REGION_TINT)(AGS_Region* self, int red, int green, int blue, int amount);
typedef AGS_bool (*_AGS_REGION_GET_ENABLED)(AGS_Region* self);
typedef void (*_AGS_REGION_SET_ENABLED)(AGS_Region* self, AGS_bool new_value);
typedef int (*_AGS_REGION_GET_ID)(AGS_Region* self);
typedef int (*_AGS_REGION_GET_LIGHTLEVEL)(AGS_Region* self);
typedef void (*_AGS_REGION_SET_LIGHTLEVEL)(AGS_Region* self, int new_value);
typedef AGS_bool (*_AGS_REGION_GET_TINTENABLED)(AGS_Region* self);
typedef int (*_AGS_REGION_GET_TINTBLUE)(AGS_Region* self);
typedef int (*_AGS_REGION_GET_TINTGREEN)(AGS_Region* self);
typedef int (*_AGS_REGION_GET_TINTRED)(AGS_Region* self);
typedef int (*_AGS_REGION_GET_TINTSATURATION)(AGS_Region* self);

// Dialog method signatures
typedef int (*_AGS_DIALOG_DISPLAYOPTIONS)(AGS_Dialog* self, AGS_DialogOptionSayStyle param1);
typedef AGS_DialogOptionState (*_AGS_DIALOG_GETOPTIONSTATE)(AGS_Dialog* self, int option);
typedef const char* (*_AGS_DIALOG_GETOPTIONTEXT)(AGS_Dialog* self, int option);
typedef AGS_bool (*_AGS_DIALOG_HASOPTIONBEENCHOSEN)(AGS_Dialog* self, int option);
typedef void (*_AGS_DIALOG_SETOPTIONSTATE)(AGS_Dialog* self, int option, AGS_DialogOptionState param2);
typedef void (*_AGS_DIALOG_START)(AGS_Dialog* self);
typedef int (*_AGS_DIALOG_GET_ID)(AGS_Dialog* self);
typedef int (*_AGS_DIALOG_GET_OPTIONCOUNT)(AGS_Dialog* self);

// DateTime method signatures
typedef AGS_DateTime* (*_AGS_DATETIME_GET_NOW)();
typedef int (*_AGS_DATETIME_GET_YEAR)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_MONTH)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_DAYOFMONTH)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_HOUR)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_MINUTE)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_SECOND)(AGS_DateTime* self);
typedef int (*_AGS_DATETIME_GET_RAWTIME)(AGS_DateTime* self);

// AudioChannel method signatures
typedef void (*_AGS_AUDIOCHANNEL_SEEK)(AGS_AudioChannel* self, int position);
typedef void (*_AGS_AUDIOCHANNEL_SETROOMLOCATION)(AGS_AudioChannel* self, int x, int y);
typedef void (*_AGS_AUDIOCHANNEL_STOP)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_ID)(AGS_AudioChannel* self);
typedef AGS_bool (*_AGS_AUDIOCHANNEL_GET_ISPLAYING)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_LENGTHMS)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_PANNING)(AGS_AudioChannel* self);
typedef void (*_AGS_AUDIOCHANNEL_SET_PANNING)(AGS_AudioChannel* self, int new_value);
typedef AGS_AudioClip* (*_AGS_AUDIOCHANNEL_GET_PLAYINGCLIP)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_POSITION)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_POSITIONMS)(AGS_AudioChannel* self);
typedef int (*_AGS_AUDIOCHANNEL_GET_VOLUME)(AGS_AudioChannel* self);
typedef void (*_AGS_AUDIOCHANNEL_SET_VOLUME)(AGS_AudioChannel* self, int new_value);

// AudioClip method signatures
typedef AGS_AudioChannel* (*_AGS_AUDIOCLIP_PLAY)(AGS_AudioClip* self, AGS_AudioPriority param1, AGS_RepeatStyle param2);
typedef AGS_AudioChannel* (*_AGS_AUDIOCLIP_PLAYFROM)(AGS_AudioClip* self, int position, AGS_AudioPriority param2, AGS_RepeatStyle param3);
typedef AGS_AudioChannel* (*_AGS_AUDIOCLIP_PLAYQUEUED)(AGS_AudioClip* self, AGS_AudioPriority param1, AGS_RepeatStyle param2);
typedef void (*_AGS_AUDIOCLIP_STOP)(AGS_AudioClip* self);
typedef AGS_AudioFileType (*_AGS_AUDIOCLIP_GET_FILETYPE)(AGS_AudioClip* self);
typedef AGS_bool (*_AGS_AUDIOCLIP_GET_ISAVAILABLE)(AGS_AudioClip* self);
typedef AGS_AudioType (*_AGS_AUDIOCLIP_GET_TYPE)(AGS_AudioClip* self);

// System method signatures
typedef AGS_bool (*_AGS_SYSTEM_GET_CAPSLOCK)();
typedef AGS_AudioChannel* (*_AGS_SYSTEM_GETI_AUDIOCHANNELS)(int i);
typedef int (*_AGS_SYSTEM_GET_AUDIOCHANNELCOUNT)();
typedef int (*_AGS_SYSTEM_GET_COLORDEPTH)();
typedef int (*_AGS_SYSTEM_GET_GAMMA)();
typedef void (*_AGS_SYSTEM_SET_GAMMA)(int new_value);
typedef AGS_bool (*_AGS_SYSTEM_GET_HARDWAREACCELERATION)();
typedef AGS_bool (*_AGS_SYSTEM_GET_NUMLOCK)();
typedef AGS_eOperatingSystem (*_AGS_SYSTEM_GET_OPERATINGSYSTEM)();
typedef int (*_AGS_SYSTEM_GET_SCREENHEIGHT)();
typedef int (*_AGS_SYSTEM_GET_SCREENWIDTH)();
typedef AGS_bool (*_AGS_SYSTEM_GET_SCROLLLOCK)();
typedef AGS_bool (*_AGS_SYSTEM_GET_SUPPORTSGAMMACONTROL)();
typedef const char* (*_AGS_SYSTEM_GET_VERSION)();
typedef int (*_AGS_SYSTEM_GET_VIEWPORTHEIGHT)();
typedef int (*_AGS_SYSTEM_GET_VIEWPORTWIDTH)();
typedef int (*_AGS_SYSTEM_GET_VOLUME)();
typedef void (*_AGS_SYSTEM_SET_VOLUME)(int new_value);
typedef AGS_bool (*_AGS_SYSTEM_GET_VSYNC)();
typedef void (*_AGS_SYSTEM_SET_VSYNC)(AGS_bool new_value);
typedef AGS_bool (*_AGS_SYSTEM_GET_WINDOWED)();

// Object method signatures
typedef int (*_AGS_OBJECT_ANIMATE)(AGS_Object* self, int loop, int delay, AGS_RepeatStyle param3, AGS_BlockingStyle param4, AGS_Direction param5);
typedef AGS_Object* (*_AGS_OBJECT_GETATSCREENXY)(int x, int y);
typedef int (*_AGS_OBJECT_GETPROPERTY)(AGS_Object* self, const char* property);
typedef const char* (*_AGS_OBJECT_GETTEXTPROPERTY)(AGS_Object* self, const char* property);
typedef AGS_bool (*_AGS_OBJECT_ISCOLLIDINGWITHOBJECT)(AGS_Object* self, AGS_Object* param1);
typedef int (*_AGS_OBJECT_MERGEINTOBACKGROUND)(AGS_Object* self);
typedef int (*_AGS_OBJECT_MOVE)(AGS_Object* self, int x, int y, int speed, AGS_BlockingStyle param4, AGS_WalkWhere param5);
typedef int (*_AGS_OBJECT_REMOVETINT)(AGS_Object* self);
typedef int (*_AGS_OBJECT_RUNINTERACTION)(AGS_Object* self, AGS_CursorMode param1);
typedef int (*_AGS_OBJECT_SETPOSITION)(AGS_Object* self, int x, int y);
typedef int (*_AGS_OBJECT_SETVIEW)(AGS_Object* self, int view, int loop, int frame);
typedef int (*_AGS_OBJECT_STOPANIMATING)(AGS_Object* self);
typedef int (*_AGS_OBJECT_STOPMOVING)(AGS_Object* self);
typedef int (*_AGS_OBJECT_TINT)(AGS_Object* self, int red, int green, int blue, int saturation, int luminance);
typedef AGS_bool (*_AGS_OBJECT_GET_ANIMATING)(AGS_Object* self);
typedef int (*_AGS_OBJECT_GET_BASELINE)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_BASELINE)(AGS_Object* self, int new_value);
typedef int (*_AGS_OBJECT_GET_BLOCKINGHEIGHT)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_BLOCKINGHEIGHT)(AGS_Object* self, int new_value);
typedef int (*_AGS_OBJECT_GET_BLOCKINGWIDTH)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_BLOCKINGWIDTH)(AGS_Object* self, int new_value);
typedef AGS_bool (*_AGS_OBJECT_GET_CLICKABLE)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_CLICKABLE)(AGS_Object* self, AGS_bool new_value);
typedef int (*_AGS_OBJECT_GET_FRAME)(AGS_Object* self);
typedef int (*_AGS_OBJECT_GET_GRAPHIC)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_GRAPHIC)(AGS_Object* self, int new_value);
typedef int (*_AGS_OBJECT_GET_ID)(AGS_Object* self);
typedef AGS_bool (*_AGS_OBJECT_GET_IGNORESCALING)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_IGNORESCALING)(AGS_Object* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_OBJECT_GET_IGNOREWALKBEHINDS)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_IGNOREWALKBEHINDS)(AGS_Object* self, AGS_bool new_value);
typedef int (*_AGS_OBJECT_GET_LOOP)(AGS_Object* self);
typedef AGS_bool (*_AGS_OBJECT_GET_MOVING)(AGS_Object* self);
typedef const char* (*_AGS_OBJECT_GET_NAME)(AGS_Object* self);
typedef AGS_bool (*_AGS_OBJECT_GET_SOLID)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_SOLID)(AGS_Object* self, AGS_bool new_value);
typedef int (*_AGS_OBJECT_GET_TRANSPARENCY)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_TRANSPARENCY)(AGS_Object* self, int new_value);
typedef int (*_AGS_OBJECT_GET_VIEW)(AGS_Object* self);
typedef AGS_bool (*_AGS_OBJECT_GET_VISIBLE)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_VISIBLE)(AGS_Object* self, AGS_bool new_value);
typedef int (*_AGS_OBJECT_GET_X)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_X)(AGS_Object* self, int new_value);
typedef int (*_AGS_OBJECT_GET_Y)(AGS_Object* self);
typedef void (*_AGS_OBJECT_SET_Y)(AGS_Object* self, int new_value);

// Character method signatures
typedef int (*_AGS_CHARACTER_ADDINVENTORY)(AGS_Character* self, AGS_InventoryItem* item, int addAtIndex);
typedef int (*_AGS_CHARACTER_ADDWAYPOINT)(AGS_Character* self, int x, int y);
typedef int (*_AGS_CHARACTER_ANIMATE)(AGS_Character* self, int loop, int delay, AGS_RepeatStyle param3, AGS_BlockingStyle param4, AGS_Direction param5);
typedef int (*_AGS_CHARACTER_CHANGEROOM)(AGS_Character* self, int room, int x, int y);
typedef int (*_AGS_CHARACTER_CHANGEROOMAUTOPOSITION)(AGS_Character* self, int room, int position);
typedef int (*_AGS_CHARACTER_CHANGEVIEW)(AGS_Character* self, int view);
typedef int (*_AGS_CHARACTER_FACECHARACTER)(AGS_Character* self, AGS_Character* param1, AGS_BlockingStyle param2);
typedef int (*_AGS_CHARACTER_FACELOCATION)(AGS_Character* self, int x, int y, AGS_BlockingStyle param3);
typedef int (*_AGS_CHARACTER_FACEOBJECT)(AGS_Character* self, AGS_Object* param1, AGS_BlockingStyle param2);
typedef int (*_AGS_CHARACTER_FOLLOWCHARACTER)(AGS_Character* self, AGS_Character* param1, int dist, int eagerness);
typedef AGS_Character* (*_AGS_CHARACTER_GETATSCREENXY)(int x, int y);
typedef int (*_AGS_CHARACTER_GETPROPERTY)(AGS_Character* self, const char* property);
typedef const char* (*_AGS_CHARACTER_GETTEXTPROPERTY)(AGS_Character* self, const char* property);
typedef AGS_bool (*_AGS_CHARACTER_HASINVENTORY)(AGS_Character* self, AGS_InventoryItem* item);
typedef int (*_AGS_CHARACTER_ISCOLLIDINGWITHCHAR)(AGS_Character* self, AGS_Character* param1);
typedef int (*_AGS_CHARACTER_ISCOLLIDINGWITHOBJECT)(AGS_Character* self, AGS_Object* param1);
typedef int (*_AGS_CHARACTER_LOCKVIEW)(AGS_Character* self, int view);
typedef int (*_AGS_CHARACTER_LOCKVIEWALIGNED)(AGS_Character* self, int view, int loop, AGS_Alignment param3);
typedef int (*_AGS_CHARACTER_LOCKVIEWFRAME)(AGS_Character* self, int view, int loop, int frame);
typedef int (*_AGS_CHARACTER_LOCKVIEWOFFSET)(AGS_Character* self, int view, int xOffset, int yOffset);
typedef int (*_AGS_CHARACTER_LOSEINVENTORY)(AGS_Character* self, AGS_InventoryItem* item);
typedef int (*_AGS_CHARACTER_MOVE)(AGS_Character* self, int x, int y, AGS_BlockingStyle param3, AGS_WalkWhere param4);
typedef int (*_AGS_CHARACTER_PLACEONWALKABLEAREA)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_REMOVETINT)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_RUNINTERACTION)(AGS_Character* self, AGS_CursorMode param1);
typedef int (*_AGS_CHARACTER_SAY)(AGS_Character* self, const char* message, ...);
typedef int (*_AGS_CHARACTER_SAYAT)(AGS_Character* self, int x, int y, int width, const char* message);
typedef AGS_Overlay* (*_AGS_CHARACTER_SAYBACKGROUND)(AGS_Character* self, const char* message);
typedef int (*_AGS_CHARACTER_SETASPLAYER)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_SETIDLEVIEW)(AGS_Character* self, int view, int delay);
typedef int (*_AGS_CHARACTER_SETWALKSPEED)(AGS_Character* self, int x, int y);
typedef int (*_AGS_CHARACTER_STOPMOVING)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_THINK)(AGS_Character* self, const char* message, ...);
typedef void (*_AGS_CHARACTER_TINT)(AGS_Character* self, int red, int green, int blue, int saturation, int luminance);
typedef int (*_AGS_CHARACTER_UNLOCKVIEW)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_WALK)(AGS_Character* self, int x, int y, AGS_BlockingStyle param3, AGS_WalkWhere param4);
typedef int (*_AGS_CHARACTER_WALKSTRAIGHT)(AGS_Character* self, int x, int y, AGS_BlockingStyle param3);
typedef AGS_InventoryItem* (*_AGS_CHARACTER_GET_ACTIVEINVENTORY)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_ACTIVEINVENTORY)(AGS_Character* self, AGS_InventoryItem* new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_ANIMATING)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_ANIMATIONSPEED)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_ANIMATIONSPEED)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_BASELINE)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BASELINE)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_BLINKINTERVAL)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BLINKINTERVAL)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_BLINKVIEW)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BLINKVIEW)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_BLINKWHILETHINKING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BLINKWHILETHINKING)(AGS_Character* self, AGS_bool new_value);
typedef int (*_AGS_CHARACTER_GET_BLOCKINGHEIGHT)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BLOCKINGHEIGHT)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_BLOCKINGWIDTH)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_BLOCKINGWIDTH)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_CLICKABLE)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_CLICKABLE)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_DIAGONALLOOPS)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_DIAGONALLOOPS)(AGS_Character* self, AGS_bool new_value);
typedef int (*_AGS_CHARACTER_GET_FRAME)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_FRAME)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_HASEXPLICITTINT)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_ID)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_IDLEVIEW)(AGS_Character* self);
typedef AGS_bool (*_AGS_CHARACTER_GET_IGNORELIGHTING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_IGNORELIGHTING)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_IGNORESCALING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_IGNORESCALING)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_IGNOREWALKBEHINDS)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_IGNOREWALKBEHINDS)(AGS_Character* self, AGS_bool new_value);
typedef int (*_AGS_CHARACTER_GETI_INVENTORYQUANTITY)(AGS_Character* self, int i);
typedef void (*_AGS_CHARACTER_SETI_INVENTORYQUANTITY)(AGS_Character* self, int i, int new_value);
typedef int (*_AGS_CHARACTER_GET_LOOP)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_LOOP)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_MANUALSCALING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_MANUALSCALING)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_MOVEMENTLINKEDTOANIMATION)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_MOVEMENTLINKEDTOANIMATION)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_MOVING)(AGS_Character* self);
typedef const char* (*_AGS_CHARACTER_GET_NAME)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_NAME)(AGS_Character* self, const char* new_value);
typedef int (*_AGS_CHARACTER_GET_NORMALVIEW)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_PREVIOUSROOM)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_ROOM)(AGS_Character* self);
typedef AGS_bool (*_AGS_CHARACTER_GET_SCALEMOVESPEED)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SCALEMOVESPEED)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_SCALEVOLUME)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SCALEVOLUME)(AGS_Character* self, AGS_bool new_value);
typedef int (*_AGS_CHARACTER_GET_SCALING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SCALING)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_SOLID)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SOLID)(AGS_Character* self, AGS_bool new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_SPEAKING)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_SPEAKINGFRAME)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_SPEECHANIMATIONDELAY)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SPEECHANIMATIONDELAY)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_SPEECHCOLOR)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SPEECHCOLOR)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_SPEECHVIEW)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_SPEECHVIEW)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_THINKVIEW)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_THINKVIEW)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_TRANSPARENCY)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_TRANSPARENCY)(AGS_Character* self, int new_value);
typedef AGS_bool (*_AGS_CHARACTER_GET_TURNBEFOREWALKING)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_TURNBEFOREWALKING)(AGS_Character* self, AGS_bool new_value);
typedef int (*_AGS_CHARACTER_GET_VIEW)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_WALKSPEEDX)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_WALKSPEEDY)(AGS_Character* self);
typedef int (*_AGS_CHARACTER_GET_X)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_X)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_Y)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_Y)(AGS_Character* self, int new_value);
typedef int (*_AGS_CHARACTER_GET_Z)(AGS_Character* self);
typedef void (*_AGS_CHARACTER_SET_Z)(AGS_Character* self, int new_value);

// Global function externs
extern _AGS_DISPLAY AGS_Display;
extern _AGS_DISPLAYAT AGS_DisplayAt;
extern _AGS_DISPLAYATY AGS_DisplayAtY;
extern _AGS_DISPLAYMESSAGE AGS_DisplayMessage;
extern _AGS_DISPLAYMESSAGEATY AGS_DisplayMessageAtY;
extern _AGS_DISPLAYTOPBAR AGS_DisplayTopBar;
extern _AGS_DISPLAYMESSAGEBAR AGS_DisplayMessageBar;
extern _AGS_RESETROOM AGS_ResetRoom;
extern _AGS_HASPLAYERBEENINROOM AGS_HasPlayerBeenInRoom;
extern _AGS_PROCESSCLICK AGS_ProcessClick;
extern _AGS_ABORTGAME AGS_AbortGame;
extern _AGS_QUITGAME AGS_QuitGame;
extern _AGS_SETGAMESPEED AGS_SetGameSpeed;
extern _AGS_GETGAMESPEED AGS_GetGameSpeed;
extern _AGS_SETGAMEOPTION AGS_SetGameOption;
extern _AGS_GETGAMEOPTION AGS_GetGameOption;
extern _AGS_DEBUG AGS_Debug;
extern _AGS_CALLROOMSCRIPT AGS_CallRoomScript;
extern _AGS_RUNAGSGAME AGS_RunAGSGame;
extern _AGS_GETTRANSLATION AGS_GetTranslation;
extern _AGS_ISTRANSLATIONAVAILABLE AGS_IsTranslationAvailable;
extern _AGS_RESTOREGAMEDIALOG AGS_RestoreGameDialog;
extern _AGS_SAVEGAMEDIALOG AGS_SaveGameDialog;
extern _AGS_RESTARTGAME AGS_RestartGame;
extern _AGS_SAVEGAMESLOT AGS_SaveGameSlot;
extern _AGS_RESTOREGAMESLOT AGS_RestoreGameSlot;
extern _AGS_DELETESAVESLOT AGS_DeleteSaveSlot;
extern _AGS_SETRESTARTPOINT AGS_SetRestartPoint;
extern _AGS_GETLOCATIONTYPE AGS_GetLocationType;
extern _AGS_GETWALKABLEAREAAT AGS_GetWalkableAreaAt;
extern _AGS_GETSCALINGAT AGS_GetScalingAt;
extern _AGS_GETROOMPROPERTY AGS_GetRoomProperty;
extern _AGS_SETVIEWPORT AGS_SetViewport;
extern _AGS_RELEASEVIEWPORT AGS_ReleaseViewport;
extern _AGS_GETVIEWPORTX AGS_GetViewportX;
extern _AGS_GETVIEWPORTY AGS_GetViewportY;
extern _AGS_ISGAMEPAUSED AGS_IsGamePaused;
extern _AGS_GETGRAPHICALVARIABLE AGS_GetGraphicalVariable;
extern _AGS_SETGRAPHICALVARIABLE AGS_SetGraphicalVariable;
extern _AGS_DISABLEINTERFACE AGS_DisableInterface;
extern _AGS_ENABLEINTERFACE AGS_EnableInterface;
extern _AGS_ISINTERFACEENABLED AGS_IsInterfaceEnabled;
extern _AGS_SAID AGS_Said;
extern _AGS_GETTEXTWIDTH AGS_GetTextWidth;
extern _AGS_GETTEXTHEIGHT AGS_GetTextHeight;
extern _AGS_GIVESCORE AGS_GiveScore;
extern _AGS_UPDATEINVENTORY AGS_UpdateInventory;
extern _AGS_STOPDIALOG AGS_StopDialog;
extern _AGS_ARETHINGSOVERLAPPING AGS_AreThingsOverlapping;
extern _AGS_SETVOICEMODE AGS_SetVoiceMode;
extern _AGS_SETSKIPSPEECH AGS_SetSkipSpeech;
extern _AGS_SETSPEECHSTYLE AGS_SetSpeechStyle;
extern _AGS_SETTIMER AGS_SetTimer;
extern _AGS_ISTIMEREXPIRED AGS_IsTimerExpired;
extern _AGS_SETMULTITASKINGMODE AGS_SetMultitaskingMode;
extern _AGS_FLOATTOINT AGS_FloatToInt;
extern _AGS_INTTOFLOAT AGS_IntToFloat;
extern _AGS_FADEIN AGS_FadeIn;
extern _AGS_FADEOUT AGS_FadeOut;
extern _AGS_CYCLEPALETTE AGS_CyclePalette;
extern _AGS_SETPALRGB AGS_SetPalRGB;
extern _AGS_UPDATEPALETTE AGS_UpdatePalette;
extern _AGS_TINTSCREEN AGS_TintScreen;
extern _AGS_SETAMBIENTTINT AGS_SetAmbientTint;
extern _AGS_RANDOM AGS_Random;
extern _AGS_SETBACKGROUNDFRAME AGS_SetBackgroundFrame;
extern _AGS_GETBACKGROUNDFRAME AGS_GetBackgroundFrame;
extern _AGS_SHAKESCREEN AGS_ShakeScreen;
extern _AGS_SHAKESCREENBACKGROUND AGS_ShakeScreenBackground;
extern _AGS_SETSCREENTRANSITION AGS_SetScreenTransition;
extern _AGS_SETNEXTSCREENTRANSITION AGS_SetNextScreenTransition;
extern _AGS_SETFADECOLOR AGS_SetFadeColor;
extern _AGS_ISINTERACTIONAVAILABLE AGS_IsInteractionAvailable;
extern _AGS_REMOVEWALKABLEAREA AGS_RemoveWalkableArea;
extern _AGS_RESTOREWALKABLEAREA AGS_RestoreWalkableArea;
extern _AGS_SETAREASCALING AGS_SetAreaScaling;
extern _AGS_DISABLEGROUNDLEVELAREAS AGS_DisableGroundLevelAreas;
extern _AGS_ENABLEGROUNDLEVELAREAS AGS_EnableGroundLevelAreas;
extern _AGS_SETWALKBEHINDBASE AGS_SetWalkBehindBase;
extern _AGS_CDAUDIO AGS_CDAudio;
extern _AGS_PLAYFLIC AGS_PlayFlic;
extern _AGS_PLAYVIDEO AGS_PlayVideo;
extern _AGS_PLAYMUSIC AGS_PlayMusic;
extern _AGS_PLAYMUSICQUEUED AGS_PlayMusicQueued;
extern _AGS_PLAYSILENTMIDI AGS_PlaySilentMIDI;
extern _AGS_PLAYMP3FILE AGS_PlayMP3File;
extern _AGS_PLAYSOUND AGS_PlaySound;
extern _AGS_PLAYSOUNDEX AGS_PlaySoundEx;
extern _AGS_PLAYAMBIENTSOUND AGS_PlayAmbientSound;
extern _AGS_STOPAMBIENTSOUND AGS_StopAmbientSound;
extern _AGS_GETCURRENTMUSIC AGS_GetCurrentMusic;
extern _AGS_SETMUSICREPEAT AGS_SetMusicRepeat;
extern _AGS_SETMUSICVOLUME AGS_SetMusicVolume;
extern _AGS_SETSOUNDVOLUME AGS_SetSoundVolume;
extern _AGS_SETMUSICMASTERVOLUME AGS_SetMusicMasterVolume;
extern _AGS_SETDIGITALMASTERVOLUME AGS_SetDigitalMasterVolume;
extern _AGS_SEEKMODPATTERN AGS_SeekMODPattern;
extern _AGS_ISCHANNELPLAYING AGS_IsChannelPlaying;
extern _AGS_ISSOUNDPLAYING AGS_IsSoundPlaying;
extern _AGS_ISMUSICPLAYING AGS_IsMusicPlaying;
extern _AGS_GETMIDIPOSITION AGS_GetMIDIPosition;
extern _AGS_SEEKMIDIPOSITION AGS_SeekMIDIPosition;
extern _AGS_GETMP3POSMILLIS AGS_GetMP3PosMillis;
extern _AGS_SEEKMP3POSMILLIS AGS_SeekMP3PosMillis;
extern _AGS_SETCHANNELVOLUME AGS_SetChannelVolume;
extern _AGS_STOPCHANNEL AGS_StopChannel;
extern _AGS_STOPMUSIC AGS_StopMusic;
extern _AGS_ISVOXAVAILABLE AGS_IsVoxAvailable;
extern _AGS_SETSPEECHVOLUME AGS_SetSpeechVolume;
extern _AGS_ISMUSICVOXAVAILABLE AGS_IsMusicVoxAvailable;
extern _AGS_SAVESCREENSHOT AGS_SaveScreenShot;
extern _AGS_PAUSEGAME AGS_PauseGame;
extern _AGS_UNPAUSEGAME AGS_UnPauseGame;
extern _AGS_WAIT AGS_Wait;
extern _AGS_WAITKEY AGS_WaitKey;
extern _AGS_WAITMOUSEKEY AGS_WaitMouseKey;
extern _AGS_ISKEYPRESSED AGS_IsKeyPressed;
extern _AGS_SETGLOBALINT AGS_SetGlobalInt;
extern _AGS_GETGLOBALINT AGS_GetGlobalInt;
extern _AGS_FLIPSCREEN AGS_FlipScreen;
extern _AGS_SKIPUNTILCHARACTERSTOPS AGS_SkipUntilCharacterStops;
extern _AGS_STARTCUTSCENE AGS_StartCutscene;
extern _AGS_ENDCUTSCENE AGS_EndCutscene;
extern _AGS_CLAIMEVENT AGS_ClaimEvent;
extern _AGS_SETTEXTWINDOWGUI AGS_SetTextWindowGUI;
extern _AGS_FINDGUIID AGS_FindGUIID;

// ViewFrame method externs
extern _AGS_VIEWFRAME_GET_FLIPPED AGS_ViewFrame_get_Flipped;
extern _AGS_VIEWFRAME_GET_FRAME AGS_ViewFrame_get_Frame;
extern _AGS_VIEWFRAME_GET_GRAPHIC AGS_ViewFrame_get_Graphic;
extern _AGS_VIEWFRAME_SET_GRAPHIC AGS_ViewFrame_set_Graphic;
extern _AGS_VIEWFRAME_GET_LINKEDAUDIO AGS_ViewFrame_get_LinkedAudio;
extern _AGS_VIEWFRAME_SET_LINKEDAUDIO AGS_ViewFrame_set_LinkedAudio;
extern _AGS_VIEWFRAME_GET_LOOP AGS_ViewFrame_get_Loop;
extern _AGS_VIEWFRAME_GET_SOUND AGS_ViewFrame_get_Sound;
extern _AGS_VIEWFRAME_SET_SOUND AGS_ViewFrame_set_Sound;
extern _AGS_VIEWFRAME_GET_SPEED AGS_ViewFrame_get_Speed;
extern _AGS_VIEWFRAME_GET_VIEW AGS_ViewFrame_get_View;

// DrawingSurface method externs
extern _AGS_DRAWINGSURFACE_CLEAR AGS_DrawingSurface_Clear;
extern _AGS_DRAWINGSURFACE_CREATECOPY AGS_DrawingSurface_CreateCopy;
extern _AGS_DRAWINGSURFACE_DRAWCIRCLE AGS_DrawingSurface_DrawCircle;
extern _AGS_DRAWINGSURFACE_DRAWIMAGE AGS_DrawingSurface_DrawImage;
extern _AGS_DRAWINGSURFACE_DRAWLINE AGS_DrawingSurface_DrawLine;
extern _AGS_DRAWINGSURFACE_DRAWMESSAGEWRAPPED AGS_DrawingSurface_DrawMessageWrapped;
extern _AGS_DRAWINGSURFACE_DRAWPIXEL AGS_DrawingSurface_DrawPixel;
extern _AGS_DRAWINGSURFACE_DRAWRECTANGLE AGS_DrawingSurface_DrawRectangle;
extern _AGS_DRAWINGSURFACE_DRAWSTRING AGS_DrawingSurface_DrawString;
extern _AGS_DRAWINGSURFACE_DRAWSTRINGWRAPPED AGS_DrawingSurface_DrawStringWrapped;
extern _AGS_DRAWINGSURFACE_DRAWSURFACE AGS_DrawingSurface_DrawSurface;
extern _AGS_DRAWINGSURFACE_DRAWTRIANGLE AGS_DrawingSurface_DrawTriangle;
extern _AGS_DRAWINGSURFACE_GETPIXEL AGS_DrawingSurface_GetPixel;
extern _AGS_DRAWINGSURFACE_RELEASE AGS_DrawingSurface_Release;
extern _AGS_DRAWINGSURFACE_GET_DRAWINGCOLOR AGS_DrawingSurface_get_DrawingColor;
extern _AGS_DRAWINGSURFACE_SET_DRAWINGCOLOR AGS_DrawingSurface_set_DrawingColor;
extern _AGS_DRAWINGSURFACE_GET_HEIGHT AGS_DrawingSurface_get_Height;
extern _AGS_DRAWINGSURFACE_GET_USEHIGHRESCOORDINATES AGS_DrawingSurface_get_UseHighResCoordinates;
extern _AGS_DRAWINGSURFACE_SET_USEHIGHRESCOORDINATES AGS_DrawingSurface_set_UseHighResCoordinates;
extern _AGS_DRAWINGSURFACE_GET_WIDTH AGS_DrawingSurface_get_Width;

// Room method externs
extern _AGS_ROOM_GETTEXTPROPERTY AGS_Room_GetTextProperty;
extern _AGS_ROOM_GETDRAWINGSURFACEFORBACKGROUND AGS_Room_GetDrawingSurfaceForBackground;
extern _AGS_ROOM_GET_BOTTOMEDGE AGS_Room_get_BottomEdge;
extern _AGS_ROOM_GET_COLORDEPTH AGS_Room_get_ColorDepth;
extern _AGS_ROOM_GET_HEIGHT AGS_Room_get_Height;
extern _AGS_ROOM_GET_LEFTEDGE AGS_Room_get_LeftEdge;
extern _AGS_ROOM_GETI_MESSAGES AGS_Room_geti_Messages;
extern _AGS_ROOM_GET_MUSICONLOAD AGS_Room_get_MusicOnLoad;
extern _AGS_ROOM_GET_OBJECTCOUNT AGS_Room_get_ObjectCount;
extern _AGS_ROOM_GET_RIGHTEDGE AGS_Room_get_RightEdge;
extern _AGS_ROOM_GET_TOPEDGE AGS_Room_get_TopEdge;
extern _AGS_ROOM_GET_WIDTH AGS_Room_get_Width;

// Game method externs
extern _AGS_GAME_CHANGETRANSLATION AGS_Game_ChangeTranslation;
extern _AGS_GAME_DOONCEONLY AGS_Game_DoOnceOnly;
extern _AGS_GAME_GETCOLORFROMRGB AGS_Game_GetColorFromRGB;
extern _AGS_GAME_GETFRAMECOUNTFORLOOP AGS_Game_GetFrameCountForLoop;
extern _AGS_GAME_GETLOCATIONNAME AGS_Game_GetLocationName;
extern _AGS_GAME_GETLOOPCOUNTFORVIEW AGS_Game_GetLoopCountForView;
extern _AGS_GAME_GETMODPATTERN AGS_Game_GetMODPattern;
extern _AGS_GAME_GETRUNNEXTSETTINGFORLOOP AGS_Game_GetRunNextSettingForLoop;
extern _AGS_GAME_GETSAVESLOTDESCRIPTION AGS_Game_GetSaveSlotDescription;
extern _AGS_GAME_GETVIEWFRAME AGS_Game_GetViewFrame;
extern _AGS_GAME_INPUTBOX AGS_Game_InputBox;
extern _AGS_GAME_ISAUDIOPLAYING AGS_Game_IsAudioPlaying;
extern _AGS_GAME_SETSAVEGAMEDIRECTORY AGS_Game_SetSaveGameDirectory;
extern _AGS_GAME_STOPAUDIO AGS_Game_StopAudio;
extern _AGS_GAME_STOPSOUND AGS_Game_StopSound;
extern _AGS_GAME_GET_CHARACTERCOUNT AGS_Game_get_CharacterCount;
extern _AGS_GAME_GET_DIALOGCOUNT AGS_Game_get_DialogCount;
extern _AGS_GAME_GET_FILENAME AGS_Game_get_FileName;
extern _AGS_GAME_GET_FONTCOUNT AGS_Game_get_FontCount;
extern _AGS_GAME_GETI_GLOBALMESSAGES AGS_Game_geti_GlobalMessages;
extern _AGS_GAME_GETI_GLOBALSTRINGS AGS_Game_geti_GlobalStrings;
extern _AGS_GAME_SETI_GLOBALSTRINGS AGS_Game_seti_GlobalStrings;
extern _AGS_GAME_GET_GUICOUNT AGS_Game_get_GUICount;
extern _AGS_GAME_GET_IGNOREUSERINPUTAFTERTEXTTIMEOUTMS AGS_Game_get_IgnoreUserInputAfterTextTimeoutMs;
extern _AGS_GAME_SET_IGNOREUSERINPUTAFTERTEXTTIMEOUTMS AGS_Game_set_IgnoreUserInputAfterTextTimeoutMs;
extern _AGS_GAME_GET_INSKIPPABLECUTSCENE AGS_Game_get_InSkippableCutscene;
extern _AGS_GAME_GET_INVENTORYITEMCOUNT AGS_Game_get_InventoryItemCount;
extern _AGS_GAME_GET_MINIMUMTEXTDISPLAYTIMEMS AGS_Game_get_MinimumTextDisplayTimeMs;
extern _AGS_GAME_SET_MINIMUMTEXTDISPLAYTIMEMS AGS_Game_set_MinimumTextDisplayTimeMs;
extern _AGS_GAME_GET_MOUSECURSORCOUNT AGS_Game_get_MouseCursorCount;
extern _AGS_GAME_GET_NAME AGS_Game_get_Name;
extern _AGS_GAME_SET_NAME AGS_Game_set_Name;
extern _AGS_GAME_GET_NORMALFONT AGS_Game_get_NormalFont;
extern _AGS_GAME_SET_NORMALFONT AGS_Game_set_NormalFont;
extern _AGS_GAME_GET_SKIPPINGCUTSCENE AGS_Game_get_SkippingCutscene;
extern _AGS_GAME_GET_SPEECHFONT AGS_Game_get_SpeechFont;
extern _AGS_GAME_SET_SPEECHFONT AGS_Game_set_SpeechFont;
extern _AGS_GAME_GETI_SPRITEHEIGHT AGS_Game_geti_SpriteHeight;
extern _AGS_GAME_GETI_SPRITEWIDTH AGS_Game_geti_SpriteWidth;
extern _AGS_GAME_GET_TEXTREADINGSPEED AGS_Game_get_TextReadingSpeed;
extern _AGS_GAME_SET_TEXTREADINGSPEED AGS_Game_set_TextReadingSpeed;
extern _AGS_GAME_GET_TRANSLATIONFILENAME AGS_Game_get_TranslationFilename;
extern _AGS_GAME_GET_USENATIVECOORDINATES AGS_Game_get_UseNativeCoordinates;
extern _AGS_GAME_GET_VIEWCOUNT AGS_Game_get_ViewCount;

// Parser method externs
extern _AGS_PARSER_FINDWORDID AGS_Parser_FindWordID;
extern _AGS_PARSER_PARSETEXT AGS_Parser_ParseText;
extern _AGS_PARSER_SAID AGS_Parser_Said;
extern _AGS_PARSER_SAIDUNKNOWNWORD AGS_Parser_SaidUnknownWord;

// Mouse method externs
extern _AGS_MOUSE_CHANGEMODEGRAPHIC AGS_Mouse_ChangeModeGraphic;
extern _AGS_MOUSE_CHANGEMODEHOTSPOT AGS_Mouse_ChangeModeHotspot;
extern _AGS_MOUSE_CHANGEMODEVIEW AGS_Mouse_ChangeModeView;
extern _AGS_MOUSE_DISABLEMODE AGS_Mouse_DisableMode;
extern _AGS_MOUSE_ENABLEMODE AGS_Mouse_EnableMode;
extern _AGS_MOUSE_GETMODEGRAPHIC AGS_Mouse_GetModeGraphic;
extern _AGS_MOUSE_ISBUTTONDOWN AGS_Mouse_IsButtonDown;
extern _AGS_MOUSE_SAVECURSORUNTILITLEAVES AGS_Mouse_SaveCursorUntilItLeaves;
extern _AGS_MOUSE_SELECTNEXTMODE AGS_Mouse_SelectNextMode;
extern _AGS_MOUSE_SETBOUNDS AGS_Mouse_SetBounds;
extern _AGS_MOUSE_SETPOSITION AGS_Mouse_SetPosition;
extern _AGS_MOUSE_UPDATE AGS_Mouse_Update;
extern _AGS_MOUSE_USEDEFAULTGRAPHIC AGS_Mouse_UseDefaultGraphic;
extern _AGS_MOUSE_USEMODEGRAPHIC AGS_Mouse_UseModeGraphic;
extern _AGS_MOUSE_GET_MODE AGS_Mouse_get_Mode;
extern _AGS_MOUSE_SET_MODE AGS_Mouse_set_Mode;
extern _AGS_MOUSE_GET_VISIBLE AGS_Mouse_get_Visible;
extern _AGS_MOUSE_SET_VISIBLE AGS_Mouse_set_Visible;

// File method externs
extern _AGS_FILE_DELETE AGS_File_Delete;
extern _AGS_FILE_EXISTS AGS_File_Exists;
extern _AGS_FILE_OPEN AGS_File_Open;
extern _AGS_FILE_CLOSE AGS_File_Close;
extern _AGS_FILE_READINT AGS_File_ReadInt;
extern _AGS_FILE_READRAWCHAR AGS_File_ReadRawChar;
extern _AGS_FILE_READRAWINT AGS_File_ReadRawInt;
extern _AGS_FILE_READRAWLINEBACK AGS_File_ReadRawLineBack;
extern _AGS_FILE_READSTRINGBACK AGS_File_ReadStringBack;
extern _AGS_FILE_WRITEINT AGS_File_WriteInt;
extern _AGS_FILE_WRITERAWCHAR AGS_File_WriteRawChar;
extern _AGS_FILE_WRITERAWLINE AGS_File_WriteRawLine;
extern _AGS_FILE_WRITESTRING AGS_File_WriteString;
extern _AGS_FILE_GET_EOF AGS_File_get_EOF;
extern _AGS_FILE_GET_ERROR AGS_File_get_Error;

// InventoryItem method externs
extern _AGS_INVENTORYITEM_GETATSCREENXY AGS_InventoryItem_GetAtScreenXY;
extern _AGS_INVENTORYITEM_GETPROPERTY AGS_InventoryItem_GetProperty;
extern _AGS_INVENTORYITEM_GETTEXTPROPERTY AGS_InventoryItem_GetTextProperty;
extern _AGS_INVENTORYITEM_ISINTERACTIONAVAILABLE AGS_InventoryItem_IsInteractionAvailable;
extern _AGS_INVENTORYITEM_RUNINTERACTION AGS_InventoryItem_RunInteraction;
extern _AGS_INVENTORYITEM_GET_CURSORGRAPHIC AGS_InventoryItem_get_CursorGraphic;
extern _AGS_INVENTORYITEM_SET_CURSORGRAPHIC AGS_InventoryItem_set_CursorGraphic;
extern _AGS_INVENTORYITEM_GET_GRAPHIC AGS_InventoryItem_get_Graphic;
extern _AGS_INVENTORYITEM_SET_GRAPHIC AGS_InventoryItem_set_Graphic;
extern _AGS_INVENTORYITEM_GET_ID AGS_InventoryItem_get_ID;
extern _AGS_INVENTORYITEM_GET_NAME AGS_InventoryItem_get_Name;
extern _AGS_INVENTORYITEM_SET_NAME AGS_InventoryItem_set_Name;

// Overlay method externs
extern _AGS_OVERLAY_CREATEGRAPHICAL AGS_Overlay_CreateGraphical;
extern _AGS_OVERLAY_CREATETEXTUAL AGS_Overlay_CreateTextual;
extern _AGS_OVERLAY_SETTEXT AGS_Overlay_SetText;
extern _AGS_OVERLAY_REMOVE AGS_Overlay_Remove;
extern _AGS_OVERLAY_GET_VALID AGS_Overlay_get_Valid;
extern _AGS_OVERLAY_GET_X AGS_Overlay_get_X;
extern _AGS_OVERLAY_SET_X AGS_Overlay_set_X;
extern _AGS_OVERLAY_GET_Y AGS_Overlay_get_Y;
extern _AGS_OVERLAY_SET_Y AGS_Overlay_set_Y;

// DynamicSprite method externs
extern _AGS_DYNAMICSPRITE_CREATE AGS_DynamicSprite_Create;
extern _AGS_DYNAMICSPRITE_CREATEFROMBACKGROUND AGS_DynamicSprite_CreateFromBackground;
extern _AGS_DYNAMICSPRITE_CREATEFROMDRAWINGSURFACE AGS_DynamicSprite_CreateFromDrawingSurface;
extern _AGS_DYNAMICSPRITE_CREATEFROMEXISTINGSPRITE AGS_DynamicSprite_CreateFromExistingSprite;
extern _AGS_DYNAMICSPRITE_CREATEFROMFILE AGS_DynamicSprite_CreateFromFile;
extern _AGS_DYNAMICSPRITE_CREATEFROMSAVEGAME AGS_DynamicSprite_CreateFromSaveGame;
extern _AGS_DYNAMICSPRITE_CREATEFROMSCREENSHOT AGS_DynamicSprite_CreateFromScreenShot;
extern _AGS_DYNAMICSPRITE_CHANGECANVASSIZE AGS_DynamicSprite_ChangeCanvasSize;
extern _AGS_DYNAMICSPRITE_COPYTRANSPARENCYMASK AGS_DynamicSprite_CopyTransparencyMask;
extern _AGS_DYNAMICSPRITE_CROP AGS_DynamicSprite_Crop;
extern _AGS_DYNAMICSPRITE_DELETE AGS_DynamicSprite_Delete;
extern _AGS_DYNAMICSPRITE_FLIP AGS_DynamicSprite_Flip;
extern _AGS_DYNAMICSPRITE_GETDRAWINGSURFACE AGS_DynamicSprite_GetDrawingSurface;
extern _AGS_DYNAMICSPRITE_RESIZE AGS_DynamicSprite_Resize;
extern _AGS_DYNAMICSPRITE_ROTATE AGS_DynamicSprite_Rotate;
extern _AGS_DYNAMICSPRITE_SAVETOFILE AGS_DynamicSprite_SaveToFile;
extern _AGS_DYNAMICSPRITE_TINT AGS_DynamicSprite_Tint;
extern _AGS_DYNAMICSPRITE_GET_COLORDEPTH AGS_DynamicSprite_get_ColorDepth;
extern _AGS_DYNAMICSPRITE_GET_GRAPHIC AGS_DynamicSprite_get_Graphic;
extern _AGS_DYNAMICSPRITE_GET_HEIGHT AGS_DynamicSprite_get_Height;
extern _AGS_DYNAMICSPRITE_GET_WIDTH AGS_DynamicSprite_get_Width;

// GUIControl method externs
extern _AGS_GUICONTROL_BRINGTOFRONT AGS_GUIControl_BringToFront;
extern _AGS_GUICONTROL_GETATSCREENXY AGS_GUIControl_GetAtScreenXY;
extern _AGS_GUICONTROL_SENDTOBACK AGS_GUIControl_SendToBack;
extern _AGS_GUICONTROL_SETPOSITION AGS_GUIControl_SetPosition;
extern _AGS_GUICONTROL_SETSIZE AGS_GUIControl_SetSize;
extern _AGS_GUICONTROL_GET_ASBUTTON AGS_GUIControl_get_AsButton;
extern _AGS_GUICONTROL_GET_ASINVWINDOW AGS_GUIControl_get_AsInvWindow;
extern _AGS_GUICONTROL_GET_ASLABEL AGS_GUIControl_get_AsLabel;
extern _AGS_GUICONTROL_GET_ASLISTBOX AGS_GUIControl_get_AsListBox;
extern _AGS_GUICONTROL_GET_ASSLIDER AGS_GUIControl_get_AsSlider;
extern _AGS_GUICONTROL_GET_ASTEXTBOX AGS_GUIControl_get_AsTextBox;
extern _AGS_GUICONTROL_GET_CLICKABLE AGS_GUIControl_get_Clickable;
extern _AGS_GUICONTROL_SET_CLICKABLE AGS_GUIControl_set_Clickable;
extern _AGS_GUICONTROL_GET_ENABLED AGS_GUIControl_get_Enabled;
extern _AGS_GUICONTROL_SET_ENABLED AGS_GUIControl_set_Enabled;
extern _AGS_GUICONTROL_GET_HEIGHT AGS_GUIControl_get_Height;
extern _AGS_GUICONTROL_SET_HEIGHT AGS_GUIControl_set_Height;
extern _AGS_GUICONTROL_GET_ID AGS_GUIControl_get_ID;
extern _AGS_GUICONTROL_GET_OWNINGGUI AGS_GUIControl_get_OwningGUI;
extern _AGS_GUICONTROL_GET_VISIBLE AGS_GUIControl_get_Visible;
extern _AGS_GUICONTROL_SET_VISIBLE AGS_GUIControl_set_Visible;
extern _AGS_GUICONTROL_GET_WIDTH AGS_GUIControl_get_Width;
extern _AGS_GUICONTROL_SET_WIDTH AGS_GUIControl_set_Width;
extern _AGS_GUICONTROL_GET_X AGS_GUIControl_get_X;
extern _AGS_GUICONTROL_SET_X AGS_GUIControl_set_X;
extern _AGS_GUICONTROL_GET_Y AGS_GUIControl_get_Y;
extern _AGS_GUICONTROL_SET_Y AGS_GUIControl_set_Y;

// Label method externs
extern _AGS_LABEL_GET_FONT AGS_Label_get_Font;
extern _AGS_LABEL_SET_FONT AGS_Label_set_Font;
extern _AGS_LABEL_GET_TEXT AGS_Label_get_Text;
extern _AGS_LABEL_SET_TEXT AGS_Label_set_Text;
extern _AGS_LABEL_GET_TEXTCOLOR AGS_Label_get_TextColor;
extern _AGS_LABEL_SET_TEXTCOLOR AGS_Label_set_TextColor;

// Button method externs
extern _AGS_BUTTON_ANIMATE AGS_Button_Animate;
extern _AGS_BUTTON_GET_CLIPIMAGE AGS_Button_get_ClipImage;
extern _AGS_BUTTON_SET_CLIPIMAGE AGS_Button_set_ClipImage;
extern _AGS_BUTTON_GET_FONT AGS_Button_get_Font;
extern _AGS_BUTTON_SET_FONT AGS_Button_set_Font;
extern _AGS_BUTTON_GET_GRAPHIC AGS_Button_get_Graphic;
extern _AGS_BUTTON_GET_MOUSEOVERGRAPHIC AGS_Button_get_MouseOverGraphic;
extern _AGS_BUTTON_SET_MOUSEOVERGRAPHIC AGS_Button_set_MouseOverGraphic;
extern _AGS_BUTTON_GET_NORMALGRAPHIC AGS_Button_get_NormalGraphic;
extern _AGS_BUTTON_SET_NORMALGRAPHIC AGS_Button_set_NormalGraphic;
extern _AGS_BUTTON_GET_PUSHEDGRAPHIC AGS_Button_get_PushedGraphic;
extern _AGS_BUTTON_SET_PUSHEDGRAPHIC AGS_Button_set_PushedGraphic;
extern _AGS_BUTTON_GET_TEXTCOLOR AGS_Button_get_TextColor;
extern _AGS_BUTTON_SET_TEXTCOLOR AGS_Button_set_TextColor;
extern _AGS_BUTTON_GET_TEXT AGS_Button_get_Text;
extern _AGS_BUTTON_SET_TEXT AGS_Button_set_Text;

// Slider method externs
extern _AGS_SLIDER_GET_BACKGROUNDGRAPHIC AGS_Slider_get_BackgroundGraphic;
extern _AGS_SLIDER_SET_BACKGROUNDGRAPHIC AGS_Slider_set_BackgroundGraphic;
extern _AGS_SLIDER_GET_HANDLEGRAPHIC AGS_Slider_get_HandleGraphic;
extern _AGS_SLIDER_SET_HANDLEGRAPHIC AGS_Slider_set_HandleGraphic;
extern _AGS_SLIDER_GET_HANDLEOFFSET AGS_Slider_get_HandleOffset;
extern _AGS_SLIDER_SET_HANDLEOFFSET AGS_Slider_set_HandleOffset;
extern _AGS_SLIDER_GET_MAX AGS_Slider_get_Max;
extern _AGS_SLIDER_SET_MAX AGS_Slider_set_Max;
extern _AGS_SLIDER_GET_MIN AGS_Slider_get_Min;
extern _AGS_SLIDER_SET_MIN AGS_Slider_set_Min;
extern _AGS_SLIDER_GET_VALUE AGS_Slider_get_Value;
extern _AGS_SLIDER_SET_VALUE AGS_Slider_set_Value;

// TextBox method externs
extern _AGS_TEXTBOX_GET_FONT AGS_TextBox_get_Font;
extern _AGS_TEXTBOX_SET_FONT AGS_TextBox_set_Font;
extern _AGS_TEXTBOX_GET_TEXT AGS_TextBox_get_Text;
extern _AGS_TEXTBOX_SET_TEXT AGS_TextBox_set_Text;
extern _AGS_TEXTBOX_GET_TEXTCOLOR AGS_TextBox_get_TextColor;
extern _AGS_TEXTBOX_SET_TEXTCOLOR AGS_TextBox_set_TextColor;

// InvWindow method externs
extern _AGS_INVWINDOW_SCROLLDOWN AGS_InvWindow_ScrollDown;
extern _AGS_INVWINDOW_SCROLLUP AGS_InvWindow_ScrollUp;
extern _AGS_INVWINDOW_GET_CHARACTERTOUSE AGS_InvWindow_get_CharacterToUse;
extern _AGS_INVWINDOW_SET_CHARACTERTOUSE AGS_InvWindow_set_CharacterToUse;
extern _AGS_INVWINDOW_GETI_ITEMATINDEX AGS_InvWindow_geti_ItemAtIndex;
extern _AGS_INVWINDOW_GET_ITEMCOUNT AGS_InvWindow_get_ItemCount;
extern _AGS_INVWINDOW_GET_ITEMHEIGHT AGS_InvWindow_get_ItemHeight;
extern _AGS_INVWINDOW_SET_ITEMHEIGHT AGS_InvWindow_set_ItemHeight;
extern _AGS_INVWINDOW_GET_ITEMWIDTH AGS_InvWindow_get_ItemWidth;
extern _AGS_INVWINDOW_SET_ITEMWIDTH AGS_InvWindow_set_ItemWidth;
extern _AGS_INVWINDOW_GET_TOPITEM AGS_InvWindow_get_TopItem;
extern _AGS_INVWINDOW_SET_TOPITEM AGS_InvWindow_set_TopItem;
extern _AGS_INVWINDOW_GET_ITEMSPERROW AGS_InvWindow_get_ItemsPerRow;
extern _AGS_INVWINDOW_GET_ROWCOUNT AGS_InvWindow_get_RowCount;

// ListBox method externs
extern _AGS_LISTBOX_ADDITEM AGS_ListBox_AddItem;
extern _AGS_LISTBOX_CLEAR AGS_ListBox_Clear;
extern _AGS_LISTBOX_FILLDIRLIST AGS_ListBox_FillDirList;
extern _AGS_LISTBOX_FILLSAVEGAMELIST AGS_ListBox_FillSaveGameList;
extern _AGS_LISTBOX_GETITEMATLOCATION AGS_ListBox_GetItemAtLocation;
extern _AGS_LISTBOX_INSERTITEMAT AGS_ListBox_InsertItemAt;
extern _AGS_LISTBOX_REMOVEITEM AGS_ListBox_RemoveItem;
extern _AGS_LISTBOX_SCROLLDOWN AGS_ListBox_ScrollDown;
extern _AGS_LISTBOX_SCROLLUP AGS_ListBox_ScrollUp;
extern _AGS_LISTBOX_GET_FONT AGS_ListBox_get_Font;
extern _AGS_LISTBOX_SET_FONT AGS_ListBox_set_Font;
extern _AGS_LISTBOX_GET_HIDEBORDER AGS_ListBox_get_HideBorder;
extern _AGS_LISTBOX_SET_HIDEBORDER AGS_ListBox_set_HideBorder;
extern _AGS_LISTBOX_GET_HIDESCROLLARROWS AGS_ListBox_get_HideScrollArrows;
extern _AGS_LISTBOX_SET_HIDESCROLLARROWS AGS_ListBox_set_HideScrollArrows;
extern _AGS_LISTBOX_GET_ITEMCOUNT AGS_ListBox_get_ItemCount;
extern _AGS_LISTBOX_GETI_ITEMS AGS_ListBox_geti_Items;
extern _AGS_LISTBOX_SETI_ITEMS AGS_ListBox_seti_Items;
extern _AGS_LISTBOX_GET_ROWCOUNT AGS_ListBox_get_RowCount;
extern _AGS_LISTBOX_GETI_SAVEGAMESLOTS AGS_ListBox_geti_SaveGameSlots;
extern _AGS_LISTBOX_GET_SELECTEDINDEX AGS_ListBox_get_SelectedIndex;
extern _AGS_LISTBOX_SET_SELECTEDINDEX AGS_ListBox_set_SelectedIndex;
extern _AGS_LISTBOX_GET_TOPITEM AGS_ListBox_get_TopItem;
extern _AGS_LISTBOX_SET_TOPITEM AGS_ListBox_set_TopItem;

// GUI method externs
extern _AGS_GUI_CENTRE AGS_GUI_Centre;
extern _AGS_GUI_GETATSCREENXY AGS_GUI_GetAtScreenXY;
extern _AGS_GUI_SETPOSITION AGS_GUI_SetPosition;
extern _AGS_GUI_SETSIZE AGS_GUI_SetSize;
extern _AGS_GUI_GET_BACKGROUNDGRAPHIC AGS_GUI_get_BackgroundGraphic;
extern _AGS_GUI_SET_BACKGROUNDGRAPHIC AGS_GUI_set_BackgroundGraphic;
extern _AGS_GUI_GET_CLICKABLE AGS_GUI_get_Clickable;
extern _AGS_GUI_SET_CLICKABLE AGS_GUI_set_Clickable;
extern _AGS_GUI_GETI_CONTROLS AGS_GUI_geti_Controls;
extern _AGS_GUI_GET_CONTROLCOUNT AGS_GUI_get_ControlCount;
extern _AGS_GUI_GET_HEIGHT AGS_GUI_get_Height;
extern _AGS_GUI_SET_HEIGHT AGS_GUI_set_Height;
extern _AGS_GUI_GET_ID AGS_GUI_get_ID;
extern _AGS_GUI_GET_TRANSPARENCY AGS_GUI_get_Transparency;
extern _AGS_GUI_SET_TRANSPARENCY AGS_GUI_set_Transparency;
extern _AGS_GUI_GET_VISIBLE AGS_GUI_get_Visible;
extern _AGS_GUI_SET_VISIBLE AGS_GUI_set_Visible;
extern _AGS_GUI_GET_WIDTH AGS_GUI_get_Width;
extern _AGS_GUI_SET_WIDTH AGS_GUI_set_Width;
extern _AGS_GUI_GET_X AGS_GUI_get_X;
extern _AGS_GUI_SET_X AGS_GUI_set_X;
extern _AGS_GUI_GET_Y AGS_GUI_get_Y;
extern _AGS_GUI_SET_Y AGS_GUI_set_Y;
extern _AGS_GUI_GET_ZORDER AGS_GUI_get_ZOrder;
extern _AGS_GUI_SET_ZORDER AGS_GUI_set_ZOrder;

// Hotspot method externs
extern _AGS_HOTSPOT_GETATSCREENXY AGS_Hotspot_GetAtScreenXY;
extern _AGS_HOTSPOT_GETPROPERTY AGS_Hotspot_GetProperty;
extern _AGS_HOTSPOT_GETTEXTPROPERTY AGS_Hotspot_GetTextProperty;
extern _AGS_HOTSPOT_RUNINTERACTION AGS_Hotspot_RunInteraction;
extern _AGS_HOTSPOT_GET_ENABLED AGS_Hotspot_get_Enabled;
extern _AGS_HOTSPOT_SET_ENABLED AGS_Hotspot_set_Enabled;
extern _AGS_HOTSPOT_GET_ID AGS_Hotspot_get_ID;
extern _AGS_HOTSPOT_GET_NAME AGS_Hotspot_get_Name;
extern _AGS_HOTSPOT_GET_WALKTOX AGS_Hotspot_get_WalkToX;
extern _AGS_HOTSPOT_GET_WALKTOY AGS_Hotspot_get_WalkToY;

// Region method externs
extern _AGS_REGION_GETATROOMXY AGS_Region_GetAtRoomXY;
extern _AGS_REGION_RUNINTERACTION AGS_Region_RunInteraction;
extern _AGS_REGION_TINT AGS_Region_Tint;
extern _AGS_REGION_GET_ENABLED AGS_Region_get_Enabled;
extern _AGS_REGION_SET_ENABLED AGS_Region_set_Enabled;
extern _AGS_REGION_GET_ID AGS_Region_get_ID;
extern _AGS_REGION_GET_LIGHTLEVEL AGS_Region_get_LightLevel;
extern _AGS_REGION_SET_LIGHTLEVEL AGS_Region_set_LightLevel;
extern _AGS_REGION_GET_TINTENABLED AGS_Region_get_TintEnabled;
extern _AGS_REGION_GET_TINTBLUE AGS_Region_get_TintBlue;
extern _AGS_REGION_GET_TINTGREEN AGS_Region_get_TintGreen;
extern _AGS_REGION_GET_TINTRED AGS_Region_get_TintRed;
extern _AGS_REGION_GET_TINTSATURATION AGS_Region_get_TintSaturation;

// Dialog method externs
extern _AGS_DIALOG_DISPLAYOPTIONS AGS_Dialog_DisplayOptions;
extern _AGS_DIALOG_GETOPTIONSTATE AGS_Dialog_GetOptionState;
extern _AGS_DIALOG_GETOPTIONTEXT AGS_Dialog_GetOptionText;
extern _AGS_DIALOG_HASOPTIONBEENCHOSEN AGS_Dialog_HasOptionBeenChosen;
extern _AGS_DIALOG_SETOPTIONSTATE AGS_Dialog_SetOptionState;
extern _AGS_DIALOG_START AGS_Dialog_Start;
extern _AGS_DIALOG_GET_ID AGS_Dialog_get_ID;
extern _AGS_DIALOG_GET_OPTIONCOUNT AGS_Dialog_get_OptionCount;

// DateTime method externs
extern _AGS_DATETIME_GET_NOW AGS_DateTime_get_Now;
extern _AGS_DATETIME_GET_YEAR AGS_DateTime_get_Year;
extern _AGS_DATETIME_GET_MONTH AGS_DateTime_get_Month;
extern _AGS_DATETIME_GET_DAYOFMONTH AGS_DateTime_get_DayOfMonth;
extern _AGS_DATETIME_GET_HOUR AGS_DateTime_get_Hour;
extern _AGS_DATETIME_GET_MINUTE AGS_DateTime_get_Minute;
extern _AGS_DATETIME_GET_SECOND AGS_DateTime_get_Second;
extern _AGS_DATETIME_GET_RAWTIME AGS_DateTime_get_RawTime;

// AudioChannel method externs
extern _AGS_AUDIOCHANNEL_SEEK AGS_AudioChannel_Seek;
extern _AGS_AUDIOCHANNEL_SETROOMLOCATION AGS_AudioChannel_SetRoomLocation;
extern _AGS_AUDIOCHANNEL_STOP AGS_AudioChannel_Stop;
extern _AGS_AUDIOCHANNEL_GET_ID AGS_AudioChannel_get_ID;
extern _AGS_AUDIOCHANNEL_GET_ISPLAYING AGS_AudioChannel_get_IsPlaying;
extern _AGS_AUDIOCHANNEL_GET_LENGTHMS AGS_AudioChannel_get_LengthMs;
extern _AGS_AUDIOCHANNEL_GET_PANNING AGS_AudioChannel_get_Panning;
extern _AGS_AUDIOCHANNEL_SET_PANNING AGS_AudioChannel_set_Panning;
extern _AGS_AUDIOCHANNEL_GET_PLAYINGCLIP AGS_AudioChannel_get_PlayingClip;
extern _AGS_AUDIOCHANNEL_GET_POSITION AGS_AudioChannel_get_Position;
extern _AGS_AUDIOCHANNEL_GET_POSITIONMS AGS_AudioChannel_get_PositionMs;
extern _AGS_AUDIOCHANNEL_GET_VOLUME AGS_AudioChannel_get_Volume;
extern _AGS_AUDIOCHANNEL_SET_VOLUME AGS_AudioChannel_set_Volume;

// AudioClip method externs
extern _AGS_AUDIOCLIP_PLAY AGS_AudioClip_Play;
extern _AGS_AUDIOCLIP_PLAYFROM AGS_AudioClip_PlayFrom;
extern _AGS_AUDIOCLIP_PLAYQUEUED AGS_AudioClip_PlayQueued;
extern _AGS_AUDIOCLIP_STOP AGS_AudioClip_Stop;
extern _AGS_AUDIOCLIP_GET_FILETYPE AGS_AudioClip_get_FileType;
extern _AGS_AUDIOCLIP_GET_ISAVAILABLE AGS_AudioClip_get_IsAvailable;
extern _AGS_AUDIOCLIP_GET_TYPE AGS_AudioClip_get_Type;

// System method externs
extern _AGS_SYSTEM_GET_CAPSLOCK AGS_System_get_CapsLock;
extern _AGS_SYSTEM_GETI_AUDIOCHANNELS AGS_System_geti_AudioChannels;
extern _AGS_SYSTEM_GET_AUDIOCHANNELCOUNT AGS_System_get_AudioChannelCount;
extern _AGS_SYSTEM_GET_COLORDEPTH AGS_System_get_ColorDepth;
extern _AGS_SYSTEM_GET_GAMMA AGS_System_get_Gamma;
extern _AGS_SYSTEM_SET_GAMMA AGS_System_set_Gamma;
extern _AGS_SYSTEM_GET_HARDWAREACCELERATION AGS_System_get_HardwareAcceleration;
extern _AGS_SYSTEM_GET_NUMLOCK AGS_System_get_NumLock;
extern _AGS_SYSTEM_GET_OPERATINGSYSTEM AGS_System_get_OperatingSystem;
extern _AGS_SYSTEM_GET_SCREENHEIGHT AGS_System_get_ScreenHeight;
extern _AGS_SYSTEM_GET_SCREENWIDTH AGS_System_get_ScreenWidth;
extern _AGS_SYSTEM_GET_SCROLLLOCK AGS_System_get_ScrollLock;
extern _AGS_SYSTEM_GET_SUPPORTSGAMMACONTROL AGS_System_get_SupportsGammaControl;
extern _AGS_SYSTEM_GET_VERSION AGS_System_get_Version;
extern _AGS_SYSTEM_GET_VIEWPORTHEIGHT AGS_System_get_ViewportHeight;
extern _AGS_SYSTEM_GET_VIEWPORTWIDTH AGS_System_get_ViewportWidth;
extern _AGS_SYSTEM_GET_VOLUME AGS_System_get_Volume;
extern _AGS_SYSTEM_SET_VOLUME AGS_System_set_Volume;
extern _AGS_SYSTEM_GET_VSYNC AGS_System_get_VSync;
extern _AGS_SYSTEM_SET_VSYNC AGS_System_set_VSync;
extern _AGS_SYSTEM_GET_WINDOWED AGS_System_get_Windowed;

// Object method externs
extern _AGS_OBJECT_ANIMATE AGS_Object_Animate;
extern _AGS_OBJECT_GETATSCREENXY AGS_Object_GetAtScreenXY;
extern _AGS_OBJECT_GETPROPERTY AGS_Object_GetProperty;
extern _AGS_OBJECT_GETTEXTPROPERTY AGS_Object_GetTextProperty;
extern _AGS_OBJECT_ISCOLLIDINGWITHOBJECT AGS_Object_IsCollidingWithObject;
extern _AGS_OBJECT_MERGEINTOBACKGROUND AGS_Object_MergeIntoBackground;
extern _AGS_OBJECT_MOVE AGS_Object_Move;
extern _AGS_OBJECT_REMOVETINT AGS_Object_RemoveTint;
extern _AGS_OBJECT_RUNINTERACTION AGS_Object_RunInteraction;
extern _AGS_OBJECT_SETPOSITION AGS_Object_SetPosition;
extern _AGS_OBJECT_SETVIEW AGS_Object_SetView;
extern _AGS_OBJECT_STOPANIMATING AGS_Object_StopAnimating;
extern _AGS_OBJECT_STOPMOVING AGS_Object_StopMoving;
extern _AGS_OBJECT_TINT AGS_Object_Tint;
extern _AGS_OBJECT_GET_ANIMATING AGS_Object_get_Animating;
extern _AGS_OBJECT_GET_BASELINE AGS_Object_get_Baseline;
extern _AGS_OBJECT_SET_BASELINE AGS_Object_set_Baseline;
extern _AGS_OBJECT_GET_BLOCKINGHEIGHT AGS_Object_get_BlockingHeight;
extern _AGS_OBJECT_SET_BLOCKINGHEIGHT AGS_Object_set_BlockingHeight;
extern _AGS_OBJECT_GET_BLOCKINGWIDTH AGS_Object_get_BlockingWidth;
extern _AGS_OBJECT_SET_BLOCKINGWIDTH AGS_Object_set_BlockingWidth;
extern _AGS_OBJECT_GET_CLICKABLE AGS_Object_get_Clickable;
extern _AGS_OBJECT_SET_CLICKABLE AGS_Object_set_Clickable;
extern _AGS_OBJECT_GET_FRAME AGS_Object_get_Frame;
extern _AGS_OBJECT_GET_GRAPHIC AGS_Object_get_Graphic;
extern _AGS_OBJECT_SET_GRAPHIC AGS_Object_set_Graphic;
extern _AGS_OBJECT_GET_ID AGS_Object_get_ID;
extern _AGS_OBJECT_GET_IGNORESCALING AGS_Object_get_IgnoreScaling;
extern _AGS_OBJECT_SET_IGNORESCALING AGS_Object_set_IgnoreScaling;
extern _AGS_OBJECT_GET_IGNOREWALKBEHINDS AGS_Object_get_IgnoreWalkbehinds;
extern _AGS_OBJECT_SET_IGNOREWALKBEHINDS AGS_Object_set_IgnoreWalkbehinds;
extern _AGS_OBJECT_GET_LOOP AGS_Object_get_Loop;
extern _AGS_OBJECT_GET_MOVING AGS_Object_get_Moving;
extern _AGS_OBJECT_GET_NAME AGS_Object_get_Name;
extern _AGS_OBJECT_GET_SOLID AGS_Object_get_Solid;
extern _AGS_OBJECT_SET_SOLID AGS_Object_set_Solid;
extern _AGS_OBJECT_GET_TRANSPARENCY AGS_Object_get_Transparency;
extern _AGS_OBJECT_SET_TRANSPARENCY AGS_Object_set_Transparency;
extern _AGS_OBJECT_GET_VIEW AGS_Object_get_View;
extern _AGS_OBJECT_GET_VISIBLE AGS_Object_get_Visible;
extern _AGS_OBJECT_SET_VISIBLE AGS_Object_set_Visible;
extern _AGS_OBJECT_GET_X AGS_Object_get_X;
extern _AGS_OBJECT_SET_X AGS_Object_set_X;
extern _AGS_OBJECT_GET_Y AGS_Object_get_Y;
extern _AGS_OBJECT_SET_Y AGS_Object_set_Y;

// Character method externs
extern _AGS_CHARACTER_ADDINVENTORY AGS_Character_AddInventory;
extern _AGS_CHARACTER_ADDWAYPOINT AGS_Character_AddWaypoint;
extern _AGS_CHARACTER_ANIMATE AGS_Character_Animate;
extern _AGS_CHARACTER_CHANGEROOM AGS_Character_ChangeRoom;
extern _AGS_CHARACTER_CHANGEROOMAUTOPOSITION AGS_Character_ChangeRoomAutoPosition;
extern _AGS_CHARACTER_CHANGEVIEW AGS_Character_ChangeView;
extern _AGS_CHARACTER_FACECHARACTER AGS_Character_FaceCharacter;
extern _AGS_CHARACTER_FACELOCATION AGS_Character_FaceLocation;
extern _AGS_CHARACTER_FACEOBJECT AGS_Character_FaceObject;
extern _AGS_CHARACTER_FOLLOWCHARACTER AGS_Character_FollowCharacter;
extern _AGS_CHARACTER_GETATSCREENXY AGS_Character_GetAtScreenXY;
extern _AGS_CHARACTER_GETPROPERTY AGS_Character_GetProperty;
extern _AGS_CHARACTER_GETTEXTPROPERTY AGS_Character_GetTextProperty;
extern _AGS_CHARACTER_HASINVENTORY AGS_Character_HasInventory;
extern _AGS_CHARACTER_ISCOLLIDINGWITHCHAR AGS_Character_IsCollidingWithChar;
extern _AGS_CHARACTER_ISCOLLIDINGWITHOBJECT AGS_Character_IsCollidingWithObject;
extern _AGS_CHARACTER_LOCKVIEW AGS_Character_LockView;
extern _AGS_CHARACTER_LOCKVIEWALIGNED AGS_Character_LockViewAligned;
extern _AGS_CHARACTER_LOCKVIEWFRAME AGS_Character_LockViewFrame;
extern _AGS_CHARACTER_LOCKVIEWOFFSET AGS_Character_LockViewOffset;
extern _AGS_CHARACTER_LOSEINVENTORY AGS_Character_LoseInventory;
extern _AGS_CHARACTER_MOVE AGS_Character_Move;
extern _AGS_CHARACTER_PLACEONWALKABLEAREA AGS_Character_PlaceOnWalkableArea;
extern _AGS_CHARACTER_REMOVETINT AGS_Character_RemoveTint;
extern _AGS_CHARACTER_RUNINTERACTION AGS_Character_RunInteraction;
extern _AGS_CHARACTER_SAY AGS_Character_Say;
extern _AGS_CHARACTER_SAYAT AGS_Character_SayAt;
extern _AGS_CHARACTER_SAYBACKGROUND AGS_Character_SayBackground;
extern _AGS_CHARACTER_SETASPLAYER AGS_Character_SetAsPlayer;
extern _AGS_CHARACTER_SETIDLEVIEW AGS_Character_SetIdleView;
extern _AGS_CHARACTER_SETWALKSPEED AGS_Character_SetWalkSpeed;
extern _AGS_CHARACTER_STOPMOVING AGS_Character_StopMoving;
extern _AGS_CHARACTER_THINK AGS_Character_Think;
extern _AGS_CHARACTER_TINT AGS_Character_Tint;
extern _AGS_CHARACTER_UNLOCKVIEW AGS_Character_UnlockView;
extern _AGS_CHARACTER_WALK AGS_Character_Walk;
extern _AGS_CHARACTER_WALKSTRAIGHT AGS_Character_WalkStraight;
extern _AGS_CHARACTER_GET_ACTIVEINVENTORY AGS_Character_get_ActiveInventory;
extern _AGS_CHARACTER_SET_ACTIVEINVENTORY AGS_Character_set_ActiveInventory;
extern _AGS_CHARACTER_GET_ANIMATING AGS_Character_get_Animating;
extern _AGS_CHARACTER_GET_ANIMATIONSPEED AGS_Character_get_AnimationSpeed;
extern _AGS_CHARACTER_SET_ANIMATIONSPEED AGS_Character_set_AnimationSpeed;
extern _AGS_CHARACTER_GET_BASELINE AGS_Character_get_Baseline;
extern _AGS_CHARACTER_SET_BASELINE AGS_Character_set_Baseline;
extern _AGS_CHARACTER_GET_BLINKINTERVAL AGS_Character_get_BlinkInterval;
extern _AGS_CHARACTER_SET_BLINKINTERVAL AGS_Character_set_BlinkInterval;
extern _AGS_CHARACTER_GET_BLINKVIEW AGS_Character_get_BlinkView;
extern _AGS_CHARACTER_SET_BLINKVIEW AGS_Character_set_BlinkView;
extern _AGS_CHARACTER_GET_BLINKWHILETHINKING AGS_Character_get_BlinkWhileThinking;
extern _AGS_CHARACTER_SET_BLINKWHILETHINKING AGS_Character_set_BlinkWhileThinking;
extern _AGS_CHARACTER_GET_BLOCKINGHEIGHT AGS_Character_get_BlockingHeight;
extern _AGS_CHARACTER_SET_BLOCKINGHEIGHT AGS_Character_set_BlockingHeight;
extern _AGS_CHARACTER_GET_BLOCKINGWIDTH AGS_Character_get_BlockingWidth;
extern _AGS_CHARACTER_SET_BLOCKINGWIDTH AGS_Character_set_BlockingWidth;
extern _AGS_CHARACTER_GET_CLICKABLE AGS_Character_get_Clickable;
extern _AGS_CHARACTER_SET_CLICKABLE AGS_Character_set_Clickable;
extern _AGS_CHARACTER_GET_DIAGONALLOOPS AGS_Character_get_DiagonalLoops;
extern _AGS_CHARACTER_SET_DIAGONALLOOPS AGS_Character_set_DiagonalLoops;
extern _AGS_CHARACTER_GET_FRAME AGS_Character_get_Frame;
extern _AGS_CHARACTER_SET_FRAME AGS_Character_set_Frame;
extern _AGS_CHARACTER_GET_HASEXPLICITTINT AGS_Character_get_HasExplicitTint;
extern _AGS_CHARACTER_GET_ID AGS_Character_get_ID;
extern _AGS_CHARACTER_GET_IDLEVIEW AGS_Character_get_IdleView;
extern _AGS_CHARACTER_GET_IGNORELIGHTING AGS_Character_get_IgnoreLighting;
extern _AGS_CHARACTER_SET_IGNORELIGHTING AGS_Character_set_IgnoreLighting;
extern _AGS_CHARACTER_GET_IGNORESCALING AGS_Character_get_IgnoreScaling;
extern _AGS_CHARACTER_SET_IGNORESCALING AGS_Character_set_IgnoreScaling;
extern _AGS_CHARACTER_GET_IGNOREWALKBEHINDS AGS_Character_get_IgnoreWalkbehinds;
extern _AGS_CHARACTER_SET_IGNOREWALKBEHINDS AGS_Character_set_IgnoreWalkbehinds;
extern _AGS_CHARACTER_GETI_INVENTORYQUANTITY AGS_Character_geti_InventoryQuantity;
extern _AGS_CHARACTER_SETI_INVENTORYQUANTITY AGS_Character_seti_InventoryQuantity;
extern _AGS_CHARACTER_GET_LOOP AGS_Character_get_Loop;
extern _AGS_CHARACTER_SET_LOOP AGS_Character_set_Loop;
extern _AGS_CHARACTER_GET_MANUALSCALING AGS_Character_get_ManualScaling;
extern _AGS_CHARACTER_SET_MANUALSCALING AGS_Character_set_ManualScaling;
extern _AGS_CHARACTER_GET_MOVEMENTLINKEDTOANIMATION AGS_Character_get_MovementLinkedToAnimation;
extern _AGS_CHARACTER_SET_MOVEMENTLINKEDTOANIMATION AGS_Character_set_MovementLinkedToAnimation;
extern _AGS_CHARACTER_GET_MOVING AGS_Character_get_Moving;
extern _AGS_CHARACTER_GET_NAME AGS_Character_get_Name;
extern _AGS_CHARACTER_SET_NAME AGS_Character_set_Name;
extern _AGS_CHARACTER_GET_NORMALVIEW AGS_Character_get_NormalView;
extern _AGS_CHARACTER_GET_PREVIOUSROOM AGS_Character_get_PreviousRoom;
extern _AGS_CHARACTER_GET_ROOM AGS_Character_get_Room;
extern _AGS_CHARACTER_GET_SCALEMOVESPEED AGS_Character_get_ScaleMoveSpeed;
extern _AGS_CHARACTER_SET_SCALEMOVESPEED AGS_Character_set_ScaleMoveSpeed;
extern _AGS_CHARACTER_GET_SCALEVOLUME AGS_Character_get_ScaleVolume;
extern _AGS_CHARACTER_SET_SCALEVOLUME AGS_Character_set_ScaleVolume;
extern _AGS_CHARACTER_GET_SCALING AGS_Character_get_Scaling;
extern _AGS_CHARACTER_SET_SCALING AGS_Character_set_Scaling;
extern _AGS_CHARACTER_GET_SOLID AGS_Character_get_Solid;
extern _AGS_CHARACTER_SET_SOLID AGS_Character_set_Solid;
extern _AGS_CHARACTER_GET_SPEAKING AGS_Character_get_Speaking;
extern _AGS_CHARACTER_GET_SPEAKINGFRAME AGS_Character_get_SpeakingFrame;
extern _AGS_CHARACTER_GET_SPEECHANIMATIONDELAY AGS_Character_get_SpeechAnimationDelay;
extern _AGS_CHARACTER_SET_SPEECHANIMATIONDELAY AGS_Character_set_SpeechAnimationDelay;
extern _AGS_CHARACTER_GET_SPEECHCOLOR AGS_Character_get_SpeechColor;
extern _AGS_CHARACTER_SET_SPEECHCOLOR AGS_Character_set_SpeechColor;
extern _AGS_CHARACTER_GET_SPEECHVIEW AGS_Character_get_SpeechView;
extern _AGS_CHARACTER_SET_SPEECHVIEW AGS_Character_set_SpeechView;
extern _AGS_CHARACTER_GET_THINKVIEW AGS_Character_get_ThinkView;
extern _AGS_CHARACTER_SET_THINKVIEW AGS_Character_set_ThinkView;
extern _AGS_CHARACTER_GET_TRANSPARENCY AGS_Character_get_Transparency;
extern _AGS_CHARACTER_SET_TRANSPARENCY AGS_Character_set_Transparency;
extern _AGS_CHARACTER_GET_TURNBEFOREWALKING AGS_Character_get_TurnBeforeWalking;
extern _AGS_CHARACTER_SET_TURNBEFOREWALKING AGS_Character_set_TurnBeforeWalking;
extern _AGS_CHARACTER_GET_VIEW AGS_Character_get_View;
extern _AGS_CHARACTER_GET_WALKSPEEDX AGS_Character_get_WalkSpeedX;
extern _AGS_CHARACTER_GET_WALKSPEEDY AGS_Character_get_WalkSpeedY;
extern _AGS_CHARACTER_GET_X AGS_Character_get_x;
extern _AGS_CHARACTER_SET_X AGS_Character_set_x;
extern _AGS_CHARACTER_GET_Y AGS_Character_get_y;
extern _AGS_CHARACTER_SET_Y AGS_Character_set_y;
extern _AGS_CHARACTER_GET_Z AGS_Character_get_z;
extern _AGS_CHARACTER_SET_Z AGS_Character_set_z;
typedef struct AGS_RoomThing {
	int RoomID;
	int ThingID;
} AGS_RoomThing;

#define luags_checkRoomThing(L,idx,meta,name)  (AGS_RoomThing*)llh_checkstruct(L,idx,meta,name)

extern int ags_current_room;
extern long long* ags_hotspot_array;
extern long long* ags_region_array;
extern long long* ags_object_array;
extern int luaopen_ags(lua_State *L);
extern int luaopen_ags_ViewFrame(lua_State *L);
extern int luaopen_ags_DrawingSurface(lua_State *L);
extern int luaopen_ags_Room(lua_State *L);
extern int luaopen_ags_Game(lua_State *L);
extern int luaopen_ags_Parser(lua_State *L);
extern int luaopen_ags_Mouse(lua_State *L);
extern int luaopen_ags_File(lua_State *L);
extern int luaopen_ags_InventoryItem(lua_State *L);
extern int luaopen_ags_Overlay(lua_State *L);
extern int luaopen_ags_DynamicSprite(lua_State *L);
extern int luaopen_ags_GUIControl(lua_State *L);
extern int luaopen_ags_Label(lua_State *L);
extern int luaopen_ags_Button(lua_State *L);
extern int luaopen_ags_Slider(lua_State *L);
extern int luaopen_ags_TextBox(lua_State *L);
extern int luaopen_ags_InvWindow(lua_State *L);
extern int luaopen_ags_ListBox(lua_State *L);
extern int luaopen_ags_GUI(lua_State *L);
extern int luaopen_ags_Hotspot(lua_State *L);
extern int luaopen_ags_Region(lua_State *L);
extern int luaopen_ags_Dialog(lua_State *L);
extern int luaopen_ags_DateTime(lua_State *L);
extern int luaopen_ags_AudioChannel(lua_State *L);
extern int luaopen_ags_AudioClip(lua_State *L);
extern int luaopen_ags_System(lua_State *L);
extern int luaopen_ags_Object(lua_State *L);
extern int luaopen_ags_Character(lua_State *L);

// AGS Interop Method Signatures
AGS_ViewFrame* Lua_ToViewFrame(void* ptr);
AGS_ViewFrame* LuaValueList_geti_AsViewFrames(void* ptr, int i);
void LuaValueList_seti_AsViewFrames(void* ptr, int i, AGS_ViewFrame* viewframe);
void* ViewFrame_AsLuaValue(AGS_ViewFrame* viewframe);
AGS_DrawingSurface* Lua_ToDrawingSurface(void* ptr);
AGS_DrawingSurface* LuaValueList_geti_AsDrawingSurfaces(void* ptr, int i);
void LuaValueList_seti_AsDrawingSurfaces(void* ptr, int i, AGS_DrawingSurface* drawingsurface);
void* DrawingSurface_AsLuaValue(AGS_DrawingSurface* drawingsurface);
AGS_File* Lua_ToFile(void* ptr);
AGS_File* LuaValueList_geti_AsFiles(void* ptr, int i);
void LuaValueList_seti_AsFiles(void* ptr, int i, AGS_File* file);
void* File_AsLuaValue(AGS_File* file);
AGS_InventoryItem* Lua_ToInventoryItem(void* ptr);
AGS_InventoryItem* LuaValueList_geti_AsInventoryItems(void* ptr, int i);
void LuaValueList_seti_AsInventoryItems(void* ptr, int i, AGS_InventoryItem* inventoryitem);
void* InventoryItem_AsLuaValue(AGS_InventoryItem* inventoryitem);
AGS_Overlay* Lua_ToOverlay(void* ptr);
AGS_Overlay* LuaValueList_geti_AsOverlays(void* ptr, int i);
void LuaValueList_seti_AsOverlays(void* ptr, int i, AGS_Overlay* overlay);
void* Overlay_AsLuaValue(AGS_Overlay* overlay);
AGS_DynamicSprite* Lua_ToDynamicSprite(void* ptr);
AGS_DynamicSprite* LuaValueList_geti_AsDynamicSprites(void* ptr, int i);
void LuaValueList_seti_AsDynamicSprites(void* ptr, int i, AGS_DynamicSprite* dynamicsprite);
void* DynamicSprite_AsLuaValue(AGS_DynamicSprite* dynamicsprite);
AGS_GUIControl* Lua_ToGUIControl(void* ptr);
AGS_GUIControl* LuaValueList_geti_AsGUIControls(void* ptr, int i);
void LuaValueList_seti_AsGUIControls(void* ptr, int i, AGS_GUIControl* guicontrol);
void* GUIControl_AsLuaValue(AGS_GUIControl* guicontrol);
AGS_Label* Lua_ToLabel(void* ptr);
AGS_Label* LuaValueList_geti_AsLabels(void* ptr, int i);
void LuaValueList_seti_AsLabels(void* ptr, int i, AGS_Label* label);
void* Label_AsLuaValue(AGS_Label* label);
AGS_Button* Lua_ToButton(void* ptr);
AGS_Button* LuaValueList_geti_AsButtons(void* ptr, int i);
void LuaValueList_seti_AsButtons(void* ptr, int i, AGS_Button* button);
void* Button_AsLuaValue(AGS_Button* button);
AGS_Slider* Lua_ToSlider(void* ptr);
AGS_Slider* LuaValueList_geti_AsSliders(void* ptr, int i);
void LuaValueList_seti_AsSliders(void* ptr, int i, AGS_Slider* slider);
void* Slider_AsLuaValue(AGS_Slider* slider);
AGS_TextBox* Lua_ToTextBox(void* ptr);
AGS_TextBox* LuaValueList_geti_AsTextBoxes(void* ptr, int i);
void LuaValueList_seti_AsTextBoxes(void* ptr, int i, AGS_TextBox* textbox);
void* TextBox_AsLuaValue(AGS_TextBox* textbox);
AGS_InvWindow* Lua_ToInvWindow(void* ptr);
AGS_InvWindow* LuaValueList_geti_AsInvWindows(void* ptr, int i);
void LuaValueList_seti_AsInvWindows(void* ptr, int i, AGS_InvWindow* invwindow);
void* InvWindow_AsLuaValue(AGS_InvWindow* invwindow);
AGS_ListBox* Lua_ToListBox(void* ptr);
AGS_ListBox* LuaValueList_geti_AsListBoxes(void* ptr, int i);
void LuaValueList_seti_AsListBoxes(void* ptr, int i, AGS_ListBox* listbox);
void* ListBox_AsLuaValue(AGS_ListBox* listbox);
AGS_GUI* Lua_ToGUI(void* ptr);
AGS_GUI* LuaValueList_geti_AsGUIs(void* ptr, int i);
void LuaValueList_seti_AsGUIs(void* ptr, int i, AGS_GUI* gui);
void* GUI_AsLuaValue(AGS_GUI* gui);
AGS_Hotspot* Lua_ToHotspot(void* ptr);
AGS_Hotspot* LuaValueList_geti_AsHotspots(void* ptr, int i);
void LuaValueList_seti_AsHotspots(void* ptr, int i, AGS_Hotspot* hotspot);
void* Hotspot_AsLuaValue(AGS_Hotspot* hotspot);
AGS_Region* Lua_ToRegion(void* ptr);
AGS_Region* LuaValueList_geti_AsRegions(void* ptr, int i);
void LuaValueList_seti_AsRegions(void* ptr, int i, AGS_Region* region);
void* Region_AsLuaValue(AGS_Region* region);
AGS_Dialog* Lua_ToDialog(void* ptr);
AGS_Dialog* LuaValueList_geti_AsDialogs(void* ptr, int i);
void LuaValueList_seti_AsDialogs(void* ptr, int i, AGS_Dialog* dialog);
void* Dialog_AsLuaValue(AGS_Dialog* dialog);
AGS_DateTime* Lua_ToDateTime(void* ptr);
AGS_DateTime* LuaValueList_geti_AsDateTimes(void* ptr, int i);
void LuaValueList_seti_AsDateTimes(void* ptr, int i, AGS_DateTime* datetime);
void* DateTime_AsLuaValue(AGS_DateTime* datetime);
AGS_AudioChannel* Lua_ToAudioChannel(void* ptr);
AGS_AudioChannel* LuaValueList_geti_AsAudioChannels(void* ptr, int i);
void LuaValueList_seti_AsAudioChannels(void* ptr, int i, AGS_AudioChannel* audiochannel);
void* AudioChannel_AsLuaValue(AGS_AudioChannel* audiochannel);
AGS_AudioClip* Lua_ToAudioClip(void* ptr);
AGS_AudioClip* LuaValueList_geti_AsAudioClips(void* ptr, int i);
void LuaValueList_seti_AsAudioClips(void* ptr, int i, AGS_AudioClip* audioclip);
void* AudioClip_AsLuaValue(AGS_AudioClip* audioclip);
AGS_Object* Lua_ToObject(void* ptr);
AGS_Object* LuaValueList_geti_AsObjects(void* ptr, int i);
void LuaValueList_seti_AsObjects(void* ptr, int i, AGS_Object* object);
void* Object_AsLuaValue(AGS_Object* object);
AGS_Character* Lua_ToCharacter(void* ptr);
AGS_Character* LuaValueList_geti_AsCharacters(void* ptr, int i);
void LuaValueList_seti_AsCharacters(void* ptr, int i, AGS_Character* character);
void* Character_AsLuaValue(AGS_Character* character);
#endif
