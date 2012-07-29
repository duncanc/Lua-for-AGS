#include "AGSStructFields.h"
extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
	#include "pluto.h"
	#include "zlib.h"
	#include "malloc.h"
}
#include "llh.h"

AGSGameState* gamestate;

#define DEF_GAMESTATE_GETTER(fname) \
	static int ags_game_get_##fname(lua_State* L) { \
		lua_pushinteger(L, gamestate->fname); \
		return 1; \
	}

#define DEF_GAMESTATE_FIELD(fname) \
	DEF_GAMESTATE_GETTER(fname) \
	static int ags_game_set_##fname(lua_State* L) { \
		gamestate->##fname = (int)luaL_checkinteger(L, 1); \
		return 0; \
	}

#define DEF_GAMESTATE_BOOL_GETTER(fname) \
	static int ags_game_get_##fname(lua_State* L) { \
		lua_pushboolean(L, gamestate->fname); \
		return 1; \
	}

#define DEF_GAMESTATE_BOOL_FIELD(fname) \
	DEF_GAMESTATE_BOOL_GETTER(fname) \
	static int ags_game_set_##fname(lua_State* L) { \
		gamestate->##fname = (int)llh_checkboolean(L, 1); \
		return 0; \
	}

DEF_GAMESTATE_FIELD(score)
DEF_GAMESTATE_FIELD(used_mode)
DEF_GAMESTATE_FIELD(disabled_user_interface)
DEF_GAMESTATE_FIELD(gscript_timer)
DEF_GAMESTATE_BOOL_FIELD(debug_mode)

int ags_game_geti_globalvars(lua_State *L) {
	lua_Integer idx = luaL_checkinteger(L,1);
	if (idx < 0 || idx >= 50) return luaL_error(L, "globalvars index out of range");
	lua_pushinteger(L, gamestate->globalvars[idx]);
	return 1;
}
int ags_game_seti_globalvars(lua_State *L) {
	lua_Integer idx = luaL_checkinteger(L,1);
	if (idx < 0 || idx >= 50) return luaL_error(L, "globalvars index out of range");
	gamestate->globalvars[idx] = (int)luaL_checkinteger(L,2);
	return 0;
}

DEF_GAMESTATE_FIELD(messagetime)
DEF_GAMESTATE_FIELD(usedinv)
DEF_GAMESTATE_FIELD(top_inv_item)
DEF_GAMESTATE_FIELD(num_inv_displayed)
DEF_GAMESTATE_FIELD(num_inv_items)
DEF_GAMESTATE_FIELD(items_per_line)
DEF_GAMESTATE_FIELD(sierra_inv_color)
DEF_GAMESTATE_FIELD(talkanim_speed)
DEF_GAMESTATE_FIELD(inv_item_wid)
DEF_GAMESTATE_FIELD(inv_item_hit)
DEF_GAMESTATE_FIELD(text_shadow_color)
DEF_GAMESTATE_FIELD(swap_portrait)
DEF_GAMESTATE_FIELD(speech_text_gui)
DEF_GAMESTATE_FIELD(following_room_timer)
DEF_GAMESTATE_FIELD(total_score)
DEF_GAMESTATE_FIELD(skip_display)
DEF_GAMESTATE_BOOL_FIELD(no_multiloop_repeat)
DEF_GAMESTATE_FIELD(roomscript_finished)
DEF_GAMESTATE_FIELD(inv_activated)
DEF_GAMESTATE_BOOL_FIELD(no_textbg_when_voice)
DEF_GAMESTATE_FIELD(max_dialogoption_width)
DEF_GAMESTATE_BOOL_FIELD(no_hicolor_fadein)
DEF_GAMESTATE_BOOL_FIELD(bgspeech_game_speed)
DEF_GAMESTATE_BOOL_FIELD(bgspeech_stay_on_display)
DEF_GAMESTATE_BOOL_FIELD(unfactor_speech_from_textlength)
DEF_GAMESTATE_FIELD(mp3_loop_before_end)
DEF_GAMESTATE_FIELD(speech_music_drop)

