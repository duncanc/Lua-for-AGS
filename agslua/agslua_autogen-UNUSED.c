
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <llh.h>
}

#include "agsplugin.h"



// Error messages
static const char* ATTEMPT_TO_SET_READONLY_ATTRIBUTE = "attempt to set read-only attribute";

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

// Integer constants and enums
static const llh_const_int luags_constants[] = {
	{"MAX_INV",AGS_MAX_INV},
	{"FOLLOW_EXACTLY",AGS_FOLLOW_EXACTLY},
	{"NARRATOR",AGS_NARRATOR},
	{"OPT_WALKONLOOK",AGS_OPT_WALKONLOOK},
	{"OPT_DIALOGOPTIONSGUI",AGS_OPT_DIALOGOPTIONSGUI},
	{"OPT_ANTIGLIDE",AGS_OPT_ANTIGLIDE},
	{"OPT_DIALOGOPTIONSGAP",AGS_OPT_DIALOGOPTIONSGAP},
	{"OPT_WHENGUIDISABLED",AGS_OPT_WHENGUIDISABLED},
	{"OPT_ALWAYSSPEECH",AGS_OPT_ALWAYSSPEECH},
	{"OPT_PIXELPERFECT",AGS_OPT_PIXELPERFECT},
	{"OPT_NOWALKMODE",AGS_OPT_NOWALKMODE},
	{"OPT_FIXEDINVCURSOR",AGS_OPT_FIXEDINVCURSOR},
	{"OPT_DONTLOSEINV",AGS_OPT_DONTLOSEINV},
	{"OPT_TURNBEFOREWALK",AGS_OPT_TURNBEFOREWALK},
	{"OPT_HANDLEINVCLICKS",AGS_OPT_HANDLEINVCLICKS},
	{"OPT_MOUSEWHEEL",AGS_OPT_MOUSEWHEEL},
	{"OPT_DIALOGNUMBERED",AGS_OPT_DIALOGNUMBERED},
	{"OPT_DIALOGUPWARDS",AGS_OPT_DIALOGUPWARDS},
	{"OPT_CROSSFADEMUSIC",AGS_OPT_CROSSFADEMUSIC},
	{"OPT_ANTIALIASFONTS",AGS_OPT_ANTIALIASFONTS},
	{"OPT_THOUGHTGUI",AGS_OPT_THOUGHTGUI},
	{"OPT_TURNWHENFACING",AGS_OPT_TURNWHENFACING},
	{"OPT_RIGHTTOLEFT",AGS_OPT_RIGHTTOLEFT},
	{"OPT_MULTIPLEINV",AGS_OPT_MULTIPLEINV},
	{"OPT_SAVEGAMESCREENSHOTS",AGS_OPT_SAVEGAMESCREENSHOTS},
	{"OPT_PORTRAITPOSITION",AGS_OPT_PORTRAITPOSITION},
	{"OPT_LIPSYNCTEXT",AGS_OPT_LIPSYNCTEXT},
	{"COLOR_TRANSPARENT",AGS_COLOR_TRANSPARENT},
	{"DIALOG_PARSER_SELECTED",AGS_DIALOG_PARSER_SELECTED},
	{"RUN_DIALOG_RETURN",AGS_RUN_DIALOG_RETURN},
	{"RUN_DIALOG_STOP_DIALOG",AGS_RUN_DIALOG_STOP_DIALOG},
	{"RUN_DIALOG_GOTO_PREVIOUS",AGS_RUN_DIALOG_GOTO_PREVIOUS},
	{"SCR_NO_VALUE",AGS_SCR_NO_VALUE},

	// bool
	{"false",AGS_false},
	{"true",AGS_true},

	// eOperatingSystem
	{"eOSDOS",AGS_eOSDOS},
	{"eOSWindows",AGS_eOSWindows},
	{"eOSLinux",AGS_eOSLinux},
	{"eOSMacOS",AGS_eOSMacOS},

	// TransitionStyle
	{"eTransitionFade",AGS_eTransitionFade},
	{"eTransitionInstant",AGS_eTransitionInstant},
	{"eTransitionDissolve",AGS_eTransitionDissolve},
	{"eTransitionBoxout",AGS_eTransitionBoxout},
	{"eTransitionCrossfade",AGS_eTransitionCrossfade},

	// MouseButton
	{"eMouseLeft",AGS_eMouseLeft},
	{"eMouseRight",AGS_eMouseRight},
	{"eMouseMiddle",AGS_eMouseMiddle},
	{"eMouseLeftInv",AGS_eMouseLeftInv},
	{"eMouseRightInv",AGS_eMouseRightInv},
	{"eMouseWheelNorth",AGS_eMouseWheelNorth},
	{"eMouseWheelSouth",AGS_eMouseWheelSouth},

	// RoundDirection
	{"eRoundDown",AGS_eRoundDown},
	{"eRoundNearest",AGS_eRoundNearest},
	{"eRoundUp",AGS_eRoundUp},

	// RepeatStyle
	{"eOnce",AGS_eOnce},
	{"eRepeat",AGS_eRepeat},

	// Alignment
	{"eAlignLeft",AGS_eAlignLeft},
	{"eAlignCentre",AGS_eAlignCentre},
	{"eAlignRight",AGS_eAlignRight},

	// LocationType
	{"eLocationNothing",AGS_eLocationNothing},
	{"eLocationHotspot",AGS_eLocationHotspot},
	{"eLocationCharacter",AGS_eLocationCharacter},
	{"eLocationObject",AGS_eLocationObject},

	// CutsceneSkipType
	{"eSkipESCOnly",AGS_eSkipESCOnly},
	{"eSkipAnyKey",AGS_eSkipAnyKey},
	{"eSkipMouseClick",AGS_eSkipMouseClick},
	{"eSkipAnyKeyOrMouseClick",AGS_eSkipAnyKeyOrMouseClick},
	{"eSkipESCOrRightButton",AGS_eSkipESCOrRightButton},

	// DialogOptionState
	{"eOptionOff",AGS_eOptionOff},
	{"eOptionOn",AGS_eOptionOn},
	{"eOptionOffForever",AGS_eOptionOffForever},

	// eSpeechStyle
	{"eSpeechLucasarts",AGS_eSpeechLucasarts},
	{"eSpeechSierra",AGS_eSpeechSierra},
	{"eSpeechSierraWithBackground",AGS_eSpeechSierraWithBackground},
	{"eSpeechFullScreen",AGS_eSpeechFullScreen},

	// eVoiceMode
	{"eSpeechTextOnly",AGS_eSpeechTextOnly},
	{"eSpeechVoiceAndText",AGS_eSpeechVoiceAndText},
	{"eSpeechVoiceOnly",AGS_eSpeechVoiceOnly},

	// eFlipDirection
	{"eFlipLeftToRight",AGS_eFlipLeftToRight},
	{"eFlipUpsideDown",AGS_eFlipUpsideDown},
	{"eFlipBoth",AGS_eFlipBoth},

	// eCDAudioFunction
	{"eCDIsDriverPresent",AGS_eCDIsDriverPresent},
	{"eCDGetPlayingStatus",AGS_eCDGetPlayingStatus},
	{"eCDPlayTrack",AGS_eCDPlayTrack},
	{"eCDPausePlayback",AGS_eCDPausePlayback},
	{"eCDResumePlayback",AGS_eCDResumePlayback},
	{"eCDGetNumTracks",AGS_eCDGetNumTracks},
	{"eCDEject",AGS_eCDEject},
	{"eCDCloseTray",AGS_eCDCloseTray},
	{"eCDGetCDDriveCount",AGS_eCDGetCDDriveCount},
	{"eCDSelectActiveCDDrive",AGS_eCDSelectActiveCDDrive},

	// DialogOptionSayStyle
	{"eSayUseOptionSetting",AGS_eSayUseOptionSetting},
	{"eSayAlways",AGS_eSayAlways},
	{"eSayNever",AGS_eSayNever},

	// VideoSkipStyle
	{"eVideoSkipNotAllowed",AGS_eVideoSkipNotAllowed},
	{"eVideoSkipEscKey",AGS_eVideoSkipEscKey},
	{"eVideoSkipAnyKey",AGS_eVideoSkipAnyKey},
	{"eVideoSkipAnyKeyOrMouse",AGS_eVideoSkipAnyKeyOrMouse},

	// eKeyCode
	{"eKeyCtrlA",AGS_eKeyCtrlA},
	{"eKeyCtrlB",AGS_eKeyCtrlB},
	{"eKeyCtrlC",AGS_eKeyCtrlC},
	{"eKeyCtrlD",AGS_eKeyCtrlD},
	{"eKeyCtrlE",AGS_eKeyCtrlE},
	{"eKeyCtrlF",AGS_eKeyCtrlF},
	{"eKeyCtrlG",AGS_eKeyCtrlG},
	{"eKeyCtrlH",AGS_eKeyCtrlH},
	{"eKeyBackspace",AGS_eKeyBackspace},
	{"eKeyCtrlI",AGS_eKeyCtrlI},
	{"eKeyTab",AGS_eKeyTab},
	{"eKeyCtrlJ",AGS_eKeyCtrlJ},
	{"eKeyCtrlK",AGS_eKeyCtrlK},
	{"eKeyCtrlL",AGS_eKeyCtrlL},
	{"eKeyCtrlM",AGS_eKeyCtrlM},
	{"eKeyReturn",AGS_eKeyReturn},
	{"eKeyCtrlN",AGS_eKeyCtrlN},
	{"eKeyCtrlO",AGS_eKeyCtrlO},
	{"eKeyCtrlP",AGS_eKeyCtrlP},
	{"eKeyCtrlQ",AGS_eKeyCtrlQ},
	{"eKeyCtrlR",AGS_eKeyCtrlR},
	{"eKeyCtrlS",AGS_eKeyCtrlS},
	{"eKeyCtrlT",AGS_eKeyCtrlT},
	{"eKeyCtrlU",AGS_eKeyCtrlU},
	{"eKeyCtrlV",AGS_eKeyCtrlV},
	{"eKeyCtrlW",AGS_eKeyCtrlW},
	{"eKeyCtrlX",AGS_eKeyCtrlX},
	{"eKeyCtrlY",AGS_eKeyCtrlY},
	{"eKeyCtrlZ",AGS_eKeyCtrlZ},
	{"eKeyEscape",AGS_eKeyEscape},
	{"eKeySpace",AGS_eKeySpace},
	{"eKeyExclamationMark",AGS_eKeyExclamationMark},
	{"eKeyDoubleQuote",AGS_eKeyDoubleQuote},
	{"eKeyHash",AGS_eKeyHash},
	{"eKeyDollar",AGS_eKeyDollar},
	{"eKeyPercent",AGS_eKeyPercent},
	{"eKeyAmpersand",AGS_eKeyAmpersand},
	{"eKeySingleQuote",AGS_eKeySingleQuote},
	{"eKeyOpenParenthesis",AGS_eKeyOpenParenthesis},
	{"eKeyCloseParenthesis",AGS_eKeyCloseParenthesis},
	{"eKeyAsterisk",AGS_eKeyAsterisk},
	{"eKeyPlus",AGS_eKeyPlus},
	{"eKeyComma",AGS_eKeyComma},
	{"eKeyHyphen",AGS_eKeyHyphen},
	{"eKeyPeriod",AGS_eKeyPeriod},
	{"eKeyForwardSlash",AGS_eKeyForwardSlash},
	{"eKey0",AGS_eKey0},
	{"eKey1",AGS_eKey1},
	{"eKey2",AGS_eKey2},
	{"eKey3",AGS_eKey3},
	{"eKey4",AGS_eKey4},
	{"eKey5",AGS_eKey5},
	{"eKey6",AGS_eKey6},
	{"eKey7",AGS_eKey7},
	{"eKey8",AGS_eKey8},
	{"eKey9",AGS_eKey9},
	{"eKeyColon",AGS_eKeyColon},
	{"eKeySemiColon",AGS_eKeySemiColon},
	{"eKeyLessThan",AGS_eKeyLessThan},
	{"eKeyEquals",AGS_eKeyEquals},
	{"eKeyGreaterThan",AGS_eKeyGreaterThan},
	{"eKeyQuestionMark",AGS_eKeyQuestionMark},
	{"eKeyAt",AGS_eKeyAt},
	{"eKeyA",AGS_eKeyA},
	{"eKeyB",AGS_eKeyB},
	{"eKeyC",AGS_eKeyC},
	{"eKeyD",AGS_eKeyD},
	{"eKeyE",AGS_eKeyE},
	{"eKeyF",AGS_eKeyF},
	{"eKeyG",AGS_eKeyG},
	{"eKeyH",AGS_eKeyH},
	{"eKeyI",AGS_eKeyI},
	{"eKeyJ",AGS_eKeyJ},
	{"eKeyK",AGS_eKeyK},
	{"eKeyL",AGS_eKeyL},
	{"eKeyM",AGS_eKeyM},
	{"eKeyN",AGS_eKeyN},
	{"eKeyO",AGS_eKeyO},
	{"eKeyP",AGS_eKeyP},
	{"eKeyQ",AGS_eKeyQ},
	{"eKeyR",AGS_eKeyR},
	{"eKeyS",AGS_eKeyS},
	{"eKeyT",AGS_eKeyT},
	{"eKeyU",AGS_eKeyU},
	{"eKeyV",AGS_eKeyV},
	{"eKeyW",AGS_eKeyW},
	{"eKeyX",AGS_eKeyX},
	{"eKeyY",AGS_eKeyY},
	{"eKeyZ",AGS_eKeyZ},
	{"eKeyOpenBracket",AGS_eKeyOpenBracket},
	{"eKeyBackSlash",AGS_eKeyBackSlash},
	{"eKeyCloseBracket",AGS_eKeyCloseBracket},
	{"eKeyUnderscore",AGS_eKeyUnderscore},
	{"eKeyF1",AGS_eKeyF1},
	{"eKeyF2",AGS_eKeyF2},
	{"eKeyF3",AGS_eKeyF3},
	{"eKeyF4",AGS_eKeyF4},
	{"eKeyF5",AGS_eKeyF5},
	{"eKeyF6",AGS_eKeyF6},
	{"eKeyF7",AGS_eKeyF7},
	{"eKeyF8",AGS_eKeyF8},
	{"eKeyF9",AGS_eKeyF9},
	{"eKeyF10",AGS_eKeyF10},
	{"eKeyHome",AGS_eKeyHome},
	{"eKeyUpArrow",AGS_eKeyUpArrow},
	{"eKeyPageUp",AGS_eKeyPageUp},
	{"eKeyLeftArrow",AGS_eKeyLeftArrow},
	{"eKeyNumPad5",AGS_eKeyNumPad5},
	{"eKeyRightArrow",AGS_eKeyRightArrow},
	{"eKeyEnd",AGS_eKeyEnd},
	{"eKeyDownArrow",AGS_eKeyDownArrow},
	{"eKeyPageDown",AGS_eKeyPageDown},
	{"eKeyInsert",AGS_eKeyInsert},
	{"eKeyDelete",AGS_eKeyDelete},
	{"eKeyF11",AGS_eKeyF11},
	{"eKeyF12",AGS_eKeyF12},

	// FileMode
	{"eFileRead",AGS_eFileRead},
	{"eFileWrite",AGS_eFileWrite},
	{"eFileAppend",AGS_eFileAppend},

	// EventType
	{"eEventLeaveRoom",AGS_eEventLeaveRoom},
	{"eEventEnterRoomBeforeFadein",AGS_eEventEnterRoomBeforeFadein},
	{"eEventGotScore",AGS_eEventGotScore},
	{"eEventGUIMouseDown",AGS_eEventGUIMouseDown},
	{"eEventGUIMouseUp",AGS_eEventGUIMouseUp},
	{"eEventAddInventory",AGS_eEventAddInventory},
	{"eEventLoseInventory",AGS_eEventLoseInventory},
	{"eEventRestoreGame",AGS_eEventRestoreGame},

	// BlockingStyle
	{"eBlock",AGS_eBlock},
	{"eNoBlock",AGS_eNoBlock},

	// Direction
	{"eForwards",AGS_eForwards},
	{"eBackwards",AGS_eBackwards},

	// WalkWhere
	{"eAnywhere",AGS_eAnywhere},
	{"eWalkableAreas",AGS_eWalkableAreas},
};

// Enum labels
#define AGS_eVoiceMode int
#define AGS_RepeatStyle int
#define AGS_CursorMode int
#define AGS_eFlipDirection int
#define AGS_EventType int
#define AGS_DialogOptionState int
#define AGS_FontType int
#define AGS_eKeyCode int
#define AGS_eSpeechStyle int
#define AGS_WalkWhere int
#define AGS_bool int
#define AGS_Direction int
#define AGS_LocationType int
#define AGS_eOperatingSystem int
#define AGS_CHARID int
#define AGS_MouseButton int
#define AGS_BlockingStyle int
#define AGS_eCDAudioFunction int
#define AGS_DialogOptionSayStyle int
#define AGS_FileMode int
#define AGS_CutsceneSkipType int
#define AGS_TransitionStyle int
#define AGS_RoundDirection int
#define AGS_VideoSkipStyle int
#define AGS_function int
#define AGS_Alignment int

// Struct labels
#define AGS_ViewFrame void
#define AGS_DrawingSurface void
#define AGS_Room void
#define AGS_Game void
#define AGS_Parser void
#define AGS_Mouse void
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
#define AGS_DialogOptionsRenderingInfo void
#define AGS_System void
#define AGS_Object void
#define AGS_Character void

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
typedef int (*_AGS_ISGAMEPAUSED)();
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
typedef int (*_AGS_FLOATTOINT)(float value, AGS_RoundDirection param2);
typedef float (*_AGS_INTTOFLOAT)(int value);
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
typedef int (*_AGS_ISVOXAVAILABLE)();
typedef int (*_AGS_ISMUSICVOXAVAILABLE)();
typedef int (*_AGS_GETCURRENTMUSIC)();
typedef void (*_AGS_SETMUSICREPEAT)(int repeat);
typedef void (*_AGS_SETMUSICVOLUME)(int volume);
typedef void (*_AGS_SETSOUNDVOLUME)(int volume);
typedef void (*_AGS_SETSPEECHVOLUME)(int volume);
typedef void (*_AGS_SETMUSICMASTERVOLUME)(int volume);
typedef void (*_AGS_SETDIGITALMASTERVOLUME)(int volume);
typedef void (*_AGS_SEEKMODPATTERN)(int pattern);
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
typedef AGS_bool (*_AGS_GAME_SETSAVEGAMEDIRECTORY)(const char* directory);
typedef void (*_AGS_GAME_STOPSOUND)(AGS_bool includeAmbientSounds);
typedef int (*_AGS_GAME_GET_CHARACTERCOUNT)();
typedef int (*_AGS_GAME_GET_DIALOGCOUNT)();
typedef const char* (*_AGS_GAME_GET_FILENAME)();
typedef int (*_AGS_GAME_GET_FONTCOUNT)();
typedef const char* (*_AGS_GAME_GETI_GLOBALMESSAGES)(int i);
typedef const char* (*_AGS_GAME_GETI_GLOBALSTRINGS)(int i);
typedef void (*_AGS_GAME_SETI_GLOBALSTRINGS)(int i, const char* new_value);
typedef int (*_AGS_GAME_GET_GUICOUNT)();
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

// DialogOptionsRenderingInfo method signatures
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_ACTIVEOPTIONID)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_ACTIVEOPTIONID)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef AGS_Dialog* (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_DIALOGTORENDER)(AGS_DialogOptionsRenderingInfo* self);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_HEIGHT)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_HEIGHT)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXWIDTH)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXWIDTH)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXX)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXX)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXY)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXY)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef AGS_DrawingSurface* (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_SURFACE)(AGS_DialogOptionsRenderingInfo* self);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_WIDTH)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_WIDTH)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_X)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_X)(AGS_DialogOptionsRenderingInfo* self, int new_value);
typedef int (*_AGS_DIALOGOPTIONSRENDERINGINFO_GET_Y)(AGS_DialogOptionsRenderingInfo* self);
typedef void (*_AGS_DIALOGOPTIONSRENDERINGINFO_SET_Y)(AGS_DialogOptionsRenderingInfo* self, int new_value);

// System method signatures
typedef AGS_bool (*_AGS_SYSTEM_GET_CAPSLOCK)();
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

// Global function instances
_AGS_DISPLAY AGS_Display;
_AGS_DISPLAYAT AGS_DisplayAt;
_AGS_DISPLAYATY AGS_DisplayAtY;
_AGS_DISPLAYMESSAGE AGS_DisplayMessage;
_AGS_DISPLAYMESSAGEATY AGS_DisplayMessageAtY;
_AGS_DISPLAYTOPBAR AGS_DisplayTopBar;
_AGS_DISPLAYMESSAGEBAR AGS_DisplayMessageBar;
_AGS_RESETROOM AGS_ResetRoom;
_AGS_HASPLAYERBEENINROOM AGS_HasPlayerBeenInRoom;
_AGS_PROCESSCLICK AGS_ProcessClick;
_AGS_ABORTGAME AGS_AbortGame;
_AGS_QUITGAME AGS_QuitGame;
_AGS_SETGAMESPEED AGS_SetGameSpeed;
_AGS_GETGAMESPEED AGS_GetGameSpeed;
_AGS_SETGAMEOPTION AGS_SetGameOption;
_AGS_GETGAMEOPTION AGS_GetGameOption;
_AGS_DEBUG AGS_Debug;
_AGS_CALLROOMSCRIPT AGS_CallRoomScript;
_AGS_RUNAGSGAME AGS_RunAGSGame;
_AGS_GETTRANSLATION AGS_GetTranslation;
_AGS_ISTRANSLATIONAVAILABLE AGS_IsTranslationAvailable;
_AGS_RESTOREGAMEDIALOG AGS_RestoreGameDialog;
_AGS_SAVEGAMEDIALOG AGS_SaveGameDialog;
_AGS_RESTARTGAME AGS_RestartGame;
_AGS_SAVEGAMESLOT AGS_SaveGameSlot;
_AGS_RESTOREGAMESLOT AGS_RestoreGameSlot;
_AGS_DELETESAVESLOT AGS_DeleteSaveSlot;
_AGS_SETRESTARTPOINT AGS_SetRestartPoint;
_AGS_GETLOCATIONTYPE AGS_GetLocationType;
_AGS_GETWALKABLEAREAAT AGS_GetWalkableAreaAt;
_AGS_GETSCALINGAT AGS_GetScalingAt;
_AGS_GETROOMPROPERTY AGS_GetRoomProperty;
_AGS_SETVIEWPORT AGS_SetViewport;
_AGS_RELEASEVIEWPORT AGS_ReleaseViewport;
_AGS_GETVIEWPORTX AGS_GetViewportX;
_AGS_GETVIEWPORTY AGS_GetViewportY;
_AGS_ISGAMEPAUSED AGS_IsGamePaused;
_AGS_ISCHANNELPLAYING AGS_IsChannelPlaying;
_AGS_ISSOUNDPLAYING AGS_IsSoundPlaying;
_AGS_ISMUSICPLAYING AGS_IsMusicPlaying;
_AGS_GETMIDIPOSITION AGS_GetMIDIPosition;
_AGS_SEEKMIDIPOSITION AGS_SeekMIDIPosition;
_AGS_GETMP3POSMILLIS AGS_GetMP3PosMillis;
_AGS_SEEKMP3POSMILLIS AGS_SeekMP3PosMillis;
_AGS_SETCHANNELVOLUME AGS_SetChannelVolume;
_AGS_STOPCHANNEL AGS_StopChannel;
_AGS_STOPMUSIC AGS_StopMusic;
_AGS_GETGRAPHICALVARIABLE AGS_GetGraphicalVariable;
_AGS_SETGRAPHICALVARIABLE AGS_SetGraphicalVariable;
_AGS_DISABLEINTERFACE AGS_DisableInterface;
_AGS_ENABLEINTERFACE AGS_EnableInterface;
_AGS_ISINTERFACEENABLED AGS_IsInterfaceEnabled;
_AGS_SAID AGS_Said;
_AGS_GETTEXTWIDTH AGS_GetTextWidth;
_AGS_GETTEXTHEIGHT AGS_GetTextHeight;
_AGS_GIVESCORE AGS_GiveScore;
_AGS_UPDATEINVENTORY AGS_UpdateInventory;
_AGS_STOPDIALOG AGS_StopDialog;
_AGS_ARETHINGSOVERLAPPING AGS_AreThingsOverlapping;
_AGS_SETVOICEMODE AGS_SetVoiceMode;
_AGS_SETSKIPSPEECH AGS_SetSkipSpeech;
_AGS_SETSPEECHSTYLE AGS_SetSpeechStyle;
_AGS_SETTIMER AGS_SetTimer;
_AGS_ISTIMEREXPIRED AGS_IsTimerExpired;
_AGS_SETMULTITASKINGMODE AGS_SetMultitaskingMode;
_AGS_FLOATTOINT AGS_FloatToInt;
_AGS_INTTOFLOAT AGS_IntToFloat;
_AGS_FADEIN AGS_FadeIn;
_AGS_FADEOUT AGS_FadeOut;
_AGS_CYCLEPALETTE AGS_CyclePalette;
_AGS_SETPALRGB AGS_SetPalRGB;
_AGS_UPDATEPALETTE AGS_UpdatePalette;
_AGS_TINTSCREEN AGS_TintScreen;
_AGS_SETAMBIENTTINT AGS_SetAmbientTint;
_AGS_RANDOM AGS_Random;
_AGS_SETBACKGROUNDFRAME AGS_SetBackgroundFrame;
_AGS_GETBACKGROUNDFRAME AGS_GetBackgroundFrame;
_AGS_SHAKESCREEN AGS_ShakeScreen;
_AGS_SHAKESCREENBACKGROUND AGS_ShakeScreenBackground;
_AGS_SETSCREENTRANSITION AGS_SetScreenTransition;
_AGS_SETNEXTSCREENTRANSITION AGS_SetNextScreenTransition;
_AGS_SETFADECOLOR AGS_SetFadeColor;
_AGS_ISINTERACTIONAVAILABLE AGS_IsInteractionAvailable;
_AGS_REMOVEWALKABLEAREA AGS_RemoveWalkableArea;
_AGS_RESTOREWALKABLEAREA AGS_RestoreWalkableArea;
_AGS_SETAREASCALING AGS_SetAreaScaling;
_AGS_DISABLEGROUNDLEVELAREAS AGS_DisableGroundLevelAreas;
_AGS_ENABLEGROUNDLEVELAREAS AGS_EnableGroundLevelAreas;
_AGS_SETWALKBEHINDBASE AGS_SetWalkBehindBase;
_AGS_CDAUDIO AGS_CDAudio;
_AGS_PLAYFLIC AGS_PlayFlic;
_AGS_PLAYVIDEO AGS_PlayVideo;
_AGS_PLAYMUSIC AGS_PlayMusic;
_AGS_PLAYMUSICQUEUED AGS_PlayMusicQueued;
_AGS_PLAYSILENTMIDI AGS_PlaySilentMIDI;
_AGS_PLAYMP3FILE AGS_PlayMP3File;
_AGS_PLAYSOUND AGS_PlaySound;
_AGS_PLAYSOUNDEX AGS_PlaySoundEx;
_AGS_PLAYAMBIENTSOUND AGS_PlayAmbientSound;
_AGS_STOPAMBIENTSOUND AGS_StopAmbientSound;
_AGS_ISVOXAVAILABLE AGS_IsVoxAvailable;
_AGS_ISMUSICVOXAVAILABLE AGS_IsMusicVoxAvailable;
_AGS_GETCURRENTMUSIC AGS_GetCurrentMusic;
_AGS_SETMUSICREPEAT AGS_SetMusicRepeat;
_AGS_SETMUSICVOLUME AGS_SetMusicVolume;
_AGS_SETSOUNDVOLUME AGS_SetSoundVolume;
_AGS_SETSPEECHVOLUME AGS_SetSpeechVolume;
_AGS_SETMUSICMASTERVOLUME AGS_SetMusicMasterVolume;
_AGS_SETDIGITALMASTERVOLUME AGS_SetDigitalMasterVolume;
_AGS_SEEKMODPATTERN AGS_SeekMODPattern;
_AGS_SAVESCREENSHOT AGS_SaveScreenShot;
_AGS_PAUSEGAME AGS_PauseGame;
_AGS_UNPAUSEGAME AGS_UnPauseGame;
_AGS_WAIT AGS_Wait;
_AGS_WAITKEY AGS_WaitKey;
_AGS_WAITMOUSEKEY AGS_WaitMouseKey;
_AGS_ISKEYPRESSED AGS_IsKeyPressed;
_AGS_SETGLOBALINT AGS_SetGlobalInt;
_AGS_GETGLOBALINT AGS_GetGlobalInt;
_AGS_FLIPSCREEN AGS_FlipScreen;
_AGS_SKIPUNTILCHARACTERSTOPS AGS_SkipUntilCharacterStops;
_AGS_STARTCUTSCENE AGS_StartCutscene;
_AGS_ENDCUTSCENE AGS_EndCutscene;
_AGS_CLAIMEVENT AGS_ClaimEvent;
_AGS_SETTEXTWINDOWGUI AGS_SetTextWindowGUI;
_AGS_FINDGUIID AGS_FindGUIID;

// ViewFrame method instances
_AGS_VIEWFRAME_GET_FLIPPED AGS_ViewFrame_get_Flipped;
_AGS_VIEWFRAME_GET_FRAME AGS_ViewFrame_get_Frame;
_AGS_VIEWFRAME_GET_GRAPHIC AGS_ViewFrame_get_Graphic;
_AGS_VIEWFRAME_SET_GRAPHIC AGS_ViewFrame_set_Graphic;
_AGS_VIEWFRAME_GET_LOOP AGS_ViewFrame_get_Loop;
_AGS_VIEWFRAME_GET_SOUND AGS_ViewFrame_get_Sound;
_AGS_VIEWFRAME_SET_SOUND AGS_ViewFrame_set_Sound;
_AGS_VIEWFRAME_GET_SPEED AGS_ViewFrame_get_Speed;
_AGS_VIEWFRAME_GET_VIEW AGS_ViewFrame_get_View;

// DrawingSurface method instances
_AGS_DRAWINGSURFACE_CLEAR AGS_DrawingSurface_Clear;
_AGS_DRAWINGSURFACE_CREATECOPY AGS_DrawingSurface_CreateCopy;
_AGS_DRAWINGSURFACE_DRAWCIRCLE AGS_DrawingSurface_DrawCircle;
_AGS_DRAWINGSURFACE_DRAWIMAGE AGS_DrawingSurface_DrawImage;
_AGS_DRAWINGSURFACE_DRAWLINE AGS_DrawingSurface_DrawLine;
_AGS_DRAWINGSURFACE_DRAWMESSAGEWRAPPED AGS_DrawingSurface_DrawMessageWrapped;
_AGS_DRAWINGSURFACE_DRAWPIXEL AGS_DrawingSurface_DrawPixel;
_AGS_DRAWINGSURFACE_DRAWRECTANGLE AGS_DrawingSurface_DrawRectangle;
_AGS_DRAWINGSURFACE_DRAWSTRING AGS_DrawingSurface_DrawString;
_AGS_DRAWINGSURFACE_DRAWSTRINGWRAPPED AGS_DrawingSurface_DrawStringWrapped;
_AGS_DRAWINGSURFACE_DRAWSURFACE AGS_DrawingSurface_DrawSurface;
_AGS_DRAWINGSURFACE_DRAWTRIANGLE AGS_DrawingSurface_DrawTriangle;
_AGS_DRAWINGSURFACE_GETPIXEL AGS_DrawingSurface_GetPixel;
_AGS_DRAWINGSURFACE_RELEASE AGS_DrawingSurface_Release;
_AGS_DRAWINGSURFACE_GET_DRAWINGCOLOR AGS_DrawingSurface_get_DrawingColor;
_AGS_DRAWINGSURFACE_SET_DRAWINGCOLOR AGS_DrawingSurface_set_DrawingColor;
_AGS_DRAWINGSURFACE_GET_HEIGHT AGS_DrawingSurface_get_Height;
_AGS_DRAWINGSURFACE_GET_USEHIGHRESCOORDINATES AGS_DrawingSurface_get_UseHighResCoordinates;
_AGS_DRAWINGSURFACE_SET_USEHIGHRESCOORDINATES AGS_DrawingSurface_set_UseHighResCoordinates;
_AGS_DRAWINGSURFACE_GET_WIDTH AGS_DrawingSurface_get_Width;

// Room method instances
_AGS_ROOM_GETTEXTPROPERTY AGS_Room_GetTextProperty;
_AGS_ROOM_GETDRAWINGSURFACEFORBACKGROUND AGS_Room_GetDrawingSurfaceForBackground;
_AGS_ROOM_GET_BOTTOMEDGE AGS_Room_get_BottomEdge;
_AGS_ROOM_GET_COLORDEPTH AGS_Room_get_ColorDepth;
_AGS_ROOM_GET_HEIGHT AGS_Room_get_Height;
_AGS_ROOM_GET_LEFTEDGE AGS_Room_get_LeftEdge;
_AGS_ROOM_GETI_MESSAGES AGS_Room_geti_Messages;
_AGS_ROOM_GET_MUSICONLOAD AGS_Room_get_MusicOnLoad;
_AGS_ROOM_GET_OBJECTCOUNT AGS_Room_get_ObjectCount;
_AGS_ROOM_GET_RIGHTEDGE AGS_Room_get_RightEdge;
_AGS_ROOM_GET_TOPEDGE AGS_Room_get_TopEdge;
_AGS_ROOM_GET_WIDTH AGS_Room_get_Width;

