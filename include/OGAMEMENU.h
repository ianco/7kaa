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

//Filename	  : OGAMEMENU.H
//Description : Header file for Game Menu class

#ifndef __OGAMEMENU_H
#define __OGAMEMENU_H

#include <ALL.h>
#include <OCONFIG.h>
#include <OGAMEINFO.h>
#include <OGAMECTL.h>

#pragma pack(1)
class GameMenu
{
public:
	GameMenu();

	void			main_menu();
   void			in_game_menu();
	int			in_game_option_menu();
	void 			game_end(int winNationRecno, int playerDestroyed=0, int surrenderToNationRecno=0, int retireFlag=0);

	int 			select_run_scenario();
	int 			select_scenario(int scenCount, ScenInfo* scenInfoArray);
	int 			run_scenario(ScenInfo* scenInfo);

	void 			demo_disp_ad_page();
	void			demo_disp_logo();

	// ###### begin Gilbert 13/2 #######//
	void 			multi_player_menu(int lobbied, char *game_host);
	// ###### end Gilbert 13/2 #######//

private:
	void			disp_version();
	void			run_main_menu_option(int);
	void 			single_player_menu();
//	void 			multi_player_menu();

	void			single_player_game(int);
	void			multi_player_game(int lobbied, char *game_host);
	void			test_game();
	void			load_mp_game(char *saveFileName, int lobbied, char *game_host);
	void			view_encyclopedia();
	void			view_credits();

	int			input_box(const char *tell_string, char *buf, int len, char hide_input=0);
	int			input_name_pass(const char *txt[], char *name, int name_len, char *pass, int pass_len);

	//------- multiplayer game functions -------//

	int 			mp_select_mode(char *saveGameName, int service_mode);
	int			mp_get_leader_board();
	int			mp_join_session(int session_id);
	void			mp_close_session();
	int			mp_select_option(NewNationPara*, int*);
	int			mp_select_service();
	int			mp_select_session();
	void			mp_disp_players();
	int			mp_select_load_option(char *);
};
#pragma pack()

extern GameMenu game_menu;
extern char game_demo_mode, game_design_mode;

//-------------------------------------//

#endif