DEF_GAMESTATE_FIELD(game_speed_modifier)
DEF_GAMESTATE_FIELD(score_sound)
DEF_GAMESTATE_FIELD(previous_game_data)
DEF_GAMESTATE_FIELD(replay_hotkey)
DEF_GAMESTATE_FIELD(dialog_options_x)
DEF_GAMESTATE_FIELD(dialog_options_y)
DEF_GAMESTATE_FIELD(narrator_speech)
DEF_GAMESTATE_BOOL_FIELD(ambient_sounds_persist)
DEF_GAMESTATE_FIELD(lipsync_speed)
DEF_GAMESTATE_FIELD(close_mouth_end_speech_time)
DEF_GAMESTATE_BOOL_FIELD(disable_antialiasing)
DEF_GAMESTATE_FIELD(text_speed_modifier)
DEF_GAMESTATE_FIELD(text_align)
DEF_GAMESTATE_FIELD(speech_bubble_width)
DEF_GAMESTATE_FIELD(min_dialogoption_width)
DEF_GAMESTATE_FIELD(disable_dialog_parser)
DEF_GAMESTATE_FIELD(anim_background_speed)
DEF_GAMESTATE_FIELD(top_bar_backcolor)
DEF_GAMESTATE_FIELD(top_bar_textcolor)
DEF_GAMESTATE_FIELD(top_bar_bordercolor)
DEF_GAMESTATE_FIELD(top_bar_borderwidth)
DEF_GAMESTATE_FIELD(top_bar_ypos)
DEF_GAMESTATE_FIELD(screenshot_width)
DEF_GAMESTATE_FIELD(screenshot_height)
DEF_GAMESTATE_FIELD(top_bar_font)
DEF_GAMESTATE_FIELD(speech_text_align)
DEF_GAMESTATE_BOOL_FIELD(auto_use_walkto_points)
DEF_GAMESTATE_BOOL_FIELD(inventory_greys_out)
DEF_GAMESTATE_FIELD(skip_speech_specific_key)
DEF_GAMESTATE_FIELD(abort_key)
DEF_GAMESTATE_GETTER(fade_color_red)
DEF_GAMESTATE_GETTER(fade_color_green)
DEF_GAMESTATE_GETTER(fade_color_blue)
DEF_GAMESTATE_BOOL_FIELD(show_single_dialog_option)
DEF_GAMESTATE_BOOL_FIELD(keep_screen_during_instant_transition)
DEF_GAMESTATE_FIELD(read_dialog_option_color)
DEF_GAMESTATE_FIELD(stop_dialog_at_end)

