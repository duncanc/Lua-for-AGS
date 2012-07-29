
#include "AGSLua.h"

// more up-to-date version than in agsplugin.h
typedef struct AGSGameState {
  int score;
  int used_mode;
  int disabled_user_interface;
  int gscript_timer;
  int debug_mode;
  int globalvars[50];
  int messagetime;
  int usedinv;
  int top_inv_item;
  int num_inv_displayed;
  int num_inv_items;
  int items_per_line;
  int text_speed;
  int sierra_inv_color;
  int talkanim_speed;
  int inv_item_wid;
  int inv_item_hit;
  int text_shadow_color;
  int swap_portrait;
  int speech_text_gui;
  int following_room_timer;
  int total_score;
  int skip_display;
  int no_multiloop_repeat;
  int roomscript_finished;
  int inv_activated;
  int no_textbg_when_voice;
  int max_dialogoption_width;
  int no_hicolor_fadein;
  int bgspeech_game_speed;
  int bgspeech_stay_on_display;
  int unfactor_speech_from_textlength;
  int mp3_loop_before_end;
  int speech_music_drop;
  int in_cutscene; // readonly
  int skipping_cutscene; // readonly
  int room_width; // readonly
  int room_height; // readonly

  int game_speed_modifier;
  int score_sound;
  int previous_game_data;
  int replay_hotkey;
  int dialog_options_x;
  int dialog_options_y;
  int narrator_speech;
  int ambient_sounds_persist;
  int lipsync_speed;
  int close_mouth_end_speech_time;
  int disable_antialiasing;
  int text_speed_modifier;
  int text_align;
  int speech_bubble_width;
  int min_dialogoption_width;
  int disable_dialog_parser;
  int anim_background_speed;
  int top_bar_backcolor;
  int top_bar_textcolor;
  int top_bar_bordercolor;
  int top_bar_borderwidth;
  int top_bar_ypos;
  int screenshot_width;
  int screenshot_height;
  int top_bar_font;
  int speech_text_align;
  int auto_use_walkto_points;
  int inventory_greys_out;
  int skip_speech_specific_key;
  int abort_key;
  int fade_color_red; // readonly
  int fade_color_green; // readonly
  int fade_color_blue; // readonly
  int show_single_dialog_option;
  int keep_screen_during_instant_transition;
  int read_dialog_option_color;
  int stop_dialog_at_end;
} AGSGameState;
extern AGSGameState* gamestate;

void AddGameStateFields(lua_State* L, int IDX_ROOM_LIB);
void AddCharacterStructFields(lua_State* L);
