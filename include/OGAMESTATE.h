/*
 * Seven Kingdoms: Ancient Adversaries
 *
 * Copyright 1997,1998 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

//Filename    : OGAMESTATE.H
//Description : Header file of global objects
//Owner		  : Ian

#ifndef __OGAMESTATE_H
#define __OGAMESTATE_H

//------ define global variables ------//

#ifndef NO_MEM_CLASS
   Mem   mem;              // constructor only init var and allocate memory
#endif

Error             err;              // constructor only call set_new_handler()d
Mouse             mouse;
MouseCursor       mouse_cursor;
Misc              misc, misc2;
DateInfo          date;
Vga               vga;
VgaUtil           vga_util;
VgaBuf            vga_front, vga_back, vga_true_front;
#ifdef ENABLE_INTRO_VIDEO
Video             video;
#endif
Audio             audio;
Music             music;
MultiPlayer       mp_obj;
#ifdef HAVE_LIBCURL
WebService        ws;
#endif
Sys               sys;
SysInfo           sys_info;
SeekPath          seek_path;
SeekPathReuse     seek_path_reuse;
Flame             flame[FLAME_GROW_STEP];
Remote            remote;
ErrorControl      ec_remote;
AnimLine          anim_line;
SECtrl            se_ctrl(&audio);
SERes             se_res;
Log               msg_log;
#ifdef DEBUG
LongLog *			long_log;
#endif
//### begin alex 3/10 ###//
GroupSelect			group_select;
//#### end alex 3/10 ####//

//------- Resource class ----------//

Font              font_san, font_std, font_small, font_mid, font_news;
Font              font_hitpoint, font_bible, font_bard;

#if( defined(GERMAN) || defined(FRENCH) || defined(SPANISH) )
Font					font_hall;
#endif

Box               box;
ImageRes          image_icon, image_interface, image_menu,
						image_button, image_spict;
ImageRes          image_encyc;
ImageRes				image_tpict;
ImageRes				image_tutorial;
ImageRes				image_menu_plus;
ImageRes&			image_menu2 = image_menu_plus;
SpriteRes         sprite_res;
SpriteFrameRes    sprite_frame_res;
UnitRes           unit_res;
TerrainRes        terrain_res;
PlantRes          plant_res;
WallRes           wall_res;
RawRes            raw_res;
FirmRes           firm_res;
FirmDieRes			firm_die_res;
RaceRes           race_res;
TownRes           town_res;
HillRes           hill_res;
TalkRes           talk_res;
TechRes           tech_res;
GodRes            god_res;
MonsterRes        monster_res;
SnowRes           snow_res;
RockRes           rock_res;
ExploredMask      explored_mask;
Help              help;
Tutor             tutor;

//-------- Game Data class -----------//

UnitArray         unit_array(100);        // 100-initial array size
BulletArray       bullet_array(100);
SiteArray         site_array;
TownArray         town_array;
TownNetworkArray  town_network_array;
NationArray       nation_array;
FirmArray         firm_array;
FirmDieArray	  firm_die_array;
TornadoArray      tornado_array(10);
RebelArray        rebel_array;
SpyArray          spy_array;
SnowGroundArray   snow_ground_array;
RockArray         rock_array;
RockArray         dirt_array;
SpriteArray       effect_array(50);
RegionArray       region_array;
NewsArray         news_array;
WarPointArray     war_point_array;
CrcStore				crc_store;

//--------- Game Surface class ------------//

Info              info;
Weather           weather, weather_forecast[MAX_WEATHER_FORECAST];
MagicWeather      magic_weather;
Config            config;
GameInfo          game_info;
GameMenu          game_menu;
GameCtl           game_ctl;
GameSet           game_set;         // no constructor
Battle            battle;
Power             power;
World             world;
GameFileArray     game_file_array;
GameFile          game_file;
// ###### begin Gilbert 23/10 #######//
OptionMenu			option_menu;
InGameMenu			in_game_menu;
// ###### end Gilbert 23/10 #######//

//----------- Global Variables -----------//

char game_design_mode=0;
char game_demo_mode=0;
char debug2_enable_flag=0;
File seedCompareFile;
char debug_seed_status_flag=0;
int  debug_sim_game_type = 0;
int  unit_search_node_used=0;
short nation_hand_over_flag=0;
int     unit_search_tries = 0;        // the number of tries used in the current searching
char    unit_search_tries_flag = 0;   // indicate num of tries is set, reset after searching

//char 	new_config_dat_flag=0;

#ifdef DEBUG
int check_unit_dir1, check_unit_dir2;
unsigned long	last_unit_ai_profile_time = 0L;
unsigned long	unit_ai_profile_time = 0L;
unsigned long	last_unit_profile_time = 0L;
unsigned long	unit_profile_time = 0L;
unsigned long seek_path_profile_time = 0L;
unsigned long last_seek_path_profile_time = 0L;
unsigned long last_sprite_array_profile_time = 0L;
unsigned long sprite_array_profile_time = 0L;
unsigned long last_sprite_idle_profile_time = 0L;
unsigned long sprite_idle_profile_time = 0L;
unsigned long last_sprite_move_profile_time = 0L;
unsigned long sprite_move_profile_time = 0L;
unsigned long last_sprite_wait_profile_time = 0L;
unsigned long sprite_wait_profile_time = 0L;
unsigned long last_sprite_attack_profile_time = 0L;
unsigned long sprite_attack_profile_time = 0L;
unsigned long last_unit_attack_profile_time = 0L;
unsigned long unit_attack_profile_time = 0L;
unsigned long last_unit_assign_profile_time = 0L;
unsigned long unit_assign_profile_time = 0L;
#endif

const char *msg_names[] = {
		"FIRST_REMOTE_MSG_ID",
		"MSG_QUEUE_TRAILER",
		"MSG_NEW_NATION",
		"MSG_UPDATE_GAME_SETTING",
		"MSG_START_GAME",
		"MSG_NEXT_FRAME",
		"MSG_REQUEST_RESEND",
		"MSG_TELL_SEND_TIME",
		"MSG_SET_SPEED",
		"MSG_TELL_RANDOM_SEED",
		"MSG_REQUEST_SAVE",
		"MSG_PLAYER_QUIT",

		"MSG_UNIT_STOP",
		"MSG_UNIT_MOVE",
		"MSG_UNIT_SET_FORCE_MOVE",
		"MSG_UNIT_ATTACK",
		"MSG_UNIT_ASSIGN",
		"MSG_UNIT_CHANGE_NATION",
		"MSG_UNIT_BUILD_FIRM",
		"MSG_UNIT_BURN",
		"MSG_UNITS_SETTLE",
		"MSG_UNIT_SET_GUARD",
		"MSG_UNIT_SET_RANK",
		"MSG_UNIT_DISMOUNT",
		"MSG_UNIT_REWARD",
		"MSG_UNITS_TRANSFORM",
		"MSG_UNIT_RESIGN",
		"MSG_UNITS_ASSIGN_TO_SHIP",
		"MSG_UNITS_SHIP_TO_BEACH",
		"MSG_UNIT_SUCCEED_KING",
		"MSG_UNITS_RETURN_CAMP",
		"MSG_U_CARA_CHANGE_GOODS",
		"MSG_U_CARA_SET_STOP",
		"MSG_U_CARA_DEL_STOP",
		"MSG_U_CARA_SELECTED",
		"MSG_U_SHIP_UNLOAD_UNIT",
		"MSG_U_SHIP_UNLOAD_ALL_UNITS",
		"MSG_U_SHIP_CHANGE_GOODS",
		"MSG_U_SHIP_SET_STOP",
		"MSG_U_SHIP_DEL_STOP",
		"MSG_U_SHIP_CHANGE_MODE",
		"MSG_U_SHIP_SELECTED",
		"MSG_U_GOD_CAST",
		"MSG_UNIT_SPY_NATION",
		"MSG_UNIT_SPY_NOTIFY_CLOAKED_NATION",
		"MSG_UNIT_CHANGE_AGGRESSIVE_MODE",
		"MSG_SPY_CHANGE_NOTIFY_FLAG",

		//##### trevor 15/10 ######//
		"MSG_SPY_ASSASSINATE",
		//##### trevor 15/10 ######//

		//### begin alex 14/10 ###//
		"MSG_UNIT_ADD_WAY_POINT",
		//#### end alex 14/10 ####//

		"MSG_FIRM_SELL",
		"MSG_FIRM_CANCEL",
		"MSG_FIRM_DESTRUCT",
		"MSG_FIRM_SET_REPAIR",
		"MSG_FIRM_TRAIN_LEVEL",
		"MSG_FIRM_MOBL_WORKER",
		"MSG_FIRM_MOBL_ALL_WORKERS",
		"MSG_FIRM_MOBL_OVERSEER",
		"MSG_FIRM_MOBL_BUILDER",
		"MSG_FIRM_TOGGLE_LINK_FIRM",
		"MSG_FIRM_TOGGLE_LINK_TOWN",
		"MSG_FIRM_PULL_TOWN_PEOPLE",
		"MSG_FIRM_SET_WORKER_HOME",
		"MSG_FIRM_BRIBE",
		"MSG_FIRM_CAPTURE",

		//### trevor 2/10 ###//
		"MSG_FIRM_REWARD",
		"MSG_F_CAMP_PATROL",
		"MSG_F_CAMP_TOGGLE_PATROL",
		"MSG_F_INN_HIRE",
		//### trevor 2/10 ###//
		"MSG_F_MARKET_SCRAP",
		"MSG_F_MARKET_HIRE_CARA",
		"MSG_F_RESEARCH_START",
		"MSG_F_WAR_BUILD_WEAPON",
		"MSG_F_WAR_CANCEL_WEAPON",
		"MSG_F_WAR_SKIP_WEAPON",
		"MSG_F_HARBOR_BUILD_SHIP",
		"MSG_F_HARBOR_SAIL_SHIP",
		"MSG_F_HARBOR_SKIP_SHIP",
		"MSG_F_FACTORY_CHG_PROD",
		"MSG_F_BASE_MOBL_PRAYER",
		"MSG_F_BASE_INVOKE_GOD",

		"MSG_TOWN_RECRUIT",
		"MSG_TOWN_SKIP_RECRUIT",
		"MSG_TOWN_MIGRATE",
		"MSG_TOWN_COLLECT_TAX",
		"MSG_TOWN_REWARD",
		"MSG_TOWN_TOGGLE_LINK_FIRM",
		"MSG_TOWN_TOGGLE_LINK_TOWN",
		"MSG_TOWN_AUTO_TAX",
		"MSG_TOWN_AUTO_GRANT",
		"MSG_TOWN_GRANT_INDEPENDENT",

		"MSG_WALL_BUILD",
		"MSG_WALL_DESTRUCT",

		"MSG_SPY_CYCLE_ACTION",
		"MSG_SPY_LEAVE_TOWN",
		"MSG_SPY_LEAVE_FIRM",
		"MSG_SPY_CAPTURE_FIRM",
		"MSG_SPY_DROP_IDENTITY",
		"MSG_SPY_REWARD",
		"MSG_SPY_EXPOSED",

		"MSG_SEND_TALK_MSG",			// for diplomacy
		"MSG_REPLY_TALK_MSG",
		"MSG_NATION_CONTACT",
		"MSG_NATION_SET_SHOULD_ATTACK",
		"MSG_CHAT",

		"MSG_COMPARE_NATION",
		"MSG_COMPARE_UNIT",
		"MSG_COMPARE_FIRM",
		"MSG_COMPARE_TOWN",
		"MSG_COMPARE_BULLET",
		"MSG_COMPARE_REBEL",
		"MSG_COMPARE_SPY",
		"MSG_COMPARE_TALK",

		"LAST_REMOTE_MSG_ID"			// keep this item last
};


//------- define game version constant --------//

	const char *GAME_VERSION_STR = SKVERSION;
	const int GAME_VERSION = 212;	// Version 2.00, don't change it unless the format of save game files has been changed

//----------- Define class GameState -----------//

#pragma pack(1)
class GameState 
{
	void		load_from_json( std::string sjson );
	std::string	convert_to_json();
};

//-----------------------------------------//

#endif  // __OGAMESTATE_H