void AddGameStateFields(lua_State* L, int IDX_ROOM_LIB)
{
	int IDX_GAME_LIB = lua_gettop(L);
	gamestate = (AGSGameState*)engine->GetGameOptions();

	#define ADD_ALIAS(oldName, newName) { \
		lua_getfield(L, IDX_GAME_LIB, "get_" #oldName); \
		lua_setfield(L, IDX_GAME_LIB, "get_" #newName); \
		lua_getfield(L, IDX_GAME_LIB, "set_" #oldName); \
		lua_setfield(L, IDX_GAME_LIB, "set_" #newName); \
	}
	#define ADD_GAMESTATE_GETTER(name) { \
		lua_pushcfunction(L, ags_game_get_##name); \
		lua_setfield(L, IDX_GAME_LIB, "get_" #name); \
	}
	#define ADD_GAMESTATE_FIELD(name) { \
		ADD_GAMESTATE_GETTER(name); \
		lua_pushcfunction(L, ags_game_set_##name); \
		lua_setfield(L, IDX_GAME_LIB, "set_" #name); \
	}

	ADD_GAMESTATE_FIELD(score);
	ADD_GAMESTATE_FIELD(used_mode);
	ADD_GAMESTATE_FIELD(disabled_user_interface);
	ADD_GAMESTATE_FIELD(gscript_timer);
	ADD_GAMESTATE_FIELD(debug_mode);

	lua_pushcfunction(L, ags_game_geti_globalvars);
	lua_setfield(L, -2, "geti_globalvars");
	lua_pushcfunction(L, ags_game_seti_globalvars);
	lua_setfield(L, -2, "seti_globalvars");

	ADD_GAMESTATE_FIELD(messagetime);
	ADD_GAMESTATE_FIELD(usedinv);
	ADD_GAMESTATE_FIELD(top_inv_item);
	ADD_GAMESTATE_FIELD(num_inv_displayed);
	ADD_GAMESTATE_FIELD(num_inv_items);
	ADD_GAMESTATE_FIELD(items_per_line);
	ADD_ALIAS(TextReadingSpeed, text_speed);
	ADD_GAMESTATE_FIELD(sierra_inv_color);
	ADD_GAMESTATE_FIELD(talkanim_speed);
	ADD_GAMESTATE_FIELD(inv_item_wid);
	ADD_GAMESTATE_FIELD(inv_item_hit);
	ADD_GAMESTATE_FIELD(text_shadow_color);
	ADD_GAMESTATE_FIELD(swap_portrait);
	ADD_GAMESTATE_FIELD(speech_text_gui);
	ADD_GAMESTATE_FIELD(following_room_timer);
	ADD_GAMESTATE_FIELD(total_score);
	ADD_GAMESTATE_FIELD(skip_display);
	ADD_GAMESTATE_FIELD(no_multiloop_repeat);
	ADD_GAMESTATE_FIELD(roomscript_finished);
	ADD_GAMESTATE_FIELD(inv_activated);
	ADD_GAMESTATE_FIELD(no_textbg_when_voice);
	ADD_GAMESTATE_FIELD(max_dialogoption_width);
	ADD_GAMESTATE_FIELD(no_hicolor_fadein);
	ADD_GAMESTATE_FIELD(bgspeech_game_speed);
	ADD_GAMESTATE_FIELD(bgspeech_stay_on_display);
	ADD_GAMESTATE_FIELD(unfactor_speech_from_textlength);
	ADD_GAMESTATE_FIELD(mp3_loop_before_end);
	ADD_GAMESTATE_FIELD(speech_music_drop);
	ADD_ALIAS(InSkippableCutscene, in_cutscene);
	ADD_ALIAS(SkippingCutscene, skipping_cutscene);
	lua_getfield(L, IDX_ROOM_LIB, "get_Width");
	lua_setfield(L, IDX_GAME_LIB, "get_room_width");
	lua_getfield(L, IDX_ROOM_LIB, "get_Height");
	lua_setfield(L, IDX_GAME_LIB, "get_room_height");

	ADD_GAMESTATE_FIELD(game_speed_modifier);
	ADD_GAMESTATE_FIELD(score_sound);
	ADD_GAMESTATE_FIELD(previous_game_data);
	ADD_GAMESTATE_FIELD(replay_hotkey);
	ADD_GAMESTATE_FIELD(dialog_options_x);
	ADD_GAMESTATE_FIELD(dialog_options_y);
	ADD_GAMESTATE_FIELD(narrator_speech);
	ADD_GAMESTATE_FIELD(ambient_sounds_persist);
	ADD_GAMESTATE_FIELD(lipsync_speed);
	ADD_GAMESTATE_FIELD(close_mouth_end_speech_time);
	ADD_GAMESTATE_FIELD(disable_antialiasing);
	ADD_GAMESTATE_FIELD(text_speed_modifier);
	ADD_GAMESTATE_FIELD(text_align);
	ADD_GAMESTATE_FIELD(speech_bubble_width);
	ADD_GAMESTATE_FIELD(min_dialogoption_width);
	ADD_GAMESTATE_FIELD(disable_dialog_parser);
	ADD_GAMESTATE_FIELD(anim_background_speed);
	ADD_GAMESTATE_FIELD(top_bar_backcolor);
	ADD_GAMESTATE_FIELD(top_bar_textcolor);
	ADD_GAMESTATE_FIELD(top_bar_bordercolor);
	ADD_GAMESTATE_FIELD(top_bar_borderwidth);
	ADD_GAMESTATE_FIELD(top_bar_ypos);
	ADD_GAMESTATE_FIELD(screenshot_width);
	ADD_GAMESTATE_FIELD(screenshot_height);
	ADD_GAMESTATE_FIELD(top_bar_font);
	ADD_GAMESTATE_FIELD(speech_text_align);
	ADD_GAMESTATE_FIELD(auto_use_walkto_points);
	ADD_GAMESTATE_FIELD(inventory_greys_out);
	ADD_GAMESTATE_FIELD(skip_speech_specific_key);
	ADD_GAMESTATE_FIELD(abort_key);
	ADD_GAMESTATE_GETTER(fade_color_red);
	ADD_GAMESTATE_GETTER(fade_color_green);
	ADD_GAMESTATE_GETTER(fade_color_blue);
	ADD_GAMESTATE_FIELD(show_single_dialog_option);
	ADD_GAMESTATE_FIELD(keep_screen_during_instant_transition);
	ADD_GAMESTATE_FIELD(read_dialog_option_color);
	ADD_GAMESTATE_FIELD(stop_dialog_at_end);

	#undef ADD_GAMESTATE_GETTER
	#undef ADD_GAMESTATE_FIELD
	#undef ADD_ALIAS
}

#define CHARACTER_UV_META lua_upvalueindex(1)

static int ags_Character_get_wait(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->wait);
	return 1;
};

static int ags_Character_set_wait(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	self2->wait = luaL_checkint(L,2);
	return 0;
};

static int ags_Character_get_on(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushboolean(L, self2->on);
	return 1;
};

static int ags_Character_set_on(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	self2->on = (char)llh_checkboolean(L, 2);
	return 0;
};

static int ags_Character_get_flags(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->flags);
	return 1;
};

static int ags_Character_get_activeinv(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->activeinv);
	return 1;
};

static int ags_Character_set_activeinv(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	self2->activeinv = luaL_checkint(L,2);
	return 0;
};

static int ags_Character_get_walkspeed(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->walkspeed);
	return 1;
};

static int ags_Character_get_scrname(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushstring(L, self2->scrname);
	return 1;
};

static int ags_Character_get_actx(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->actx);
	return 1;
};