// Game method instances
_AGS_GAME_CHANGETRANSLATION AGS_Game_ChangeTranslation;
_AGS_GAME_DOONCEONLY AGS_Game_DoOnceOnly;
_AGS_GAME_GETCOLORFROMRGB AGS_Game_GetColorFromRGB;
_AGS_GAME_GETFRAMECOUNTFORLOOP AGS_Game_GetFrameCountForLoop;
_AGS_GAME_GETLOCATIONNAME AGS_Game_GetLocationName;
_AGS_GAME_GETLOOPCOUNTFORVIEW AGS_Game_GetLoopCountForView;
_AGS_GAME_GETMODPATTERN AGS_Game_GetMODPattern;
_AGS_GAME_GETRUNNEXTSETTINGFORLOOP AGS_Game_GetRunNextSettingForLoop;
_AGS_GAME_GETSAVESLOTDESCRIPTION AGS_Game_GetSaveSlotDescription;
_AGS_GAME_GETVIEWFRAME AGS_Game_GetViewFrame;
_AGS_GAME_INPUTBOX AGS_Game_InputBox;
_AGS_GAME_SETSAVEGAMEDIRECTORY AGS_Game_SetSaveGameDirectory;
_AGS_GAME_STOPSOUND AGS_Game_StopSound;
_AGS_GAME_GET_CHARACTERCOUNT AGS_Game_get_CharacterCount;
_AGS_GAME_GET_DIALOGCOUNT AGS_Game_get_DialogCount;
_AGS_GAME_GET_FILENAME AGS_Game_get_FileName;
_AGS_GAME_GET_FONTCOUNT AGS_Game_get_FontCount;
_AGS_GAME_GETI_GLOBALMESSAGES AGS_Game_geti_GlobalMessages;
_AGS_GAME_GETI_GLOBALSTRINGS AGS_Game_geti_GlobalStrings;
_AGS_GAME_SETI_GLOBALSTRINGS AGS_Game_seti_GlobalStrings;
_AGS_GAME_GET_GUICOUNT AGS_Game_get_GUICount;
_AGS_GAME_GET_INSKIPPABLECUTSCENE AGS_Game_get_InSkippableCutscene;
_AGS_GAME_GET_INVENTORYITEMCOUNT AGS_Game_get_InventoryItemCount;
_AGS_GAME_GET_MINIMUMTEXTDISPLAYTIMEMS AGS_Game_get_MinimumTextDisplayTimeMs;
_AGS_GAME_SET_MINIMUMTEXTDISPLAYTIMEMS AGS_Game_set_MinimumTextDisplayTimeMs;
_AGS_GAME_GET_MOUSECURSORCOUNT AGS_Game_get_MouseCursorCount;
_AGS_GAME_GET_NAME AGS_Game_get_Name;
_AGS_GAME_SET_NAME AGS_Game_set_Name;
_AGS_GAME_GET_NORMALFONT AGS_Game_get_NormalFont;
_AGS_GAME_SET_NORMALFONT AGS_Game_set_NormalFont;
_AGS_GAME_GET_SKIPPINGCUTSCENE AGS_Game_get_SkippingCutscene;
_AGS_GAME_GET_SPEECHFONT AGS_Game_get_SpeechFont;
_AGS_GAME_SET_SPEECHFONT AGS_Game_set_SpeechFont;
_AGS_GAME_GETI_SPRITEHEIGHT AGS_Game_geti_SpriteHeight;
_AGS_GAME_GETI_SPRITEWIDTH AGS_Game_geti_SpriteWidth;
_AGS_GAME_GET_TEXTREADINGSPEED AGS_Game_get_TextReadingSpeed;
_AGS_GAME_SET_TEXTREADINGSPEED AGS_Game_set_TextReadingSpeed;
_AGS_GAME_GET_TRANSLATIONFILENAME AGS_Game_get_TranslationFilename;
_AGS_GAME_GET_USENATIVECOORDINATES AGS_Game_get_UseNativeCoordinates;
_AGS_GAME_GET_VIEWCOUNT AGS_Game_get_ViewCount;

// Parser method instances
_AGS_PARSER_FINDWORDID AGS_Parser_FindWordID;
_AGS_PARSER_PARSETEXT AGS_Parser_ParseText;
_AGS_PARSER_SAID AGS_Parser_Said;
_AGS_PARSER_SAIDUNKNOWNWORD AGS_Parser_SaidUnknownWord;

// Mouse method instances
_AGS_MOUSE_CHANGEMODEGRAPHIC AGS_Mouse_ChangeModeGraphic;
_AGS_MOUSE_CHANGEMODEHOTSPOT AGS_Mouse_ChangeModeHotspot;
_AGS_MOUSE_CHANGEMODEVIEW AGS_Mouse_ChangeModeView;
_AGS_MOUSE_DISABLEMODE AGS_Mouse_DisableMode;
_AGS_MOUSE_ENABLEMODE AGS_Mouse_EnableMode;
_AGS_MOUSE_GETMODEGRAPHIC AGS_Mouse_GetModeGraphic;
_AGS_MOUSE_ISBUTTONDOWN AGS_Mouse_IsButtonDown;
_AGS_MOUSE_SAVECURSORUNTILITLEAVES AGS_Mouse_SaveCursorUntilItLeaves;
_AGS_MOUSE_SELECTNEXTMODE AGS_Mouse_SelectNextMode;
_AGS_MOUSE_SETBOUNDS AGS_Mouse_SetBounds;
_AGS_MOUSE_SETPOSITION AGS_Mouse_SetPosition;
_AGS_MOUSE_UPDATE AGS_Mouse_Update;
_AGS_MOUSE_USEDEFAULTGRAPHIC AGS_Mouse_UseDefaultGraphic;
_AGS_MOUSE_USEMODEGRAPHIC AGS_Mouse_UseModeGraphic;
_AGS_MOUSE_GET_MODE AGS_Mouse_get_Mode;
_AGS_MOUSE_SET_MODE AGS_Mouse_set_Mode;
_AGS_MOUSE_GET_VISIBLE AGS_Mouse_get_Visible;
_AGS_MOUSE_SET_VISIBLE AGS_Mouse_set_Visible;

// File method instances
_AGS_FILE_DELETE AGS_File_Delete;
_AGS_FILE_EXISTS AGS_File_Exists;
_AGS_FILE_OPEN AGS_File_Open;
_AGS_FILE_CLOSE AGS_File_Close;
_AGS_FILE_READINT AGS_File_ReadInt;
_AGS_FILE_READRAWCHAR AGS_File_ReadRawChar;
_AGS_FILE_READRAWINT AGS_File_ReadRawInt;
_AGS_FILE_READRAWLINEBACK AGS_File_ReadRawLineBack;
_AGS_FILE_READSTRINGBACK AGS_File_ReadStringBack;
_AGS_FILE_WRITEINT AGS_File_WriteInt;
_AGS_FILE_WRITERAWCHAR AGS_File_WriteRawChar;
_AGS_FILE_WRITERAWLINE AGS_File_WriteRawLine;
_AGS_FILE_WRITESTRING AGS_File_WriteString;
_AGS_FILE_GET_EOF AGS_File_get_EOF;
_AGS_FILE_GET_ERROR AGS_File_get_Error;

// InventoryItem method instances
_AGS_INVENTORYITEM_GETATSCREENXY AGS_InventoryItem_GetAtScreenXY;
_AGS_INVENTORYITEM_GETPROPERTY AGS_InventoryItem_GetProperty;
_AGS_INVENTORYITEM_GETTEXTPROPERTY AGS_InventoryItem_GetTextProperty;
_AGS_INVENTORYITEM_ISINTERACTIONAVAILABLE AGS_InventoryItem_IsInteractionAvailable;
_AGS_INVENTORYITEM_RUNINTERACTION AGS_InventoryItem_RunInteraction;
_AGS_INVENTORYITEM_GET_CURSORGRAPHIC AGS_InventoryItem_get_CursorGraphic;
_AGS_INVENTORYITEM_SET_CURSORGRAPHIC AGS_InventoryItem_set_CursorGraphic;
_AGS_INVENTORYITEM_GET_GRAPHIC AGS_InventoryItem_get_Graphic;
_AGS_INVENTORYITEM_SET_GRAPHIC AGS_InventoryItem_set_Graphic;
_AGS_INVENTORYITEM_GET_ID AGS_InventoryItem_get_ID;
_AGS_INVENTORYITEM_GET_NAME AGS_InventoryItem_get_Name;
_AGS_INVENTORYITEM_SET_NAME AGS_InventoryItem_set_Name;

// Overlay method instances
_AGS_OVERLAY_CREATEGRAPHICAL AGS_Overlay_CreateGraphical;
_AGS_OVERLAY_CREATETEXTUAL AGS_Overlay_CreateTextual;
_AGS_OVERLAY_SETTEXT AGS_Overlay_SetText;
_AGS_OVERLAY_REMOVE AGS_Overlay_Remove;
_AGS_OVERLAY_GET_VALID AGS_Overlay_get_Valid;
_AGS_OVERLAY_GET_X AGS_Overlay_get_X;
_AGS_OVERLAY_SET_X AGS_Overlay_set_X;
_AGS_OVERLAY_GET_Y AGS_Overlay_get_Y;
_AGS_OVERLAY_SET_Y AGS_Overlay_set_Y;

// DynamicSprite method instances
_AGS_DYNAMICSPRITE_CREATE AGS_DynamicSprite_Create;
_AGS_DYNAMICSPRITE_CREATEFROMBACKGROUND AGS_DynamicSprite_CreateFromBackground;
_AGS_DYNAMICSPRITE_CREATEFROMDRAWINGSURFACE AGS_DynamicSprite_CreateFromDrawingSurface;
_AGS_DYNAMICSPRITE_CREATEFROMEXISTINGSPRITE AGS_DynamicSprite_CreateFromExistingSprite;
_AGS_DYNAMICSPRITE_CREATEFROMFILE AGS_DynamicSprite_CreateFromFile;
_AGS_DYNAMICSPRITE_CREATEFROMSAVEGAME AGS_DynamicSprite_CreateFromSaveGame;
_AGS_DYNAMICSPRITE_CREATEFROMSCREENSHOT AGS_DynamicSprite_CreateFromScreenShot;
_AGS_DYNAMICSPRITE_CHANGECANVASSIZE AGS_DynamicSprite_ChangeCanvasSize;
_AGS_DYNAMICSPRITE_COPYTRANSPARENCYMASK AGS_DynamicSprite_CopyTransparencyMask;
_AGS_DYNAMICSPRITE_CROP AGS_DynamicSprite_Crop;
_AGS_DYNAMICSPRITE_DELETE AGS_DynamicSprite_Delete;
_AGS_DYNAMICSPRITE_FLIP AGS_DynamicSprite_Flip;
_AGS_DYNAMICSPRITE_GETDRAWINGSURFACE AGS_DynamicSprite_GetDrawingSurface;
_AGS_DYNAMICSPRITE_RESIZE AGS_DynamicSprite_Resize;
_AGS_DYNAMICSPRITE_ROTATE AGS_DynamicSprite_Rotate;
_AGS_DYNAMICSPRITE_SAVETOFILE AGS_DynamicSprite_SaveToFile;
_AGS_DYNAMICSPRITE_TINT AGS_DynamicSprite_Tint;
_AGS_DYNAMICSPRITE_GET_COLORDEPTH AGS_DynamicSprite_get_ColorDepth;
_AGS_DYNAMICSPRITE_GET_GRAPHIC AGS_DynamicSprite_get_Graphic;
_AGS_DYNAMICSPRITE_GET_HEIGHT AGS_DynamicSprite_get_Height;
_AGS_DYNAMICSPRITE_GET_WIDTH AGS_DynamicSprite_get_Width;

// GUIControl method instances
_AGS_GUICONTROL_BRINGTOFRONT AGS_GUIControl_BringToFront;
_AGS_GUICONTROL_GETATSCREENXY AGS_GUIControl_GetAtScreenXY;
_AGS_GUICONTROL_SENDTOBACK AGS_GUIControl_SendToBack;
_AGS_GUICONTROL_SETPOSITION AGS_GUIControl_SetPosition;
_AGS_GUICONTROL_SETSIZE AGS_GUIControl_SetSize;
_AGS_GUICONTROL_GET_ASBUTTON AGS_GUIControl_get_AsButton;
_AGS_GUICONTROL_GET_ASINVWINDOW AGS_GUIControl_get_AsInvWindow;
_AGS_GUICONTROL_GET_ASLABEL AGS_GUIControl_get_AsLabel;
_AGS_GUICONTROL_GET_ASLISTBOX AGS_GUIControl_get_AsListBox;
_AGS_GUICONTROL_GET_ASSLIDER AGS_GUIControl_get_AsSlider;
_AGS_GUICONTROL_GET_ASTEXTBOX AGS_GUIControl_get_AsTextBox;
_AGS_GUICONTROL_GET_CLICKABLE AGS_GUIControl_get_Clickable;
_AGS_GUICONTROL_SET_CLICKABLE AGS_GUIControl_set_Clickable;
_AGS_GUICONTROL_GET_ENABLED AGS_GUIControl_get_Enabled;
_AGS_GUICONTROL_SET_ENABLED AGS_GUIControl_set_Enabled;
_AGS_GUICONTROL_GET_HEIGHT AGS_GUIControl_get_Height;
_AGS_GUICONTROL_SET_HEIGHT AGS_GUIControl_set_Height;
_AGS_GUICONTROL_GET_ID AGS_GUIControl_get_ID;
_AGS_GUICONTROL_GET_OWNINGGUI AGS_GUIControl_get_OwningGUI;
_AGS_GUICONTROL_GET_VISIBLE AGS_GUIControl_get_Visible;
_AGS_GUICONTROL_SET_VISIBLE AGS_GUIControl_set_Visible;
_AGS_GUICONTROL_GET_WIDTH AGS_GUIControl_get_Width;
_AGS_GUICONTROL_SET_WIDTH AGS_GUIControl_set_Width;
_AGS_GUICONTROL_GET_X AGS_GUIControl_get_X;
_AGS_GUICONTROL_SET_X AGS_GUIControl_set_X;
_AGS_GUICONTROL_GET_Y AGS_GUIControl_get_Y;
_AGS_GUICONTROL_SET_Y AGS_GUIControl_set_Y;

// Label method instances
_AGS_LABEL_GET_FONT AGS_Label_get_Font;
_AGS_LABEL_SET_FONT AGS_Label_set_Font;
_AGS_LABEL_GET_TEXT AGS_Label_get_Text;
_AGS_LABEL_SET_TEXT AGS_Label_set_Text;
_AGS_LABEL_GET_TEXTCOLOR AGS_Label_get_TextColor;
_AGS_LABEL_SET_TEXTCOLOR AGS_Label_set_TextColor;

// Button method instances
_AGS_BUTTON_ANIMATE AGS_Button_Animate;
_AGS_BUTTON_GET_CLIPIMAGE AGS_Button_get_ClipImage;
_AGS_BUTTON_SET_CLIPIMAGE AGS_Button_set_ClipImage;
_AGS_BUTTON_GET_FONT AGS_Button_get_Font;
_AGS_BUTTON_SET_FONT AGS_Button_set_Font;
_AGS_BUTTON_GET_GRAPHIC AGS_Button_get_Graphic;
_AGS_BUTTON_GET_MOUSEOVERGRAPHIC AGS_Button_get_MouseOverGraphic;
_AGS_BUTTON_SET_MOUSEOVERGRAPHIC AGS_Button_set_MouseOverGraphic;
_AGS_BUTTON_GET_NORMALGRAPHIC AGS_Button_get_NormalGraphic;
_AGS_BUTTON_SET_NORMALGRAPHIC AGS_Button_set_NormalGraphic;
_AGS_BUTTON_GET_PUSHEDGRAPHIC AGS_Button_get_PushedGraphic;
_AGS_BUTTON_SET_PUSHEDGRAPHIC AGS_Button_set_PushedGraphic;
_AGS_BUTTON_GET_TEXTCOLOR AGS_Button_get_TextColor;
_AGS_BUTTON_SET_TEXTCOLOR AGS_Button_set_TextColor;
_AGS_BUTTON_GET_TEXT AGS_Button_get_Text;
_AGS_BUTTON_SET_TEXT AGS_Button_set_Text;

// Slider method instances
_AGS_SLIDER_GET_BACKGROUNDGRAPHIC AGS_Slider_get_BackgroundGraphic;
_AGS_SLIDER_SET_BACKGROUNDGRAPHIC AGS_Slider_set_BackgroundGraphic;
_AGS_SLIDER_GET_HANDLEGRAPHIC AGS_Slider_get_HandleGraphic;
_AGS_SLIDER_SET_HANDLEGRAPHIC AGS_Slider_set_HandleGraphic;
_AGS_SLIDER_GET_HANDLEOFFSET AGS_Slider_get_HandleOffset;
_AGS_SLIDER_SET_HANDLEOFFSET AGS_Slider_set_HandleOffset;
_AGS_SLIDER_GET_MAX AGS_Slider_get_Max;
_AGS_SLIDER_SET_MAX AGS_Slider_set_Max;
_AGS_SLIDER_GET_MIN AGS_Slider_get_Min;
_AGS_SLIDER_SET_MIN AGS_Slider_set_Min;
_AGS_SLIDER_GET_VALUE AGS_Slider_get_Value;
_AGS_SLIDER_SET_VALUE AGS_Slider_set_Value;

// TextBox method instances
_AGS_TEXTBOX_GET_FONT AGS_TextBox_get_Font;
_AGS_TEXTBOX_SET_FONT AGS_TextBox_set_Font;
_AGS_TEXTBOX_GET_TEXT AGS_TextBox_get_Text;
_AGS_TEXTBOX_SET_TEXT AGS_TextBox_set_Text;
_AGS_TEXTBOX_GET_TEXTCOLOR AGS_TextBox_get_TextColor;
_AGS_TEXTBOX_SET_TEXTCOLOR AGS_TextBox_set_TextColor;

// InvWindow method instances
_AGS_INVWINDOW_SCROLLDOWN AGS_InvWindow_ScrollDown;
_AGS_INVWINDOW_SCROLLUP AGS_InvWindow_ScrollUp;
_AGS_INVWINDOW_GET_CHARACTERTOUSE AGS_InvWindow_get_CharacterToUse;
_AGS_INVWINDOW_SET_CHARACTERTOUSE AGS_InvWindow_set_CharacterToUse;
_AGS_INVWINDOW_GETI_ITEMATINDEX AGS_InvWindow_geti_ItemAtIndex;
_AGS_INVWINDOW_GET_ITEMCOUNT AGS_InvWindow_get_ItemCount;
_AGS_INVWINDOW_GET_ITEMHEIGHT AGS_InvWindow_get_ItemHeight;
_AGS_INVWINDOW_SET_ITEMHEIGHT AGS_InvWindow_set_ItemHeight;
_AGS_INVWINDOW_GET_ITEMWIDTH AGS_InvWindow_get_ItemWidth;
_AGS_INVWINDOW_SET_ITEMWIDTH AGS_InvWindow_set_ItemWidth;
_AGS_INVWINDOW_GET_TOPITEM AGS_InvWindow_get_TopItem;
_AGS_INVWINDOW_SET_TOPITEM AGS_InvWindow_set_TopItem;
_AGS_INVWINDOW_GET_ITEMSPERROW AGS_InvWindow_get_ItemsPerRow;
_AGS_INVWINDOW_GET_ROWCOUNT AGS_InvWindow_get_RowCount;

// ListBox method instances
_AGS_LISTBOX_ADDITEM AGS_ListBox_AddItem;
_AGS_LISTBOX_CLEAR AGS_ListBox_Clear;
_AGS_LISTBOX_FILLDIRLIST AGS_ListBox_FillDirList;
_AGS_LISTBOX_FILLSAVEGAMELIST AGS_ListBox_FillSaveGameList;
_AGS_LISTBOX_GETITEMATLOCATION AGS_ListBox_GetItemAtLocation;
_AGS_LISTBOX_INSERTITEMAT AGS_ListBox_InsertItemAt;
_AGS_LISTBOX_REMOVEITEM AGS_ListBox_RemoveItem;
_AGS_LISTBOX_SCROLLDOWN AGS_ListBox_ScrollDown;
_AGS_LISTBOX_SCROLLUP AGS_ListBox_ScrollUp;
_AGS_LISTBOX_GET_FONT AGS_ListBox_get_Font;
_AGS_LISTBOX_SET_FONT AGS_ListBox_set_Font;
_AGS_LISTBOX_GET_HIDEBORDER AGS_ListBox_get_HideBorder;
_AGS_LISTBOX_SET_HIDEBORDER AGS_ListBox_set_HideBorder;
_AGS_LISTBOX_GET_HIDESCROLLARROWS AGS_ListBox_get_HideScrollArrows;
_AGS_LISTBOX_SET_HIDESCROLLARROWS AGS_ListBox_set_HideScrollArrows;
_AGS_LISTBOX_GET_ITEMCOUNT AGS_ListBox_get_ItemCount;
_AGS_LISTBOX_GETI_ITEMS AGS_ListBox_geti_Items;
_AGS_LISTBOX_SETI_ITEMS AGS_ListBox_seti_Items;
_AGS_LISTBOX_GET_ROWCOUNT AGS_ListBox_get_RowCount;
_AGS_LISTBOX_GETI_SAVEGAMESLOTS AGS_ListBox_geti_SaveGameSlots;
_AGS_LISTBOX_GET_SELECTEDINDEX AGS_ListBox_get_SelectedIndex;
_AGS_LISTBOX_SET_SELECTEDINDEX AGS_ListBox_set_SelectedIndex;
_AGS_LISTBOX_GET_TOPITEM AGS_ListBox_get_TopItem;
_AGS_LISTBOX_SET_TOPITEM AGS_ListBox_set_TopItem;

// GUI method instances
_AGS_GUI_CENTRE AGS_GUI_Centre;
_AGS_GUI_GETATSCREENXY AGS_GUI_GetAtScreenXY;
_AGS_GUI_SETPOSITION AGS_GUI_SetPosition;
_AGS_GUI_SETSIZE AGS_GUI_SetSize;
_AGS_GUI_GET_BACKGROUNDGRAPHIC AGS_GUI_get_BackgroundGraphic;
_AGS_GUI_SET_BACKGROUNDGRAPHIC AGS_GUI_set_BackgroundGraphic;
_AGS_GUI_GET_CLICKABLE AGS_GUI_get_Clickable;
_AGS_GUI_SET_CLICKABLE AGS_GUI_set_Clickable;
_AGS_GUI_GETI_CONTROLS AGS_GUI_geti_Controls;
_AGS_GUI_GET_CONTROLCOUNT AGS_GUI_get_ControlCount;
_AGS_GUI_GET_HEIGHT AGS_GUI_get_Height;
_AGS_GUI_SET_HEIGHT AGS_GUI_set_Height;
_AGS_GUI_GET_ID AGS_GUI_get_ID;
_AGS_GUI_GET_TRANSPARENCY AGS_GUI_get_Transparency;
_AGS_GUI_SET_TRANSPARENCY AGS_GUI_set_Transparency;
_AGS_GUI_GET_VISIBLE AGS_GUI_get_Visible;
_AGS_GUI_SET_VISIBLE AGS_GUI_set_Visible;
_AGS_GUI_GET_WIDTH AGS_GUI_get_Width;
_AGS_GUI_SET_WIDTH AGS_GUI_set_Width;
_AGS_GUI_GET_X AGS_GUI_get_X;
_AGS_GUI_SET_X AGS_GUI_set_X;
_AGS_GUI_GET_Y AGS_GUI_get_Y;
_AGS_GUI_SET_Y AGS_GUI_set_Y;
_AGS_GUI_GET_ZORDER AGS_GUI_get_ZOrder;
_AGS_GUI_SET_ZORDER AGS_GUI_set_ZOrder;

// Hotspot method instances
_AGS_HOTSPOT_GETATSCREENXY AGS_Hotspot_GetAtScreenXY;
_AGS_HOTSPOT_GETPROPERTY AGS_Hotspot_GetProperty;
_AGS_HOTSPOT_GETTEXTPROPERTY AGS_Hotspot_GetTextProperty;
_AGS_HOTSPOT_RUNINTERACTION AGS_Hotspot_RunInteraction;
_AGS_HOTSPOT_GET_ENABLED AGS_Hotspot_get_Enabled;
_AGS_HOTSPOT_SET_ENABLED AGS_Hotspot_set_Enabled;
_AGS_HOTSPOT_GET_ID AGS_Hotspot_get_ID;
_AGS_HOTSPOT_GET_NAME AGS_Hotspot_get_Name;
_AGS_HOTSPOT_GET_WALKTOX AGS_Hotspot_get_WalkToX;
_AGS_HOTSPOT_GET_WALKTOY AGS_Hotspot_get_WalkToY;

// Region method instances
_AGS_REGION_GETATROOMXY AGS_Region_GetAtRoomXY;
_AGS_REGION_RUNINTERACTION AGS_Region_RunInteraction;
_AGS_REGION_TINT AGS_Region_Tint;
_AGS_REGION_GET_ENABLED AGS_Region_get_Enabled;
_AGS_REGION_SET_ENABLED AGS_Region_set_Enabled;
_AGS_REGION_GET_ID AGS_Region_get_ID;
_AGS_REGION_GET_LIGHTLEVEL AGS_Region_get_LightLevel;
_AGS_REGION_SET_LIGHTLEVEL AGS_Region_set_LightLevel;
_AGS_REGION_GET_TINTENABLED AGS_Region_get_TintEnabled;
_AGS_REGION_GET_TINTBLUE AGS_Region_get_TintBlue;
_AGS_REGION_GET_TINTGREEN AGS_Region_get_TintGreen;
_AGS_REGION_GET_TINTRED AGS_Region_get_TintRed;
_AGS_REGION_GET_TINTSATURATION AGS_Region_get_TintSaturation;

// Dialog method instances
_AGS_DIALOG_DISPLAYOPTIONS AGS_Dialog_DisplayOptions;
_AGS_DIALOG_GETOPTIONSTATE AGS_Dialog_GetOptionState;
_AGS_DIALOG_GETOPTIONTEXT AGS_Dialog_GetOptionText;
_AGS_DIALOG_HASOPTIONBEENCHOSEN AGS_Dialog_HasOptionBeenChosen;
_AGS_DIALOG_SETOPTIONSTATE AGS_Dialog_SetOptionState;
_AGS_DIALOG_START AGS_Dialog_Start;
_AGS_DIALOG_GET_ID AGS_Dialog_get_ID;
_AGS_DIALOG_GET_OPTIONCOUNT AGS_Dialog_get_OptionCount;

// DateTime method instances
_AGS_DATETIME_GET_NOW AGS_DateTime_get_Now;
_AGS_DATETIME_GET_YEAR AGS_DateTime_get_Year;
_AGS_DATETIME_GET_MONTH AGS_DateTime_get_Month;
_AGS_DATETIME_GET_DAYOFMONTH AGS_DateTime_get_DayOfMonth;
_AGS_DATETIME_GET_HOUR AGS_DateTime_get_Hour;
_AGS_DATETIME_GET_MINUTE AGS_DateTime_get_Minute;
_AGS_DATETIME_GET_SECOND AGS_DateTime_get_Second;
_AGS_DATETIME_GET_RAWTIME AGS_DateTime_get_RawTime;

// DialogOptionsRenderingInfo method instances
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_ACTIVEOPTIONID AGS_DialogOptionsRenderingInfo_get_ActiveOptionID;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_ACTIVEOPTIONID AGS_DialogOptionsRenderingInfo_set_ActiveOptionID;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_DIALOGTORENDER AGS_DialogOptionsRenderingInfo_get_DialogToRender;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_HEIGHT AGS_DialogOptionsRenderingInfo_get_Height;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_HEIGHT AGS_DialogOptionsRenderingInfo_set_Height;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXWIDTH AGS_DialogOptionsRenderingInfo_get_ParserTextBoxWidth;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXWIDTH AGS_DialogOptionsRenderingInfo_set_ParserTextBoxWidth;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXX AGS_DialogOptionsRenderingInfo_get_ParserTextBoxX;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXX AGS_DialogOptionsRenderingInfo_set_ParserTextBoxX;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXY AGS_DialogOptionsRenderingInfo_get_ParserTextBoxY;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXY AGS_DialogOptionsRenderingInfo_set_ParserTextBoxY;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_SURFACE AGS_DialogOptionsRenderingInfo_get_Surface;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_WIDTH AGS_DialogOptionsRenderingInfo_get_Width;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_WIDTH AGS_DialogOptionsRenderingInfo_set_Width;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_X AGS_DialogOptionsRenderingInfo_get_X;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_X AGS_DialogOptionsRenderingInfo_set_X;
_AGS_DIALOGOPTIONSRENDERINGINFO_GET_Y AGS_DialogOptionsRenderingInfo_get_Y;
_AGS_DIALOGOPTIONSRENDERINGINFO_SET_Y AGS_DialogOptionsRenderingInfo_set_Y;

// System method instances
_AGS_SYSTEM_GET_CAPSLOCK AGS_System_get_CapsLock;
_AGS_SYSTEM_GET_COLORDEPTH AGS_System_get_ColorDepth;
_AGS_SYSTEM_GET_GAMMA AGS_System_get_Gamma;
_AGS_SYSTEM_SET_GAMMA AGS_System_set_Gamma;
_AGS_SYSTEM_GET_HARDWAREACCELERATION AGS_System_get_HardwareAcceleration;
_AGS_SYSTEM_GET_NUMLOCK AGS_System_get_NumLock;
_AGS_SYSTEM_GET_OPERATINGSYSTEM AGS_System_get_OperatingSystem;
_AGS_SYSTEM_GET_SCREENHEIGHT AGS_System_get_ScreenHeight;
_AGS_SYSTEM_GET_SCREENWIDTH AGS_System_get_ScreenWidth;
_AGS_SYSTEM_GET_SCROLLLOCK AGS_System_get_ScrollLock;
_AGS_SYSTEM_GET_SUPPORTSGAMMACONTROL AGS_System_get_SupportsGammaControl;
_AGS_SYSTEM_GET_VERSION AGS_System_get_Version;
_AGS_SYSTEM_GET_VIEWPORTHEIGHT AGS_System_get_ViewportHeight;
_AGS_SYSTEM_GET_VIEWPORTWIDTH AGS_System_get_ViewportWidth;
_AGS_SYSTEM_GET_VSYNC AGS_System_get_VSync;
_AGS_SYSTEM_SET_VSYNC AGS_System_set_VSync;
_AGS_SYSTEM_GET_WINDOWED AGS_System_get_Windowed;

// Object method instances
_AGS_OBJECT_ANIMATE AGS_Object_Animate;
_AGS_OBJECT_GETATSCREENXY AGS_Object_GetAtScreenXY;
_AGS_OBJECT_GETPROPERTY AGS_Object_GetProperty;
_AGS_OBJECT_GETTEXTPROPERTY AGS_Object_GetTextProperty;
_AGS_OBJECT_ISCOLLIDINGWITHOBJECT AGS_Object_IsCollidingWithObject;
_AGS_OBJECT_MERGEINTOBACKGROUND AGS_Object_MergeIntoBackground;
_AGS_OBJECT_MOVE AGS_Object_Move;
_AGS_OBJECT_REMOVETINT AGS_Object_RemoveTint;
_AGS_OBJECT_RUNINTERACTION AGS_Object_RunInteraction;
_AGS_OBJECT_SETPOSITION AGS_Object_SetPosition;
_AGS_OBJECT_SETVIEW AGS_Object_SetView;
_AGS_OBJECT_STOPANIMATING AGS_Object_StopAnimating;
_AGS_OBJECT_STOPMOVING AGS_Object_StopMoving;
_AGS_OBJECT_TINT AGS_Object_Tint;
_AGS_OBJECT_GET_ANIMATING AGS_Object_get_Animating;
_AGS_OBJECT_GET_BASELINE AGS_Object_get_Baseline;
_AGS_OBJECT_SET_BASELINE AGS_Object_set_Baseline;
_AGS_OBJECT_GET_BLOCKINGHEIGHT AGS_Object_get_BlockingHeight;
_AGS_OBJECT_SET_BLOCKINGHEIGHT AGS_Object_set_BlockingHeight;
_AGS_OBJECT_GET_BLOCKINGWIDTH AGS_Object_get_BlockingWidth;
_AGS_OBJECT_SET_BLOCKINGWIDTH AGS_Object_set_BlockingWidth;
_AGS_OBJECT_GET_CLICKABLE AGS_Object_get_Clickable;
_AGS_OBJECT_SET_CLICKABLE AGS_Object_set_Clickable;
_AGS_OBJECT_GET_FRAME AGS_Object_get_Frame;
_AGS_OBJECT_GET_GRAPHIC AGS_Object_get_Graphic;
_AGS_OBJECT_SET_GRAPHIC AGS_Object_set_Graphic;
_AGS_OBJECT_GET_ID AGS_Object_get_ID;
_AGS_OBJECT_GET_IGNORESCALING AGS_Object_get_IgnoreScaling;
_AGS_OBJECT_SET_IGNORESCALING AGS_Object_set_IgnoreScaling;
_AGS_OBJECT_GET_IGNOREWALKBEHINDS AGS_Object_get_IgnoreWalkbehinds;
_AGS_OBJECT_SET_IGNOREWALKBEHINDS AGS_Object_set_IgnoreWalkbehinds;
_AGS_OBJECT_GET_LOOP AGS_Object_get_Loop;
_AGS_OBJECT_GET_MOVING AGS_Object_get_Moving;
_AGS_OBJECT_GET_NAME AGS_Object_get_Name;
_AGS_OBJECT_GET_SOLID AGS_Object_get_Solid;
_AGS_OBJECT_SET_SOLID AGS_Object_set_Solid;
_AGS_OBJECT_GET_TRANSPARENCY AGS_Object_get_Transparency;
_AGS_OBJECT_SET_TRANSPARENCY AGS_Object_set_Transparency;
_AGS_OBJECT_GET_VIEW AGS_Object_get_View;
_AGS_OBJECT_GET_VISIBLE AGS_Object_get_Visible;
_AGS_OBJECT_SET_VISIBLE AGS_Object_set_Visible;
_AGS_OBJECT_GET_X AGS_Object_get_X;
_AGS_OBJECT_SET_X AGS_Object_set_X;
_AGS_OBJECT_GET_Y AGS_Object_get_Y;
_AGS_OBJECT_SET_Y AGS_Object_set_Y;

