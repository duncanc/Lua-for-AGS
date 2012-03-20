extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
}
#include "agsplugin.h"
#include "agslua.h"

AGS_ARETHINGSOVERLAPPING AGS_AreThingsOverlapping;
AGS_CALLROOMSCRIPT AGS_CallRoomScript;
AGS_CLAIMEVENT AGS_ClaimEvent;
AGS_CYCLEPALETTE AGS_CyclePalette;
AGS_DEBUG AGS_Debug;
AGS_DELETESAVESLOT AGS_DeleteSaveSlot;
AGS_DISABLEGROUNDLEVELAREAS AGS_DisableGroundLevelAreas;
AGS_DISABLEINTERFACE AGS_DisableInterface;
AGS_DISPLAY AGS_Display;
AGS_DISPLAYAT AGS_DisplayAt;
AGS_DISPLAYATY AGS_DisplayAtY;
AGS_DISPLAYMESSAGE AGS_DisplayMessage;
AGS_DISPLAYMESSAGEATY AGS_DisplayMessageAtY;
AGS_DISPLAYMESSAGEBAR AGS_DisplayMessageBar;
AGS_DISPLAYSPEECH AGS_DisplaySpeech;
AGS_DISPLAYTOPBAR AGS_DisplayTopBar;
AGS_ENABLEGROUNDLEVELAREAS AGS_EnableGroundLevelAreas;
AGS_ENABLEINTERFACE AGS_EnableInterface;
AGS_ENDCUTSCENE AGS_EndCutscene;
AGS_FADEIN AGS_FadeIn;
AGS_FADEOUT AGS_FadeOut;
AGS_FLIPSCREEN AGS_FlipScreen;
AGS_FLOATTOINT AGS_FloatToInt;
AGS_GETBACKGROUNDFRAME AGS_GetBackgroundFrame;
AGS_GETCURRENTMUSIC AGS_GetCurrentMusic;
AGS_GETGAMEOPTION AGS_GetGameOption;
AGS_GETGAMESPEED AGS_GetGameSpeed;
AGS_GETGLOBALINT AGS_GetGlobalInt;
AGS_GETGRAPHICALVARIABLE AGS_GetGraphicalVariable;
AGS_GETLOCATIONTYPE AGS_GetLocationType;
AGS_GETMIDIPOSITION AGS_GetMIDIPosition;
AGS_GETMP3POSMILLIS AGS_GetMP3PosMillis;
AGS_GETROOMPROPERTY AGS_GetRoomProperty;
AGS_GETSCALINGAT AGS_GetScalingAt;
AGS_GETTEXTHEIGHT AGS_GetTextHeight;
AGS_GETTEXTWIDTH AGS_GetTextWidth;
AGS_GETTRANSLATION AGS_GetTranslation;
AGS_GETVIEWPORTX AGS_GetViewportX;
AGS_GETVIEWPORTY AGS_GetViewportY;
AGS_GETWALKABLEAREAAT AGS_GetWalkableAreaAt;
AGS_GIVESCORE AGS_GiveScore;
AGS_HASPLAYERBEENINROOM AGS_HasPlayerBeenInRoom;
AGS_INTTOFLOAT AGS_IntToFloat;
AGS_ISCHANNELPLAYING AGS_IsChannelPlaying;
AGS_ISCHANNELPAUSED AGS_IsChannelPaused;
AGS_ISINTERACTIONAVAILABLE AGS_IsInteractionAvailable;
AGS_ISINTERFACEENABLED AGS_IsInterfaceEnabled;
AGS_ISKEYPRESSED AGS_IsKeyPressed;
AGS_ISMUSICPLAYING AGS_IsMusicPlaying;
AGS_ISMUSICVOXAVAILABLE AGS_IsMusicVoxAvailable;
AGS_ISSOUNDPLAYING AGS_IsSoundPlaying;
AGS_ISTIMEREXPIRED AGS_IsTimerExpired;
AGS_ISTRANSLATIONAVAILABLE AGS_IsTranslationAvailable;
AGS_ISVOXAVAILABLE AGS_IsVoxAvailable;
AGS_PAUSEGAME AGS_PauseGame;
AGS_PLAYAMBIENTSOUND AGS_PlayAmbientSound;
AGS_PLAYFLIC AGS_PlayFlic;
AGS_PLAYMP3FILE AGS_PlayMP3File;
AGS_PLAYMUSIC AGS_PlayMusic;
AGS_PLAYMUSICQUEUED AGS_PlayMusicQueued;
AGS_PLAYSILENTMIDI AGS_PlaySilentMidi;
AGS_PLAYSOUND AGS_PlaySound;
AGS_PLAYSOUNDEX AGS_PlaySoundEx;
AGS_PLAYVIDEO AGS_PlayVideo;
AGS_PROCESSCLICK AGS_ProcessClick;
AGS_QUITGAME AGS_QuitGame;
AGS_RANDOM AGS_Random;
AGS_RELEASEVIEWPORT AGS_ReleaseViewport;
AGS_REMOVEWALKABLEAREA AGS_RemoveWalkableArea;
AGS_RESETROOM AGS_ResetRoom;
AGS_RESTARTGAME AGS_RestartGame;
AGS_RESTOREGAMEDIALOG AGS_RestoreGameDialog;
AGS_RESTOREGAMESLOT AGS_RestoreGameSlot;
AGS_RESTOREWALKABLEAREA AGS_RestoreWalkableArea;
AGS_RUNAGSGAME AGS_RunAGSGame;
AGS_SAID AGS_Said;
AGS_SAVEGAMEDIALOG AGS_SaveGameDialog;
AGS_SAVEGAMESLOT AGS_SaveGameSlot;
AGS_SAVESCREENSHOT AGS_SaveScreenshot;
AGS_SEEKMIDIPOSITION AGS_SeekMIDIPosition;
AGS_SEEKMODPATTERN AGS_SeekMODPattern;
AGS_SEEKMP3POSMILLIS AGS_SeekMP3PosMillis;
AGS_SETAMBIENTTINT AGS_SetAmbientTint;
AGS_SETAREASCALING AGS_SetAreaScaling;
AGS_SETBACKGROUNDFRAME AGS_SetBackgroundFrame;
AGS_SETCHANNELVOLUME AGS_SetChannelVolume;
AGS_SETDIGITALMASTERVOLUME AGS_SetDigitalMasterVolume;
AGS_SETFADECOLOR AGS_SetFadeColor;
AGS_SETGAMEOPTION AGS_SetGameOption;
AGS_SETGAMESPEED AGS_SetGameSpeed;
AGS_SETGLOBALINT AGS_SetGlobalInt;
AGS_SETGRAPHICALVARIABLE AGS_SetGraphicalVariable;
AGS_SETMULTITASKINGMODE AGS_SetMultitaskingMode;
AGS_SETMUSICMASTERVOLUME AGS_SetMusicMasterVolume;
AGS_SETMUSICREPEAT AGS_SetMusicRepeat;
AGS_SETMUSICVOLUME AGS_SetMusicVolume;
AGS_SETNEXTSCREENTRANSITION AGS_SetNextScreenTransition;
AGS_SETPALRGB AGS_SetPalRGB;
AGS_SETRESTARTPOINT AGS_SetRestartPoint;
AGS_SETSCREENTRANSITION AGS_SetScreenTransition;
AGS_SETSKIPSPEECH AGS_SetSkipSpeech;
AGS_SETSOUNDVOLUME AGS_SetSoundVolume;
AGS_SETSPEECHSTYLE AGS_SetSpeechStyle;
AGS_SETSPEECHVOLUME AGS_SetSpeechVolume;
AGS_SETTEXTWINDOWGUI AGS_SetTextWindowGUI;
AGS_SETTIMER AGS_SetTimer;
AGS_SETVIEWPORT AGS_SetViewport;
AGS_SETVOICEMODE AGS_SetVoiceMode;
AGS_SETWALKBEHINDBASE AGS_SetWalkBehindBase;
AGS_SHAKESCREEN AGS_ShakeScreen;
AGS_SHAKESCREENBACKGROUND AGS_ShakeScreenBackground;
AGS_SKIPUNTILCHARACTERSTOPS AGS_SkipUntilCharacterStops;
AGS_STARTCUTSCENE AGS_StartCutscene;
AGS_STOPAMBIENTNOISE AGS_StopAmbientNoise;
AGS_STOPCHANNEL AGS_StopChannel;
AGS_STOPDIALOG AGS_StopDialog;
AGS_STOPMUSIC AGS_StopMusic;
AGS_TINTSCREEN AGS_TintScreen;
AGS_UNPAUSEGAME AGS_UnpauseGame;
AGS_UPDATEINVENTORY AGS_UpdateInventory;
AGS_UPDATEPALETTE AGS_UpdatePalette;
AGS_WAIT AGS_Wait;
AGS_WAITKEY AGS_WaitKey;
AGS_WAITMOUSEKEY AGS_WaitMouseKey;

