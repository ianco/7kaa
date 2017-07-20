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

//Filename	  : OSYSINFO.H
//Description : Header file for Game info class

#ifndef __OSYSINFO_H
#define __OSYSINFO_H

#include <ALL.h>
#include <stdint.h>

//------ Define common data buffer size  ------//

enum { COMMON_DATA_BUF_SIZE = 64*1024 };			// keep a 64K common buffer for all temporary memory storage like reading files temporarily into memory

//-------------- define constant ------------//

#define FRAMES_PER_DAY	10			// no. of frames per day

#define MAX_SCENARIO_PATH 2


//------------ sys_flag --------------//

enum { SYS_PREGAME=0, SYS_RUN };

//--------- game version ---------//

enum { VERSION_FULL,
		 VERSION_DEMO,
		 VERSION_MULTIPLAYER_ONLY };

//--------- Define info modes --------//

enum { VIEW_MODE_COUNT=10 };

enum { MODE_NORMAL,
		 MODE_NATION,
		 MODE_TOWN,
		 MODE_ECONOMY,
		 MODE_TRADE,
		 MODE_MILITARY,
		 MODE_TECH,
		 MODE_SPY,
		 MODE_RANK,
		 MODE_NEWS_LOG,
		 MODE_AI_ACTION,
	  };

//### begin alex 11/8 ###//
//------------------ define debug_seed_status_flag ----------------//
enum	{	NO_DEBUG_SYN = 0,
			DEBUG_SYN_LOAD_AND_COMPARE_ONCE,
			DEBUG_SYN_AUTO_SAVE,
			DEBUG_SYN_AUTO_LOAD,
		};
//#### end alex 11/8 ####//

//-------- Define class SysInfo -----------//

class SysInfo
{
public:
	char		game_version;			// VERSION_???

	char		sys_flag;
	char		init_flag;
	char		signal_exit_flag; // 0 - not exiting; 1 - exit to OS; 2 - exit to main menu
	char		need_redraw_flag;    // set to 1 if task switched back. After redraw, clear it
	char		toggle_full_screen_flag;
	char		cheat_enabled_flag;
	char		user_pause_flag;
	char		disp_fps_flag;

	char 		view_mode;				// the view mode can be MODE_???

	char		map_need_redraw;
	char		zoom_need_redraw;

	//------ frame related vars -----//

	int 		day_frame_count;
	uint32_t	next_frame_time;		// next frame's time for maintaining a specific game speed

	//----- multiplayer vars ----//

	char		is_mp_game;
	uint32_t 	frame_count;  			// frame count, for is_sync_frame only
	char		is_sync_frame;			// whether sync should take place at the current frame (for handling one sync per n frames)
	char		mp_save_flag;			// indicate a request to save game in multi-player game
	uint32_t	mp_save_frame;			// save game in which frame

	//---- continous key string -----//

	enum { MAX_KEY_STR = 10 };       // Maximum 10 different key string

	int  key_str_pos[MAX_KEY_STR];  // for detecting cheating codes

	//-------- statistic --------//

	uint32_t	last_second_time;
	int		frames_in_this_second;
	int	 	frames_per_second;   // the actual frames per second

	//------- file paths -------//

	char  	cdrom_drive;

	char    dir_config[MAX_PATH+1];
	char  	dir_image[MAX_PATH+1];
	char  	dir_encyc[MAX_PATH+1];
	char  	dir_encyc2[MAX_PATH+1];
	char  	dir_music[MAX_PATH+1];
	char  	dir_movie[MAX_PATH+1];
	char  	dir_tutorial[MAX_PATH+1];

	union
	{
		char dir_scenario[MAX_PATH+1];
		char dir_scenario_path[MAX_SCENARIO_PATH][MAX_PATH+1];
	};

	//------- other vars --------//

	char*		common_data_buf;
	char		debug_session;
	char		testing_session;

public:
	//-------- for load/save games --------//

	int 		write_file(File* filePtr);
	int		read_file(File* filePtr);

};

extern SysInfo sys_info;

//-------------------------------------//

#endif