// Character method instances
_AGS_CHARACTER_ADDINVENTORY AGS_Character_AddInventory;
_AGS_CHARACTER_ADDWAYPOINT AGS_Character_AddWaypoint;
_AGS_CHARACTER_ANIMATE AGS_Character_Animate;
_AGS_CHARACTER_CHANGEROOM AGS_Character_ChangeRoom;
_AGS_CHARACTER_CHANGEROOMAUTOPOSITION AGS_Character_ChangeRoomAutoPosition;
_AGS_CHARACTER_CHANGEVIEW AGS_Character_ChangeView;
_AGS_CHARACTER_FACECHARACTER AGS_Character_FaceCharacter;
_AGS_CHARACTER_FACELOCATION AGS_Character_FaceLocation;
_AGS_CHARACTER_FACEOBJECT AGS_Character_FaceObject;
_AGS_CHARACTER_FOLLOWCHARACTER AGS_Character_FollowCharacter;
_AGS_CHARACTER_GETATSCREENXY AGS_Character_GetAtScreenXY;
_AGS_CHARACTER_GETPROPERTY AGS_Character_GetProperty;
_AGS_CHARACTER_GETTEXTPROPERTY AGS_Character_GetTextProperty;
_AGS_CHARACTER_HASINVENTORY AGS_Character_HasInventory;
_AGS_CHARACTER_ISCOLLIDINGWITHCHAR AGS_Character_IsCollidingWithChar;
_AGS_CHARACTER_ISCOLLIDINGWITHOBJECT AGS_Character_IsCollidingWithObject;
_AGS_CHARACTER_LOCKVIEW AGS_Character_LockView;
_AGS_CHARACTER_LOCKVIEWALIGNED AGS_Character_LockViewAligned;
_AGS_CHARACTER_LOCKVIEWFRAME AGS_Character_LockViewFrame;
_AGS_CHARACTER_LOCKVIEWOFFSET AGS_Character_LockViewOffset;
_AGS_CHARACTER_LOSEINVENTORY AGS_Character_LoseInventory;
_AGS_CHARACTER_MOVE AGS_Character_Move;
_AGS_CHARACTER_PLACEONWALKABLEAREA AGS_Character_PlaceOnWalkableArea;
_AGS_CHARACTER_REMOVETINT AGS_Character_RemoveTint;
_AGS_CHARACTER_RUNINTERACTION AGS_Character_RunInteraction;
_AGS_CHARACTER_SAY AGS_Character_Say;
_AGS_CHARACTER_SAYAT AGS_Character_SayAt;
_AGS_CHARACTER_SAYBACKGROUND AGS_Character_SayBackground;
_AGS_CHARACTER_SETASPLAYER AGS_Character_SetAsPlayer;
_AGS_CHARACTER_SETIDLEVIEW AGS_Character_SetIdleView;
_AGS_CHARACTER_SETWALKSPEED AGS_Character_SetWalkSpeed;
_AGS_CHARACTER_STOPMOVING AGS_Character_StopMoving;
_AGS_CHARACTER_THINK AGS_Character_Think;
_AGS_CHARACTER_TINT AGS_Character_Tint;
_AGS_CHARACTER_UNLOCKVIEW AGS_Character_UnlockView;
_AGS_CHARACTER_WALK AGS_Character_Walk;
_AGS_CHARACTER_WALKSTRAIGHT AGS_Character_WalkStraight;
_AGS_CHARACTER_GET_ACTIVEINVENTORY AGS_Character_get_ActiveInventory;
_AGS_CHARACTER_SET_ACTIVEINVENTORY AGS_Character_set_ActiveInventory;
_AGS_CHARACTER_GET_ANIMATING AGS_Character_get_Animating;
_AGS_CHARACTER_GET_ANIMATIONSPEED AGS_Character_get_AnimationSpeed;
_AGS_CHARACTER_SET_ANIMATIONSPEED AGS_Character_set_AnimationSpeed;
_AGS_CHARACTER_GET_BASELINE AGS_Character_get_Baseline;
_AGS_CHARACTER_SET_BASELINE AGS_Character_set_Baseline;
_AGS_CHARACTER_GET_BLINKINTERVAL AGS_Character_get_BlinkInterval;
_AGS_CHARACTER_SET_BLINKINTERVAL AGS_Character_set_BlinkInterval;
_AGS_CHARACTER_GET_BLINKVIEW AGS_Character_get_BlinkView;
_AGS_CHARACTER_SET_BLINKVIEW AGS_Character_set_BlinkView;
_AGS_CHARACTER_GET_BLINKWHILETHINKING AGS_Character_get_BlinkWhileThinking;
_AGS_CHARACTER_SET_BLINKWHILETHINKING AGS_Character_set_BlinkWhileThinking;
_AGS_CHARACTER_GET_BLOCKINGHEIGHT AGS_Character_get_BlockingHeight;
_AGS_CHARACTER_SET_BLOCKINGHEIGHT AGS_Character_set_BlockingHeight;
_AGS_CHARACTER_GET_BLOCKINGWIDTH AGS_Character_get_BlockingWidth;
_AGS_CHARACTER_SET_BLOCKINGWIDTH AGS_Character_set_BlockingWidth;
_AGS_CHARACTER_GET_CLICKABLE AGS_Character_get_Clickable;
_AGS_CHARACTER_SET_CLICKABLE AGS_Character_set_Clickable;
_AGS_CHARACTER_GET_DIAGONALLOOPS AGS_Character_get_DiagonalLoops;
_AGS_CHARACTER_SET_DIAGONALLOOPS AGS_Character_set_DiagonalLoops;
_AGS_CHARACTER_GET_FRAME AGS_Character_get_Frame;
_AGS_CHARACTER_SET_FRAME AGS_Character_set_Frame;
_AGS_CHARACTER_GET_HASEXPLICITTINT AGS_Character_get_HasExplicitTint;
_AGS_CHARACTER_GET_ID AGS_Character_get_ID;
_AGS_CHARACTER_GET_IDLEVIEW AGS_Character_get_IdleView;
_AGS_CHARACTER_GET_IGNORELIGHTING AGS_Character_get_IgnoreLighting;
_AGS_CHARACTER_SET_IGNORELIGHTING AGS_Character_set_IgnoreLighting;
_AGS_CHARACTER_GET_IGNORESCALING AGS_Character_get_IgnoreScaling;
_AGS_CHARACTER_SET_IGNORESCALING AGS_Character_set_IgnoreScaling;
_AGS_CHARACTER_GET_IGNOREWALKBEHINDS AGS_Character_get_IgnoreWalkbehinds;
_AGS_CHARACTER_SET_IGNOREWALKBEHINDS AGS_Character_set_IgnoreWalkbehinds;
_AGS_CHARACTER_GETI_INVENTORYQUANTITY AGS_Character_geti_InventoryQuantity;
_AGS_CHARACTER_SETI_INVENTORYQUANTITY AGS_Character_seti_InventoryQuantity;
_AGS_CHARACTER_GET_LOOP AGS_Character_get_Loop;
_AGS_CHARACTER_SET_LOOP AGS_Character_set_Loop;
_AGS_CHARACTER_GET_MANUALSCALING AGS_Character_get_ManualScaling;
_AGS_CHARACTER_SET_MANUALSCALING AGS_Character_set_ManualScaling;
_AGS_CHARACTER_GET_MOVEMENTLINKEDTOANIMATION AGS_Character_get_MovementLinkedToAnimation;
_AGS_CHARACTER_SET_MOVEMENTLINKEDTOANIMATION AGS_Character_set_MovementLinkedToAnimation;
_AGS_CHARACTER_GET_MOVING AGS_Character_get_Moving;
_AGS_CHARACTER_GET_NAME AGS_Character_get_Name;
_AGS_CHARACTER_SET_NAME AGS_Character_set_Name;
_AGS_CHARACTER_GET_NORMALVIEW AGS_Character_get_NormalView;
_AGS_CHARACTER_GET_PREVIOUSROOM AGS_Character_get_PreviousRoom;
_AGS_CHARACTER_GET_ROOM AGS_Character_get_Room;
_AGS_CHARACTER_GET_SCALEMOVESPEED AGS_Character_get_ScaleMoveSpeed;
_AGS_CHARACTER_SET_SCALEMOVESPEED AGS_Character_set_ScaleMoveSpeed;
_AGS_CHARACTER_GET_SCALEVOLUME AGS_Character_get_ScaleVolume;
_AGS_CHARACTER_SET_SCALEVOLUME AGS_Character_set_ScaleVolume;
_AGS_CHARACTER_GET_SCALING AGS_Character_get_Scaling;
_AGS_CHARACTER_SET_SCALING AGS_Character_set_Scaling;
_AGS_CHARACTER_GET_SOLID AGS_Character_get_Solid;
_AGS_CHARACTER_SET_SOLID AGS_Character_set_Solid;
_AGS_CHARACTER_GET_SPEAKING AGS_Character_get_Speaking;
_AGS_CHARACTER_GET_SPEAKINGFRAME AGS_Character_get_SpeakingFrame;
_AGS_CHARACTER_GET_SPEECHANIMATIONDELAY AGS_Character_get_SpeechAnimationDelay;
_AGS_CHARACTER_SET_SPEECHANIMATIONDELAY AGS_Character_set_SpeechAnimationDelay;
_AGS_CHARACTER_GET_SPEECHCOLOR AGS_Character_get_SpeechColor;
_AGS_CHARACTER_SET_SPEECHCOLOR AGS_Character_set_SpeechColor;
_AGS_CHARACTER_GET_SPEECHVIEW AGS_Character_get_SpeechView;
_AGS_CHARACTER_SET_SPEECHVIEW AGS_Character_set_SpeechView;
_AGS_CHARACTER_GET_THINKVIEW AGS_Character_get_ThinkView;
_AGS_CHARACTER_SET_THINKVIEW AGS_Character_set_ThinkView;
_AGS_CHARACTER_GET_TRANSPARENCY AGS_Character_get_Transparency;
_AGS_CHARACTER_SET_TRANSPARENCY AGS_Character_set_Transparency;
_AGS_CHARACTER_GET_TURNBEFOREWALKING AGS_Character_get_TurnBeforeWalking;
_AGS_CHARACTER_SET_TURNBEFOREWALKING AGS_Character_set_TurnBeforeWalking;
_AGS_CHARACTER_GET_VIEW AGS_Character_get_View;
_AGS_CHARACTER_GET_WALKSPEEDX AGS_Character_get_WalkSpeedX;
_AGS_CHARACTER_GET_WALKSPEEDY AGS_Character_get_WalkSpeedY;
_AGS_CHARACTER_GET_X AGS_Character_get_x;
_AGS_CHARACTER_SET_X AGS_Character_set_x;
_AGS_CHARACTER_GET_Y AGS_Character_get_y;
_AGS_CHARACTER_SET_Y AGS_Character_set_y;
_AGS_CHARACTER_GET_Z AGS_Character_get_z;
_AGS_CHARACTER_SET_Z AGS_Character_set_z;