/*

int luags_version(lua_State *L) {
	lua_pushnumber(L, engine->version);
	return 1;
}

int luags_AbortGame(lua_State *L) {
	engine->AbortGame(luaL_checkstring(L,1));
	return 0;
}

int luags_GetEngineVersion(lua_State *L) {
	lua_pushstring(L, engine->GetEngineVersion());
	return 1;
}

int luags_GetGraphicsDriverID(lua_State *L) {
	lua_pushstring(L, engine->GetGraphicsDriverID());
	return 1;
}

int luags_GetScreenDimensions(lua_State *L) {
	long width,height,coldepth;
	engine->GetScreenDimensions(&width, &height, &coldepth);
	lua_pushnumber(L, width);
	lua_pushnumber(L, height);
	lua_pushnumber(L, coldepth);
	return 3;
}

int luags_DrawText(lua_State *L) {
	engine->DrawTextA(
		(long)luaL_checknumber(L,1),
		(long)luaL_checknumber(L,2),
		(long)luaL_checknumber(L,3),
		(long)luaL_checknumber(L,4),
		(char*)luaL_checkstring(L,5));
	return 0;
}

int luags_GetMousePosition(lua_State *L) {
	long x,y;
	engine->GetMousePosition(&x,&y);
	lua_pushnumber(L,(lua_Number)x);
	lua_pushnumber(L,(lua_Number)y);
	return 2;
}

int luags_GetNumBackgrounds(lua_State *L) {
	lua_pushinteger(L, engine->GetNumBackgrounds());
	return 1;
}

int luags_GetCurrentBackground(lua_State *L) {
	lua_pushinteger(L, engine->GetCurrentBackground());
	return 1;
}

int luags_GetCurrentRoom(lua_State *L) {
	lua_pushinteger(L, engine->GetCurrentRoom());
	return 1;
}

int luags_DrawTextWrapped(lua_State *L) {
	engine->DrawTextWrapped(
		(long)luaL_checknumber(L,1),
		(long)luaL_checknumber(L,2),
		(long)luaL_checknumber(L,3),
		(long)luaL_checknumber(L,4),
		(long)luaL_checknumber(L,5),
		(char*)luaL_checkstring(L,6));
	return 0;
}

int luags_LookUpParserWord(lua_State *L) {
	lua_pushinteger(L, engine->LookupParserWord(luaL_checkstring(L,1)));
	return 1;
}

int luags_PollSystem(lua_State *L) {
	engine->PollSystem();
	return 0;
}

int luags_GetNumCharacters(lua_State *L) {
	lua_pushinteger(L, engine->GetNumCharacters());
	return 1;
}

int luags_GetCharacter(lua_State *L) {
	AGSCharacter* character = engine->GetCharacter((long)luaL_checknumber(L,1));
	// TODO
	return 0;
}

int luags_GetPlayerCharacter(lua_State *L) {
	lua_pushinteger(L, engine->GetPlayerCharacter());
	return 1;
}

static const luaL_Reg luags_lib[] = {
	{"version", luags_version},
	{"AbortGame", luags_AbortGame},
	{"GetEngineVersion", luags_GetEngineVersion},
	{"GetGraphicsDriverID", luags_GetGraphicsDriverID},
	{"GetScreenDimensions", luags_GetScreenDimensions},
	{"DrawText", luags_DrawText},
	{"GetMousePosition", luags_GetMousePosition},
	{"GetNumBackgrounds", luags_GetNumBackgrounds},
	{"GetCurrentBackground", luags_GetCurrentBackground},
	{"GetCurrentRoom", luags_GetCurrentRoom},
	{"DrawTextWrapped", luags_DrawTextWrapped},
	{"LookUpParserWord", luags_LookUpParserWord},
	{"PollSystem", luags_PollSystem},
	{"GetNumCharacters", luags_GetNumCharacters},
	{"GetPlayerCharacter", luags_GetPlayerCharacter},
	{NULL, NULL}
};

#define GAME_OPTIONS_READONLY(name) \
	int luags_game_##name(lua_State *L) { \
		if (lua_gettop(L) == 0) { \
			lua_pushinteger(L, game_options->##name); \
		} \
		else { \
			return luaL_error(L, "cannot modify game variable " LUA_QL(#name)); \
		} \
		return 0; \
	}

#define GAME_OPTIONS_READWRITE(name) \
	int luags_game_##name(lua_State *L) { \
		if (lua_gettop(L) == 0) { \
			lua_pushinteger(L, game_options->##name); \
		} \
		else { \
			game_options->##name = luaL_checkint(L,1); \
		} \
		return 0; \
	}

GAME_OPTIONS_READWRITE(score);
GAME_OPTIONS_READWRITE(usedmode);
GAME_OPTIONS_READWRITE(disabled_user_interface);
GAME_OPTIONS_READWRITE(debug_mode);
GAME_OPTIONS_READWRITE(messagetime);
GAME_OPTIONS_READWRITE(usedinv);
GAME_OPTIONS_READWRITE(inv_top);
GAME_OPTIONS_READWRITE(inv_numdisp);
GAME_OPTIONS_READWRITE(inv_numorder);
GAME_OPTIONS_READWRITE(inv_numinline);
GAME_OPTIONS_READWRITE(text_speed);
GAME_OPTIONS_READWRITE(sierra_inv_color);
GAME_OPTIONS_READWRITE(talkanim_speed);
GAME_OPTIONS_READWRITE(inv_item_wid);
GAME_OPTIONS_READWRITE(inv_item_hit);
GAME_OPTIONS_READWRITE(speech_text_shadow);
GAME_OPTIONS_READWRITE(swap_portrait_side);
GAME_OPTIONS_READWRITE(speech_textwindow_gui);
GAME_OPTIONS_READWRITE(follow_change_room_timer);
GAME_OPTIONS_READWRITE(totalscore);
GAME_OPTIONS_READWRITE(skip_display);
GAME_OPTIONS_READWRITE(no_multiloop_repeat);
GAME_OPTIONS_READWRITE(roomscript_finished);
GAME_OPTIONS_READWRITE(used_inv_on);
GAME_OPTIONS_READWRITE(no_textbg_when_voice);
GAME_OPTIONS_READWRITE(max_dialogoption_width);
GAME_OPTIONS_READWRITE(no_hicolor_fadein);
GAME_OPTIONS_READWRITE(bgspeech_game_speed);
GAME_OPTIONS_READWRITE(bgspeech_stay_on_display);
GAME_OPTIONS_READWRITE(unfactor_speech_from_textlength);
GAME_OPTIONS_READWRITE(mp3_loop_before_end);
GAME_OPTIONS_READWRITE(speech_music_drop);
GAME_OPTIONS_READWRITE(in_cutscene);
GAME_OPTIONS_READWRITE(fast_forward);
GAME_OPTIONS_READWRITE(room_width);
GAME_OPTIONS_READWRITE(room_height);

static const luaL_Reg luags_game_lib[] = {
	{"score", luags_game_score},
	{"usedmode", luags_game_usedmode},
	{"disabled_user_interface", luags_game_disabled_user_interface},
	{"debug_mode", luags_game_debug_mode},
	{"messagetime", luags_game_messagetime},
	{"usedinv", luags_game_usedinv},
	{"inv_top", luags_game_inv_top},
	{"inv_numdisp", luags_game_inv_numdisp},
	{"inv_numorder", luags_game_inv_numorder},
	{"inv_numinline", luags_game_inv_numinline},
	{"text_speed", luags_game_text_speed},
	{"sierra_inv_color", luags_game_sierra_inv_color},
	{"talkanim_speed", luags_game_talkanim_speed},
	{"inv_item_wid", luags_game_inv_item_wid},
	{"inv_item_hit", luags_game_inv_item_hit},
	{"speech_text_shadow", luags_game_speech_text_shadow},
	{"swap_portrait_side", luags_game_swap_portrait_side},
	{"speech_textwindow_gui", luags_game_speech_textwindow_gui},
	{"follow_change_room_timer", luags_game_follow_change_room_timer},
	{"totalscore", luags_game_totalscore},
	{"skip_display", luags_game_skip_display},
	{"no_multiloop_repeat", luags_game_no_multiloop_repeat},
	{"roomscript_finished", luags_game_roomscript_finished},
	{"used_inv_on", luags_game_used_inv_on},
	{"no_textbg_when_voice", luags_game_no_textbg_when_voice},
	{"max_dialogoption_width", luags_game_max_dialogoption_width},
	{"no_hicolor_fadein", luags_game_no_hicolor_fadein},
	{"bgspeech_game_speed", luags_game_bgspeech_game_speed},
	{"bgspeech_stay_on_display", luags_game_bgspeech_stay_on_display},
	{"unfactor_speech_from_textlength", luags_game_unfactor_speech_from_textlength},
	{"mp3_loop_before_end", luags_game_mp3_loop_before_end},
	{"speech_music_drop", luags_game_speech_music_drop},
	{"in_cutscene", luags_game_in_cutscene},
	{"fast_forward", luags_game_fast_forward},
	{"room_width", luags_game_room_width},
	{"room_height", luags_game_room_height},
	{NULL, NULL}
};

*/