static int ags_Character_set_actx(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	self2->actx = luaL_checkint(L,2);
	return 0;
};

static int ags_Character_get_acty(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_pushinteger(L, self2->acty);
	return 1;
};

static int ags_Character_set_acty(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	self2->acty = luaL_checkint(L,2);
	return 0;
};

static int ags_Character_geti_inv(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_Integer idx = luaL_checkint(L,2);
	if (idx < 0 || idx >= (sizeof(self2->inv)/sizeof(short)))
	{
		return luaL_error(L, "inv index out of range");
	}
	lua_pushinteger(L, self2->inv[idx]);
	return 1;
};

static int ags_Character_seti_inv(lua_State *L) {
	AGS_Character* self = luags_checkCharacter(L, 1, CHARACTER_UV_META);
	AGSCharacter* self2 = (AGSCharacter*)self;
	lua_Integer idx = luaL_checkint(L,2);
	if (idx < 0 || idx >= (sizeof(self2->inv)/sizeof(short)))
	{
		return luaL_error(L, "inv index out of range");
	}
	self2->inv[idx] = luaL_checkint(L,3);
	return 0;
};

#undef CHARACTER_UV_META

void AddCharacterStructFields(lua_State *L)
{
	int IDX_CHARACTER_LIB = lua_gettop(L);

	luaL_getmetatable(L, "AGS_Character*");
	int IDX_CHARACTER_META = lua_gettop(L);

	#define ADD_ALIAS(original, alias) { \
		lua_getfield(L, IDX_CHARACTER_LIB, "get_" #original); \
		lua_setfield(L, IDX_CHARACTER_LIB, "get_" #alias); \
		lua_getfield(L, IDX_CHARACTER_LIB, "set_" #original); \
		lua_setfield(L, IDX_CHARACTER_LIB, "set_" #alias); \
	}
	#define ADD_GETTER(name) { \
		lua_pushvalue(L, IDX_CHARACTER_META); \
		lua_pushcclosure(L, ags_Character_get_##name, 1); \
		lua_setfield(L, IDX_CHARACTER_LIB, "get_" #name); \
	}
	#define ADD_FIELD(name) { \
		ADD_GETTER(name) \
		lua_pushvalue(L, IDX_CHARACTER_META); \
		lua_pushcclosure(L, ags_Character_set_##name, 1); \
		lua_setfield(L, IDX_CHARACTER_LIB, "set_" #name); \
	}

	ADD_ALIAS(NormalView, defview);
	ADD_ALIAS(SpeechView, talkview);
	ADD_ALIAS(View, view);
	ADD_ALIAS(Room, room);
	ADD_ALIAS(PreviousRoom, prevroom);
	ADD_FIELD(wait);
	ADD_GETTER(flags);
	ADD_ALIAS(IdleView, idleview);
	ADD_FIELD(activeinv);
	ADD_ALIAS(SpeechColor, talkcolor);
	ADD_ALIAS(ThinkView, thinkview);
	ADD_ALIAS(Loop, loop);
	ADD_ALIAS(Frame, frame);
	ADD_ALIAS(Moving, walking);
	ADD_ALIAS(Animating, animating);
	ADD_GETTER(walkspeed);
	ADD_ALIAS(AnimationSpeed, animspeed);
	{
		lua_pushvalue(L, IDX_CHARACTER_META);
		lua_pushcclosure(L, ags_Character_geti_inv, 1);
		lua_setfield(L, IDX_CHARACTER_LIB, "geti_inv");

		lua_pushvalue(L, IDX_CHARACTER_META);
		lua_pushcclosure(L, ags_Character_seti_inv, 1);
		lua_setfield(L, IDX_CHARACTER_LIB, "seti_inv");
	}
	ADD_FIELD(actx);
	ADD_FIELD(acty);
	ADD_ALIAS(Name, name);
	ADD_GETTER(scrname);
	ADD_FIELD(on);
	#undef ADD_ALIAS
	#undef ADD_GETTER
	#undef ADD_FIELD

	lua_settop(L, IDX_CHARACTER_LIB);
}