void GetScriptFunctionAddresses(IAGSEditor* editor) {
	// Global functions
	AGS_Display = (_AGSDISPLAY)engine->GetScriptFunctionAddress("Display");
	AGS_DisplayAt = (_AGSDISPLAYAT)engine->GetScriptFunctionAddress("DisplayAt");
	AGS_DisplayAtY = (_AGSDISPLAYATY)engine->GetScriptFunctionAddress("DisplayAtY");
	AGS_DisplayMessage = (_AGSDISPLAYMESSAGE)engine->GetScriptFunctionAddress("DisplayMessage");
	AGS_DisplayMessageAtY = (_AGSDISPLAYMESSAGEATY)engine->GetScriptFunctionAddress("DisplayMessageAtY");
	AGS_DisplayTopBar = (_AGSDISPLAYTOPBAR)engine->GetScriptFunctionAddress("DisplayTopBar");
	AGS_DisplayMessageBar = (_AGSDISPLAYMESSAGEBAR)engine->GetScriptFunctionAddress("DisplayMessageBar");
	AGS_ResetRoom = (_AGSRESETROOM)engine->GetScriptFunctionAddress("ResetRoom");
	AGS_HasPlayerBeenInRoom = (_AGSHASPLAYERBEENINROOM)engine->GetScriptFunctionAddress("HasPlayerBeenInRoom");
	AGS_ProcessClick = (_AGSPROCESSCLICK)engine->GetScriptFunctionAddress("ProcessClick");
	AGS_AbortGame = (_AGSABORTGAME)engine->GetScriptFunctionAddress("AbortGame");
	AGS_QuitGame = (_AGSQUITGAME)engine->GetScriptFunctionAddress("QuitGame");
	AGS_SetGameSpeed = (_AGSSETGAMESPEED)engine->GetScriptFunctionAddress("SetGameSpeed");
	AGS_GetGameSpeed = (_AGSGETGAMESPEED)engine->GetScriptFunctionAddress("GetGameSpeed");
	AGS_SetGameOption = (_AGSSETGAMEOPTION)engine->GetScriptFunctionAddress("SetGameOption");
	AGS_GetGameOption = (_AGSGETGAMEOPTION)engine->GetScriptFunctionAddress("GetGameOption");
	AGS_Debug = (_AGSDEBUG)engine->GetScriptFunctionAddress("Debug");
	AGS_CallRoomScript = (_AGSCALLROOMSCRIPT)engine->GetScriptFunctionAddress("CallRoomScript");
	AGS_RunAGSGame = (_AGSRUNAGSGAME)engine->GetScriptFunctionAddress("RunAGSGame");
	AGS_GetTranslation = (_AGSGETTRANSLATION)engine->GetScriptFunctionAddress("GetTranslation");
	AGS_IsTranslationAvailable = (_AGSISTRANSLATIONAVAILABLE)engine->GetScriptFunctionAddress("IsTranslationAvailable");
	AGS_RestoreGameDialog = (_AGSRESTOREGAMEDIALOG)engine->GetScriptFunctionAddress("RestoreGameDialog");
	AGS_SaveGameDialog = (_AGSSAVEGAMEDIALOG)engine->GetScriptFunctionAddress("SaveGameDialog");
	AGS_RestartGame = (_AGSRESTARTGAME)engine->GetScriptFunctionAddress("RestartGame");
	AGS_SaveGameSlot = (_AGSSAVEGAMESLOT)engine->GetScriptFunctionAddress("SaveGameSlot");
	AGS_RestoreGameSlot = (_AGSRESTOREGAMESLOT)engine->GetScriptFunctionAddress("RestoreGameSlot");
	AGS_DeleteSaveSlot = (_AGSDELETESAVESLOT)engine->GetScriptFunctionAddress("DeleteSaveSlot");
	AGS_SetRestartPoint = (_AGSSETRESTARTPOINT)engine->GetScriptFunctionAddress("SetRestartPoint");
	AGS_GetLocationType = (_AGSGETLOCATIONTYPE)engine->GetScriptFunctionAddress("GetLocationType");
	AGS_GetWalkableAreaAt = (_AGSGETWALKABLEAREAAT)engine->GetScriptFunctionAddress("GetWalkableAreaAt");
	AGS_GetScalingAt = (_AGSGETSCALINGAT)engine->GetScriptFunctionAddress("GetScalingAt");
	AGS_GetRoomProperty = (_AGSGETROOMPROPERTY)engine->GetScriptFunctionAddress("GetRoomProperty");
	AGS_SetViewport = (_AGSSETVIEWPORT)engine->GetScriptFunctionAddress("SetViewport");
	AGS_ReleaseViewport = (_AGSRELEASEVIEWPORT)engine->GetScriptFunctionAddress("ReleaseViewport");
	AGS_GetViewportX = (_AGSGETVIEWPORTX)engine->GetScriptFunctionAddress("GetViewportX");
	AGS_GetViewportY = (_AGSGETVIEWPORTY)engine->GetScriptFunctionAddress("GetViewportY");
	AGS_IsGamePaused = (_AGSISGAMEPAUSED)engine->GetScriptFunctionAddress("IsGamePaused");
	AGS_IsChannelPlaying = (_AGSISCHANNELPLAYING)engine->GetScriptFunctionAddress("IsChannelPlaying");
	AGS_IsSoundPlaying = (_AGSISSOUNDPLAYING)engine->GetScriptFunctionAddress("IsSoundPlaying");
	AGS_IsMusicPlaying = (_AGSISMUSICPLAYING)engine->GetScriptFunctionAddress("IsMusicPlaying");
	AGS_GetMIDIPosition = (_AGSGETMIDIPOSITION)engine->GetScriptFunctionAddress("GetMIDIPosition");
	AGS_SeekMIDIPosition = (_AGSSEEKMIDIPOSITION)engine->GetScriptFunctionAddress("SeekMIDIPosition");
	AGS_GetMP3PosMillis = (_AGSGETMP3POSMILLIS)engine->GetScriptFunctionAddress("GetMP3PosMillis");
	AGS_SeekMP3PosMillis = (_AGSSEEKMP3POSMILLIS)engine->GetScriptFunctionAddress("SeekMP3PosMillis");
	AGS_SetChannelVolume = (_AGSSETCHANNELVOLUME)engine->GetScriptFunctionAddress("SetChannelVolume");
	AGS_StopChannel = (_AGSSTOPCHANNEL)engine->GetScriptFunctionAddress("StopChannel");
	AGS_StopMusic = (_AGSSTOPMUSIC)engine->GetScriptFunctionAddress("StopMusic");
	AGS_GetGraphicalVariable = (_AGSGETGRAPHICALVARIABLE)engine->GetScriptFunctionAddress("GetGraphicalVariable");
	AGS_SetGraphicalVariable = (_AGSSETGRAPHICALVARIABLE)engine->GetScriptFunctionAddress("SetGraphicalVariable");
	AGS_DisableInterface = (_AGSDISABLEINTERFACE)engine->GetScriptFunctionAddress("DisableInterface");
	AGS_EnableInterface = (_AGSENABLEINTERFACE)engine->GetScriptFunctionAddress("EnableInterface");
	AGS_IsInterfaceEnabled = (_AGSISINTERFACEENABLED)engine->GetScriptFunctionAddress("IsInterfaceEnabled");
	AGS_Said = (_AGSSAID)engine->GetScriptFunctionAddress("Said");
	AGS_GetTextWidth = (_AGSGETTEXTWIDTH)engine->GetScriptFunctionAddress("GetTextWidth");
	AGS_GetTextHeight = (_AGSGETTEXTHEIGHT)engine->GetScriptFunctionAddress("GetTextHeight");
	AGS_GiveScore = (_AGSGIVESCORE)engine->GetScriptFunctionAddress("GiveScore");
	AGS_UpdateInventory = (_AGSUPDATEINVENTORY)engine->GetScriptFunctionAddress("UpdateInventory");
	AGS_StopDialog = (_AGSSTOPDIALOG)engine->GetScriptFunctionAddress("StopDialog");
	AGS_AreThingsOverlapping = (_AGSARETHINGSOVERLAPPING)engine->GetScriptFunctionAddress("AreThingsOverlapping");
	AGS_SetVoiceMode = (_AGSSETVOICEMODE)engine->GetScriptFunctionAddress("SetVoiceMode");
	AGS_SetSkipSpeech = (_AGSSETSKIPSPEECH)engine->GetScriptFunctionAddress("SetSkipSpeech");
	AGS_SetSpeechStyle = (_AGSSETSPEECHSTYLE)engine->GetScriptFunctionAddress("SetSpeechStyle");
	AGS_SetTimer = (_AGSSETTIMER)engine->GetScriptFunctionAddress("SetTimer");
	AGS_IsTimerExpired = (_AGSISTIMEREXPIRED)engine->GetScriptFunctionAddress("IsTimerExpired");
	AGS_SetMultitaskingMode = (_AGSSETMULTITASKINGMODE)engine->GetScriptFunctionAddress("SetMultitaskingMode");
	AGS_FloatToInt = (_AGSFLOATTOINT)engine->GetScriptFunctionAddress("FloatToInt");
	AGS_IntToFloat = (_AGSINTTOFLOAT)engine->GetScriptFunctionAddress("IntToFloat");
	AGS_FadeIn = (_AGSFADEIN)engine->GetScriptFunctionAddress("FadeIn");
	AGS_FadeOut = (_AGSFADEOUT)engine->GetScriptFunctionAddress("FadeOut");
	AGS_CyclePalette = (_AGSCYCLEPALETTE)engine->GetScriptFunctionAddress("CyclePalette");
	AGS_SetPalRGB = (_AGSSETPALRGB)engine->GetScriptFunctionAddress("SetPalRGB");
	AGS_UpdatePalette = (_AGSUPDATEPALETTE)engine->GetScriptFunctionAddress("UpdatePalette");
	AGS_TintScreen = (_AGSTINTSCREEN)engine->GetScriptFunctionAddress("TintScreen");
	AGS_SetAmbientTint = (_AGSSETAMBIENTTINT)engine->GetScriptFunctionAddress("SetAmbientTint");
	AGS_Random = (_AGSRANDOM)engine->GetScriptFunctionAddress("Random");
	AGS_SetBackgroundFrame = (_AGSSETBACKGROUNDFRAME)engine->GetScriptFunctionAddress("SetBackgroundFrame");
	AGS_GetBackgroundFrame = (_AGSGETBACKGROUNDFRAME)engine->GetScriptFunctionAddress("GetBackgroundFrame");
	AGS_ShakeScreen = (_AGSSHAKESCREEN)engine->GetScriptFunctionAddress("ShakeScreen");
	AGS_ShakeScreenBackground = (_AGSSHAKESCREENBACKGROUND)engine->GetScriptFunctionAddress("ShakeScreenBackground");
	AGS_SetScreenTransition = (_AGSSETSCREENTRANSITION)engine->GetScriptFunctionAddress("SetScreenTransition");
	AGS_SetNextScreenTransition = (_AGSSETNEXTSCREENTRANSITION)engine->GetScriptFunctionAddress("SetNextScreenTransition");
	AGS_SetFadeColor = (_AGSSETFADECOLOR)engine->GetScriptFunctionAddress("SetFadeColor");
	AGS_IsInteractionAvailable = (_AGSISINTERACTIONAVAILABLE)engine->GetScriptFunctionAddress("IsInteractionAvailable");
	AGS_RemoveWalkableArea = (_AGSREMOVEWALKABLEAREA)engine->GetScriptFunctionAddress("RemoveWalkableArea");
	AGS_RestoreWalkableArea = (_AGSRESTOREWALKABLEAREA)engine->GetScriptFunctionAddress("RestoreWalkableArea");
	AGS_SetAreaScaling = (_AGSSETAREASCALING)engine->GetScriptFunctionAddress("SetAreaScaling");
	AGS_DisableGroundLevelAreas = (_AGSDISABLEGROUNDLEVELAREAS)engine->GetScriptFunctionAddress("DisableGroundLevelAreas");
	AGS_EnableGroundLevelAreas = (_AGSENABLEGROUNDLEVELAREAS)engine->GetScriptFunctionAddress("EnableGroundLevelAreas");
	AGS_SetWalkBehindBase = (_AGSSETWALKBEHINDBASE)engine->GetScriptFunctionAddress("SetWalkBehindBase");
	AGS_CDAudio = (_AGSCDAUDIO)engine->GetScriptFunctionAddress("CDAudio");
	AGS_PlayFlic = (_AGSPLAYFLIC)engine->GetScriptFunctionAddress("PlayFlic");
	AGS_PlayVideo = (_AGSPLAYVIDEO)engine->GetScriptFunctionAddress("PlayVideo");
	AGS_PlayMusic = (_AGSPLAYMUSIC)engine->GetScriptFunctionAddress("PlayMusic");
	AGS_PlayMusicQueued = (_AGSPLAYMUSICQUEUED)engine->GetScriptFunctionAddress("PlayMusicQueued");
	AGS_PlaySilentMIDI = (_AGSPLAYSILENTMIDI)engine->GetScriptFunctionAddress("PlaySilentMIDI");
	AGS_PlayMP3File = (_AGSPLAYMP3FILE)engine->GetScriptFunctionAddress("PlayMP3File");
	AGS_PlaySound = (_AGSPLAYSOUND)engine->GetScriptFunctionAddress("PlaySound");
	AGS_PlaySoundEx = (_AGSPLAYSOUNDEX)engine->GetScriptFunctionAddress("PlaySoundEx");
	AGS_PlayAmbientSound = (_AGSPLAYAMBIENTSOUND)engine->GetScriptFunctionAddress("PlayAmbientSound");
	AGS_StopAmbientSound = (_AGSSTOPAMBIENTSOUND)engine->GetScriptFunctionAddress("StopAmbientSound");
	AGS_IsVoxAvailable = (_AGSISVOXAVAILABLE)engine->GetScriptFunctionAddress("IsVoxAvailable");
	AGS_IsMusicVoxAvailable = (_AGSISMUSICVOXAVAILABLE)engine->GetScriptFunctionAddress("IsMusicVoxAvailable");
	AGS_GetCurrentMusic = (_AGSGETCURRENTMUSIC)engine->GetScriptFunctionAddress("GetCurrentMusic");
	AGS_SetMusicRepeat = (_AGSSETMUSICREPEAT)engine->GetScriptFunctionAddress("SetMusicRepeat");
	AGS_SetMusicVolume = (_AGSSETMUSICVOLUME)engine->GetScriptFunctionAddress("SetMusicVolume");
	AGS_SetSoundVolume = (_AGSSETSOUNDVOLUME)engine->GetScriptFunctionAddress("SetSoundVolume");
	AGS_SetSpeechVolume = (_AGSSETSPEECHVOLUME)engine->GetScriptFunctionAddress("SetSpeechVolume");
	AGS_SetMusicMasterVolume = (_AGSSETMUSICMASTERVOLUME)engine->GetScriptFunctionAddress("SetMusicMasterVolume");
	AGS_SetDigitalMasterVolume = (_AGSSETDIGITALMASTERVOLUME)engine->GetScriptFunctionAddress("SetDigitalMasterVolume");
	AGS_SeekMODPattern = (_AGSSEEKMODPATTERN)engine->GetScriptFunctionAddress("SeekMODPattern");
	AGS_SaveScreenShot = (_AGSSAVESCREENSHOT)engine->GetScriptFunctionAddress("SaveScreenShot");
	AGS_PauseGame = (_AGSPAUSEGAME)engine->GetScriptFunctionAddress("PauseGame");
	AGS_UnPauseGame = (_AGSUNPAUSEGAME)engine->GetScriptFunctionAddress("UnPauseGame");
	AGS_Wait = (_AGSWAIT)engine->GetScriptFunctionAddress("Wait");
	AGS_WaitKey = (_AGSWAITKEY)engine->GetScriptFunctionAddress("WaitKey");
	AGS_WaitMouseKey = (_AGSWAITMOUSEKEY)engine->GetScriptFunctionAddress("WaitMouseKey");
	AGS_IsKeyPressed = (_AGSISKEYPRESSED)engine->GetScriptFunctionAddress("IsKeyPressed");
	AGS_SetGlobalInt = (_AGSSETGLOBALINT)engine->GetScriptFunctionAddress("SetGlobalInt");
	AGS_GetGlobalInt = (_AGSGETGLOBALINT)engine->GetScriptFunctionAddress("GetGlobalInt");
	AGS_FlipScreen = (_AGSFLIPSCREEN)engine->GetScriptFunctionAddress("FlipScreen");
	AGS_SkipUntilCharacterStops = (_AGSSKIPUNTILCHARACTERSTOPS)engine->GetScriptFunctionAddress("SkipUntilCharacterStops");
	AGS_StartCutscene = (_AGSSTARTCUTSCENE)engine->GetScriptFunctionAddress("StartCutscene");
	AGS_EndCutscene = (_AGSENDCUTSCENE)engine->GetScriptFunctionAddress("EndCutscene");
	AGS_ClaimEvent = (_AGSCLAIMEVENT)engine->GetScriptFunctionAddress("ClaimEvent");
	AGS_SetTextWindowGUI = (_AGSSETTEXTWINDOWGUI)engine->GetScriptFunctionAddress("SetTextWindowGUI");
	AGS_FindGUIID = (_AGSFINDGUIID)engine->GetScriptFunctionAddress("FindGUIID");
	
	// ViewFrame methods
	AGS_ViewFrame_get_Flipped = (_AGS_VIEWFRAME_GET_FLIPPED)engine->GetScriptFunctionAddress("ViewFrame::get_Flipped");
	AGS_ViewFrame_get_Frame = (_AGS_VIEWFRAME_GET_FRAME)engine->GetScriptFunctionAddress("ViewFrame::get_Frame");
	AGS_ViewFrame_get_Graphic = (_AGS_VIEWFRAME_GET_GRAPHIC)engine->GetScriptFunctionAddress("ViewFrame::get_Graphic");
	AGS_ViewFrame_set_Graphic = (_AGSVIEWFRAME_SET_GRAPHIC)engine->GetScriptFunctionAddress("ViewFrame::set_Graphic");
	AGS_ViewFrame_get_Loop = (_AGS_VIEWFRAME_GET_LOOP)engine->GetScriptFunctionAddress("ViewFrame::get_Loop");
	AGS_ViewFrame_get_Sound = (_AGS_VIEWFRAME_GET_SOUND)engine->GetScriptFunctionAddress("ViewFrame::get_Sound");
	AGS_ViewFrame_set_Sound = (_AGSVIEWFRAME_SET_SOUND)engine->GetScriptFunctionAddress("ViewFrame::set_Sound");
	AGS_ViewFrame_get_Speed = (_AGS_VIEWFRAME_GET_SPEED)engine->GetScriptFunctionAddress("ViewFrame::get_Speed");
	AGS_ViewFrame_get_View = (_AGS_VIEWFRAME_GET_VIEW)engine->GetScriptFunctionAddress("ViewFrame::get_View");
	
	// DrawingSurface methods
	AGS_DrawingSurface_Clear = (_AGSDRAWINGSURFACE_CLEAR)engine->GetScriptFunctionAddress("DrawingSurface::Clear^1");
	AGS_DrawingSurface_CreateCopy = (_AGSDRAWINGSURFACE_CREATECOPY)engine->GetScriptFunctionAddress("DrawingSurface::CreateCopy^0");
	AGS_DrawingSurface_DrawCircle = (_AGSDRAWINGSURFACE_DRAWCIRCLE)engine->GetScriptFunctionAddress("DrawingSurface::DrawCircle^3");
	AGS_DrawingSurface_DrawImage = (_AGSDRAWINGSURFACE_DRAWIMAGE)engine->GetScriptFunctionAddress("DrawingSurface::DrawImage^6");
	AGS_DrawingSurface_DrawLine = (_AGSDRAWINGSURFACE_DRAWLINE)engine->GetScriptFunctionAddress("DrawingSurface::DrawLine^5");
	AGS_DrawingSurface_DrawMessageWrapped = (_AGSDRAWINGSURFACE_DRAWMESSAGEWRAPPED)engine->GetScriptFunctionAddress("DrawingSurface::DrawMessageWrapped^5");
	AGS_DrawingSurface_DrawPixel = (_AGSDRAWINGSURFACE_DRAWPIXEL)engine->GetScriptFunctionAddress("DrawingSurface::DrawPixel^2");
	AGS_DrawingSurface_DrawRectangle = (_AGSDRAWINGSURFACE_DRAWRECTANGLE)engine->GetScriptFunctionAddress("DrawingSurface::DrawRectangle^4");
	AGS_DrawingSurface_DrawString = (_AGSDRAWINGSURFACE_DRAWSTRING)engine->GetScriptFunctionAddress("DrawingSurface::DrawString^101");
	AGS_DrawingSurface_DrawStringWrapped = (_AGSDRAWINGSURFACE_DRAWSTRINGWRAPPED)engine->GetScriptFunctionAddress("DrawingSurface::DrawStringWrapped^6");
	AGS_DrawingSurface_DrawSurface = (_AGSDRAWINGSURFACE_DRAWSURFACE)engine->GetScriptFunctionAddress("DrawingSurface::DrawSurface^2");
	AGS_DrawingSurface_DrawTriangle = (_AGSDRAWINGSURFACE_DRAWTRIANGLE)engine->GetScriptFunctionAddress("DrawingSurface::DrawTriangle^6");
	AGS_DrawingSurface_GetPixel = (_AGSDRAWINGSURFACE_GETPIXEL)engine->GetScriptFunctionAddress("DrawingSurface::GetPixel^2");
	AGS_DrawingSurface_Release = (_AGSDRAWINGSURFACE_RELEASE)engine->GetScriptFunctionAddress("DrawingSurface::Release^0");
	AGS_DrawingSurface_get_DrawingColor = (_AGS_DRAWINGSURFACE_GET_DRAWINGCOLOR)engine->GetScriptFunctionAddress("DrawingSurface::get_DrawingColor");
	AGS_DrawingSurface_set_DrawingColor = (_AGSDRAWINGSURFACE_SET_DRAWINGCOLOR)engine->GetScriptFunctionAddress("DrawingSurface::set_DrawingColor");
	AGS_DrawingSurface_get_Height = (_AGS_DRAWINGSURFACE_GET_HEIGHT)engine->GetScriptFunctionAddress("DrawingSurface::get_Height");
	AGS_DrawingSurface_get_UseHighResCoordinates = (_AGS_DRAWINGSURFACE_GET_USEHIGHRESCOORDINATES)engine->GetScriptFunctionAddress("DrawingSurface::get_UseHighResCoordinates");
	AGS_DrawingSurface_set_UseHighResCoordinates = (_AGSDRAWINGSURFACE_SET_USEHIGHRESCOORDINATES)engine->GetScriptFunctionAddress("DrawingSurface::set_UseHighResCoordinates");
	AGS_DrawingSurface_get_Width = (_AGS_DRAWINGSURFACE_GET_WIDTH)engine->GetScriptFunctionAddress("DrawingSurface::get_Width");
	
	// Room methods
	AGS_Room_GetTextProperty = (_AGSROOM_GETTEXTPROPERTY)engine->GetScriptFunctionAddress("Room::GetTextProperty^1");
	AGS_Room_GetDrawingSurfaceForBackground = (_AGSROOM_GETDRAWINGSURFACEFORBACKGROUND)engine->GetScriptFunctionAddress("Room::GetDrawingSurfaceForBackground^1");
	AGS_Room_get_BottomEdge = (_AGS_ROOM_GET_BOTTOMEDGE)engine->GetScriptFunctionAddress("Room::get_BottomEdge");
	AGS_Room_get_ColorDepth = (_AGS_ROOM_GET_COLORDEPTH)engine->GetScriptFunctionAddress("Room::get_ColorDepth");
	AGS_Room_get_Height = (_AGS_ROOM_GET_HEIGHT)engine->GetScriptFunctionAddress("Room::get_Height");
	AGS_Room_get_LeftEdge = (_AGS_ROOM_GET_LEFTEDGE)engine->GetScriptFunctionAddress("Room::get_LeftEdge");
	AGS_Room_geti_Messages = (_AGS_ROOM_GETI_MESSAGES)engine->GetScriptFunctionAddress("Room::geti_Messages");
	AGS_Room_get_MusicOnLoad = (_AGS_ROOM_GET_MUSICONLOAD)engine->GetScriptFunctionAddress("Room::get_MusicOnLoad");
	AGS_Room_get_ObjectCount = (_AGS_ROOM_GET_OBJECTCOUNT)engine->GetScriptFunctionAddress("Room::get_ObjectCount");
	AGS_Room_get_RightEdge = (_AGS_ROOM_GET_RIGHTEDGE)engine->GetScriptFunctionAddress("Room::get_RightEdge");
	AGS_Room_get_TopEdge = (_AGS_ROOM_GET_TOPEDGE)engine->GetScriptFunctionAddress("Room::get_TopEdge");
	AGS_Room_get_Width = (_AGS_ROOM_GET_WIDTH)engine->GetScriptFunctionAddress("Room::get_Width");
	
	// Game methods
	AGS_Game_ChangeTranslation = (_AGSGAME_CHANGETRANSLATION)engine->GetScriptFunctionAddress("Game::ChangeTranslation^1");
	AGS_Game_DoOnceOnly = (_AGSGAME_DOONCEONLY)engine->GetScriptFunctionAddress("Game::DoOnceOnly^1");
	AGS_Game_GetColorFromRGB = (_AGSGAME_GETCOLORFROMRGB)engine->GetScriptFunctionAddress("Game::GetColorFromRGB^3");
	AGS_Game_GetFrameCountForLoop = (_AGSGAME_GETFRAMECOUNTFORLOOP)engine->GetScriptFunctionAddress("Game::GetFrameCountForLoop^2");
	AGS_Game_GetLocationName = (_AGSGAME_GETLOCATIONNAME)engine->GetScriptFunctionAddress("Game::GetLocationName^2");
	AGS_Game_GetLoopCountForView = (_AGSGAME_GETLOOPCOUNTFORVIEW)engine->GetScriptFunctionAddress("Game::GetLoopCountForView^1");
	AGS_Game_GetMODPattern = (_AGSGAME_GETMODPATTERN)engine->GetScriptFunctionAddress("Game::GetMODPattern^0");
	AGS_Game_GetRunNextSettingForLoop = (_AGSGAME_GETRUNNEXTSETTINGFORLOOP)engine->GetScriptFunctionAddress("Game::GetRunNextSettingForLoop^2");
	AGS_Game_GetSaveSlotDescription = (_AGSGAME_GETSAVESLOTDESCRIPTION)engine->GetScriptFunctionAddress("Game::GetSaveSlotDescription^1");
	AGS_Game_GetViewFrame = (_AGSGAME_GETVIEWFRAME)engine->GetScriptFunctionAddress("Game::GetViewFrame^3");
	AGS_Game_InputBox = (_AGSGAME_INPUTBOX)engine->GetScriptFunctionAddress("Game::InputBox^1");
	AGS_Game_SetSaveGameDirectory = (_AGSGAME_SETSAVEGAMEDIRECTORY)engine->GetScriptFunctionAddress("Game::SetSaveGameDirectory^1");
	AGS_Game_StopSound = (_AGSGAME_STOPSOUND)engine->GetScriptFunctionAddress("Game::StopSound^1");
	AGS_Game_get_CharacterCount = (_AGS_GAME_GET_CHARACTERCOUNT)engine->GetScriptFunctionAddress("Game::get_CharacterCount");
	AGS_Game_get_DialogCount = (_AGS_GAME_GET_DIALOGCOUNT)engine->GetScriptFunctionAddress("Game::get_DialogCount");
	AGS_Game_get_FileName = (_AGS_GAME_GET_FILENAME)engine->GetScriptFunctionAddress("Game::get_FileName");
	AGS_Game_get_FontCount = (_AGS_GAME_GET_FONTCOUNT)engine->GetScriptFunctionAddress("Game::get_FontCount");
	AGS_Game_geti_GlobalMessages = (_AGS_GAME_GETI_GLOBALMESSAGES)engine->GetScriptFunctionAddress("Game::geti_GlobalMessages");
	AGS_Game_geti_GlobalStrings = (_AGS_GAME_GETI_GLOBALSTRINGS)engine->GetScriptFunctionAddress("Game::geti_GlobalStrings");
	AGS_Game_seti_GlobalStrings = (_AGSGAME_SETI_GLOBALSTRINGS)engine->GetScriptFunctionAddress("Game::seti_GlobalStrings");
	AGS_Game_get_GUICount = (_AGS_GAME_GET_GUICOUNT)engine->GetScriptFunctionAddress("Game::get_GUICount");
	AGS_Game_get_InSkippableCutscene = (_AGS_GAME_GET_INSKIPPABLECUTSCENE)engine->GetScriptFunctionAddress("Game::get_InSkippableCutscene");
	AGS_Game_get_InventoryItemCount = (_AGS_GAME_GET_INVENTORYITEMCOUNT)engine->GetScriptFunctionAddress("Game::get_InventoryItemCount");
	AGS_Game_get_MinimumTextDisplayTimeMs = (_AGS_GAME_GET_MINIMUMTEXTDISPLAYTIMEMS)engine->GetScriptFunctionAddress("Game::get_MinimumTextDisplayTimeMs");
	AGS_Game_set_MinimumTextDisplayTimeMs = (_AGSGAME_SET_MINIMUMTEXTDISPLAYTIMEMS)engine->GetScriptFunctionAddress("Game::set_MinimumTextDisplayTimeMs");
	AGS_Game_get_MouseCursorCount = (_AGS_GAME_GET_MOUSECURSORCOUNT)engine->GetScriptFunctionAddress("Game::get_MouseCursorCount");
	AGS_Game_get_Name = (_AGS_GAME_GET_NAME)engine->GetScriptFunctionAddress("Game::get_Name");
	AGS_Game_set_Name = (_AGSGAME_SET_NAME)engine->GetScriptFunctionAddress("Game::set_Name");
	AGS_Game_get_NormalFont = (_AGS_GAME_GET_NORMALFONT)engine->GetScriptFunctionAddress("Game::get_NormalFont");
	AGS_Game_set_NormalFont = (_AGSGAME_SET_NORMALFONT)engine->GetScriptFunctionAddress("Game::set_NormalFont");
	AGS_Game_get_SkippingCutscene = (_AGS_GAME_GET_SKIPPINGCUTSCENE)engine->GetScriptFunctionAddress("Game::get_SkippingCutscene");
	AGS_Game_get_SpeechFont = (_AGS_GAME_GET_SPEECHFONT)engine->GetScriptFunctionAddress("Game::get_SpeechFont");
	AGS_Game_set_SpeechFont = (_AGSGAME_SET_SPEECHFONT)engine->GetScriptFunctionAddress("Game::set_SpeechFont");
	AGS_Game_geti_SpriteHeight = (_AGS_GAME_GETI_SPRITEHEIGHT)engine->GetScriptFunctionAddress("Game::geti_SpriteHeight");
	AGS_Game_geti_SpriteWidth = (_AGS_GAME_GETI_SPRITEWIDTH)engine->GetScriptFunctionAddress("Game::geti_SpriteWidth");
	AGS_Game_get_TextReadingSpeed = (_AGS_GAME_GET_TEXTREADINGSPEED)engine->GetScriptFunctionAddress("Game::get_TextReadingSpeed");
	AGS_Game_set_TextReadingSpeed = (_AGSGAME_SET_TEXTREADINGSPEED)engine->GetScriptFunctionAddress("Game::set_TextReadingSpeed");
	AGS_Game_get_TranslationFilename = (_AGS_GAME_GET_TRANSLATIONFILENAME)engine->GetScriptFunctionAddress("Game::get_TranslationFilename");
	AGS_Game_get_UseNativeCoordinates = (_AGS_GAME_GET_USENATIVECOORDINATES)engine->GetScriptFunctionAddress("Game::get_UseNativeCoordinates");
	AGS_Game_get_ViewCount = (_AGS_GAME_GET_VIEWCOUNT)engine->GetScriptFunctionAddress("Game::get_ViewCount");
	
	// Parser methods
	AGS_Parser_FindWordID = (_AGSPARSER_FINDWORDID)engine->GetScriptFunctionAddress("Parser::FindWordID^1");
	AGS_Parser_ParseText = (_AGSPARSER_PARSETEXT)engine->GetScriptFunctionAddress("Parser::ParseText^1");
	AGS_Parser_Said = (_AGSPARSER_SAID)engine->GetScriptFunctionAddress("Parser::Said^1");
	AGS_Parser_SaidUnknownWord = (_AGSPARSER_SAIDUNKNOWNWORD)engine->GetScriptFunctionAddress("Parser::SaidUnknownWord^0");
	
	// Mouse methods
	AGS_Mouse_ChangeModeGraphic = (_AGSMOUSE_CHANGEMODEGRAPHIC)engine->GetScriptFunctionAddress("Mouse::ChangeModeGraphic^2");
	AGS_Mouse_ChangeModeHotspot = (_AGSMOUSE_CHANGEMODEHOTSPOT)engine->GetScriptFunctionAddress("Mouse::ChangeModeHotspot^3");
	AGS_Mouse_ChangeModeView = (_AGSMOUSE_CHANGEMODEVIEW)engine->GetScriptFunctionAddress("Mouse::ChangeModeView^2");
	AGS_Mouse_DisableMode = (_AGSMOUSE_DISABLEMODE)engine->GetScriptFunctionAddress("Mouse::DisableMode^1");
	AGS_Mouse_EnableMode = (_AGSMOUSE_ENABLEMODE)engine->GetScriptFunctionAddress("Mouse::EnableMode^1");
	AGS_Mouse_GetModeGraphic = (_AGSMOUSE_GETMODEGRAPHIC)engine->GetScriptFunctionAddress("Mouse::GetModeGraphic^1");
	AGS_Mouse_IsButtonDown = (_AGSMOUSE_ISBUTTONDOWN)engine->GetScriptFunctionAddress("Mouse::IsButtonDown^1");
	AGS_Mouse_SaveCursorUntilItLeaves = (_AGSMOUSE_SAVECURSORUNTILITLEAVES)engine->GetScriptFunctionAddress("Mouse::SaveCursorUntilItLeaves^0");
	AGS_Mouse_SelectNextMode = (_AGSMOUSE_SELECTNEXTMODE)engine->GetScriptFunctionAddress("Mouse::SelectNextMode^0");
	AGS_Mouse_SetBounds = (_AGSMOUSE_SETBOUNDS)engine->GetScriptFunctionAddress("Mouse::SetBounds^4");
	AGS_Mouse_SetPosition = (_AGSMOUSE_SETPOSITION)engine->GetScriptFunctionAddress("Mouse::SetPosition^2");
	AGS_Mouse_Update = (_AGSMOUSE_UPDATE)engine->GetScriptFunctionAddress("Mouse::Update^0");
	AGS_Mouse_UseDefaultGraphic = (_AGSMOUSE_USEDEFAULTGRAPHIC)engine->GetScriptFunctionAddress("Mouse::UseDefaultGraphic^0");
	AGS_Mouse_UseModeGraphic = (_AGSMOUSE_USEMODEGRAPHIC)engine->GetScriptFunctionAddress("Mouse::UseModeGraphic^1");
	AGS_Mouse_get_Mode = (_AGS_MOUSE_GET_MODE)engine->GetScriptFunctionAddress("Mouse::get_Mode");
	AGS_Mouse_set_Mode = (_AGSMOUSE_SET_MODE)engine->GetScriptFunctionAddress("Mouse::set_Mode");
	AGS_Mouse_get_Visible = (_AGS_MOUSE_GET_VISIBLE)engine->GetScriptFunctionAddress("Mouse::get_Visible");
	AGS_Mouse_set_Visible = (_AGSMOUSE_SET_VISIBLE)engine->GetScriptFunctionAddress("Mouse::set_Visible");
	
	// File methods
	AGS_File_Delete = (_AGSFILE_DELETE)engine->GetScriptFunctionAddress("File::Delete^1");
	AGS_File_Exists = (_AGSFILE_EXISTS)engine->GetScriptFunctionAddress("File::Exists^1");
	AGS_File_Open = (_AGSFILE_OPEN)engine->GetScriptFunctionAddress("File::Open^2");
	AGS_File_Close = (_AGSFILE_CLOSE)engine->GetScriptFunctionAddress("File::Close^0");
	AGS_File_ReadInt = (_AGSFILE_READINT)engine->GetScriptFunctionAddress("File::ReadInt^0");
	AGS_File_ReadRawChar = (_AGSFILE_READRAWCHAR)engine->GetScriptFunctionAddress("File::ReadRawChar^0");
	AGS_File_ReadRawInt = (_AGSFILE_READRAWINT)engine->GetScriptFunctionAddress("File::ReadRawInt^0");
	AGS_File_ReadRawLineBack = (_AGSFILE_READRAWLINEBACK)engine->GetScriptFunctionAddress("File::ReadRawLineBack^0");
	AGS_File_ReadStringBack = (_AGSFILE_READSTRINGBACK)engine->GetScriptFunctionAddress("File::ReadStringBack^0");
	AGS_File_WriteInt = (_AGSFILE_WRITEINT)engine->GetScriptFunctionAddress("File::WriteInt^1");
	AGS_File_WriteRawChar = (_AGSFILE_WRITERAWCHAR)engine->GetScriptFunctionAddress("File::WriteRawChar^1");
	AGS_File_WriteRawLine = (_AGSFILE_WRITERAWLINE)engine->GetScriptFunctionAddress("File::WriteRawLine^1");
	AGS_File_WriteString = (_AGSFILE_WRITESTRING)engine->GetScriptFunctionAddress("File::WriteString^1");
	AGS_File_get_EOF = (_AGS_FILE_GET_EOF)engine->GetScriptFunctionAddress("File::get_EOF");
	AGS_File_get_Error = (_AGS_FILE_GET_ERROR)engine->GetScriptFunctionAddress("File::get_Error");
	
	// InventoryItem methods
	AGS_InventoryItem_GetAtScreenXY = (_AGSINVENTORYITEM_GETATSCREENXY)engine->GetScriptFunctionAddress("InventoryItem::GetAtScreenXY^2");
	AGS_InventoryItem_GetProperty = (_AGSINVENTORYITEM_GETPROPERTY)engine->GetScriptFunctionAddress("InventoryItem::GetProperty^1");
	AGS_InventoryItem_GetTextProperty = (_AGSINVENTORYITEM_GETTEXTPROPERTY)engine->GetScriptFunctionAddress("InventoryItem::GetTextProperty^1");
	AGS_InventoryItem_IsInteractionAvailable = (_AGSINVENTORYITEM_ISINTERACTIONAVAILABLE)engine->GetScriptFunctionAddress("InventoryItem::IsInteractionAvailable^1");
	AGS_InventoryItem_RunInteraction = (_AGSINVENTORYITEM_RUNINTERACTION)engine->GetScriptFunctionAddress("InventoryItem::RunInteraction^1");
	AGS_InventoryItem_get_CursorGraphic = (_AGS_INVENTORYITEM_GET_CURSORGRAPHIC)engine->GetScriptFunctionAddress("InventoryItem::get_CursorGraphic");
	AGS_InventoryItem_set_CursorGraphic = (_AGSINVENTORYITEM_SET_CURSORGRAPHIC)engine->GetScriptFunctionAddress("InventoryItem::set_CursorGraphic");
	AGS_InventoryItem_get_Graphic = (_AGS_INVENTORYITEM_GET_GRAPHIC)engine->GetScriptFunctionAddress("InventoryItem::get_Graphic");
	AGS_InventoryItem_set_Graphic = (_AGSINVENTORYITEM_SET_GRAPHIC)engine->GetScriptFunctionAddress("InventoryItem::set_Graphic");
	AGS_InventoryItem_get_ID = (_AGS_INVENTORYITEM_GET_ID)engine->GetScriptFunctionAddress("InventoryItem::get_ID");
	AGS_InventoryItem_get_Name = (_AGS_INVENTORYITEM_GET_NAME)engine->GetScriptFunctionAddress("InventoryItem::get_Name");
	AGS_InventoryItem_set_Name = (_AGSINVENTORYITEM_SET_NAME)engine->GetScriptFunctionAddress("InventoryItem::set_Name");
	
	// Overlay methods
	AGS_Overlay_CreateGraphical = (_AGSOVERLAY_CREATEGRAPHICAL)engine->GetScriptFunctionAddress("Overlay::CreateGraphical^4");
	AGS_Overlay_CreateTextual = (_AGSOVERLAY_CREATETEXTUAL)engine->GetScriptFunctionAddress("Overlay::CreateTextual^101");
	AGS_Overlay_SetText = (_AGSOVERLAY_SETTEXT)engine->GetScriptFunctionAddress("Overlay::SetText^101");
	AGS_Overlay_Remove = (_AGSOVERLAY_REMOVE)engine->GetScriptFunctionAddress("Overlay::Remove^0");
	AGS_Overlay_get_Valid = (_AGS_OVERLAY_GET_VALID)engine->GetScriptFunctionAddress("Overlay::get_Valid");
	AGS_Overlay_get_X = (_AGS_OVERLAY_GET_X)engine->GetScriptFunctionAddress("Overlay::get_X");
	AGS_Overlay_set_X = (_AGSOVERLAY_SET_X)engine->GetScriptFunctionAddress("Overlay::set_X");
	AGS_Overlay_get_Y = (_AGS_OVERLAY_GET_Y)engine->GetScriptFunctionAddress("Overlay::get_Y");
	AGS_Overlay_set_Y = (_AGSOVERLAY_SET_Y)engine->GetScriptFunctionAddress("Overlay::set_Y");
	
	// DynamicSprite methods
	AGS_DynamicSprite_Create = (_AGSDYNAMICSPRITE_CREATE)engine->GetScriptFunctionAddress("DynamicSprite::Create^3");
	AGS_DynamicSprite_CreateFromBackground = (_AGSDYNAMICSPRITE_CREATEFROMBACKGROUND)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromBackground^5");
	AGS_DynamicSprite_CreateFromDrawingSurface = (_AGSDYNAMICSPRITE_CREATEFROMDRAWINGSURFACE)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromDrawingSurface^5");
	AGS_DynamicSprite_CreateFromExistingSprite = (_AGSDYNAMICSPRITE_CREATEFROMEXISTINGSPRITE)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromExistingSprite^2");
	AGS_DynamicSprite_CreateFromFile = (_AGSDYNAMICSPRITE_CREATEFROMFILE)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromFile^1");
	AGS_DynamicSprite_CreateFromSaveGame = (_AGSDYNAMICSPRITE_CREATEFROMSAVEGAME)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromSaveGame^3");
	AGS_DynamicSprite_CreateFromScreenShot = (_AGSDYNAMICSPRITE_CREATEFROMSCREENSHOT)engine->GetScriptFunctionAddress("DynamicSprite::CreateFromScreenShot^2");
	AGS_DynamicSprite_ChangeCanvasSize = (_AGSDYNAMICSPRITE_CHANGECANVASSIZE)engine->GetScriptFunctionAddress("DynamicSprite::ChangeCanvasSize^4");
	AGS_DynamicSprite_CopyTransparencyMask = (_AGSDYNAMICSPRITE_COPYTRANSPARENCYMASK)engine->GetScriptFunctionAddress("DynamicSprite::CopyTransparencyMask^1");
	AGS_DynamicSprite_Crop = (_AGSDYNAMICSPRITE_CROP)engine->GetScriptFunctionAddress("DynamicSprite::Crop^4");
	AGS_DynamicSprite_Delete = (_AGSDYNAMICSPRITE_DELETE)engine->GetScriptFunctionAddress("DynamicSprite::Delete^0");
	AGS_DynamicSprite_Flip = (_AGSDYNAMICSPRITE_FLIP)engine->GetScriptFunctionAddress("DynamicSprite::Flip^1");
	AGS_DynamicSprite_GetDrawingSurface = (_AGSDYNAMICSPRITE_GETDRAWINGSURFACE)engine->GetScriptFunctionAddress("DynamicSprite::GetDrawingSurface^0");
	AGS_DynamicSprite_Resize = (_AGSDYNAMICSPRITE_RESIZE)engine->GetScriptFunctionAddress("DynamicSprite::Resize^2");
	AGS_DynamicSprite_Rotate = (_AGSDYNAMICSPRITE_ROTATE)engine->GetScriptFunctionAddress("DynamicSprite::Rotate^3");
	AGS_DynamicSprite_SaveToFile = (_AGSDYNAMICSPRITE_SAVETOFILE)engine->GetScriptFunctionAddress("DynamicSprite::SaveToFile^1");
	AGS_DynamicSprite_Tint = (_AGSDYNAMICSPRITE_TINT)engine->GetScriptFunctionAddress("DynamicSprite::Tint^5");
	AGS_DynamicSprite_get_ColorDepth = (_AGS_DYNAMICSPRITE_GET_COLORDEPTH)engine->GetScriptFunctionAddress("DynamicSprite::get_ColorDepth");
	AGS_DynamicSprite_get_Graphic = (_AGS_DYNAMICSPRITE_GET_GRAPHIC)engine->GetScriptFunctionAddress("DynamicSprite::get_Graphic");
	AGS_DynamicSprite_get_Height = (_AGS_DYNAMICSPRITE_GET_HEIGHT)engine->GetScriptFunctionAddress("DynamicSprite::get_Height");
	AGS_DynamicSprite_get_Width = (_AGS_DYNAMICSPRITE_GET_WIDTH)engine->GetScriptFunctionAddress("DynamicSprite::get_Width");
	
	// GUIControl methods
	AGS_GUIControl_BringToFront = (_AGSGUICONTROL_BRINGTOFRONT)engine->GetScriptFunctionAddress("GUIControl::BringToFront^0");
	AGS_GUIControl_GetAtScreenXY = (_AGSGUICONTROL_GETATSCREENXY)engine->GetScriptFunctionAddress("GUIControl::GetAtScreenXY^2");
	AGS_GUIControl_SendToBack = (_AGSGUICONTROL_SENDTOBACK)engine->GetScriptFunctionAddress("GUIControl::SendToBack^0");
	AGS_GUIControl_SetPosition = (_AGSGUICONTROL_SETPOSITION)engine->GetScriptFunctionAddress("GUIControl::SetPosition^2");
	AGS_GUIControl_SetSize = (_AGSGUICONTROL_SETSIZE)engine->GetScriptFunctionAddress("GUIControl::SetSize^2");
	AGS_GUIControl_get_AsButton = (_AGS_GUICONTROL_GET_ASBUTTON)engine->GetScriptFunctionAddress("GUIControl::get_AsButton");
	AGS_GUIControl_get_AsInvWindow = (_AGS_GUICONTROL_GET_ASINVWINDOW)engine->GetScriptFunctionAddress("GUIControl::get_AsInvWindow");
	AGS_GUIControl_get_AsLabel = (_AGS_GUICONTROL_GET_ASLABEL)engine->GetScriptFunctionAddress("GUIControl::get_AsLabel");
	AGS_GUIControl_get_AsListBox = (_AGS_GUICONTROL_GET_ASLISTBOX)engine->GetScriptFunctionAddress("GUIControl::get_AsListBox");
	AGS_GUIControl_get_AsSlider = (_AGS_GUICONTROL_GET_ASSLIDER)engine->GetScriptFunctionAddress("GUIControl::get_AsSlider");
	AGS_GUIControl_get_AsTextBox = (_AGS_GUICONTROL_GET_ASTEXTBOX)engine->GetScriptFunctionAddress("GUIControl::get_AsTextBox");
	AGS_GUIControl_get_Clickable = (_AGS_GUICONTROL_GET_CLICKABLE)engine->GetScriptFunctionAddress("GUIControl::get_Clickable");
	AGS_GUIControl_set_Clickable = (_AGSGUICONTROL_SET_CLICKABLE)engine->GetScriptFunctionAddress("GUIControl::set_Clickable");
	AGS_GUIControl_get_Enabled = (_AGS_GUICONTROL_GET_ENABLED)engine->GetScriptFunctionAddress("GUIControl::get_Enabled");
	AGS_GUIControl_set_Enabled = (_AGSGUICONTROL_SET_ENABLED)engine->GetScriptFunctionAddress("GUIControl::set_Enabled");
	AGS_GUIControl_get_Height = (_AGS_GUICONTROL_GET_HEIGHT)engine->GetScriptFunctionAddress("GUIControl::get_Height");
	AGS_GUIControl_set_Height = (_AGSGUICONTROL_SET_HEIGHT)engine->GetScriptFunctionAddress("GUIControl::set_Height");
	AGS_GUIControl_get_ID = (_AGS_GUICONTROL_GET_ID)engine->GetScriptFunctionAddress("GUIControl::get_ID");
	AGS_GUIControl_get_OwningGUI = (_AGS_GUICONTROL_GET_OWNINGGUI)engine->GetScriptFunctionAddress("GUIControl::get_OwningGUI");
	AGS_GUIControl_get_Visible = (_AGS_GUICONTROL_GET_VISIBLE)engine->GetScriptFunctionAddress("GUIControl::get_Visible");
	AGS_GUIControl_set_Visible = (_AGSGUICONTROL_SET_VISIBLE)engine->GetScriptFunctionAddress("GUIControl::set_Visible");
	AGS_GUIControl_get_Width = (_AGS_GUICONTROL_GET_WIDTH)engine->GetScriptFunctionAddress("GUIControl::get_Width");
	AGS_GUIControl_set_Width = (_AGSGUICONTROL_SET_WIDTH)engine->GetScriptFunctionAddress("GUIControl::set_Width");
	AGS_GUIControl_get_X = (_AGS_GUICONTROL_GET_X)engine->GetScriptFunctionAddress("GUIControl::get_X");
	AGS_GUIControl_set_X = (_AGSGUICONTROL_SET_X)engine->GetScriptFunctionAddress("GUIControl::set_X");
	AGS_GUIControl_get_Y = (_AGS_GUICONTROL_GET_Y)engine->GetScriptFunctionAddress("GUIControl::get_Y");
	AGS_GUIControl_set_Y = (_AGSGUICONTROL_SET_Y)engine->GetScriptFunctionAddress("GUIControl::set_Y");
	
	// Label methods
	AGS_Label_get_Font = (_AGS_LABEL_GET_FONT)engine->GetScriptFunctionAddress("Label::get_Font");
	AGS_Label_set_Font = (_AGSLABEL_SET_FONT)engine->GetScriptFunctionAddress("Label::set_Font");
	AGS_Label_get_Text = (_AGS_LABEL_GET_TEXT)engine->GetScriptFunctionAddress("Label::get_Text");
	AGS_Label_set_Text = (_AGSLABEL_SET_TEXT)engine->GetScriptFunctionAddress("Label::set_Text");
	AGS_Label_get_TextColor = (_AGS_LABEL_GET_TEXTCOLOR)engine->GetScriptFunctionAddress("Label::get_TextColor");
	AGS_Label_set_TextColor = (_AGSLABEL_SET_TEXTCOLOR)engine->GetScriptFunctionAddress("Label::set_TextColor");
	
	// Button methods
	AGS_Button_Animate = (_AGSBUTTON_ANIMATE)engine->GetScriptFunctionAddress("Button::Animate^4");
	AGS_Button_get_ClipImage = (_AGS_BUTTON_GET_CLIPIMAGE)engine->GetScriptFunctionAddress("Button::get_ClipImage");
	AGS_Button_set_ClipImage = (_AGSBUTTON_SET_CLIPIMAGE)engine->GetScriptFunctionAddress("Button::set_ClipImage");
	AGS_Button_get_Font = (_AGS_BUTTON_GET_FONT)engine->GetScriptFunctionAddress("Button::get_Font");
	AGS_Button_set_Font = (_AGSBUTTON_SET_FONT)engine->GetScriptFunctionAddress("Button::set_Font");
	AGS_Button_get_Graphic = (_AGS_BUTTON_GET_GRAPHIC)engine->GetScriptFunctionAddress("Button::get_Graphic");
	AGS_Button_get_MouseOverGraphic = (_AGS_BUTTON_GET_MOUSEOVERGRAPHIC)engine->GetScriptFunctionAddress("Button::get_MouseOverGraphic");
	AGS_Button_set_MouseOverGraphic = (_AGSBUTTON_SET_MOUSEOVERGRAPHIC)engine->GetScriptFunctionAddress("Button::set_MouseOverGraphic");
	AGS_Button_get_NormalGraphic = (_AGS_BUTTON_GET_NORMALGRAPHIC)engine->GetScriptFunctionAddress("Button::get_NormalGraphic");
	AGS_Button_set_NormalGraphic = (_AGSBUTTON_SET_NORMALGRAPHIC)engine->GetScriptFunctionAddress("Button::set_NormalGraphic");
	AGS_Button_get_PushedGraphic = (_AGS_BUTTON_GET_PUSHEDGRAPHIC)engine->GetScriptFunctionAddress("Button::get_PushedGraphic");
	AGS_Button_set_PushedGraphic = (_AGSBUTTON_SET_PUSHEDGRAPHIC)engine->GetScriptFunctionAddress("Button::set_PushedGraphic");
	AGS_Button_get_TextColor = (_AGS_BUTTON_GET_TEXTCOLOR)engine->GetScriptFunctionAddress("Button::get_TextColor");
	AGS_Button_set_TextColor = (_AGSBUTTON_SET_TEXTCOLOR)engine->GetScriptFunctionAddress("Button::set_TextColor");
	AGS_Button_get_Text = (_AGS_BUTTON_GET_TEXT)engine->GetScriptFunctionAddress("Button::get_Text");
	AGS_Button_set_Text = (_AGSBUTTON_SET_TEXT)engine->GetScriptFunctionAddress("Button::set_Text");
	
	// Slider methods
	AGS_Slider_get_BackgroundGraphic = (_AGS_SLIDER_GET_BACKGROUNDGRAPHIC)engine->GetScriptFunctionAddress("Slider::get_BackgroundGraphic");
	AGS_Slider_set_BackgroundGraphic = (_AGSSLIDER_SET_BACKGROUNDGRAPHIC)engine->GetScriptFunctionAddress("Slider::set_BackgroundGraphic");
	AGS_Slider_get_HandleGraphic = (_AGS_SLIDER_GET_HANDLEGRAPHIC)engine->GetScriptFunctionAddress("Slider::get_HandleGraphic");
	AGS_Slider_set_HandleGraphic = (_AGSSLIDER_SET_HANDLEGRAPHIC)engine->GetScriptFunctionAddress("Slider::set_HandleGraphic");
	AGS_Slider_get_HandleOffset = (_AGS_SLIDER_GET_HANDLEOFFSET)engine->GetScriptFunctionAddress("Slider::get_HandleOffset");
	AGS_Slider_set_HandleOffset = (_AGSSLIDER_SET_HANDLEOFFSET)engine->GetScriptFunctionAddress("Slider::set_HandleOffset");
	AGS_Slider_get_Max = (_AGS_SLIDER_GET_MAX)engine->GetScriptFunctionAddress("Slider::get_Max");
	AGS_Slider_set_Max = (_AGSSLIDER_SET_MAX)engine->GetScriptFunctionAddress("Slider::set_Max");
	AGS_Slider_get_Min = (_AGS_SLIDER_GET_MIN)engine->GetScriptFunctionAddress("Slider::get_Min");
	AGS_Slider_set_Min = (_AGSSLIDER_SET_MIN)engine->GetScriptFunctionAddress("Slider::set_Min");
	AGS_Slider_get_Value = (_AGS_SLIDER_GET_VALUE)engine->GetScriptFunctionAddress("Slider::get_Value");
	AGS_Slider_set_Value = (_AGSSLIDER_SET_VALUE)engine->GetScriptFunctionAddress("Slider::set_Value");
	
	// TextBox methods
	AGS_TextBox_get_Font = (_AGS_TEXTBOX_GET_FONT)engine->GetScriptFunctionAddress("TextBox::get_Font");
	AGS_TextBox_set_Font = (_AGSTEXTBOX_SET_FONT)engine->GetScriptFunctionAddress("TextBox::set_Font");
	AGS_TextBox_get_Text = (_AGS_TEXTBOX_GET_TEXT)engine->GetScriptFunctionAddress("TextBox::get_Text");
	AGS_TextBox_set_Text = (_AGSTEXTBOX_SET_TEXT)engine->GetScriptFunctionAddress("TextBox::set_Text");
	AGS_TextBox_get_TextColor = (_AGS_TEXTBOX_GET_TEXTCOLOR)engine->GetScriptFunctionAddress("TextBox::get_TextColor");
	AGS_TextBox_set_TextColor = (_AGSTEXTBOX_SET_TEXTCOLOR)engine->GetScriptFunctionAddress("TextBox::set_TextColor");
	
	// InvWindow methods
	AGS_InvWindow_ScrollDown = (_AGSINVWINDOW_SCROLLDOWN)engine->GetScriptFunctionAddress("InvWindow::ScrollDown^0");
	AGS_InvWindow_ScrollUp = (_AGSINVWINDOW_SCROLLUP)engine->GetScriptFunctionAddress("InvWindow::ScrollUp^0");
	AGS_InvWindow_get_CharacterToUse = (_AGS_INVWINDOW_GET_CHARACTERTOUSE)engine->GetScriptFunctionAddress("InvWindow::get_CharacterToUse");
	AGS_InvWindow_set_CharacterToUse = (_AGSINVWINDOW_SET_CHARACTERTOUSE)engine->GetScriptFunctionAddress("InvWindow::set_CharacterToUse");
	AGS_InvWindow_geti_ItemAtIndex = (_AGS_INVWINDOW_GETI_ITEMATINDEX)engine->GetScriptFunctionAddress("InvWindow::geti_ItemAtIndex");
	AGS_InvWindow_get_ItemCount = (_AGS_INVWINDOW_GET_ITEMCOUNT)engine->GetScriptFunctionAddress("InvWindow::get_ItemCount");
	AGS_InvWindow_get_ItemHeight = (_AGS_INVWINDOW_GET_ITEMHEIGHT)engine->GetScriptFunctionAddress("InvWindow::get_ItemHeight");
	AGS_InvWindow_set_ItemHeight = (_AGSINVWINDOW_SET_ITEMHEIGHT)engine->GetScriptFunctionAddress("InvWindow::set_ItemHeight");
	AGS_InvWindow_get_ItemWidth = (_AGS_INVWINDOW_GET_ITEMWIDTH)engine->GetScriptFunctionAddress("InvWindow::get_ItemWidth");
	AGS_InvWindow_set_ItemWidth = (_AGSINVWINDOW_SET_ITEMWIDTH)engine->GetScriptFunctionAddress("InvWindow::set_ItemWidth");
	AGS_InvWindow_get_TopItem = (_AGS_INVWINDOW_GET_TOPITEM)engine->GetScriptFunctionAddress("InvWindow::get_TopItem");
	AGS_InvWindow_set_TopItem = (_AGSINVWINDOW_SET_TOPITEM)engine->GetScriptFunctionAddress("InvWindow::set_TopItem");
	AGS_InvWindow_get_ItemsPerRow = (_AGS_INVWINDOW_GET_ITEMSPERROW)engine->GetScriptFunctionAddress("InvWindow::get_ItemsPerRow");
	AGS_InvWindow_get_RowCount = (_AGS_INVWINDOW_GET_ROWCOUNT)engine->GetScriptFunctionAddress("InvWindow::get_RowCount");
	
	// ListBox methods
	AGS_ListBox_AddItem = (_AGSLISTBOX_ADDITEM)engine->GetScriptFunctionAddress("ListBox::AddItem^1");
	AGS_ListBox_Clear = (_AGSLISTBOX_CLEAR)engine->GetScriptFunctionAddress("ListBox::Clear^0");
	AGS_ListBox_FillDirList = (_AGSLISTBOX_FILLDIRLIST)engine->GetScriptFunctionAddress("ListBox::FillDirList^1");
	AGS_ListBox_FillSaveGameList = (_AGSLISTBOX_FILLSAVEGAMELIST)engine->GetScriptFunctionAddress("ListBox::FillSaveGameList^0");
	AGS_ListBox_GetItemAtLocation = (_AGSLISTBOX_GETITEMATLOCATION)engine->GetScriptFunctionAddress("ListBox::GetItemAtLocation^2");
	AGS_ListBox_InsertItemAt = (_AGSLISTBOX_INSERTITEMAT)engine->GetScriptFunctionAddress("ListBox::InsertItemAt^2");
	AGS_ListBox_RemoveItem = (_AGSLISTBOX_REMOVEITEM)engine->GetScriptFunctionAddress("ListBox::RemoveItem^1");
	AGS_ListBox_ScrollDown = (_AGSLISTBOX_SCROLLDOWN)engine->GetScriptFunctionAddress("ListBox::ScrollDown^0");
	AGS_ListBox_ScrollUp = (_AGSLISTBOX_SCROLLUP)engine->GetScriptFunctionAddress("ListBox::ScrollUp^0");
	AGS_ListBox_get_Font = (_AGS_LISTBOX_GET_FONT)engine->GetScriptFunctionAddress("ListBox::get_Font");
	AGS_ListBox_set_Font = (_AGSLISTBOX_SET_FONT)engine->GetScriptFunctionAddress("ListBox::set_Font");
	AGS_ListBox_get_HideBorder = (_AGS_LISTBOX_GET_HIDEBORDER)engine->GetScriptFunctionAddress("ListBox::get_HideBorder");
	AGS_ListBox_set_HideBorder = (_AGSLISTBOX_SET_HIDEBORDER)engine->GetScriptFunctionAddress("ListBox::set_HideBorder");
	AGS_ListBox_get_HideScrollArrows = (_AGS_LISTBOX_GET_HIDESCROLLARROWS)engine->GetScriptFunctionAddress("ListBox::get_HideScrollArrows");
	AGS_ListBox_set_HideScrollArrows = (_AGSLISTBOX_SET_HIDESCROLLARROWS)engine->GetScriptFunctionAddress("ListBox::set_HideScrollArrows");
	AGS_ListBox_get_ItemCount = (_AGS_LISTBOX_GET_ITEMCOUNT)engine->GetScriptFunctionAddress("ListBox::get_ItemCount");
	AGS_ListBox_geti_Items = (_AGS_LISTBOX_GETI_ITEMS)engine->GetScriptFunctionAddress("ListBox::geti_Items");
	AGS_ListBox_seti_Items = (_AGSLISTBOX_SETI_ITEMS)engine->GetScriptFunctionAddress("ListBox::seti_Items");
	AGS_ListBox_get_RowCount = (_AGS_LISTBOX_GET_ROWCOUNT)engine->GetScriptFunctionAddress("ListBox::get_RowCount");
	AGS_ListBox_geti_SaveGameSlots = (_AGS_LISTBOX_GETI_SAVEGAMESLOTS)engine->GetScriptFunctionAddress("ListBox::geti_SaveGameSlots");
	AGS_ListBox_get_SelectedIndex = (_AGS_LISTBOX_GET_SELECTEDINDEX)engine->GetScriptFunctionAddress("ListBox::get_SelectedIndex");
	AGS_ListBox_set_SelectedIndex = (_AGSLISTBOX_SET_SELECTEDINDEX)engine->GetScriptFunctionAddress("ListBox::set_SelectedIndex");
	AGS_ListBox_get_TopItem = (_AGS_LISTBOX_GET_TOPITEM)engine->GetScriptFunctionAddress("ListBox::get_TopItem");
	AGS_ListBox_set_TopItem = (_AGSLISTBOX_SET_TOPITEM)engine->GetScriptFunctionAddress("ListBox::set_TopItem");
	
	// GUI methods
	AGS_GUI_Centre = (_AGSGUI_CENTRE)engine->GetScriptFunctionAddress("GUI::Centre^0");
	AGS_GUI_GetAtScreenXY = (_AGSGUI_GETATSCREENXY)engine->GetScriptFunctionAddress("GUI::GetAtScreenXY^2");
	AGS_GUI_SetPosition = (_AGSGUI_SETPOSITION)engine->GetScriptFunctionAddress("GUI::SetPosition^2");
	AGS_GUI_SetSize = (_AGSGUI_SETSIZE)engine->GetScriptFunctionAddress("GUI::SetSize^2");
	AGS_GUI_get_BackgroundGraphic = (_AGS_GUI_GET_BACKGROUNDGRAPHIC)engine->GetScriptFunctionAddress("GUI::get_BackgroundGraphic");
	AGS_GUI_set_BackgroundGraphic = (_AGSGUI_SET_BACKGROUNDGRAPHIC)engine->GetScriptFunctionAddress("GUI::set_BackgroundGraphic");
	AGS_GUI_get_Clickable = (_AGS_GUI_GET_CLICKABLE)engine->GetScriptFunctionAddress("GUI::get_Clickable");
	AGS_GUI_set_Clickable = (_AGSGUI_SET_CLICKABLE)engine->GetScriptFunctionAddress("GUI::set_Clickable");
	AGS_GUI_geti_Controls = (_AGS_GUI_GETI_CONTROLS)engine->GetScriptFunctionAddress("GUI::geti_Controls");
	AGS_GUI_get_ControlCount = (_AGS_GUI_GET_CONTROLCOUNT)engine->GetScriptFunctionAddress("GUI::get_ControlCount");
	AGS_GUI_get_Height = (_AGS_GUI_GET_HEIGHT)engine->GetScriptFunctionAddress("GUI::get_Height");
	AGS_GUI_set_Height = (_AGSGUI_SET_HEIGHT)engine->GetScriptFunctionAddress("GUI::set_Height");
	AGS_GUI_get_ID = (_AGS_GUI_GET_ID)engine->GetScriptFunctionAddress("GUI::get_ID");
	AGS_GUI_get_Transparency = (_AGS_GUI_GET_TRANSPARENCY)engine->GetScriptFunctionAddress("GUI::get_Transparency");
	AGS_GUI_set_Transparency = (_AGSGUI_SET_TRANSPARENCY)engine->GetScriptFunctionAddress("GUI::set_Transparency");
	AGS_GUI_get_Visible = (_AGS_GUI_GET_VISIBLE)engine->GetScriptFunctionAddress("GUI::get_Visible");
	AGS_GUI_set_Visible = (_AGSGUI_SET_VISIBLE)engine->GetScriptFunctionAddress("GUI::set_Visible");
	AGS_GUI_get_Width = (_AGS_GUI_GET_WIDTH)engine->GetScriptFunctionAddress("GUI::get_Width");
	AGS_GUI_set_Width = (_AGSGUI_SET_WIDTH)engine->GetScriptFunctionAddress("GUI::set_Width");
	AGS_GUI_get_X = (_AGS_GUI_GET_X)engine->GetScriptFunctionAddress("GUI::get_X");
	AGS_GUI_set_X = (_AGSGUI_SET_X)engine->GetScriptFunctionAddress("GUI::set_X");
	AGS_GUI_get_Y = (_AGS_GUI_GET_Y)engine->GetScriptFunctionAddress("GUI::get_Y");
	AGS_GUI_set_Y = (_AGSGUI_SET_Y)engine->GetScriptFunctionAddress("GUI::set_Y");
	AGS_GUI_get_ZOrder = (_AGS_GUI_GET_ZORDER)engine->GetScriptFunctionAddress("GUI::get_ZOrder");
	AGS_GUI_set_ZOrder = (_AGSGUI_SET_ZORDER)engine->GetScriptFunctionAddress("GUI::set_ZOrder");
	
	// Hotspot methods
	AGS_Hotspot_GetAtScreenXY = (_AGSHOTSPOT_GETATSCREENXY)engine->GetScriptFunctionAddress("Hotspot::GetAtScreenXY^2");
	AGS_Hotspot_GetProperty = (_AGSHOTSPOT_GETPROPERTY)engine->GetScriptFunctionAddress("Hotspot::GetProperty^1");
	AGS_Hotspot_GetTextProperty = (_AGSHOTSPOT_GETTEXTPROPERTY)engine->GetScriptFunctionAddress("Hotspot::GetTextProperty^1");
	AGS_Hotspot_RunInteraction = (_AGSHOTSPOT_RUNINTERACTION)engine->GetScriptFunctionAddress("Hotspot::RunInteraction^1");
	AGS_Hotspot_get_Enabled = (_AGS_HOTSPOT_GET_ENABLED)engine->GetScriptFunctionAddress("Hotspot::get_Enabled");
	AGS_Hotspot_set_Enabled = (_AGSHOTSPOT_SET_ENABLED)engine->GetScriptFunctionAddress("Hotspot::set_Enabled");
	AGS_Hotspot_get_ID = (_AGS_HOTSPOT_GET_ID)engine->GetScriptFunctionAddress("Hotspot::get_ID");
	AGS_Hotspot_get_Name = (_AGS_HOTSPOT_GET_NAME)engine->GetScriptFunctionAddress("Hotspot::get_Name");
	AGS_Hotspot_get_WalkToX = (_AGS_HOTSPOT_GET_WALKTOX)engine->GetScriptFunctionAddress("Hotspot::get_WalkToX");
	AGS_Hotspot_get_WalkToY = (_AGS_HOTSPOT_GET_WALKTOY)engine->GetScriptFunctionAddress("Hotspot::get_WalkToY");
	
	// Region methods
	AGS_Region_GetAtRoomXY = (_AGSREGION_GETATROOMXY)engine->GetScriptFunctionAddress("Region::GetAtRoomXY^2");
	AGS_Region_RunInteraction = (_AGSREGION_RUNINTERACTION)engine->GetScriptFunctionAddress("Region::RunInteraction^1");
	AGS_Region_Tint = (_AGSREGION_TINT)engine->GetScriptFunctionAddress("Region::Tint^4");
	AGS_Region_get_Enabled = (_AGS_REGION_GET_ENABLED)engine->GetScriptFunctionAddress("Region::get_Enabled");
	AGS_Region_set_Enabled = (_AGSREGION_SET_ENABLED)engine->GetScriptFunctionAddress("Region::set_Enabled");
	AGS_Region_get_ID = (_AGS_REGION_GET_ID)engine->GetScriptFunctionAddress("Region::get_ID");
	AGS_Region_get_LightLevel = (_AGS_REGION_GET_LIGHTLEVEL)engine->GetScriptFunctionAddress("Region::get_LightLevel");
	AGS_Region_set_LightLevel = (_AGSREGION_SET_LIGHTLEVEL)engine->GetScriptFunctionAddress("Region::set_LightLevel");
	AGS_Region_get_TintEnabled = (_AGS_REGION_GET_TINTENABLED)engine->GetScriptFunctionAddress("Region::get_TintEnabled");
	AGS_Region_get_TintBlue = (_AGS_REGION_GET_TINTBLUE)engine->GetScriptFunctionAddress("Region::get_TintBlue");
	AGS_Region_get_TintGreen = (_AGS_REGION_GET_TINTGREEN)engine->GetScriptFunctionAddress("Region::get_TintGreen");
	AGS_Region_get_TintRed = (_AGS_REGION_GET_TINTRED)engine->GetScriptFunctionAddress("Region::get_TintRed");
	AGS_Region_get_TintSaturation = (_AGS_REGION_GET_TINTSATURATION)engine->GetScriptFunctionAddress("Region::get_TintSaturation");
	
	// Dialog methods
	AGS_Dialog_DisplayOptions = (_AGSDIALOG_DISPLAYOPTIONS)engine->GetScriptFunctionAddress("Dialog::DisplayOptions^1");
	AGS_Dialog_GetOptionState = (_AGSDIALOG_GETOPTIONSTATE)engine->GetScriptFunctionAddress("Dialog::GetOptionState^1");
	AGS_Dialog_GetOptionText = (_AGSDIALOG_GETOPTIONTEXT)engine->GetScriptFunctionAddress("Dialog::GetOptionText^1");
	AGS_Dialog_HasOptionBeenChosen = (_AGSDIALOG_HASOPTIONBEENCHOSEN)engine->GetScriptFunctionAddress("Dialog::HasOptionBeenChosen^1");
	AGS_Dialog_SetOptionState = (_AGSDIALOG_SETOPTIONSTATE)engine->GetScriptFunctionAddress("Dialog::SetOptionState^2");
	AGS_Dialog_Start = (_AGSDIALOG_START)engine->GetScriptFunctionAddress("Dialog::Start^0");
	AGS_Dialog_get_ID = (_AGS_DIALOG_GET_ID)engine->GetScriptFunctionAddress("Dialog::get_ID");
	AGS_Dialog_get_OptionCount = (_AGS_DIALOG_GET_OPTIONCOUNT)engine->GetScriptFunctionAddress("Dialog::get_OptionCount");
	
	// DateTime methods
	AGS_DateTime_get_Now = (_AGS_DATETIME_GET_NOW)engine->GetScriptFunctionAddress("DateTime::get_Now");
	AGS_DateTime_get_Year = (_AGS_DATETIME_GET_YEAR)engine->GetScriptFunctionAddress("DateTime::get_Year");
	AGS_DateTime_get_Month = (_AGS_DATETIME_GET_MONTH)engine->GetScriptFunctionAddress("DateTime::get_Month");
	AGS_DateTime_get_DayOfMonth = (_AGS_DATETIME_GET_DAYOFMONTH)engine->GetScriptFunctionAddress("DateTime::get_DayOfMonth");
	AGS_DateTime_get_Hour = (_AGS_DATETIME_GET_HOUR)engine->GetScriptFunctionAddress("DateTime::get_Hour");
	AGS_DateTime_get_Minute = (_AGS_DATETIME_GET_MINUTE)engine->GetScriptFunctionAddress("DateTime::get_Minute");
	AGS_DateTime_get_Second = (_AGS_DATETIME_GET_SECOND)engine->GetScriptFunctionAddress("DateTime::get_Second");
	AGS_DateTime_get_RawTime = (_AGS_DATETIME_GET_RAWTIME)engine->GetScriptFunctionAddress("DateTime::get_RawTime");
	
	// DialogOptionsRenderingInfo methods
	AGS_DialogOptionsRenderingInfo_get_ActiveOptionID = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_ACTIVEOPTIONID)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_ActiveOptionID");
	AGS_DialogOptionsRenderingInfo_set_ActiveOptionID = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_ACTIVEOPTIONID)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_ActiveOptionID");
	AGS_DialogOptionsRenderingInfo_get_DialogToRender = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_DIALOGTORENDER)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_DialogToRender");
	AGS_DialogOptionsRenderingInfo_get_Height = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_HEIGHT)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_Height");
	AGS_DialogOptionsRenderingInfo_set_Height = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_HEIGHT)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_Height");
	AGS_DialogOptionsRenderingInfo_get_ParserTextBoxWidth = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXWIDTH)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_ParserTextBoxWidth");
	AGS_DialogOptionsRenderingInfo_set_ParserTextBoxWidth = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXWIDTH)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_ParserTextBoxWidth");
	AGS_DialogOptionsRenderingInfo_get_ParserTextBoxX = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXX)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_ParserTextBoxX");
	AGS_DialogOptionsRenderingInfo_set_ParserTextBoxX = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXX)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_ParserTextBoxX");
	AGS_DialogOptionsRenderingInfo_get_ParserTextBoxY = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_PARSERTEXTBOXY)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_ParserTextBoxY");
	AGS_DialogOptionsRenderingInfo_set_ParserTextBoxY = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_PARSERTEXTBOXY)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_ParserTextBoxY");
	AGS_DialogOptionsRenderingInfo_get_Surface = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_SURFACE)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_Surface");
	AGS_DialogOptionsRenderingInfo_get_Width = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_WIDTH)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_Width");
	AGS_DialogOptionsRenderingInfo_set_Width = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_WIDTH)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_Width");
	AGS_DialogOptionsRenderingInfo_get_X = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_X)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_X");
	AGS_DialogOptionsRenderingInfo_set_X = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_X)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_X");
	AGS_DialogOptionsRenderingInfo_get_Y = (_AGS_DIALOGOPTIONSRENDERINGINFO_GET_Y)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::get_Y");
	AGS_DialogOptionsRenderingInfo_set_Y = (_AGSDIALOGOPTIONSRENDERINGINFO_SET_Y)engine->GetScriptFunctionAddress("DialogOptionsRenderingInfo::set_Y");
	
	// System methods
	AGS_System_get_CapsLock = (_AGS_SYSTEM_GET_CAPSLOCK)engine->GetScriptFunctionAddress("System::get_CapsLock");
	AGS_System_get_ColorDepth = (_AGS_SYSTEM_GET_COLORDEPTH)engine->GetScriptFunctionAddress("System::get_ColorDepth");
	AGS_System_get_Gamma = (_AGS_SYSTEM_GET_GAMMA)engine->GetScriptFunctionAddress("System::get_Gamma");
	AGS_System_set_Gamma = (_AGSSYSTEM_SET_GAMMA)engine->GetScriptFunctionAddress("System::set_Gamma");
	AGS_System_get_HardwareAcceleration = (_AGS_SYSTEM_GET_HARDWAREACCELERATION)engine->GetScriptFunctionAddress("System::get_HardwareAcceleration");
	AGS_System_get_NumLock = (_AGS_SYSTEM_GET_NUMLOCK)engine->GetScriptFunctionAddress("System::get_NumLock");
	AGS_System_get_OperatingSystem = (_AGS_SYSTEM_GET_OPERATINGSYSTEM)engine->GetScriptFunctionAddress("System::get_OperatingSystem");
	AGS_System_get_ScreenHeight = (_AGS_SYSTEM_GET_SCREENHEIGHT)engine->GetScriptFunctionAddress("System::get_ScreenHeight");
	AGS_System_get_ScreenWidth = (_AGS_SYSTEM_GET_SCREENWIDTH)engine->GetScriptFunctionAddress("System::get_ScreenWidth");
	AGS_System_get_ScrollLock = (_AGS_SYSTEM_GET_SCROLLLOCK)engine->GetScriptFunctionAddress("System::get_ScrollLock");
	AGS_System_get_SupportsGammaControl = (_AGS_SYSTEM_GET_SUPPORTSGAMMACONTROL)engine->GetScriptFunctionAddress("System::get_SupportsGammaControl");
	AGS_System_get_Version = (_AGS_SYSTEM_GET_VERSION)engine->GetScriptFunctionAddress("System::get_Version");
	AGS_System_get_ViewportHeight = (_AGS_SYSTEM_GET_VIEWPORTHEIGHT)engine->GetScriptFunctionAddress("System::get_ViewportHeight");
	AGS_System_get_ViewportWidth = (_AGS_SYSTEM_GET_VIEWPORTWIDTH)engine->GetScriptFunctionAddress("System::get_ViewportWidth");
	AGS_System_get_VSync = (_AGS_SYSTEM_GET_VSYNC)engine->GetScriptFunctionAddress("System::get_VSync");
	AGS_System_set_VSync = (_AGSSYSTEM_SET_VSYNC)engine->GetScriptFunctionAddress("System::set_VSync");
	AGS_System_get_Windowed = (_AGS_SYSTEM_GET_WINDOWED)engine->GetScriptFunctionAddress("System::get_Windowed");
	
	// Object methods
	AGS_Object_Animate = (_AGSOBJECT_ANIMATE)engine->GetScriptFunctionAddress("Object::Animate^5");
	AGS_Object_GetAtScreenXY = (_AGSOBJECT_GETATSCREENXY)engine->GetScriptFunctionAddress("Object::GetAtScreenXY^2");
	AGS_Object_GetProperty = (_AGSOBJECT_GETPROPERTY)engine->GetScriptFunctionAddress("Object::GetProperty^1");
	AGS_Object_GetTextProperty = (_AGSOBJECT_GETTEXTPROPERTY)engine->GetScriptFunctionAddress("Object::GetTextProperty^1");
	AGS_Object_IsCollidingWithObject = (_AGSOBJECT_ISCOLLIDINGWITHOBJECT)engine->GetScriptFunctionAddress("Object::IsCollidingWithObject^1");
	AGS_Object_MergeIntoBackground = (_AGSOBJECT_MERGEINTOBACKGROUND)engine->GetScriptFunctionAddress("Object::MergeIntoBackground^0");
	AGS_Object_Move = (_AGSOBJECT_MOVE)engine->GetScriptFunctionAddress("Object::Move^5");
	AGS_Object_RemoveTint = (_AGSOBJECT_REMOVETINT)engine->GetScriptFunctionAddress("Object::RemoveTint^0");
	AGS_Object_RunInteraction = (_AGSOBJECT_RUNINTERACTION)engine->GetScriptFunctionAddress("Object::RunInteraction^1");
	AGS_Object_SetPosition = (_AGSOBJECT_SETPOSITION)engine->GetScriptFunctionAddress("Object::SetPosition^2");
	AGS_Object_SetView = (_AGSOBJECT_SETVIEW)engine->GetScriptFunctionAddress("Object::SetView^3");
	AGS_Object_StopAnimating = (_AGSOBJECT_STOPANIMATING)engine->GetScriptFunctionAddress("Object::StopAnimating^0");
	AGS_Object_StopMoving = (_AGSOBJECT_STOPMOVING)engine->GetScriptFunctionAddress("Object::StopMoving^0");
	AGS_Object_Tint = (_AGSOBJECT_TINT)engine->GetScriptFunctionAddress("Object::Tint^5");
	AGS_Object_get_Animating = (_AGS_OBJECT_GET_ANIMATING)engine->GetScriptFunctionAddress("Object::get_Animating");
	AGS_Object_get_Baseline = (_AGS_OBJECT_GET_BASELINE)engine->GetScriptFunctionAddress("Object::get_Baseline");
	AGS_Object_set_Baseline = (_AGSOBJECT_SET_BASELINE)engine->GetScriptFunctionAddress("Object::set_Baseline");
	AGS_Object_get_BlockingHeight = (_AGS_OBJECT_GET_BLOCKINGHEIGHT)engine->GetScriptFunctionAddress("Object::get_BlockingHeight");
	AGS_Object_set_BlockingHeight = (_AGSOBJECT_SET_BLOCKINGHEIGHT)engine->GetScriptFunctionAddress("Object::set_BlockingHeight");
	AGS_Object_get_BlockingWidth = (_AGS_OBJECT_GET_BLOCKINGWIDTH)engine->GetScriptFunctionAddress("Object::get_BlockingWidth");
	AGS_Object_set_BlockingWidth = (_AGSOBJECT_SET_BLOCKINGWIDTH)engine->GetScriptFunctionAddress("Object::set_BlockingWidth");
	AGS_Object_get_Clickable = (_AGS_OBJECT_GET_CLICKABLE)engine->GetScriptFunctionAddress("Object::get_Clickable");
	AGS_Object_set_Clickable = (_AGSOBJECT_SET_CLICKABLE)engine->GetScriptFunctionAddress("Object::set_Clickable");
	AGS_Object_get_Frame = (_AGS_OBJECT_GET_FRAME)engine->GetScriptFunctionAddress("Object::get_Frame");
	AGS_Object_get_Graphic = (_AGS_OBJECT_GET_GRAPHIC)engine->GetScriptFunctionAddress("Object::get_Graphic");
	AGS_Object_set_Graphic = (_AGSOBJECT_SET_GRAPHIC)engine->GetScriptFunctionAddress("Object::set_Graphic");
	AGS_Object_get_ID = (_AGS_OBJECT_GET_ID)engine->GetScriptFunctionAddress("Object::get_ID");
	AGS_Object_get_IgnoreScaling = (_AGS_OBJECT_GET_IGNORESCALING)engine->GetScriptFunctionAddress("Object::get_IgnoreScaling");
	AGS_Object_set_IgnoreScaling = (_AGSOBJECT_SET_IGNORESCALING)engine->GetScriptFunctionAddress("Object::set_IgnoreScaling");
	AGS_Object_get_IgnoreWalkbehinds = (_AGS_OBJECT_GET_IGNOREWALKBEHINDS)engine->GetScriptFunctionAddress("Object::get_IgnoreWalkbehinds");
	AGS_Object_set_IgnoreWalkbehinds = (_AGSOBJECT_SET_IGNOREWALKBEHINDS)engine->GetScriptFunctionAddress("Object::set_IgnoreWalkbehinds");
	AGS_Object_get_Loop = (_AGS_OBJECT_GET_LOOP)engine->GetScriptFunctionAddress("Object::get_Loop");
	AGS_Object_get_Moving = (_AGS_OBJECT_GET_MOVING)engine->GetScriptFunctionAddress("Object::get_Moving");
	AGS_Object_get_Name = (_AGS_OBJECT_GET_NAME)engine->GetScriptFunctionAddress("Object::get_Name");
	AGS_Object_get_Solid = (_AGS_OBJECT_GET_SOLID)engine->GetScriptFunctionAddress("Object::get_Solid");
	AGS_Object_set_Solid = (_AGSOBJECT_SET_SOLID)engine->GetScriptFunctionAddress("Object::set_Solid");
	AGS_Object_get_Transparency = (_AGS_OBJECT_GET_TRANSPARENCY)engine->GetScriptFunctionAddress("Object::get_Transparency");
	AGS_Object_set_Transparency = (_AGSOBJECT_SET_TRANSPARENCY)engine->GetScriptFunctionAddress("Object::set_Transparency");
	AGS_Object_get_View = (_AGS_OBJECT_GET_VIEW)engine->GetScriptFunctionAddress("Object::get_View");
	AGS_Object_get_Visible = (_AGS_OBJECT_GET_VISIBLE)engine->GetScriptFunctionAddress("Object::get_Visible");
	AGS_Object_set_Visible = (_AGSOBJECT_SET_VISIBLE)engine->GetScriptFunctionAddress("Object::set_Visible");
	AGS_Object_get_X = (_AGS_OBJECT_GET_X)engine->GetScriptFunctionAddress("Object::get_X");
	AGS_Object_set_X = (_AGSOBJECT_SET_X)engine->GetScriptFunctionAddress("Object::set_X");
	AGS_Object_get_Y = (_AGS_OBJECT_GET_Y)engine->GetScriptFunctionAddress("Object::get_Y");
	AGS_Object_set_Y = (_AGSOBJECT_SET_Y)engine->GetScriptFunctionAddress("Object::set_Y");
	
	// Character methods
	AGS_Character_AddInventory = (_AGSCHARACTER_ADDINVENTORY)engine->GetScriptFunctionAddress("Character::AddInventory^2");
	AGS_Character_AddWaypoint = (_AGSCHARACTER_ADDWAYPOINT)engine->GetScriptFunctionAddress("Character::AddWaypoint^2");
	AGS_Character_Animate = (_AGSCHARACTER_ANIMATE)engine->GetScriptFunctionAddress("Character::Animate^5");
	AGS_Character_ChangeRoom = (_AGSCHARACTER_CHANGEROOM)engine->GetScriptFunctionAddress("Character::ChangeRoom^3");
	AGS_Character_ChangeRoomAutoPosition = (_AGSCHARACTER_CHANGEROOMAUTOPOSITION)engine->GetScriptFunctionAddress("Character::ChangeRoomAutoPosition^2");
	AGS_Character_ChangeView = (_AGSCHARACTER_CHANGEVIEW)engine->GetScriptFunctionAddress("Character::ChangeView^1");
	AGS_Character_FaceCharacter = (_AGSCHARACTER_FACECHARACTER)engine->GetScriptFunctionAddress("Character::FaceCharacter^2");
	AGS_Character_FaceLocation = (_AGSCHARACTER_FACELOCATION)engine->GetScriptFunctionAddress("Character::FaceLocation^3");
	AGS_Character_FaceObject = (_AGSCHARACTER_FACEOBJECT)engine->GetScriptFunctionAddress("Character::FaceObject^2");
	AGS_Character_FollowCharacter = (_AGSCHARACTER_FOLLOWCHARACTER)engine->GetScriptFunctionAddress("Character::FollowCharacter^3");
	AGS_Character_GetAtScreenXY = (_AGSCHARACTER_GETATSCREENXY)engine->GetScriptFunctionAddress("Character::GetAtScreenXY^2");
	AGS_Character_GetProperty = (_AGSCHARACTER_GETPROPERTY)engine->GetScriptFunctionAddress("Character::GetProperty^1");
	AGS_Character_GetTextProperty = (_AGSCHARACTER_GETTEXTPROPERTY)engine->GetScriptFunctionAddress("Character::GetTextProperty^1");
	AGS_Character_HasInventory = (_AGSCHARACTER_HASINVENTORY)engine->GetScriptFunctionAddress("Character::HasInventory^1");
	AGS_Character_IsCollidingWithChar = (_AGSCHARACTER_ISCOLLIDINGWITHCHAR)engine->GetScriptFunctionAddress("Character::IsCollidingWithChar^1");
	AGS_Character_IsCollidingWithObject = (_AGSCHARACTER_ISCOLLIDINGWITHOBJECT)engine->GetScriptFunctionAddress("Character::IsCollidingWithObject^1");
	AGS_Character_LockView = (_AGSCHARACTER_LOCKVIEW)engine->GetScriptFunctionAddress("Character::LockView^1");
	AGS_Character_LockViewAligned = (_AGSCHARACTER_LOCKVIEWALIGNED)engine->GetScriptFunctionAddress("Character::LockViewAligned^3");
	AGS_Character_LockViewFrame = (_AGSCHARACTER_LOCKVIEWFRAME)engine->GetScriptFunctionAddress("Character::LockViewFrame^3");
	AGS_Character_LockViewOffset = (_AGSCHARACTER_LOCKVIEWOFFSET)engine->GetScriptFunctionAddress("Character::LockViewOffset^3");
	AGS_Character_LoseInventory = (_AGSCHARACTER_LOSEINVENTORY)engine->GetScriptFunctionAddress("Character::LoseInventory^1");
	AGS_Character_Move = (_AGSCHARACTER_MOVE)engine->GetScriptFunctionAddress("Character::Move^4");
	AGS_Character_PlaceOnWalkableArea = (_AGSCHARACTER_PLACEONWALKABLEAREA)engine->GetScriptFunctionAddress("Character::PlaceOnWalkableArea^0");
	AGS_Character_RemoveTint = (_AGSCHARACTER_REMOVETINT)engine->GetScriptFunctionAddress("Character::RemoveTint^0");
	AGS_Character_RunInteraction = (_AGSCHARACTER_RUNINTERACTION)engine->GetScriptFunctionAddress("Character::RunInteraction^1");
	AGS_Character_Say = (_AGSCHARACTER_SAY)engine->GetScriptFunctionAddress("Character::Say^101");
	AGS_Character_SayAt = (_AGSCHARACTER_SAYAT)engine->GetScriptFunctionAddress("Character::SayAt^4");
	AGS_Character_SayBackground = (_AGSCHARACTER_SAYBACKGROUND)engine->GetScriptFunctionAddress("Character::SayBackground^1");
	AGS_Character_SetAsPlayer = (_AGSCHARACTER_SETASPLAYER)engine->GetScriptFunctionAddress("Character::SetAsPlayer^0");
	AGS_Character_SetIdleView = (_AGSCHARACTER_SETIDLEVIEW)engine->GetScriptFunctionAddress("Character::SetIdleView^2");
	AGS_Character_SetWalkSpeed = (_AGSCHARACTER_SETWALKSPEED)engine->GetScriptFunctionAddress("Character::SetWalkSpeed^2");
	AGS_Character_StopMoving = (_AGSCHARACTER_STOPMOVING)engine->GetScriptFunctionAddress("Character::StopMoving^0");
	AGS_Character_Think = (_AGSCHARACTER_THINK)engine->GetScriptFunctionAddress("Character::Think^101");
	AGS_Character_Tint = (_AGSCHARACTER_TINT)engine->GetScriptFunctionAddress("Character::Tint^5");
	AGS_Character_UnlockView = (_AGSCHARACTER_UNLOCKVIEW)engine->GetScriptFunctionAddress("Character::UnlockView^0");
	AGS_Character_Walk = (_AGSCHARACTER_WALK)engine->GetScriptFunctionAddress("Character::Walk^4");
	AGS_Character_WalkStraight = (_AGSCHARACTER_WALKSTRAIGHT)engine->GetScriptFunctionAddress("Character::WalkStraight^3");
	AGS_Character_get_ActiveInventory = (_AGS_CHARACTER_GET_ACTIVEINVENTORY)engine->GetScriptFunctionAddress("Character::get_ActiveInventory");
	AGS_Character_set_ActiveInventory = (_AGSCHARACTER_SET_ACTIVEINVENTORY)engine->GetScriptFunctionAddress("Character::set_ActiveInventory");
	AGS_Character_get_Animating = (_AGS_CHARACTER_GET_ANIMATING)engine->GetScriptFunctionAddress("Character::get_Animating");
	AGS_Character_get_AnimationSpeed = (_AGS_CHARACTER_GET_ANIMATIONSPEED)engine->GetScriptFunctionAddress("Character::get_AnimationSpeed");
	AGS_Character_set_AnimationSpeed = (_AGSCHARACTER_SET_ANIMATIONSPEED)engine->GetScriptFunctionAddress("Character::set_AnimationSpeed");
	AGS_Character_get_Baseline = (_AGS_CHARACTER_GET_BASELINE)engine->GetScriptFunctionAddress("Character::get_Baseline");
	AGS_Character_set_Baseline = (_AGSCHARACTER_SET_BASELINE)engine->GetScriptFunctionAddress("Character::set_Baseline");
	AGS_Character_get_BlinkInterval = (_AGS_CHARACTER_GET_BLINKINTERVAL)engine->GetScriptFunctionAddress("Character::get_BlinkInterval");
	AGS_Character_set_BlinkInterval = (_AGSCHARACTER_SET_BLINKINTERVAL)engine->GetScriptFunctionAddress("Character::set_BlinkInterval");
	AGS_Character_get_BlinkView = (_AGS_CHARACTER_GET_BLINKVIEW)engine->GetScriptFunctionAddress("Character::get_BlinkView");
	AGS_Character_set_BlinkView = (_AGSCHARACTER_SET_BLINKVIEW)engine->GetScriptFunctionAddress("Character::set_BlinkView");
	AGS_Character_get_BlinkWhileThinking = (_AGS_CHARACTER_GET_BLINKWHILETHINKING)engine->GetScriptFunctionAddress("Character::get_BlinkWhileThinking");
	AGS_Character_set_BlinkWhileThinking = (_AGSCHARACTER_SET_BLINKWHILETHINKING)engine->GetScriptFunctionAddress("Character::set_BlinkWhileThinking");
	AGS_Character_get_BlockingHeight = (_AGS_CHARACTER_GET_BLOCKINGHEIGHT)engine->GetScriptFunctionAddress("Character::get_BlockingHeight");
	AGS_Character_set_BlockingHeight = (_AGSCHARACTER_SET_BLOCKINGHEIGHT)engine->GetScriptFunctionAddress("Character::set_BlockingHeight");
	AGS_Character_get_BlockingWidth = (_AGS_CHARACTER_GET_BLOCKINGWIDTH)engine->GetScriptFunctionAddress("Character::get_BlockingWidth");
	AGS_Character_set_BlockingWidth = (_AGSCHARACTER_SET_BLOCKINGWIDTH)engine->GetScriptFunctionAddress("Character::set_BlockingWidth");
	AGS_Character_get_Clickable = (_AGS_CHARACTER_GET_CLICKABLE)engine->GetScriptFunctionAddress("Character::get_Clickable");
	AGS_Character_set_Clickable = (_AGSCHARACTER_SET_CLICKABLE)engine->GetScriptFunctionAddress("Character::set_Clickable");
	AGS_Character_get_DiagonalLoops = (_AGS_CHARACTER_GET_DIAGONALLOOPS)engine->GetScriptFunctionAddress("Character::get_DiagonalLoops");
	AGS_Character_set_DiagonalLoops = (_AGSCHARACTER_SET_DIAGONALLOOPS)engine->GetScriptFunctionAddress("Character::set_DiagonalLoops");
	AGS_Character_get_Frame = (_AGS_CHARACTER_GET_FRAME)engine->GetScriptFunctionAddress("Character::get_Frame");
	AGS_Character_set_Frame = (_AGSCHARACTER_SET_FRAME)engine->GetScriptFunctionAddress("Character::set_Frame");
	AGS_Character_get_HasExplicitTint = (_AGS_CHARACTER_GET_HASEXPLICITTINT)engine->GetScriptFunctionAddress("Character::get_HasExplicitTint");
	AGS_Character_get_ID = (_AGS_CHARACTER_GET_ID)engine->GetScriptFunctionAddress("Character::get_ID");
	AGS_Character_get_IdleView = (_AGS_CHARACTER_GET_IDLEVIEW)engine->GetScriptFunctionAddress("Character::get_IdleView");
	AGS_Character_get_IgnoreLighting = (_AGS_CHARACTER_GET_IGNORELIGHTING)engine->GetScriptFunctionAddress("Character::get_IgnoreLighting");
	AGS_Character_set_IgnoreLighting = (_AGSCHARACTER_SET_IGNORELIGHTING)engine->GetScriptFunctionAddress("Character::set_IgnoreLighting");
	AGS_Character_get_IgnoreScaling = (_AGS_CHARACTER_GET_IGNORESCALING)engine->GetScriptFunctionAddress("Character::get_IgnoreScaling");
	AGS_Character_set_IgnoreScaling = (_AGSCHARACTER_SET_IGNORESCALING)engine->GetScriptFunctionAddress("Character::set_IgnoreScaling");
	AGS_Character_get_IgnoreWalkbehinds = (_AGS_CHARACTER_GET_IGNOREWALKBEHINDS)engine->GetScriptFunctionAddress("Character::get_IgnoreWalkbehinds");
	AGS_Character_set_IgnoreWalkbehinds = (_AGSCHARACTER_SET_IGNOREWALKBEHINDS)engine->GetScriptFunctionAddress("Character::set_IgnoreWalkbehinds");
	AGS_Character_geti_InventoryQuantity = (_AGS_CHARACTER_GETI_INVENTORYQUANTITY)engine->GetScriptFunctionAddress("Character::geti_InventoryQuantity");
	AGS_Character_seti_InventoryQuantity = (_AGSCHARACTER_SETI_INVENTORYQUANTITY)engine->GetScriptFunctionAddress("Character::seti_InventoryQuantity");
	AGS_Character_get_Loop = (_AGS_CHARACTER_GET_LOOP)engine->GetScriptFunctionAddress("Character::get_Loop");
	AGS_Character_set_Loop = (_AGSCHARACTER_SET_LOOP)engine->GetScriptFunctionAddress("Character::set_Loop");
	AGS_Character_get_ManualScaling = (_AGS_CHARACTER_GET_MANUALSCALING)engine->GetScriptFunctionAddress("Character::get_ManualScaling");
	AGS_Character_set_ManualScaling = (_AGSCHARACTER_SET_MANUALSCALING)engine->GetScriptFunctionAddress("Character::set_ManualScaling");
	AGS_Character_get_MovementLinkedToAnimation = (_AGS_CHARACTER_GET_MOVEMENTLINKEDTOANIMATION)engine->GetScriptFunctionAddress("Character::get_MovementLinkedToAnimation");
	AGS_Character_set_MovementLinkedToAnimation = (_AGSCHARACTER_SET_MOVEMENTLINKEDTOANIMATION)engine->GetScriptFunctionAddress("Character::set_MovementLinkedToAnimation");
	AGS_Character_get_Moving = (_AGS_CHARACTER_GET_MOVING)engine->GetScriptFunctionAddress("Character::get_Moving");
	AGS_Character_get_Name = (_AGS_CHARACTER_GET_NAME)engine->GetScriptFunctionAddress("Character::get_Name");
	AGS_Character_set_Name = (_AGSCHARACTER_SET_NAME)engine->GetScriptFunctionAddress("Character::set_Name");
	AGS_Character_get_NormalView = (_AGS_CHARACTER_GET_NORMALVIEW)engine->GetScriptFunctionAddress("Character::get_NormalView");
	AGS_Character_get_PreviousRoom = (_AGS_CHARACTER_GET_PREVIOUSROOM)engine->GetScriptFunctionAddress("Character::get_PreviousRoom");
	AGS_Character_get_Room = (_AGS_CHARACTER_GET_ROOM)engine->GetScriptFunctionAddress("Character::get_Room");
	AGS_Character_get_ScaleMoveSpeed = (_AGS_CHARACTER_GET_SCALEMOVESPEED)engine->GetScriptFunctionAddress("Character::get_ScaleMoveSpeed");
	AGS_Character_set_ScaleMoveSpeed = (_AGSCHARACTER_SET_SCALEMOVESPEED)engine->GetScriptFunctionAddress("Character::set_ScaleMoveSpeed");
	AGS_Character_get_ScaleVolume = (_AGS_CHARACTER_GET_SCALEVOLUME)engine->GetScriptFunctionAddress("Character::get_ScaleVolume");
	AGS_Character_set_ScaleVolume = (_AGSCHARACTER_SET_SCALEVOLUME)engine->GetScriptFunctionAddress("Character::set_ScaleVolume");
	AGS_Character_get_Scaling = (_AGS_CHARACTER_GET_SCALING)engine->GetScriptFunctionAddress("Character::get_Scaling");
	AGS_Character_set_Scaling = (_AGSCHARACTER_SET_SCALING)engine->GetScriptFunctionAddress("Character::set_Scaling");
	AGS_Character_get_Solid = (_AGS_CHARACTER_GET_SOLID)engine->GetScriptFunctionAddress("Character::get_Solid");
	AGS_Character_set_Solid = (_AGSCHARACTER_SET_SOLID)engine->GetScriptFunctionAddress("Character::set_Solid");
	AGS_Character_get_Speaking = (_AGS_CHARACTER_GET_SPEAKING)engine->GetScriptFunctionAddress("Character::get_Speaking");
	AGS_Character_get_SpeakingFrame = (_AGS_CHARACTER_GET_SPEAKINGFRAME)engine->GetScriptFunctionAddress("Character::get_SpeakingFrame");
	AGS_Character_get_SpeechAnimationDelay = (_AGS_CHARACTER_GET_SPEECHANIMATIONDELAY)engine->GetScriptFunctionAddress("Character::get_SpeechAnimationDelay");
	AGS_Character_set_SpeechAnimationDelay = (_AGSCHARACTER_SET_SPEECHANIMATIONDELAY)engine->GetScriptFunctionAddress("Character::set_SpeechAnimationDelay");
	AGS_Character_get_SpeechColor = (_AGS_CHARACTER_GET_SPEECHCOLOR)engine->GetScriptFunctionAddress("Character::get_SpeechColor");
	AGS_Character_set_SpeechColor = (_AGSCHARACTER_SET_SPEECHCOLOR)engine->GetScriptFunctionAddress("Character::set_SpeechColor");
	AGS_Character_get_SpeechView = (_AGS_CHARACTER_GET_SPEECHVIEW)engine->GetScriptFunctionAddress("Character::get_SpeechView");
	AGS_Character_set_SpeechView = (_AGSCHARACTER_SET_SPEECHVIEW)engine->GetScriptFunctionAddress("Character::set_SpeechView");
	AGS_Character_get_ThinkView = (_AGS_CHARACTER_GET_THINKVIEW)engine->GetScriptFunctionAddress("Character::get_ThinkView");
	AGS_Character_set_ThinkView = (_AGSCHARACTER_SET_THINKVIEW)engine->GetScriptFunctionAddress("Character::set_ThinkView");
	AGS_Character_get_Transparency = (_AGS_CHARACTER_GET_TRANSPARENCY)engine->GetScriptFunctionAddress("Character::get_Transparency");
	AGS_Character_set_Transparency = (_AGSCHARACTER_SET_TRANSPARENCY)engine->GetScriptFunctionAddress("Character::set_Transparency");
	AGS_Character_get_TurnBeforeWalking = (_AGS_CHARACTER_GET_TURNBEFOREWALKING)engine->GetScriptFunctionAddress("Character::get_TurnBeforeWalking");
	AGS_Character_set_TurnBeforeWalking = (_AGSCHARACTER_SET_TURNBEFOREWALKING)engine->GetScriptFunctionAddress("Character::set_TurnBeforeWalking");
	AGS_Character_get_View = (_AGS_CHARACTER_GET_VIEW)engine->GetScriptFunctionAddress("Character::get_View");
	AGS_Character_get_WalkSpeedX = (_AGS_CHARACTER_GET_WALKSPEEDX)engine->GetScriptFunctionAddress("Character::get_WalkSpeedX");
	AGS_Character_get_WalkSpeedY = (_AGS_CHARACTER_GET_WALKSPEEDY)engine->GetScriptFunctionAddress("Character::get_WalkSpeedY");
	AGS_Character_get_x = (_AGS_CHARACTER_GET_X)engine->GetScriptFunctionAddress("Character::get_x");
	AGS_Character_set_x = (_AGSCHARACTER_SET_X)engine->GetScriptFunctionAddress("Character::set_x");
	AGS_Character_get_y = (_AGS_CHARACTER_GET_Y)engine->GetScriptFunctionAddress("Character::get_y");
	AGS_Character_set_y = (_AGSCHARACTER_SET_Y)engine->GetScriptFunctionAddress("Character::set_y");
	AGS_Character_get_z = (_AGS_CHARACTER_GET_Z)engine->GetScriptFunctionAddress("Character::get_z");
	AGS_Character_set_z = (_AGSCHARACTER_SET_Z)engine->GetScriptFunctionAddress("Character::set_z");
};

