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

//Filename	  : OGAMEINFO.H
//Description : Header file for Game Info class

#ifndef __OGAMEINFO_H
#define __OGAMEINFO_H

#include <ALL.h>
#include <OCONFIG.h>

//-------- Define game modes -----------//

enum { GAME_PREGAME=1,
		 GAME_SINGLE_PLAYER,		// game_mode is set once the player clicks an option on the screen, the game doesn't have to be actually running.
		 GAME_TUTORIAL,
		 GAME_TEST,
		 GAME_MULTI_PLAYER,
		 GAME_CAMPAIGN,
		 GAME_ENCYCLOPEDIA,
		 // ####### begin Gilbert 2/9 ######//
		 GAME_CREDITS,
		 // ####### end Gilbert 2/9 ######//
		 GAME_DEMO
	  };

//--------- Define struct ColorRemapMethod ----------//

struct ColorRemapMethod
{
	int	primary_color;
	int	secondary_color;
};

//--------- Define struct ColorRemap ----------//

#pragma pack(1)
struct ColorRemap
{
public:
	char  main_color;
	char	color_table[256];

public:
	void	set_remap_color(ColorRemapMethod*);
   void	load(char*);
};
#pragma pack()

//----- define struct ScenInfo -------//

struct ScenInfo
{
	enum { SCEN_NAME_LEN=80 };

	char* 	file_name;
	char  	scen_name[SCEN_NAME_LEN+1];
	char		dir_id;			// real path look from DIR_SCENARIO_PATH(dir_id)
	short		goal_difficulty;
	short 	goal_score_bonus;
};

//-------- Define class Game -----------//

struct Location;
struct NewNationPara;

#pragma pack(1)
class GameInfo
{
public:
	char			init_flag;
	char			started_flag;
	char			game_mode;
	char			game_has_ended;		// whether game_end() has been called once already and the player is now just staying in the game to continue to play or observe

	//-------- color remap info -------//

	ColorRemap	color_remap_array[MAX_COLOR_SCHEME+1];

public:
	GameInfo();

	char*			get_color_remap_table(int nationRecno, int selectedFlag);
	// ###### begin Gilbert 24/10 #######//
	static void	disp_gen_map_status( int curStep, int maxStep, int section );
	// ###### end Gilbert 24/10 #######//

	int 			write_file(File* filePtr);
	int			read_file(File* filePtr);

private:
	void			init_remap_table();

};
#pragma pack()

extern GameInfo game_info;
extern char game_demo_mode, game_design_mode;

//-------------------------------------//

#endif