// Global function Lua wrappers
static int luags_Display(lua_State *L) {
	aux_formatstring(L, 1);
	AGS_Display(luaL_checkstring(L,1));
	return 0;
};
static int luags_DisplayAt(lua_State *L) {
	aux_formatstring(L, 4);
	AGS_DisplayAt((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), luaL_checkstring(L,4));
	return 0;
};
static int luags_DisplayAtY(lua_State *L) {
	AGS_DisplayAtY((int)luaL_checkint(L,1), luaL_checkstring(L,2));
	return 0;
};
static int luags_DisplayMessage(lua_State *L) {
	AGS_DisplayMessage((int)luaL_checkint(L,1));
	return 0;
};
static int luags_DisplayMessageAtY(lua_State *L) {
	AGS_DisplayMessageAtY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_DisplayTopBar(lua_State *L) {
	aux_formatstring(L, 5);
	AGS_DisplayTopBar((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), luaL_checkstring(L,4), luaL_checkstring(L,5));
	return 0;
};
static int luags_DisplayMessageBar(lua_State *L) {
	AGS_DisplayMessageBar((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), luaL_checkstring(L,4), (int)luaL_checkint(L,5));
	return 0;
};
static int luags_ResetRoom(lua_State *L) {
	AGS_ResetRoom((int)luaL_checkint(L,1));
	return 0;
};
static int luags_HasPlayerBeenInRoom(lua_State *L) {
	lua_pushinteger(L, AGS_HasPlayerBeenInRoom((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_ProcessClick(lua_State *L) {
	AGS_ProcessClick((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), /* AGS_CursorMode: */ luaL_checkint(L,3));
	return 0;
};
static int luags_AbortGame(lua_State *L) {
	aux_formatstring(L, 1);
	AGS_AbortGame(luaL_checkstring(L,1));
	return 0;
};
static int luags_QuitGame(lua_State *L) {
	AGS_QuitGame((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetGameSpeed(lua_State *L) {
	AGS_SetGameSpeed((int)luaL_checkint(L,1));
	return 0;
};
static int luags_GetGameSpeed(lua_State *L) {
	lua_pushinteger(L, AGS_GetGameSpeed());
	return 1;
};
static int luags_SetGameOption(lua_State *L) {
	lua_pushinteger(L, AGS_SetGameOption((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GetGameOption(lua_State *L) {
	lua_pushinteger(L, AGS_GetGameOption((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_Debug(lua_State *L) {
	AGS_Debug((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_CallRoomScript(lua_State *L) {
	AGS_CallRoomScript((int)luaL_checkint(L,1));
	return 0;
};
static int luags_RunAGSGame(lua_State *L) {
	lua_pushinteger(L, AGS_RunAGSGame(luaL_checkstring(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3)));
	return 1;
};
static int luags_GetTranslation(lua_State *L) {
	lua_pushstring(L, AGS_GetTranslation(luaL_checkstring(L,1)));
	return 1;
};
static int luags_IsTranslationAvailable(lua_State *L) {
	lua_pushinteger(L, AGS_IsTranslationAvailable());
	return 1;
};
static int luags_RestoreGameDialog(lua_State *L) {
	AGS_RestoreGameDialog();
	return 0;
};
static int luags_SaveGameDialog(lua_State *L) {
	AGS_SaveGameDialog();
	return 0;
};
static int luags_RestartGame(lua_State *L) {
	AGS_RestartGame();
	return 0;
};
static int luags_SaveGameSlot(lua_State *L) {
	AGS_SaveGameSlot((int)luaL_checkint(L,1), luaL_checkstring(L,2));
	return 0;
};
static int luags_RestoreGameSlot(lua_State *L) {
	AGS_RestoreGameSlot((int)luaL_checkint(L,1));
	return 0;
};
static int luags_DeleteSaveSlot(lua_State *L) {
	AGS_DeleteSaveSlot((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetRestartPoint(lua_State *L) {
	AGS_SetRestartPoint();
	return 0;
};
static int luags_GetLocationType(lua_State *L) {
	lua_pushinteger(L, /* AGS_LocationType: */ AGS_GetLocationType((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GetWalkableAreaAt(lua_State *L) {
	lua_pushinteger(L, AGS_GetWalkableAreaAt((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GetScalingAt(lua_State *L) {
	lua_pushinteger(L, AGS_GetScalingAt((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GetRoomProperty(lua_State *L) {
	lua_pushinteger(L, AGS_GetRoomProperty(luaL_checkstring(L,1)));
	return 1;
};
static int luags_SetViewport(lua_State *L) {
	AGS_SetViewport((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_ReleaseViewport(lua_State *L) {
	AGS_ReleaseViewport();
	return 0;
};
static int luags_GetViewportX(lua_State *L) {
	lua_pushinteger(L, AGS_GetViewportX());
	return 1;
};
static int luags_GetViewportY(lua_State *L) {
	lua_pushinteger(L, AGS_GetViewportY());
	return 1;
};
static int luags_IsGamePaused(lua_State *L) {
	lua_pushinteger(L, AGS_IsGamePaused());
	return 1;
};
static int luags_IsChannelPlaying(lua_State *L) {
	lua_pushinteger(L, AGS_IsChannelPlaying((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_IsSoundPlaying(lua_State *L) {
	lua_pushinteger(L, AGS_IsSoundPlaying());
	return 1;
};
static int luags_IsMusicPlaying(lua_State *L) {
	lua_pushinteger(L, AGS_IsMusicPlaying());
	return 1;
};
static int luags_GetMIDIPosition(lua_State *L) {
	lua_pushinteger(L, AGS_GetMIDIPosition());
	return 1;
};
static int luags_SeekMIDIPosition(lua_State *L) {
	AGS_SeekMIDIPosition((int)luaL_checkint(L,1));
	return 0;
};
static int luags_GetMP3PosMillis(lua_State *L) {
	lua_pushinteger(L, AGS_GetMP3PosMillis());
	return 1;
};
static int luags_SeekMP3PosMillis(lua_State *L) {
	AGS_SeekMP3PosMillis((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetChannelVolume(lua_State *L) {
	AGS_SetChannelVolume((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_StopChannel(lua_State *L) {
	AGS_StopChannel((int)luaL_checkint(L,1));
	return 0;
};
static int luags_StopMusic(lua_State *L) {
	AGS_StopMusic();
	return 0;
};
static int luags_GetGraphicalVariable(lua_State *L) {
	lua_pushinteger(L, AGS_GetGraphicalVariable(luaL_checkstring(L,1)));
	return 1;
};
static int luags_SetGraphicalVariable(lua_State *L) {
	AGS_SetGraphicalVariable(luaL_checkstring(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_DisableInterface(lua_State *L) {
	AGS_DisableInterface();
	return 0;
};
static int luags_EnableInterface(lua_State *L) {
	AGS_EnableInterface();
	return 0;
};
static int luags_IsInterfaceEnabled(lua_State *L) {
	lua_pushinteger(L, AGS_IsInterfaceEnabled());
	return 1;
};
static int luags_Said(lua_State *L) {
	lua_pushinteger(L, AGS_Said(luaL_checkstring(L,1)));
	return 1;
};
static int luags_GetTextWidth(lua_State *L) {
	lua_pushinteger(L, AGS_GetTextWidth(luaL_checkstring(L,1), /* AGS_FontType: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_GetTextHeight(lua_State *L) {
	lua_pushinteger(L, AGS_GetTextHeight(luaL_checkstring(L,1), /* AGS_FontType: */ luaL_checkint(L,2), (int)luaL_checkint(L,3)));
	return 1;
};
static int luags_GiveScore(lua_State *L) {
	AGS_GiveScore((int)luaL_checkint(L,1));
	return 0;
};
static int luags_UpdateInventory(lua_State *L) {
	AGS_UpdateInventory();
	return 0;
};
static int luags_StopDialog(lua_State *L) {
	AGS_StopDialog();
	return 0;
};
static int luags_AreThingsOverlapping(lua_State *L) {
	lua_pushinteger(L, AGS_AreThingsOverlapping((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_SetVoiceMode(lua_State *L) {
	AGS_SetVoiceMode(/* AGS_eVoiceMode: */ luaL_checkint(L,1));
	return 0;
};
static int luags_SetSkipSpeech(lua_State *L) {
	AGS_SetSkipSpeech((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetSpeechStyle(lua_State *L) {
	AGS_SetSpeechStyle(/* AGS_eSpeechStyle: */ luaL_checkint(L,1));
	return 0;
};
static int luags_SetTimer(lua_State *L) {
	AGS_SetTimer((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_IsTimerExpired(lua_State *L) {
	lua_pushboolean(L, AGS_IsTimerExpired((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_SetMultitaskingMode(lua_State *L) {
	AGS_SetMultitaskingMode((int)luaL_checkint(L,1));
	return 0;
};
static int luags_FloatToInt(lua_State *L) {
	lua_pushinteger(L, AGS_FloatToInt((float)luaL_checknumber(L,1), (int)luaL_optint(L,2,AGS_eRoundDown)));
	return 1;
};
static int luags_IntToFloat(lua_State *L) {
	lua_pushnumber(L, AGS_IntToFloat((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_FadeIn(lua_State *L) {
	AGS_FadeIn((int)luaL_checkint(L,1));
	return 0;
};
static int luags_FadeOut(lua_State *L) {
	AGS_FadeOut((int)luaL_checkint(L,1));
	return 0;
};
static int luags_CyclePalette(lua_State *L) {
	AGS_CyclePalette((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_SetPalRGB(lua_State *L) {
	AGS_SetPalRGB((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4));
	return 0;
};
static int luags_UpdatePalette(lua_State *L) {
	AGS_UpdatePalette();
	return 0;
};
static int luags_TintScreen(lua_State *L) {
	AGS_TintScreen((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_SetAmbientTint(lua_State *L) {
	AGS_SetAmbientTint((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5));
	return 0;
};
static int luags_Random(lua_State *L) {
	lua_pushinteger(L, AGS_Random((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_SetBackgroundFrame(lua_State *L) {
	AGS_SetBackgroundFrame((int)luaL_checkint(L,1));
	return 0;
};
static int luags_GetBackgroundFrame(lua_State *L) {
	lua_pushinteger(L, AGS_GetBackgroundFrame());
	return 1;
};
static int luags_ShakeScreen(lua_State *L) {
	AGS_ShakeScreen((int)luaL_checkint(L,1));
	return 0;
};
static int luags_ShakeScreenBackground(lua_State *L) {
	AGS_ShakeScreenBackground((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_SetScreenTransition(lua_State *L) {
	AGS_SetScreenTransition(/* AGS_TransitionStyle: */ luaL_checkint(L,1));
	return 0;
};
static int luags_SetNextScreenTransition(lua_State *L) {
	AGS_SetNextScreenTransition(/* AGS_TransitionStyle: */ luaL_checkint(L,1));
	return 0;
};
static int luags_SetFadeColor(lua_State *L) {
	AGS_SetFadeColor((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_IsInteractionAvailable(lua_State *L) {
	lua_pushinteger(L, AGS_IsInteractionAvailable((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), /* AGS_CursorMode: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_RemoveWalkableArea(lua_State *L) {
	AGS_RemoveWalkableArea((int)luaL_checkint(L,1));
	return 0;
};
static int luags_RestoreWalkableArea(lua_State *L) {
	AGS_RestoreWalkableArea((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetAreaScaling(lua_State *L) {
	AGS_SetAreaScaling((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_DisableGroundLevelAreas(lua_State *L) {
	AGS_DisableGroundLevelAreas((int)luaL_checkint(L,1));
	return 0;
};
static int luags_EnableGroundLevelAreas(lua_State *L) {
	AGS_EnableGroundLevelAreas();
	return 0;
};
static int luags_SetWalkBehindBase(lua_State *L) {
	AGS_SetWalkBehindBase((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_CDAudio(lua_State *L) {
	lua_pushinteger(L, AGS_CDAudio(/* AGS_eCDAudioFunction: */ luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_PlayFlic(lua_State *L) {
	AGS_PlayFlic((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_PlayVideo(lua_State *L) {
	AGS_PlayVideo(luaL_checkstring(L,1), /* AGS_VideoSkipStyle: */ luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_PlayMusic(lua_State *L) {
	AGS_PlayMusic((int)luaL_checkint(L,1));
	return 0;
};
static int luags_PlayMusicQueued(lua_State *L) {
	AGS_PlayMusicQueued((int)luaL_checkint(L,1));
	return 0;
};
static int luags_PlaySilentMIDI(lua_State *L) {
	AGS_PlaySilentMIDI((int)luaL_checkint(L,1));
	return 0;
};
static int luags_PlayMP3File(lua_State *L) {
	AGS_PlayMP3File(luaL_checkstring(L,1));
	return 0;
};
static int luags_PlaySound(lua_State *L) {
	lua_pushinteger(L, AGS_PlaySound((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_PlaySoundEx(lua_State *L) {
	AGS_PlaySoundEx((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_PlayAmbientSound(lua_State *L) {
	AGS_PlayAmbientSound((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5));
	return 0;
};
static int luags_StopAmbientSound(lua_State *L) {
	AGS_StopAmbientSound((int)luaL_checkint(L,1));
	return 0;
};
static int luags_IsVoxAvailable(lua_State *L) {
	lua_pushinteger(L, AGS_IsVoxAvailable());
	return 1;
};
static int luags_IsMusicVoxAvailable(lua_State *L) {
	lua_pushinteger(L, AGS_IsMusicVoxAvailable());
	return 1;
};
static int luags_GetCurrentMusic(lua_State *L) {
	lua_pushinteger(L, AGS_GetCurrentMusic());
	return 1;
};
static int luags_SetMusicRepeat(lua_State *L) {
	AGS_SetMusicRepeat((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetMusicVolume(lua_State *L) {
	AGS_SetMusicVolume((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetSoundVolume(lua_State *L) {
	AGS_SetSoundVolume((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetSpeechVolume(lua_State *L) {
	AGS_SetSpeechVolume((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetMusicMasterVolume(lua_State *L) {
	AGS_SetMusicMasterVolume((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SetDigitalMasterVolume(lua_State *L) {
	AGS_SetDigitalMasterVolume((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SeekMODPattern(lua_State *L) {
	AGS_SeekMODPattern((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SaveScreenShot(lua_State *L) {
	lua_pushinteger(L, AGS_SaveScreenShot(luaL_checkstring(L,1)));
	return 1;
};
static int luags_PauseGame(lua_State *L) {
	AGS_PauseGame();
	return 0;
};
static int luags_UnPauseGame(lua_State *L) {
	AGS_UnPauseGame();
	return 0;
};
static int luags_Wait(lua_State *L) {
	AGS_Wait((int)luaL_checkint(L,1));
	return 0;
};
static int luags_WaitKey(lua_State *L) {
	lua_pushinteger(L, AGS_WaitKey((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_WaitMouseKey(lua_State *L) {
	lua_pushinteger(L, AGS_WaitMouseKey((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_IsKeyPressed(lua_State *L) {
	lua_pushboolean(L, AGS_IsKeyPressed(/* AGS_eKeyCode: */ luaL_checkint(L,1)));
	return 1;
};
static int luags_SetGlobalInt(lua_State *L) {
	AGS_SetGlobalInt((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_GetGlobalInt(lua_State *L) {
	lua_pushinteger(L, AGS_GetGlobalInt((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_FlipScreen(lua_State *L) {
	AGS_FlipScreen((int)luaL_checkint(L,1));
	return 0;
};
static int luags_SkipUntilCharacterStops(lua_State *L) {
	AGS_SkipUntilCharacterStops(/* AGS_CHARID: */ luaL_checkint(L,1));
	return 0;
};
static int luags_StartCutscene(lua_State *L) {
	AGS_StartCutscene(/* AGS_CutsceneSkipType: */ luaL_checkint(L,1));
	return 0;
};
static int luags_EndCutscene(lua_State *L) {
	lua_pushinteger(L, AGS_EndCutscene());
	return 1;
};
static int luags_ClaimEvent(lua_State *L) {
	AGS_ClaimEvent();
	return 0;
};
static int luags_SetTextWindowGUI(lua_State *L) {
	AGS_SetTextWindowGUI((int)luaL_checkint(L,1));
	return 0;
};
static int luags_FindGUIID(lua_State *L) {
	lua_pushinteger(L, AGS_FindGUIID(luaL_checkstring(L,1)));
	return 1;
};

static const luaL_Reg luags_lib[] = {
	{"Display",luags_Display},
	{"DisplayAt",luags_DisplayAt},
	{"DisplayAtY",luags_DisplayAtY},
	{"DisplayMessage",luags_DisplayMessage},
	{"DisplayMessageAtY",luags_DisplayMessageAtY},
	{"DisplayTopBar",luags_DisplayTopBar},
	{"DisplayMessageBar",luags_DisplayMessageBar},
	{"ResetRoom",luags_ResetRoom},
	{"HasPlayerBeenInRoom",luags_HasPlayerBeenInRoom},
	{"ProcessClick",luags_ProcessClick},
	{"AbortGame",luags_AbortGame},
	{"QuitGame",luags_QuitGame},
	{"SetGameSpeed",luags_SetGameSpeed},
	{"GetGameSpeed",luags_GetGameSpeed},
	{"SetGameOption",luags_SetGameOption},
	{"GetGameOption",luags_GetGameOption},
	{"Debug",luags_Debug},
	{"CallRoomScript",luags_CallRoomScript},
	{"RunAGSGame",luags_RunAGSGame},
	{"GetTranslation",luags_GetTranslation},
	{"IsTranslationAvailable",luags_IsTranslationAvailable},
	{"RestoreGameDialog",luags_RestoreGameDialog},
	{"SaveGameDialog",luags_SaveGameDialog},
	{"RestartGame",luags_RestartGame},
	{"SaveGameSlot",luags_SaveGameSlot},
	{"RestoreGameSlot",luags_RestoreGameSlot},
	{"DeleteSaveSlot",luags_DeleteSaveSlot},
	{"SetRestartPoint",luags_SetRestartPoint},
	{"GetLocationType",luags_GetLocationType},
	{"GetWalkableAreaAt",luags_GetWalkableAreaAt},
	{"GetScalingAt",luags_GetScalingAt},
	{"GetRoomProperty",luags_GetRoomProperty},
	{"SetViewport",luags_SetViewport},
	{"ReleaseViewport",luags_ReleaseViewport},
	{"GetViewportX",luags_GetViewportX},
	{"GetViewportY",luags_GetViewportY},
	{"IsGamePaused",luags_IsGamePaused},
	{"IsChannelPlaying",luags_IsChannelPlaying},
	{"IsSoundPlaying",luags_IsSoundPlaying},
	{"IsMusicPlaying",luags_IsMusicPlaying},
	{"GetMIDIPosition",luags_GetMIDIPosition},
	{"SeekMIDIPosition",luags_SeekMIDIPosition},
	{"GetMP3PosMillis",luags_GetMP3PosMillis},
	{"SeekMP3PosMillis",luags_SeekMP3PosMillis},
	{"SetChannelVolume",luags_SetChannelVolume},
	{"StopChannel",luags_StopChannel},
	{"StopMusic",luags_StopMusic},
	{"GetGraphicalVariable",luags_GetGraphicalVariable},
	{"SetGraphicalVariable",luags_SetGraphicalVariable},
	{"DisableInterface",luags_DisableInterface},
	{"EnableInterface",luags_EnableInterface},
	{"IsInterfaceEnabled",luags_IsInterfaceEnabled},
	{"Said",luags_Said},
	{"GetTextWidth",luags_GetTextWidth},
	{"GetTextHeight",luags_GetTextHeight},
	{"GiveScore",luags_GiveScore},
	{"UpdateInventory",luags_UpdateInventory},
	{"StopDialog",luags_StopDialog},
	{"AreThingsOverlapping",luags_AreThingsOverlapping},
	{"SetVoiceMode",luags_SetVoiceMode},
	{"SetSkipSpeech",luags_SetSkipSpeech},
	{"SetSpeechStyle",luags_SetSpeechStyle},
	{"SetTimer",luags_SetTimer},
	{"IsTimerExpired",luags_IsTimerExpired},
	{"SetMultitaskingMode",luags_SetMultitaskingMode},
	{"FloatToInt",luags_FloatToInt},
	{"IntToFloat",luags_IntToFloat},
	{"FadeIn",luags_FadeIn},
	{"FadeOut",luags_FadeOut},
	{"CyclePalette",luags_CyclePalette},
	{"SetPalRGB",luags_SetPalRGB},
	{"UpdatePalette",luags_UpdatePalette},
	{"TintScreen",luags_TintScreen},
	{"SetAmbientTint",luags_SetAmbientTint},
	{"Random",luags_Random},
	{"SetBackgroundFrame",luags_SetBackgroundFrame},
	{"GetBackgroundFrame",luags_GetBackgroundFrame},
	{"ShakeScreen",luags_ShakeScreen},
	{"ShakeScreenBackground",luags_ShakeScreenBackground},
	{"SetScreenTransition",luags_SetScreenTransition},
	{"SetNextScreenTransition",luags_SetNextScreenTransition},
	{"SetFadeColor",luags_SetFadeColor},
	{"IsInteractionAvailable",luags_IsInteractionAvailable},
	{"RemoveWalkableArea",luags_RemoveWalkableArea},
	{"RestoreWalkableArea",luags_RestoreWalkableArea},
	{"SetAreaScaling",luags_SetAreaScaling},
	{"DisableGroundLevelAreas",luags_DisableGroundLevelAreas},
	{"EnableGroundLevelAreas",luags_EnableGroundLevelAreas},
	{"SetWalkBehindBase",luags_SetWalkBehindBase},
	{"CDAudio",luags_CDAudio},
	{"PlayFlic",luags_PlayFlic},
	{"PlayVideo",luags_PlayVideo},
	{"PlayMusic",luags_PlayMusic},
	{"PlayMusicQueued",luags_PlayMusicQueued},
	{"PlaySilentMIDI",luags_PlaySilentMIDI},
	{"PlayMP3File",luags_PlayMP3File},
	{"PlaySound",luags_PlaySound},
	{"PlaySoundEx",luags_PlaySoundEx},
	{"PlayAmbientSound",luags_PlayAmbientSound},
	{"StopAmbientSound",luags_StopAmbientSound},
	{"IsVoxAvailable",luags_IsVoxAvailable},
	{"IsMusicVoxAvailable",luags_IsMusicVoxAvailable},
	{"GetCurrentMusic",luags_GetCurrentMusic},
	{"SetMusicRepeat",luags_SetMusicRepeat},
	{"SetMusicVolume",luags_SetMusicVolume},
	{"SetSoundVolume",luags_SetSoundVolume},
	{"SetSpeechVolume",luags_SetSpeechVolume},
	{"SetMusicMasterVolume",luags_SetMusicMasterVolume},
	{"SetDigitalMasterVolume",luags_SetDigitalMasterVolume},
	{"SeekMODPattern",luags_SeekMODPattern},
	{"SaveScreenShot",luags_SaveScreenShot},
	{"PauseGame",luags_PauseGame},
	{"UnPauseGame",luags_UnPauseGame},
	{"Wait",luags_Wait},
	{"WaitKey",luags_WaitKey},
	{"WaitMouseKey",luags_WaitMouseKey},
	{"IsKeyPressed",luags_IsKeyPressed},
	{"SetGlobalInt",luags_SetGlobalInt},
	{"GetGlobalInt",luags_GetGlobalInt},
	{"FlipScreen",luags_FlipScreen},
	{"SkipUntilCharacterStops",luags_SkipUntilCharacterStops},
	{"StartCutscene",luags_StartCutscene},
	{"EndCutscene",luags_EndCutscene},
	{"ClaimEvent",luags_ClaimEvent},
	{"SetTextWindowGUI",luags_SetTextWindowGUI},
	{"FindGUIID",luags_FindGUIID},
	{NULL,NULL}
};

// 'ViewFrame' Lua wrappers
static int luags_ViewFrame_Flipped(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_ViewFrame_get_Flipped(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ViewFrame_Frame(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_Frame(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ViewFrame_Graphic(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_Graphic(self));
		return 1;
	}
	else {
		AGS_ViewFrame_set_Graphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ViewFrame_Loop(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_Loop(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ViewFrame_Sound(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_Sound(self));
		return 1;
	}
	else {
		AGS_ViewFrame_set_Sound(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ViewFrame_Speed(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_Speed(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ViewFrame_View(lua_State *L) {
	AGS_ViewFrame* self = luags_checkViewFrame(1, VIEWFRAME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ViewFrame_get_View(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_ViewFrame_lib[] = {
	{"Flipped",luags_ViewFrame_Flipped},
	{"Frame",luags_ViewFrame_Frame},
	{"Graphic",luags_ViewFrame_Graphic},
	{"Loop",luags_ViewFrame_Loop},
	{"Sound",luags_ViewFrame_Sound},
	{"Speed",luags_ViewFrame_Speed},
	{"View",luags_ViewFrame_View},
	{NULL,NULL}
};

// 'DrawingSurface' Lua wrappers
static int luags_DrawingSurface_Clear(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_Clear(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_DrawingSurface_CreateCopy(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	luags_pushDrawingSurface(L, AGS_DrawingSurface_CreateCopy(self));
	return 1;
};
static int luags_DrawingSurface_DrawCircle(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawCircle(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* _ERROR_: */ luaL_checkint(L,4));
	return 0;
};
static int luags_DrawingSurface_DrawImage(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawImage(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_optint(L,4,0), (int)luaL_optint(L,5,AGS_SCR_NO_VALUE), (int)luaL_optint(L,6,AGS_SCR_NO_VALUE), /* _ERROR_: */ luaL_checkint(L,7));
	return 0;
};
static int luags_DrawingSurface_DrawLine(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawLine(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_optint(L,5,1), /* _ERROR_: */ luaL_checkint(L,6));
	return 0;
};
static int luags_DrawingSurface_DrawMessageWrapped(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawMessageWrapped(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* AGS_FontType: */ luaL_checkint(L,4), (int)luaL_checkint(L,5), /* _ERROR_: */ luaL_checkint(L,6));
	return 0;
};
static int luags_DrawingSurface_DrawPixel(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawPixel(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_DrawingSurface_DrawRectangle(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawRectangle(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_DrawingSurface_DrawString(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	aux_formatstring(L, 4);
	AGS_DrawingSurface_DrawString(self, (int)luaL_checkint(L,2), /* AGS_FontType: */ luaL_checkint(L,3), luaL_checkstring(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_DrawingSurface_DrawStringWrapped(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawStringWrapped(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* AGS_FontType: */ luaL_checkint(L,4), /* AGS_Alignment: */ luaL_checkint(L,5), luaL_checkstring(L,6), /* _ERROR_: */ luaL_checkint(L,7));
	return 0;
};
static int luags_DrawingSurface_DrawSurface(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawSurface(self, (int)luaL_optint(L,2,0), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_DrawingSurface_DrawTriangle(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_DrawTriangle(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5), (int)luaL_checkint(L,6), /* _ERROR_: */ luaL_checkint(L,7));
	return 0;
};
static int luags_DrawingSurface_GetPixel(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	lua_pushinteger(L, AGS_DrawingSurface_GetPixel(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_DrawingSurface_Release(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	AGS_DrawingSurface_Release(self);
	return 0;
};
static int luags_DrawingSurface_DrawingColor(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DrawingSurface_get_DrawingColor(self));
		return 1;
	}
	else {
		AGS_DrawingSurface_set_DrawingColor(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DrawingSurface_Height(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DrawingSurface_get_Height(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DrawingSurface_UseHighResCoordinates(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_DrawingSurface_get_UseHighResCoordinates(self));
		return 1;
	}
	else {
		AGS_DrawingSurface_set_UseHighResCoordinates(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DrawingSurface_Width(lua_State *L) {
	AGS_DrawingSurface* self = luags_checkDrawingSurface(1, DRAWINGSURFACE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DrawingSurface_get_Width(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_DrawingSurface_lib[] = {
	{"Clear",luags_DrawingSurface_Clear},
	{"CreateCopy",luags_DrawingSurface_CreateCopy},
	{"DrawCircle",luags_DrawingSurface_DrawCircle},
	{"DrawImage",luags_DrawingSurface_DrawImage},
	{"DrawLine",luags_DrawingSurface_DrawLine},
	{"DrawMessageWrapped",luags_DrawingSurface_DrawMessageWrapped},
	{"DrawPixel",luags_DrawingSurface_DrawPixel},
	{"DrawRectangle",luags_DrawingSurface_DrawRectangle},
	{"DrawString",luags_DrawingSurface_DrawString},
	{"DrawStringWrapped",luags_DrawingSurface_DrawStringWrapped},
	{"DrawSurface",luags_DrawingSurface_DrawSurface},
	{"DrawTriangle",luags_DrawingSurface_DrawTriangle},
	{"GetPixel",luags_DrawingSurface_GetPixel},
	{"Release",luags_DrawingSurface_Release},
	{"DrawingColor",luags_DrawingSurface_DrawingColor},
	{"Height",luags_DrawingSurface_Height},
	{"UseHighResCoordinates",luags_DrawingSurface_UseHighResCoordinates},
	{"Width",luags_DrawingSurface_Width},
	{NULL,NULL}
};

// 'Room' Lua wrappers
static int luags_Room_GetTextProperty(lua_State *L) {
	lua_pushstring(L, AGS_Room_GetTextProperty(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Room_GetDrawingSurfaceForBackground(lua_State *L) {
	luags_pushDrawingSurface(L, AGS_Room_GetDrawingSurfaceForBackground((int)luaL_optint(L,1,AGS_SCR_NO_VALUE)));
	return 1;
};
static int luags_Room_BottomEdge(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_BottomEdge());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_ColorDepth(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_ColorDepth());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_Height(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_Height());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_LeftEdge(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_LeftEdge());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_Messages(lua_State *L) {
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Room_geti_Messages(luaL_checkint(L,1)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_MusicOnLoad(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_MusicOnLoad());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_ObjectCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_ObjectCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_RightEdge(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_RightEdge());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_TopEdge(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_TopEdge());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Room_Width(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Room_get_Width());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_Room_lib[] = {
	{"GetTextProperty",luags_Room_GetTextProperty},
	{"GetDrawingSurfaceForBackground",luags_Room_GetDrawingSurfaceForBackground},
	{"BottomEdge",luags_Room_BottomEdge},
	{"ColorDepth",luags_Room_ColorDepth},
	{"Height",luags_Room_Height},
	{"LeftEdge",luags_Room_LeftEdge},
	{"Messages",luags_Room_Messages},
	{"MusicOnLoad",luags_Room_MusicOnLoad},
	{"ObjectCount",luags_Room_ObjectCount},
	{"RightEdge",luags_Room_RightEdge},
	{"TopEdge",luags_Room_TopEdge},
	{"Width",luags_Room_Width},
	{NULL,NULL}
};

// 'Game' Lua wrappers
static int luags_Game_ChangeTranslation(lua_State *L) {
	lua_pushboolean(L, AGS_Game_ChangeTranslation(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Game_DoOnceOnly(lua_State *L) {
	lua_pushboolean(L, AGS_Game_DoOnceOnly(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Game_GetColorFromRGB(lua_State *L) {
	lua_pushinteger(L, AGS_Game_GetColorFromRGB((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3)));
	return 1;
};
static int luags_Game_GetFrameCountForLoop(lua_State *L) {
	lua_pushinteger(L, AGS_Game_GetFrameCountForLoop((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Game_GetLocationName(lua_State *L) {
	lua_pushstring(L, AGS_Game_GetLocationName((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Game_GetLoopCountForView(lua_State *L) {
	lua_pushinteger(L, AGS_Game_GetLoopCountForView((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_Game_GetMODPattern(lua_State *L) {
	lua_pushinteger(L, AGS_Game_GetMODPattern());
	return 1;
};
static int luags_Game_GetRunNextSettingForLoop(lua_State *L) {
	lua_pushboolean(L, AGS_Game_GetRunNextSettingForLoop((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Game_GetSaveSlotDescription(lua_State *L) {
	lua_pushstring(L, AGS_Game_GetSaveSlotDescription((int)luaL_checkint(L,1)));
	return 1;
};
static int luags_Game_GetViewFrame(lua_State *L) {
	luags_pushViewFrame(L, AGS_Game_GetViewFrame((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3)));
	return 1;
};
static int luags_Game_InputBox(lua_State *L) {
	lua_pushstring(L, AGS_Game_InputBox(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Game_SetSaveGameDirectory(lua_State *L) {
	lua_pushboolean(L, AGS_Game_SetSaveGameDirectory(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Game_StopSound(lua_State *L) {
	AGS_Game_StopSound(lua_toboolean(L,1));
	return 0;
};
static int luags_Game_CharacterCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_CharacterCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_DialogCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_DialogCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_FileName(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushstring(L, AGS_Game_get_FileName());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_FontCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_FontCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_GlobalMessages(lua_State *L) {
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Game_geti_GlobalMessages(luaL_checkint(L,1)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_GlobalStrings(lua_State *L) {
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Game_geti_GlobalStrings(luaL_checkint(L,1)));
		return 1;
	}
	else {
		AGS_Game_seti_GlobalStrings(luaL_checkint(L,2), luaL_checkstring(L,1));
		return 0;
	}
};
static int luags_Game_GUICount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_GUICount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_InSkippableCutscene(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_Game_get_InSkippableCutscene());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_InventoryItemCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_InventoryItemCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_MinimumTextDisplayTimeMs(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_MinimumTextDisplayTimeMs());
		return 1;
	}
	else {
		AGS_Game_set_MinimumTextDisplayTimeMs((int)luaL_checkint(L,1));
		return 0;
	}
};
static int luags_Game_MouseCursorCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_MouseCursorCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_Name(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushstring(L, AGS_Game_get_Name());
		return 1;
	}
	else {
		AGS_Game_set_Name(luaL_checkstring(L,1));
		return 0;
	}
};
static int luags_Game_NormalFont(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_Game_get_NormalFont());
		return 1;
	}
	else {
		AGS_Game_set_NormalFont(/* AGS_FontType: */ luaL_checkint(L,1));
		return 0;
	}
};
static int luags_Game_SkippingCutscene(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_Game_get_SkippingCutscene());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_SpeechFont(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_Game_get_SpeechFont());
		return 1;
	}
	else {
		AGS_Game_set_SpeechFont(/* AGS_FontType: */ luaL_checkint(L,1));
		return 0;
	}
};
static int luags_Game_SpriteHeight(lua_State *L) {
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Game_geti_SpriteHeight(luaL_checkint(L,1)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_SpriteWidth(lua_State *L) {
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Game_geti_SpriteWidth(luaL_checkint(L,1)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_TextReadingSpeed(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_TextReadingSpeed());
		return 1;
	}
	else {
		AGS_Game_set_TextReadingSpeed((int)luaL_checkint(L,1));
		return 0;
	}
};
static int luags_Game_TranslationFilename(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushstring(L, AGS_Game_get_TranslationFilename());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_UseNativeCoordinates(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_Game_get_UseNativeCoordinates());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Game_ViewCount(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_Game_get_ViewCount());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_Game_lib[] = {
	{"ChangeTranslation",luags_Game_ChangeTranslation},
	{"DoOnceOnly",luags_Game_DoOnceOnly},
	{"GetColorFromRGB",luags_Game_GetColorFromRGB},
	{"GetFrameCountForLoop",luags_Game_GetFrameCountForLoop},
	{"GetLocationName",luags_Game_GetLocationName},
	{"GetLoopCountForView",luags_Game_GetLoopCountForView},
	{"GetMODPattern",luags_Game_GetMODPattern},
	{"GetRunNextSettingForLoop",luags_Game_GetRunNextSettingForLoop},
	{"GetSaveSlotDescription",luags_Game_GetSaveSlotDescription},
	{"GetViewFrame",luags_Game_GetViewFrame},
	{"InputBox",luags_Game_InputBox},
	{"SetSaveGameDirectory",luags_Game_SetSaveGameDirectory},
	{"StopSound",luags_Game_StopSound},
	{"CharacterCount",luags_Game_CharacterCount},
	{"DialogCount",luags_Game_DialogCount},
	{"FileName",luags_Game_FileName},
	{"FontCount",luags_Game_FontCount},
	{"GlobalMessages",luags_Game_GlobalMessages},
	{"GlobalStrings",luags_Game_GlobalStrings},
	{"GUICount",luags_Game_GUICount},
	{"InSkippableCutscene",luags_Game_InSkippableCutscene},
	{"InventoryItemCount",luags_Game_InventoryItemCount},
	{"MinimumTextDisplayTimeMs",luags_Game_MinimumTextDisplayTimeMs},
	{"MouseCursorCount",luags_Game_MouseCursorCount},
	{"Name",luags_Game_Name},
	{"NormalFont",luags_Game_NormalFont},
	{"SkippingCutscene",luags_Game_SkippingCutscene},
	{"SpeechFont",luags_Game_SpeechFont},
	{"SpriteHeight",luags_Game_SpriteHeight},
	{"SpriteWidth",luags_Game_SpriteWidth},
	{"TextReadingSpeed",luags_Game_TextReadingSpeed},
	{"TranslationFilename",luags_Game_TranslationFilename},
	{"UseNativeCoordinates",luags_Game_UseNativeCoordinates},
	{"ViewCount",luags_Game_ViewCount},
	{NULL,NULL}
};

// 'Parser' Lua wrappers
static int luags_Parser_FindWordID(lua_State *L) {
	lua_pushinteger(L, AGS_Parser_FindWordID(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Parser_ParseText(lua_State *L) {
	AGS_Parser_ParseText(luaL_checkstring(L,1));
	return 0;
};
static int luags_Parser_Said(lua_State *L) {
	lua_pushboolean(L, AGS_Parser_Said(luaL_checkstring(L,1)));
	return 1;
};
static int luags_Parser_SaidUnknownWord(lua_State *L) {
	lua_pushstring(L, AGS_Parser_SaidUnknownWord());
	return 1;
};

static const luaL_Reg luags_Parser_lib[] = {
	{"FindWordID",luags_Parser_FindWordID},
	{"ParseText",luags_Parser_ParseText},
	{"Said",luags_Parser_Said},
	{"SaidUnknownWord",luags_Parser_SaidUnknownWord},
	{NULL,NULL}
};

// 'Mouse' Lua wrappers
static int luags_Mouse_ChangeModeGraphic(lua_State *L) {
	AGS_Mouse_ChangeModeGraphic(/* AGS_CursorMode: */ luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_Mouse_ChangeModeHotspot(lua_State *L) {
	AGS_Mouse_ChangeModeHotspot(/* AGS_CursorMode: */ luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3));
	return 0;
};
static int luags_Mouse_ChangeModeView(lua_State *L) {
	AGS_Mouse_ChangeModeView(/* AGS_CursorMode: */ luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_Mouse_DisableMode(lua_State *L) {
	AGS_Mouse_DisableMode(/* AGS_CursorMode: */ luaL_checkint(L,1));
	return 0;
};
static int luags_Mouse_EnableMode(lua_State *L) {
	AGS_Mouse_EnableMode(/* AGS_CursorMode: */ luaL_checkint(L,1));
	return 0;
};
static int luags_Mouse_GetModeGraphic(lua_State *L) {
	lua_pushinteger(L, AGS_Mouse_GetModeGraphic(/* AGS_CursorMode: */ luaL_checkint(L,1)));
	return 1;
};
static int luags_Mouse_IsButtonDown(lua_State *L) {
	lua_pushboolean(L, AGS_Mouse_IsButtonDown(/* AGS_MouseButton: */ luaL_checkint(L,1)));
	return 1;
};
static int luags_Mouse_SaveCursorUntilItLeaves(lua_State *L) {
	AGS_Mouse_SaveCursorUntilItLeaves();
	return 0;
};
static int luags_Mouse_SelectNextMode(lua_State *L) {
	AGS_Mouse_SelectNextMode();
	return 0;
};
static int luags_Mouse_SetBounds(lua_State *L) {
	AGS_Mouse_SetBounds((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4));
	return 0;
};
static int luags_Mouse_SetPosition(lua_State *L) {
	AGS_Mouse_SetPosition((int)luaL_checkint(L,1), (int)luaL_checkint(L,2));
	return 0;
};
static int luags_Mouse_Update(lua_State *L) {
	AGS_Mouse_Update();
	return 0;
};
static int luags_Mouse_UseDefaultGraphic(lua_State *L) {
	AGS_Mouse_UseDefaultGraphic();
	return 0;
};
static int luags_Mouse_UseModeGraphic(lua_State *L) {
	AGS_Mouse_UseModeGraphic(/* AGS_CursorMode: */ luaL_checkint(L,1));
	return 0;
};
static int luags_Mouse_Mode(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, /* AGS_CursorMode: */ AGS_Mouse_get_Mode());
		return 1;
	}
	else {
		AGS_Mouse_set_Mode(/* AGS_CursorMode: */ luaL_checkint(L,1));
		return 0;
	}
};
static int luags_Mouse_Visible(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_Mouse_get_Visible());
		return 1;
	}
	else {
		AGS_Mouse_set_Visible(llh_checkboolean(L,1));
		return 0;
	}
};

static const luaL_Reg luags_Mouse_lib[] = {
	{"ChangeModeGraphic",luags_Mouse_ChangeModeGraphic},
	{"ChangeModeHotspot",luags_Mouse_ChangeModeHotspot},
	{"ChangeModeView",luags_Mouse_ChangeModeView},
	{"DisableMode",luags_Mouse_DisableMode},
	{"EnableMode",luags_Mouse_EnableMode},
	{"GetModeGraphic",luags_Mouse_GetModeGraphic},
	{"IsButtonDown",luags_Mouse_IsButtonDown},
	{"SaveCursorUntilItLeaves",luags_Mouse_SaveCursorUntilItLeaves},
	{"SelectNextMode",luags_Mouse_SelectNextMode},
	{"SetBounds",luags_Mouse_SetBounds},
	{"SetPosition",luags_Mouse_SetPosition},
	{"Update",luags_Mouse_Update},
	{"UseDefaultGraphic",luags_Mouse_UseDefaultGraphic},
	{"UseModeGraphic",luags_Mouse_UseModeGraphic},
	{"Mode",luags_Mouse_Mode},
	{"Visible",luags_Mouse_Visible},
	{NULL,NULL}
};

// 'File' Lua wrappers
static int luags_File_Delete(lua_State *L) {
	lua_pushboolean(L, AGS_File_Delete(luaL_checkstring(L,1)));
	return 1;
};
static int luags_File_Exists(lua_State *L) {
	lua_pushboolean(L, AGS_File_Exists(luaL_checkstring(L,1)));
	return 1;
};
static int luags_File_Open(lua_State *L) {
	luags_pushFile(L, AGS_File_Open(luaL_checkstring(L,1), /* AGS_FileMode: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_File_Close(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	AGS_File_Close(self);
	return 0;
};
static int luags_File_ReadInt(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	lua_pushinteger(L, AGS_File_ReadInt(self));
	return 1;
};
static int luags_File_ReadRawChar(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	lua_pushinteger(L, AGS_File_ReadRawChar(self));
	return 1;
};
static int luags_File_ReadRawInt(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	lua_pushinteger(L, AGS_File_ReadRawInt(self));
	return 1;
};
static int luags_File_ReadRawLineBack(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	lua_pushstring(L, AGS_File_ReadRawLineBack(self));
	return 1;
};
static int luags_File_ReadStringBack(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	lua_pushstring(L, AGS_File_ReadStringBack(self));
	return 1;
};
static int luags_File_WriteInt(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	AGS_File_WriteInt(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_File_WriteRawChar(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	AGS_File_WriteRawChar(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_File_WriteRawLine(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	AGS_File_WriteRawLine(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_File_WriteString(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	AGS_File_WriteString(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_File_EOF(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_File_get_EOF(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_File_Error(lua_State *L) {
	AGS_File* self = luags_checkFile(1, FILE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_File_get_Error(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_File_lib[] = {
	{"Delete",luags_File_Delete},
	{"Exists",luags_File_Exists},
	{"Open",luags_File_Open},
	{"Close",luags_File_Close},
	{"ReadInt",luags_File_ReadInt},
	{"ReadRawChar",luags_File_ReadRawChar},
	{"ReadRawInt",luags_File_ReadRawInt},
	{"ReadRawLineBack",luags_File_ReadRawLineBack},
	{"ReadStringBack",luags_File_ReadStringBack},
	{"WriteInt",luags_File_WriteInt},
	{"WriteRawChar",luags_File_WriteRawChar},
	{"WriteRawLine",luags_File_WriteRawLine},
	{"WriteString",luags_File_WriteString},
	{"EOF",luags_File_EOF},
	{"Error",luags_File_Error},
	{NULL,NULL}
};

// 'InventoryItem' Lua wrappers
static int luags_InventoryItem_GetAtScreenXY(lua_State *L) {
	luags_pushInventoryItem(L, AGS_InventoryItem_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_InventoryItem_GetProperty(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	lua_pushinteger(L, AGS_InventoryItem_GetProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_InventoryItem_GetTextProperty(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	lua_pushstring(L, AGS_InventoryItem_GetTextProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_InventoryItem_IsInteractionAvailable(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	lua_pushinteger(L, AGS_InventoryItem_IsInteractionAvailable(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_InventoryItem_RunInteraction(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	AGS_InventoryItem_RunInteraction(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_InventoryItem_CursorGraphic(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InventoryItem_get_CursorGraphic(self));
		return 1;
	}
	else {
		AGS_InventoryItem_set_CursorGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InventoryItem_Graphic(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InventoryItem_get_Graphic(self));
		return 1;
	}
	else {
		AGS_InventoryItem_set_Graphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InventoryItem_ID(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InventoryItem_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_InventoryItem_Name(lua_State *L) {
	AGS_InventoryItem* self = luags_checkInventoryItem(1, INVENTORYITEM_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_InventoryItem_get_Name(self));
		return 1;
	}
	else {
		AGS_InventoryItem_set_Name(self, luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_InventoryItem_lib[] = {
	{"GetAtScreenXY",luags_InventoryItem_GetAtScreenXY},
	{"GetProperty",luags_InventoryItem_GetProperty},
	{"GetTextProperty",luags_InventoryItem_GetTextProperty},
	{"IsInteractionAvailable",luags_InventoryItem_IsInteractionAvailable},
	{"RunInteraction",luags_InventoryItem_RunInteraction},
	{"CursorGraphic",luags_InventoryItem_CursorGraphic},
	{"Graphic",luags_InventoryItem_Graphic},
	{"ID",luags_InventoryItem_ID},
	{"Name",luags_InventoryItem_Name},
	{NULL,NULL}
};

// 'Overlay' Lua wrappers
static int luags_Overlay_CreateGraphical(lua_State *L) {
	luags_pushOverlay(L, AGS_Overlay_CreateGraphical((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), llh_checkboolean(L,4)));
	return 1;
};
static int luags_Overlay_CreateTextual(lua_State *L) {
	aux_formatstring(L, 6);
	luags_pushOverlay(L, AGS_Overlay_CreateTextual((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* AGS_FontType: */ luaL_checkint(L,4), (int)luaL_checkint(L,5), luaL_checkstring(L,6)));
	return 1;
};
static int luags_Overlay_SetText(lua_State *L) {
	AGS_Overlay* self = luags_checkOverlay(1, OVERLAY_UV_META);
	aux_formatstring(L, 4);
	AGS_Overlay_SetText(self, /* AGS_FontType: */ luaL_checkint(L,2), (int)luaL_checkint(L,3), luaL_checkstring(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_Overlay_Remove(lua_State *L) {
	AGS_Overlay* self = luags_checkOverlay(1, OVERLAY_UV_META);
	AGS_Overlay_Remove(self);
	return 0;
};
static int luags_Overlay_Valid(lua_State *L) {
	AGS_Overlay* self = luags_checkOverlay(1, OVERLAY_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Overlay_get_Valid(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Overlay_X(lua_State *L) {
	AGS_Overlay* self = luags_checkOverlay(1, OVERLAY_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Overlay_get_X(self));
		return 1;
	}
	else {
		AGS_Overlay_set_X(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Overlay_Y(lua_State *L) {
	AGS_Overlay* self = luags_checkOverlay(1, OVERLAY_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Overlay_get_Y(self));
		return 1;
	}
	else {
		AGS_Overlay_set_Y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Overlay_lib[] = {
	{"CreateGraphical",luags_Overlay_CreateGraphical},
	{"CreateTextual",luags_Overlay_CreateTextual},
	{"SetText",luags_Overlay_SetText},
	{"Remove",luags_Overlay_Remove},
	{"Valid",luags_Overlay_Valid},
	{"X",luags_Overlay_X},
	{"Y",luags_Overlay_Y},
	{NULL,NULL}
};

// 'DynamicSprite' Lua wrappers
static int luags_DynamicSprite_Create(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_Create((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), lua_toboolean(L,3)));
	return 1;
};
static int luags_DynamicSprite_CreateFromBackground(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromBackground((int)luaL_optint(L,1,AGS_SCR_NO_VALUE), (int)luaL_optint(L,2,AGS_SCR_NO_VALUE), (int)luaL_optint(L,3,AGS_SCR_NO_VALUE), (int)luaL_optint(L,4,AGS_SCR_NO_VALUE), (int)luaL_optint(L,5,AGS_SCR_NO_VALUE)));
	return 1;
};
static int luags_DynamicSprite_CreateFromDrawingSurface(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromDrawingSurface(agslua_checkDrawingSurface(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5)));
	return 1;
};
static int luags_DynamicSprite_CreateFromExistingSprite(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromExistingSprite((int)luaL_checkint(L,1), lua_toboolean(L,2)));
	return 1;
};
static int luags_DynamicSprite_CreateFromFile(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromFile(luaL_checkstring(L,1)));
	return 1;
};
static int luags_DynamicSprite_CreateFromSaveGame(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromSaveGame((int)luaL_checkint(L,1), (int)luaL_checkint(L,2), (int)luaL_checkint(L,3)));
	return 1;
};
static int luags_DynamicSprite_CreateFromScreenShot(lua_State *L) {
	luags_pushDynamicSprite(L, AGS_DynamicSprite_CreateFromScreenShot((int)luaL_optint(L,1,0), (int)luaL_optint(L,2,0)));
	return 1;
};
static int luags_DynamicSprite_ChangeCanvasSize(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_ChangeCanvasSize(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_DynamicSprite_CopyTransparencyMask(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_CopyTransparencyMask(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_DynamicSprite_Crop(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Crop(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_DynamicSprite_Delete(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Delete(self);
	return 0;
};
static int luags_DynamicSprite_Flip(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Flip(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_DynamicSprite_GetDrawingSurface(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	luags_pushDrawingSurface(L, AGS_DynamicSprite_GetDrawingSurface(self));
	return 1;
};
static int luags_DynamicSprite_Resize(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Resize(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_DynamicSprite_Rotate(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Rotate(self, (int)luaL_optint(L,2,AGS_SCR_NO_VALUE), (int)luaL_optint(L,3,AGS_SCR_NO_VALUE), /* _ERROR_: */ luaL_checkint(L,4));
	return 0;
};
static int luags_DynamicSprite_SaveToFile(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	lua_pushinteger(L, AGS_DynamicSprite_SaveToFile(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_DynamicSprite_Tint(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	AGS_DynamicSprite_Tint(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5), /* _ERROR_: */ luaL_checkint(L,6));
	return 0;
};
static int luags_DynamicSprite_ColorDepth(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DynamicSprite_get_ColorDepth(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DynamicSprite_Graphic(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DynamicSprite_get_Graphic(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DynamicSprite_Height(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DynamicSprite_get_Height(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DynamicSprite_Width(lua_State *L) {
	AGS_DynamicSprite* self = luags_checkDynamicSprite(1, DYNAMICSPRITE_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DynamicSprite_get_Width(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_DynamicSprite_lib[] = {
	{"Create",luags_DynamicSprite_Create},
	{"CreateFromBackground",luags_DynamicSprite_CreateFromBackground},
	{"CreateFromDrawingSurface",luags_DynamicSprite_CreateFromDrawingSurface},
	{"CreateFromExistingSprite",luags_DynamicSprite_CreateFromExistingSprite},
	{"CreateFromFile",luags_DynamicSprite_CreateFromFile},
	{"CreateFromSaveGame",luags_DynamicSprite_CreateFromSaveGame},
	{"CreateFromScreenShot",luags_DynamicSprite_CreateFromScreenShot},
	{"ChangeCanvasSize",luags_DynamicSprite_ChangeCanvasSize},
	{"CopyTransparencyMask",luags_DynamicSprite_CopyTransparencyMask},
	{"Crop",luags_DynamicSprite_Crop},
	{"Delete",luags_DynamicSprite_Delete},
	{"Flip",luags_DynamicSprite_Flip},
	{"GetDrawingSurface",luags_DynamicSprite_GetDrawingSurface},
	{"Resize",luags_DynamicSprite_Resize},
	{"Rotate",luags_DynamicSprite_Rotate},
	{"SaveToFile",luags_DynamicSprite_SaveToFile},
	{"Tint",luags_DynamicSprite_Tint},
	{"ColorDepth",luags_DynamicSprite_ColorDepth},
	{"Graphic",luags_DynamicSprite_Graphic},
	{"Height",luags_DynamicSprite_Height},
	{"Width",luags_DynamicSprite_Width},
	{NULL,NULL}
};

// 'GUIControl' Lua wrappers
static int luags_GUIControl_BringToFront(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	AGS_GUIControl_BringToFront(self);
	return 0;
};
static int luags_GUIControl_GetAtScreenXY(lua_State *L) {
	luags_pushGUIControl(L, AGS_GUIControl_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GUIControl_SendToBack(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	AGS_GUIControl_SendToBack(self);
	return 0;
};
static int luags_GUIControl_SetPosition(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	AGS_GUIControl_SetPosition(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_GUIControl_SetSize(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	AGS_GUIControl_SetSize(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_GUIControl_AsButton(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushButton(L, AGS_GUIControl_get_AsButton(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_AsInvWindow(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushInvWindow(L, AGS_GUIControl_get_AsInvWindow(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_AsLabel(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushLabel(L, AGS_GUIControl_get_AsLabel(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_AsListBox(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushListBox(L, AGS_GUIControl_get_AsListBox(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_AsSlider(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushSlider(L, AGS_GUIControl_get_AsSlider(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_AsTextBox(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushTextBox(L, AGS_GUIControl_get_AsTextBox(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_Clickable(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_GUIControl_get_Clickable(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Clickable(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_Enabled(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_GUIControl_get_Enabled(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Enabled(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_Height(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUIControl_get_Height(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Height(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_ID(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUIControl_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_OwningGUI(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushGUI(L, AGS_GUIControl_get_OwningGUI(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUIControl_Visible(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_GUIControl_get_Visible(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Visible(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_Width(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUIControl_get_Width(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Width(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_X(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUIControl_get_X(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_X(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUIControl_Y(lua_State *L) {
	AGS_GUIControl* self = luags_checkGUIControl(1, GUICONTROL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUIControl_get_Y(self));
		return 1;
	}
	else {
		AGS_GUIControl_set_Y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_GUIControl_lib[] = {
	{"BringToFront",luags_GUIControl_BringToFront},
	{"GetAtScreenXY",luags_GUIControl_GetAtScreenXY},
	{"SendToBack",luags_GUIControl_SendToBack},
	{"SetPosition",luags_GUIControl_SetPosition},
	{"SetSize",luags_GUIControl_SetSize},
	{"AsButton",luags_GUIControl_AsButton},
	{"AsInvWindow",luags_GUIControl_AsInvWindow},
	{"AsLabel",luags_GUIControl_AsLabel},
	{"AsListBox",luags_GUIControl_AsListBox},
	{"AsSlider",luags_GUIControl_AsSlider},
	{"AsTextBox",luags_GUIControl_AsTextBox},
	{"Clickable",luags_GUIControl_Clickable},
	{"Enabled",luags_GUIControl_Enabled},
	{"Height",luags_GUIControl_Height},
	{"ID",luags_GUIControl_ID},
	{"OwningGUI",luags_GUIControl_OwningGUI},
	{"Visible",luags_GUIControl_Visible},
	{"Width",luags_GUIControl_Width},
	{"X",luags_GUIControl_X},
	{"Y",luags_GUIControl_Y},
	{NULL,NULL}
};

// 'Label' Lua wrappers
static int luags_Label_Font(lua_State *L) {
	AGS_Label* self = luags_checkLabel(1, LABEL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_Label_get_Font(self));
		return 1;
	}
	else {
		AGS_Label_set_Font(self, /* AGS_FontType: */ luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Label_Text(lua_State *L) {
	AGS_Label* self = luags_checkLabel(1, LABEL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Label_get_Text(self));
		return 1;
	}
	else {
		AGS_Label_set_Text(self, luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Label_TextColor(lua_State *L) {
	AGS_Label* self = luags_checkLabel(1, LABEL_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Label_get_TextColor(self));
		return 1;
	}
	else {
		AGS_Label_set_TextColor(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Label_lib[] = {
	{"Font",luags_Label_Font},
	{"Text",luags_Label_Text},
	{"TextColor",luags_Label_TextColor},
	{NULL,NULL}
};

// 'Button' Lua wrappers
static int luags_Button_Animate(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	AGS_Button_Animate(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* AGS_RepeatStyle: */ luaL_checkint(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_Button_ClipImage(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Button_get_ClipImage(self));
		return 1;
	}
	else {
		AGS_Button_set_ClipImage(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_Font(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_Button_get_Font(self));
		return 1;
	}
	else {
		AGS_Button_set_Font(self, /* AGS_FontType: */ luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_Graphic(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Button_get_Graphic(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Button_MouseOverGraphic(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Button_get_MouseOverGraphic(self));
		return 1;
	}
	else {
		AGS_Button_set_MouseOverGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_NormalGraphic(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Button_get_NormalGraphic(self));
		return 1;
	}
	else {
		AGS_Button_set_NormalGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_PushedGraphic(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Button_get_PushedGraphic(self));
		return 1;
	}
	else {
		AGS_Button_set_PushedGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_TextColor(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Button_get_TextColor(self));
		return 1;
	}
	else {
		AGS_Button_set_TextColor(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Button_Text(lua_State *L) {
	AGS_Button* self = luags_checkButton(1, BUTTON_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Button_get_Text(self));
		return 1;
	}
	else {
		AGS_Button_set_Text(self, luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Button_lib[] = {
	{"Animate",luags_Button_Animate},
	{"ClipImage",luags_Button_ClipImage},
	{"Font",luags_Button_Font},
	{"Graphic",luags_Button_Graphic},
	{"MouseOverGraphic",luags_Button_MouseOverGraphic},
	{"NormalGraphic",luags_Button_NormalGraphic},
	{"PushedGraphic",luags_Button_PushedGraphic},
	{"TextColor",luags_Button_TextColor},
	{"Text",luags_Button_Text},
	{NULL,NULL}
};

// 'Slider' Lua wrappers
static int luags_Slider_BackgroundGraphic(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_BackgroundGraphic(self));
		return 1;
	}
	else {
		AGS_Slider_set_BackgroundGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Slider_HandleGraphic(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_HandleGraphic(self));
		return 1;
	}
	else {
		AGS_Slider_set_HandleGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Slider_HandleOffset(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_HandleOffset(self));
		return 1;
	}
	else {
		AGS_Slider_set_HandleOffset(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Slider_Max(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_Max(self));
		return 1;
	}
	else {
		AGS_Slider_set_Max(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Slider_Min(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_Min(self));
		return 1;
	}
	else {
		AGS_Slider_set_Min(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Slider_Value(lua_State *L) {
	AGS_Slider* self = luags_checkSlider(1, SLIDER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Slider_get_Value(self));
		return 1;
	}
	else {
		AGS_Slider_set_Value(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Slider_lib[] = {
	{"BackgroundGraphic",luags_Slider_BackgroundGraphic},
	{"HandleGraphic",luags_Slider_HandleGraphic},
	{"HandleOffset",luags_Slider_HandleOffset},
	{"Max",luags_Slider_Max},
	{"Min",luags_Slider_Min},
	{"Value",luags_Slider_Value},
	{NULL,NULL}
};

// 'TextBox' Lua wrappers
static int luags_TextBox_Font(lua_State *L) {
	AGS_TextBox* self = luags_checkTextBox(1, TEXTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_TextBox_get_Font(self));
		return 1;
	}
	else {
		AGS_TextBox_set_Font(self, /* AGS_FontType: */ luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_TextBox_Text(lua_State *L) {
	AGS_TextBox* self = luags_checkTextBox(1, TEXTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_TextBox_get_Text(self));
		return 1;
	}
	else {
		AGS_TextBox_set_Text(self, luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_TextBox_TextColor(lua_State *L) {
	AGS_TextBox* self = luags_checkTextBox(1, TEXTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_TextBox_get_TextColor(self));
		return 1;
	}
	else {
		AGS_TextBox_set_TextColor(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_TextBox_lib[] = {
	{"Font",luags_TextBox_Font},
	{"Text",luags_TextBox_Text},
	{"TextColor",luags_TextBox_TextColor},
	{NULL,NULL}
};

// 'InvWindow' Lua wrappers
static int luags_InvWindow_ScrollDown(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	AGS_InvWindow_ScrollDown(self);
	return 0;
};
static int luags_InvWindow_ScrollUp(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	AGS_InvWindow_ScrollUp(self);
	return 0;
};
static int luags_InvWindow_CharacterToUse(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushCharacter(L, AGS_InvWindow_get_CharacterToUse(self));
		return 1;
	}
	else {
		AGS_InvWindow_set_CharacterToUse(self, agslua_checkCharacter(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InvWindow_ItemAtIndex(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 2) {
		luags_pushInventoryItem(L, AGS_InvWindow_geti_ItemAtIndex(self, luaL_checkint(L,2)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_InvWindow_ItemCount(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_ItemCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_InvWindow_ItemHeight(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_ItemHeight(self));
		return 1;
	}
	else {
		AGS_InvWindow_set_ItemHeight(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InvWindow_ItemWidth(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_ItemWidth(self));
		return 1;
	}
	else {
		AGS_InvWindow_set_ItemWidth(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InvWindow_TopItem(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_TopItem(self));
		return 1;
	}
	else {
		AGS_InvWindow_set_TopItem(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_InvWindow_ItemsPerRow(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_ItemsPerRow(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_InvWindow_RowCount(lua_State *L) {
	AGS_InvWindow* self = luags_checkInvWindow(1, INVWINDOW_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_InvWindow_get_RowCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_InvWindow_lib[] = {
	{"ScrollDown",luags_InvWindow_ScrollDown},
	{"ScrollUp",luags_InvWindow_ScrollUp},
	{"CharacterToUse",luags_InvWindow_CharacterToUse},
	{"ItemAtIndex",luags_InvWindow_ItemAtIndex},
	{"ItemCount",luags_InvWindow_ItemCount},
	{"ItemHeight",luags_InvWindow_ItemHeight},
	{"ItemWidth",luags_InvWindow_ItemWidth},
	{"TopItem",luags_InvWindow_TopItem},
	{"ItemsPerRow",luags_InvWindow_ItemsPerRow},
	{"RowCount",luags_InvWindow_RowCount},
	{NULL,NULL}
};

// 'ListBox' Lua wrappers
static int luags_ListBox_AddItem(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	lua_pushboolean(L, AGS_ListBox_AddItem(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_ListBox_Clear(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	AGS_ListBox_Clear(self);
	return 0;
};
static int luags_ListBox_FillDirList(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	AGS_ListBox_FillDirList(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_ListBox_FillSaveGameList(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	lua_pushinteger(L, AGS_ListBox_FillSaveGameList(self));
	return 1;
};
static int luags_ListBox_GetItemAtLocation(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	lua_pushinteger(L, AGS_ListBox_GetItemAtLocation(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_ListBox_InsertItemAt(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	lua_pushboolean(L, AGS_ListBox_InsertItemAt(self, luaL_checkstring(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_ListBox_RemoveItem(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	AGS_ListBox_RemoveItem(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_ListBox_ScrollDown(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	AGS_ListBox_ScrollDown(self);
	return 0;
};
static int luags_ListBox_ScrollUp(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	AGS_ListBox_ScrollUp(self);
	return 0;
};
static int luags_ListBox_Font(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, /* AGS_FontType: */ AGS_ListBox_get_Font(self));
		return 1;
	}
	else {
		AGS_ListBox_set_Font(self, /* AGS_FontType: */ luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ListBox_HideBorder(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_ListBox_get_HideBorder(self));
		return 1;
	}
	else {
		AGS_ListBox_set_HideBorder(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ListBox_HideScrollArrows(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_ListBox_get_HideScrollArrows(self));
		return 1;
	}
	else {
		AGS_ListBox_set_HideScrollArrows(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ListBox_ItemCount(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ListBox_get_ItemCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ListBox_Items(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 2) {
		lua_pushstring(L, AGS_ListBox_geti_Items(self, luaL_checkint(L,2)));
		return 1;
	}
	else {
		AGS_ListBox_seti_Items(self, luaL_checkint(L,2), luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ListBox_RowCount(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ListBox_get_RowCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ListBox_SaveGameSlots(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 2) {
		lua_pushinteger(L, AGS_ListBox_geti_SaveGameSlots(self, luaL_checkint(L,2)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_ListBox_SelectedIndex(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ListBox_get_SelectedIndex(self));
		return 1;
	}
	else {
		AGS_ListBox_set_SelectedIndex(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_ListBox_TopItem(lua_State *L) {
	AGS_ListBox* self = luags_checkListBox(1, LISTBOX_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_ListBox_get_TopItem(self));
		return 1;
	}
	else {
		AGS_ListBox_set_TopItem(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_ListBox_lib[] = {
	{"AddItem",luags_ListBox_AddItem},
	{"Clear",luags_ListBox_Clear},
	{"FillDirList",luags_ListBox_FillDirList},
	{"FillSaveGameList",luags_ListBox_FillSaveGameList},
	{"GetItemAtLocation",luags_ListBox_GetItemAtLocation},
	{"InsertItemAt",luags_ListBox_InsertItemAt},
	{"RemoveItem",luags_ListBox_RemoveItem},
	{"ScrollDown",luags_ListBox_ScrollDown},
	{"ScrollUp",luags_ListBox_ScrollUp},
	{"Font",luags_ListBox_Font},
	{"HideBorder",luags_ListBox_HideBorder},
	{"HideScrollArrows",luags_ListBox_HideScrollArrows},
	{"ItemCount",luags_ListBox_ItemCount},
	{"Items",luags_ListBox_Items},
	{"RowCount",luags_ListBox_RowCount},
	{"SaveGameSlots",luags_ListBox_SaveGameSlots},
	{"SelectedIndex",luags_ListBox_SelectedIndex},
	{"TopItem",luags_ListBox_TopItem},
	{NULL,NULL}
};

// 'GUI' Lua wrappers
static int luags_GUI_Centre(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	AGS_GUI_Centre(self);
	return 0;
};
static int luags_GUI_GetAtScreenXY(lua_State *L) {
	luags_pushGUI(L, AGS_GUI_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_GUI_SetPosition(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	AGS_GUI_SetPosition(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_GUI_SetSize(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	AGS_GUI_SetSize(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_GUI_BackgroundGraphic(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_BackgroundGraphic(self));
		return 1;
	}
	else {
		AGS_GUI_set_BackgroundGraphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_Clickable(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_GUI_get_Clickable(self));
		return 1;
	}
	else {
		AGS_GUI_set_Clickable(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_Controls(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 2) {
		luags_pushGUIControl(L, AGS_GUI_geti_Controls(self, luaL_checkint(L,2)));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUI_ControlCount(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_ControlCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUI_Height(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_Height(self));
		return 1;
	}
	else {
		AGS_GUI_set_Height(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_ID(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_GUI_Transparency(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_Transparency(self));
		return 1;
	}
	else {
		AGS_GUI_set_Transparency(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_Visible(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_GUI_get_Visible(self));
		return 1;
	}
	else {
		AGS_GUI_set_Visible(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_Width(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_Width(self));
		return 1;
	}
	else {
		AGS_GUI_set_Width(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_X(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_X(self));
		return 1;
	}
	else {
		AGS_GUI_set_X(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_Y(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_Y(self));
		return 1;
	}
	else {
		AGS_GUI_set_Y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_GUI_ZOrder(lua_State *L) {
	AGS_GUI* self = luags_checkGUI(1, GUI_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_GUI_get_ZOrder(self));
		return 1;
	}
	else {
		AGS_GUI_set_ZOrder(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_GUI_lib[] = {
	{"Centre",luags_GUI_Centre},
	{"GetAtScreenXY",luags_GUI_GetAtScreenXY},
	{"SetPosition",luags_GUI_SetPosition},
	{"SetSize",luags_GUI_SetSize},
	{"BackgroundGraphic",luags_GUI_BackgroundGraphic},
	{"Clickable",luags_GUI_Clickable},
	{"Controls",luags_GUI_Controls},
	{"ControlCount",luags_GUI_ControlCount},
	{"Height",luags_GUI_Height},
	{"ID",luags_GUI_ID},
	{"Transparency",luags_GUI_Transparency},
	{"Visible",luags_GUI_Visible},
	{"Width",luags_GUI_Width},
	{"X",luags_GUI_X},
	{"Y",luags_GUI_Y},
	{"ZOrder",luags_GUI_ZOrder},
	{NULL,NULL}
};

// 'Hotspot' Lua wrappers
static int luags_Hotspot_GetAtScreenXY(lua_State *L) {
	luags_pushHotspot(L, AGS_Hotspot_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Hotspot_GetProperty(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	lua_pushinteger(L, AGS_Hotspot_GetProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Hotspot_GetTextProperty(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	lua_pushstring(L, AGS_Hotspot_GetTextProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Hotspot_RunInteraction(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	AGS_Hotspot_RunInteraction(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_Hotspot_Enabled(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Hotspot_get_Enabled(self));
		return 1;
	}
	else {
		AGS_Hotspot_set_Enabled(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Hotspot_ID(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Hotspot_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Hotspot_Name(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Hotspot_get_Name(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Hotspot_WalkToX(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Hotspot_get_WalkToX(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Hotspot_WalkToY(lua_State *L) {
	AGS_Hotspot* self = luags_checkHotspot(1, HOTSPOT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Hotspot_get_WalkToY(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_Hotspot_lib[] = {
	{"GetAtScreenXY",luags_Hotspot_GetAtScreenXY},
	{"GetProperty",luags_Hotspot_GetProperty},
	{"GetTextProperty",luags_Hotspot_GetTextProperty},
	{"RunInteraction",luags_Hotspot_RunInteraction},
	{"Enabled",luags_Hotspot_Enabled},
	{"ID",luags_Hotspot_ID},
	{"Name",luags_Hotspot_Name},
	{"WalkToX",luags_Hotspot_WalkToX},
	{"WalkToY",luags_Hotspot_WalkToY},
	{NULL,NULL}
};

// 'Region' Lua wrappers
static int luags_Region_GetAtRoomXY(lua_State *L) {
	luags_pushRegion(L, AGS_Region_GetAtRoomXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Region_RunInteraction(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	AGS_Region_RunInteraction(self, /* _ERROR_: */ luaL_checkint(L,2));
	return 0;
};
static int luags_Region_Tint(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	AGS_Region_Tint(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), /* _ERROR_: */ luaL_checkint(L,5));
	return 0;
};
static int luags_Region_Enabled(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Region_get_Enabled(self));
		return 1;
	}
	else {
		AGS_Region_set_Enabled(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Region_ID(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Region_LightLevel(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_LightLevel(self));
		return 1;
	}
	else {
		AGS_Region_set_LightLevel(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Region_TintEnabled(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Region_get_TintEnabled(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Region_TintBlue(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_TintBlue(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Region_TintGreen(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_TintGreen(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Region_TintRed(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_TintRed(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Region_TintSaturation(lua_State *L) {
	AGS_Region* self = luags_checkRegion(1, REGION_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Region_get_TintSaturation(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_Region_lib[] = {
	{"GetAtRoomXY",luags_Region_GetAtRoomXY},
	{"RunInteraction",luags_Region_RunInteraction},
	{"Tint",luags_Region_Tint},
	{"Enabled",luags_Region_Enabled},
	{"ID",luags_Region_ID},
	{"LightLevel",luags_Region_LightLevel},
	{"TintEnabled",luags_Region_TintEnabled},
	{"TintBlue",luags_Region_TintBlue},
	{"TintGreen",luags_Region_TintGreen},
	{"TintRed",luags_Region_TintRed},
	{"TintSaturation",luags_Region_TintSaturation},
	{NULL,NULL}
};

// 'Dialog' Lua wrappers
static int luags_Dialog_DisplayOptions(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	lua_pushinteger(L, AGS_Dialog_DisplayOptions(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Dialog_GetOptionState(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	lua_pushinteger(L, /* AGS_DialogOptionState: */ AGS_Dialog_GetOptionState(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Dialog_GetOptionText(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	lua_pushstring(L, AGS_Dialog_GetOptionText(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Dialog_HasOptionBeenChosen(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	lua_pushboolean(L, AGS_Dialog_HasOptionBeenChosen(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Dialog_SetOptionState(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	AGS_Dialog_SetOptionState(self, /* AGS_DialogOptionState: */ luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3));
	return 0;
};
static int luags_Dialog_Start(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	AGS_Dialog_Start(self);
	return 0;
};
static int luags_Dialog_ID(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Dialog_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Dialog_OptionCount(lua_State *L) {
	AGS_Dialog* self = luags_checkDialog(1, DIALOG_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Dialog_get_OptionCount(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_Dialog_lib[] = {
	{"DisplayOptions",luags_Dialog_DisplayOptions},
	{"GetOptionState",luags_Dialog_GetOptionState},
	{"GetOptionText",luags_Dialog_GetOptionText},
	{"HasOptionBeenChosen",luags_Dialog_HasOptionBeenChosen},
	{"SetOptionState",luags_Dialog_SetOptionState},
	{"Start",luags_Dialog_Start},
	{"ID",luags_Dialog_ID},
	{"OptionCount",luags_Dialog_OptionCount},
	{NULL,NULL}
};

// 'DateTime' Lua wrappers
static int luags_DateTime_Now(lua_State *L) {
	if (lua_gettop(L) == 0) {
		luags_pushDateTime(L, AGS_DateTime_get_Now());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_Year(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_Year(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_Month(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_Month(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_DayOfMonth(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_DayOfMonth(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_Hour(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_Hour(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_Minute(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_Minute(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_Second(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_Second(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DateTime_RawTime(lua_State *L) {
	AGS_DateTime* self = luags_checkDateTime(1, DATETIME_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DateTime_get_RawTime(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_DateTime_lib[] = {
	{"Now",luags_DateTime_Now},
	{"Year",luags_DateTime_Year},
	{"Month",luags_DateTime_Month},
	{"DayOfMonth",luags_DateTime_DayOfMonth},
	{"Hour",luags_DateTime_Hour},
	{"Minute",luags_DateTime_Minute},
	{"Second",luags_DateTime_Second},
	{"RawTime",luags_DateTime_RawTime},
	{NULL,NULL}
};

// 'DialogOptionsRenderingInfo' Lua wrappers
static int luags_DialogOptionsRenderingInfo_ActiveOptionID(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_ActiveOptionID(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_ActiveOptionID(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_DialogToRender(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushDialog(L, AGS_DialogOptionsRenderingInfo_get_DialogToRender(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DialogOptionsRenderingInfo_Height(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_Height(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_Height(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_ParserTextBoxWidth(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_ParserTextBoxWidth(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_ParserTextBoxWidth(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_ParserTextBoxX(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_ParserTextBoxX(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_ParserTextBoxX(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_ParserTextBoxY(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_ParserTextBoxY(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_ParserTextBoxY(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_Surface(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushDrawingSurface(L, AGS_DialogOptionsRenderingInfo_get_Surface(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_DialogOptionsRenderingInfo_Width(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_Width(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_Width(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_X(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_X(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_X(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_DialogOptionsRenderingInfo_Y(lua_State *L) {
	AGS_DialogOptionsRenderingInfo* self = luags_checkDialogOptionsRenderingInfo(1, DIALOGOPTIONSRENDERINGINFO_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_DialogOptionsRenderingInfo_get_Y(self));
		return 1;
	}
	else {
		AGS_DialogOptionsRenderingInfo_set_Y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_DialogOptionsRenderingInfo_lib[] = {
	{"ActiveOptionID",luags_DialogOptionsRenderingInfo_ActiveOptionID},
	{"DialogToRender",luags_DialogOptionsRenderingInfo_DialogToRender},
	{"Height",luags_DialogOptionsRenderingInfo_Height},
	{"ParserTextBoxWidth",luags_DialogOptionsRenderingInfo_ParserTextBoxWidth},
	{"ParserTextBoxX",luags_DialogOptionsRenderingInfo_ParserTextBoxX},
	{"ParserTextBoxY",luags_DialogOptionsRenderingInfo_ParserTextBoxY},
	{"Surface",luags_DialogOptionsRenderingInfo_Surface},
	{"Width",luags_DialogOptionsRenderingInfo_Width},
	{"X",luags_DialogOptionsRenderingInfo_X},
	{"Y",luags_DialogOptionsRenderingInfo_Y},
	{NULL,NULL}
};

// 'System' Lua wrappers
static int luags_System_CapsLock(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_CapsLock());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ColorDepth(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_ColorDepth());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_Gamma(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_Gamma());
		return 1;
	}
	else {
		AGS_System_set_Gamma((int)luaL_checkint(L,1));
		return 0;
	}
};
static int luags_System_HardwareAcceleration(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_HardwareAcceleration());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_NumLock(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_NumLock());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_OperatingSystem(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, /* AGS_eOperatingSystem: */ AGS_System_get_OperatingSystem());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ScreenHeight(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_ScreenHeight());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ScreenWidth(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_ScreenWidth());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ScrollLock(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_ScrollLock());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_SupportsGammaControl(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_SupportsGammaControl());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_Version(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushstring(L, AGS_System_get_Version());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ViewportHeight(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_ViewportHeight());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_ViewportWidth(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushinteger(L, AGS_System_get_ViewportWidth());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_System_VSync(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_VSync());
		return 1;
	}
	else {
		AGS_System_set_VSync(llh_checkboolean(L,1));
		return 0;
	}
};
static int luags_System_Windowed(lua_State *L) {
	if (lua_gettop(L) == 0) {
		lua_pushboolean(L, AGS_System_get_Windowed());
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};

static const luaL_Reg luags_System_lib[] = {
	{"CapsLock",luags_System_CapsLock},
	{"ColorDepth",luags_System_ColorDepth},
	{"Gamma",luags_System_Gamma},
	{"HardwareAcceleration",luags_System_HardwareAcceleration},
	{"NumLock",luags_System_NumLock},
	{"OperatingSystem",luags_System_OperatingSystem},
	{"ScreenHeight",luags_System_ScreenHeight},
	{"ScreenWidth",luags_System_ScreenWidth},
	{"ScrollLock",luags_System_ScrollLock},
	{"SupportsGammaControl",luags_System_SupportsGammaControl},
	{"Version",luags_System_Version},
	{"ViewportHeight",luags_System_ViewportHeight},
	{"ViewportWidth",luags_System_ViewportWidth},
	{"VSync",luags_System_VSync},
	{"Windowed",luags_System_Windowed},
	{NULL,NULL}
};

// 'Object' Lua wrappers
static int luags_Object_Animate(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_Animate(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eOnce), (int)luaL_optint(L,4,AGS_eBlock), (int)luaL_optint(L,5,AGS_eForwards), /* _ERROR_: */ luaL_checkint(L,6)));
	return 1;
};
static int luags_Object_GetAtScreenXY(lua_State *L) {
	luags_pushObject(L, AGS_Object_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Object_GetProperty(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_GetProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Object_GetTextProperty(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushstring(L, AGS_Object_GetTextProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Object_IsCollidingWithObject(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushboolean(L, AGS_Object_IsCollidingWithObject(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Object_MergeIntoBackground(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_MergeIntoBackground(self));
	return 1;
};
static int luags_Object_Move(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_Move(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_optint(L,4,AGS_eNoBlock), (int)luaL_optint(L,5,AGS_eWalkableAreas), /* _ERROR_: */ luaL_checkint(L,6)));
	return 1;
};
static int luags_Object_RemoveTint(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_RemoveTint(self));
	return 1;
};
static int luags_Object_RunInteraction(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_RunInteraction(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Object_SetPosition(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_SetPosition(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Object_SetView(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_SetView(self, (int)luaL_optint(L,2,AGS_-1), (int)luaL_optint(L,3,AGS_-1), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Object_StopAnimating(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_StopAnimating(self));
	return 1;
};
static int luags_Object_StopMoving(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_StopMoving(self));
	return 1;
};
static int luags_Object_Tint(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	lua_pushinteger(L, AGS_Object_Tint(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5), /* _ERROR_: */ luaL_checkint(L,6)));
	return 1;
};
static int luags_Object_Animating(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_Animating(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Baseline(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Baseline(self));
		return 1;
	}
	else {
		AGS_Object_set_Baseline(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_BlockingHeight(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_BlockingHeight(self));
		return 1;
	}
	else {
		AGS_Object_set_BlockingHeight(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_BlockingWidth(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_BlockingWidth(self));
		return 1;
	}
	else {
		AGS_Object_set_BlockingWidth(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_Clickable(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_Clickable(self));
		return 1;
	}
	else {
		AGS_Object_set_Clickable(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_Frame(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Frame(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Graphic(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Graphic(self));
		return 1;
	}
	else {
		AGS_Object_set_Graphic(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_ID(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_IgnoreScaling(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_IgnoreScaling(self));
		return 1;
	}
	else {
		AGS_Object_set_IgnoreScaling(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_IgnoreWalkbehinds(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_IgnoreWalkbehinds(self));
		return 1;
	}
	else {
		AGS_Object_set_IgnoreWalkbehinds(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_Loop(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Loop(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Moving(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_Moving(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Name(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Object_get_Name(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Solid(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_Solid(self));
		return 1;
	}
	else {
		AGS_Object_set_Solid(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_Transparency(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Transparency(self));
		return 1;
	}
	else {
		AGS_Object_set_Transparency(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_View(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_View(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Object_Visible(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Object_get_Visible(self));
		return 1;
	}
	else {
		AGS_Object_set_Visible(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_X(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_X(self));
		return 1;
	}
	else {
		AGS_Object_set_X(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Object_Y(lua_State *L) {
	AGS_Object* self = luags_checkObject(1, OBJECT_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Object_get_Y(self));
		return 1;
	}
	else {
		AGS_Object_set_Y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Object_lib[] = {
	{"Animate",luags_Object_Animate},
	{"GetAtScreenXY",luags_Object_GetAtScreenXY},
	{"GetProperty",luags_Object_GetProperty},
	{"GetTextProperty",luags_Object_GetTextProperty},
	{"IsCollidingWithObject",luags_Object_IsCollidingWithObject},
	{"MergeIntoBackground",luags_Object_MergeIntoBackground},
	{"Move",luags_Object_Move},
	{"RemoveTint",luags_Object_RemoveTint},
	{"RunInteraction",luags_Object_RunInteraction},
	{"SetPosition",luags_Object_SetPosition},
	{"SetView",luags_Object_SetView},
	{"StopAnimating",luags_Object_StopAnimating},
	{"StopMoving",luags_Object_StopMoving},
	{"Tint",luags_Object_Tint},
	{"Animating",luags_Object_Animating},
	{"Baseline",luags_Object_Baseline},
	{"BlockingHeight",luags_Object_BlockingHeight},
	{"BlockingWidth",luags_Object_BlockingWidth},
	{"Clickable",luags_Object_Clickable},
	{"Frame",luags_Object_Frame},
	{"Graphic",luags_Object_Graphic},
	{"ID",luags_Object_ID},
	{"IgnoreScaling",luags_Object_IgnoreScaling},
	{"IgnoreWalkbehinds",luags_Object_IgnoreWalkbehinds},
	{"Loop",luags_Object_Loop},
	{"Moving",luags_Object_Moving},
	{"Name",luags_Object_Name},
	{"Solid",luags_Object_Solid},
	{"Transparency",luags_Object_Transparency},
	{"View",luags_Object_View},
	{"Visible",luags_Object_Visible},
	{"X",luags_Object_X},
	{"Y",luags_Object_Y},
	{NULL,NULL}
};

// 'Character' Lua wrappers
static int luags_Character_AddInventory(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_AddInventory(self, (int)luaL_optint(L,2,AGS_SCR_NO_VALUE), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_AddWaypoint(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_AddWaypoint(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_Animate(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_Animate(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eOnce), (int)luaL_optint(L,4,AGS_eBlock), (int)luaL_optint(L,5,AGS_eForwards), /* _ERROR_: */ luaL_checkint(L,6)));
	return 1;
};
static int luags_Character_ChangeRoom(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_ChangeRoom(self, (int)luaL_optint(L,2,AGS_SCR_NO_VALUE), (int)luaL_optint(L,3,AGS_SCR_NO_VALUE), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_ChangeRoomAutoPosition(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_ChangeRoomAutoPosition(self, (int)luaL_optint(L,2,0), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_ChangeView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_ChangeView(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_FaceCharacter(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_FaceCharacter(self, (int)luaL_optint(L,2,AGS_eBlock), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_FaceLocation(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_FaceLocation(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eBlock), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_FaceObject(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_FaceObject(self, (int)luaL_optint(L,2,AGS_eBlock), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_FollowCharacter(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_FollowCharacter(self, (int)luaL_optint(L,2,10), (int)luaL_optint(L,3,97), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_GetAtScreenXY(lua_State *L) {
	luags_pushCharacter(L, AGS_Character_GetAtScreenXY((int)luaL_checkint(L,1), (int)luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_GetProperty(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_GetProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_GetTextProperty(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushstring(L, AGS_Character_GetTextProperty(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_HasInventory(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushboolean(L, AGS_Character_HasInventory(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_IsCollidingWithChar(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_IsCollidingWithChar(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_IsCollidingWithObject(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_IsCollidingWithObject(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_LockView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_LockView(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_LockViewAligned(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_LockViewAligned(self, (int)luaL_checkint(L,2), /* AGS_Alignment: */ luaL_checkint(L,3), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_LockViewFrame(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_LockViewFrame(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_LockViewOffset(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_LockViewOffset(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_LoseInventory(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_LoseInventory(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_Move(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_Move(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eNoBlock), (int)luaL_optint(L,4,AGS_eWalkableAreas), /* _ERROR_: */ luaL_checkint(L,5)));
	return 1;
};
static int luags_Character_PlaceOnWalkableArea(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_PlaceOnWalkableArea(self));
	return 1;
};
static int luags_Character_RemoveTint(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	AGS_Character_RemoveTint(self);
	return 0;
};
static int luags_Character_RunInteraction(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_RunInteraction(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_Say(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	aux_formatstring(L, 1);
	lua_pushinteger(L, AGS_Character_Say(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_SayAt(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_SayAt(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), luaL_checkstring(L,4), /* _ERROR_: */ luaL_checkint(L,5)));
	return 1;
};
static int luags_Character_SayBackground(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	luags_pushOverlay(L, AGS_Character_SayBackground(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_SetAsPlayer(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_SetAsPlayer(self));
	return 1;
};
static int luags_Character_SetIdleView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_SetIdleView(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_SetWalkSpeed(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_SetWalkSpeed(self, (int)luaL_checkint(L,2), /* _ERROR_: */ luaL_checkint(L,3)));
	return 1;
};
static int luags_Character_StopMoving(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_StopMoving(self));
	return 1;
};
static int luags_Character_Think(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	aux_formatstring(L, 1);
	lua_pushinteger(L, AGS_Character_Think(self, /* _ERROR_: */ luaL_checkint(L,2)));
	return 1;
};
static int luags_Character_Tint(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	AGS_Character_Tint(self, (int)luaL_checkint(L,2), (int)luaL_checkint(L,3), (int)luaL_checkint(L,4), (int)luaL_checkint(L,5), /* _ERROR_: */ luaL_checkint(L,6));
	return 0;
};
static int luags_Character_UnlockView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_UnlockView(self));
	return 1;
};
static int luags_Character_Walk(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_Walk(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eNoBlock), (int)luaL_optint(L,4,AGS_eWalkableAreas), /* _ERROR_: */ luaL_checkint(L,5)));
	return 1;
};
static int luags_Character_WalkStraight(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	lua_pushinteger(L, AGS_Character_WalkStraight(self, (int)luaL_checkint(L,2), (int)luaL_optint(L,3,AGS_eNoBlock), /* _ERROR_: */ luaL_checkint(L,4)));
	return 1;
};
static int luags_Character_ActiveInventory(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		luags_pushInventoryItem(L, AGS_Character_get_ActiveInventory(self));
		return 1;
	}
	else {
		AGS_Character_set_ActiveInventory(self, agslua_checkInventoryItem(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Animating(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_Animating(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_AnimationSpeed(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_AnimationSpeed(self));
		return 1;
	}
	else {
		AGS_Character_set_AnimationSpeed(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Baseline(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Baseline(self));
		return 1;
	}
	else {
		AGS_Character_set_Baseline(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_BlinkInterval(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_BlinkInterval(self));
		return 1;
	}
	else {
		AGS_Character_set_BlinkInterval(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_BlinkView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_BlinkView(self));
		return 1;
	}
	else {
		AGS_Character_set_BlinkView(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_BlinkWhileThinking(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_BlinkWhileThinking(self));
		return 1;
	}
	else {
		AGS_Character_set_BlinkWhileThinking(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_BlockingHeight(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_BlockingHeight(self));
		return 1;
	}
	else {
		AGS_Character_set_BlockingHeight(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_BlockingWidth(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_BlockingWidth(self));
		return 1;
	}
	else {
		AGS_Character_set_BlockingWidth(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Clickable(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_Clickable(self));
		return 1;
	}
	else {
		AGS_Character_set_Clickable(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_DiagonalLoops(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_DiagonalLoops(self));
		return 1;
	}
	else {
		AGS_Character_set_DiagonalLoops(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Frame(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Frame(self));
		return 1;
	}
	else {
		AGS_Character_set_Frame(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_HasExplicitTint(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_HasExplicitTint(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_ID(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_ID(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_IdleView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_IdleView(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_IgnoreLighting(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_IgnoreLighting(self));
		return 1;
	}
	else {
		AGS_Character_set_IgnoreLighting(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_IgnoreScaling(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_IgnoreScaling(self));
		return 1;
	}
	else {
		AGS_Character_set_IgnoreScaling(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_IgnoreWalkbehinds(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_IgnoreWalkbehinds(self));
		return 1;
	}
	else {
		AGS_Character_set_IgnoreWalkbehinds(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_InventoryQuantity(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 2) {
		lua_pushinteger(L, AGS_Character_geti_InventoryQuantity(self, luaL_checkint(L,2)));
		return 1;
	}
	else {
		AGS_Character_seti_InventoryQuantity(self, luaL_checkint(L,2), (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Loop(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Loop(self));
		return 1;
	}
	else {
		AGS_Character_set_Loop(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_ManualScaling(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_ManualScaling(self));
		return 1;
	}
	else {
		AGS_Character_set_ManualScaling(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_MovementLinkedToAnimation(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_MovementLinkedToAnimation(self));
		return 1;
	}
	else {
		AGS_Character_set_MovementLinkedToAnimation(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Moving(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_Moving(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_Name(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushstring(L, AGS_Character_get_Name(self));
		return 1;
	}
	else {
		AGS_Character_set_Name(self, luaL_checkstring(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_NormalView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_NormalView(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_PreviousRoom(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_PreviousRoom(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_Room(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Room(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_ScaleMoveSpeed(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_ScaleMoveSpeed(self));
		return 1;
	}
	else {
		AGS_Character_set_ScaleMoveSpeed(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_ScaleVolume(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_ScaleVolume(self));
		return 1;
	}
	else {
		AGS_Character_set_ScaleVolume(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Scaling(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Scaling(self));
		return 1;
	}
	else {
		AGS_Character_set_Scaling(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Solid(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_Solid(self));
		return 1;
	}
	else {
		AGS_Character_set_Solid(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Speaking(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_Speaking(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_SpeakingFrame(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_SpeakingFrame(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_SpeechAnimationDelay(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_SpeechAnimationDelay(self));
		return 1;
	}
	else {
		AGS_Character_set_SpeechAnimationDelay(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_SpeechColor(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_SpeechColor(self));
		return 1;
	}
	else {
		AGS_Character_set_SpeechColor(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_SpeechView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_SpeechView(self));
		return 1;
	}
	else {
		AGS_Character_set_SpeechView(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_ThinkView(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_ThinkView(self));
		return 1;
	}
	else {
		AGS_Character_set_ThinkView(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_Transparency(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_Transparency(self));
		return 1;
	}
	else {
		AGS_Character_set_Transparency(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_TurnBeforeWalking(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushboolean(L, AGS_Character_get_TurnBeforeWalking(self));
		return 1;
	}
	else {
		AGS_Character_set_TurnBeforeWalking(self, llh_checkboolean(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_View(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_View(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_WalkSpeedX(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_WalkSpeedX(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_WalkSpeedY(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_WalkSpeedY(self));
		return 1;
	}
	else {
		lua_pushstring(L, ATTEMPT_TO_SET_READONLY_ATTRIBUTE);
		return lua_error(L);
	}
};
static int luags_Character_x(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_x(self));
		return 1;
	}
	else {
		AGS_Character_set_x(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_y(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_y(self));
		return 1;
	}
	else {
		AGS_Character_set_y(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};
static int luags_Character_z(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(1, CHARACTER_UV_META);
	if (lua_gettop(L) == 1) {
		lua_pushinteger(L, AGS_Character_get_z(self));
		return 1;
	}
	else {
		AGS_Character_set_z(self, (int)luaL_checkint(L,2));
		lua_settop(L,1);
		return 1;
	}
};

static const luaL_Reg luags_Character_lib[] = {
	{"AddInventory",luags_Character_AddInventory},
	{"AddWaypoint",luags_Character_AddWaypoint},
	{"Animate",luags_Character_Animate},
	{"ChangeRoom",luags_Character_ChangeRoom},
	{"ChangeRoomAutoPosition",luags_Character_ChangeRoomAutoPosition},
	{"ChangeView",luags_Character_ChangeView},
	{"FaceCharacter",luags_Character_FaceCharacter},
	{"FaceLocation",luags_Character_FaceLocation},
	{"FaceObject",luags_Character_FaceObject},
	{"FollowCharacter",luags_Character_FollowCharacter},
	{"GetAtScreenXY",luags_Character_GetAtScreenXY},
	{"GetProperty",luags_Character_GetProperty},
	{"GetTextProperty",luags_Character_GetTextProperty},
	{"HasInventory",luags_Character_HasInventory},
	{"IsCollidingWithChar",luags_Character_IsCollidingWithChar},
	{"IsCollidingWithObject",luags_Character_IsCollidingWithObject},
	{"LockView",luags_Character_LockView},
	{"LockViewAligned",luags_Character_LockViewAligned},
	{"LockViewFrame",luags_Character_LockViewFrame},
	{"LockViewOffset",luags_Character_LockViewOffset},
	{"LoseInventory",luags_Character_LoseInventory},
	{"Move",luags_Character_Move},
	{"PlaceOnWalkableArea",luags_Character_PlaceOnWalkableArea},
	{"RemoveTint",luags_Character_RemoveTint},
	{"RunInteraction",luags_Character_RunInteraction},
	{"Say",luags_Character_Say},
	{"SayAt",luags_Character_SayAt},
	{"SayBackground",luags_Character_SayBackground},
	{"SetAsPlayer",luags_Character_SetAsPlayer},
	{"SetIdleView",luags_Character_SetIdleView},
	{"SetWalkSpeed",luags_Character_SetWalkSpeed},
	{"StopMoving",luags_Character_StopMoving},
	{"Think",luags_Character_Think},
	{"Tint",luags_Character_Tint},
	{"UnlockView",luags_Character_UnlockView},
	{"Walk",luags_Character_Walk},
	{"WalkStraight",luags_Character_WalkStraight},
	{"ActiveInventory",luags_Character_ActiveInventory},
	{"Animating",luags_Character_Animating},
	{"AnimationSpeed",luags_Character_AnimationSpeed},
	{"Baseline",luags_Character_Baseline},
	{"BlinkInterval",luags_Character_BlinkInterval},
	{"BlinkView",luags_Character_BlinkView},
	{"BlinkWhileThinking",luags_Character_BlinkWhileThinking},
	{"BlockingHeight",luags_Character_BlockingHeight},
	{"BlockingWidth",luags_Character_BlockingWidth},
	{"Clickable",luags_Character_Clickable},
	{"DiagonalLoops",luags_Character_DiagonalLoops},
	{"Frame",luags_Character_Frame},
	{"HasExplicitTint",luags_Character_HasExplicitTint},
	{"ID",luags_Character_ID},
	{"IdleView",luags_Character_IdleView},
	{"IgnoreLighting",luags_Character_IgnoreLighting},
	{"IgnoreScaling",luags_Character_IgnoreScaling},
	{"IgnoreWalkbehinds",luags_Character_IgnoreWalkbehinds},
	{"InventoryQuantity",luags_Character_InventoryQuantity},
	{"Loop",luags_Character_Loop},
	{"ManualScaling",luags_Character_ManualScaling},
	{"MovementLinkedToAnimation",luags_Character_MovementLinkedToAnimation},
	{"Moving",luags_Character_Moving},
	{"Name",luags_Character_Name},
	{"NormalView",luags_Character_NormalView},
	{"PreviousRoom",luags_Character_PreviousRoom},
	{"Room",luags_Character_Room},
	{"ScaleMoveSpeed",luags_Character_ScaleMoveSpeed},
	{"ScaleVolume",luags_Character_ScaleVolume},
	{"Scaling",luags_Character_Scaling},
	{"Solid",luags_Character_Solid},
	{"Speaking",luags_Character_Speaking},
	{"SpeakingFrame",luags_Character_SpeakingFrame},
	{"SpeechAnimationDelay",luags_Character_SpeechAnimationDelay},
	{"SpeechColor",luags_Character_SpeechColor},
	{"SpeechView",luags_Character_SpeechView},
	{"ThinkView",luags_Character_ThinkView},
	{"Transparency",luags_Character_Transparency},
	{"TurnBeforeWalking",luags_Character_TurnBeforeWalking},
	{"View",luags_Character_View},
	{"WalkSpeedX",luags_Character_WalkSpeedX},
	{"WalkSpeedY",luags_Character_WalkSpeedY},
	{"x",luags_Character_x},
	{"y",luags_Character_y},
	{"z",luags_Character_z},
	{NULL,NULL}
};
