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

//Filename	  : OSYS.H
//Description : Header file for Game class

#ifndef __OSYS_H
#define __OSYS_H

#include <ALL.h>
#include <stdint.h>
#include <OSYSINFO.h>


//-------- Define class Sys -----------//

class Sys
{
public:
	Sys();
	~Sys();

	int		init();
	void		deinit();
	void		deinit_directx();
	void		deinit_objects();

	void		run(int=0);
	void		yield();
	void		yield_wsock_msg();

	void 		set_speed(int frameSpeed, int remoteCall=0);
	void 		set_view_mode(int viewMode, int viewingNationRecno=0, int viewingSpyRecno=0);
	// ##### begin Gilbert 22/10 #######//
	void		disp_view_mode(int observeMode=0);
	// ##### end Gilbert 22/10 #######//
	void		capture_screen();

	void 		disp_frame();
	void 		blt_virtual_buf();

	void		pause();
	void		unpause();

	void		show_error_dialog(const char *formatStr, ...);

	void		mp_request_save(DWORD frame);
	void		mp_clear_request_save();

	//-------------- single player syn. game testing functions --------------//
	void		sp_create_seed_file(char *filename);
	void		sp_close_seed_file();
	void		sp_load_seed_file();
	void		sp_record_match_seed();
	void		sp_record_seed();
	void		sp_write_seed();
	void		sp_compare_seed();
	void		sp_seed_pos_reset();
	void		sp_seed_pos_set(int pos);

	//---- for setting game directories ----//

	int 		set_config_dir();
	int		chdir_to_game_dir();
	int		set_game_dir();

	//-------- for load/save games --------//

	void		save_game();
	void		load_game();

	int 		init_objects();
	int 		init_directx_internal();

private:
	int		init_directx();
//	int 		init_objects();

	void		main_loop(int);
	void		detect();
	void		process();

	void		disp_button();
	void 		detect_button();

	void		disp_view();
	void		update_view();
	void		detect_view();

	void 		disp_map();
	void 		disp_zoom();

	int		should_next_frame();
	int		is_mp_sync( int *unreadyPlayerFlag );
	void		auto_save();

	void 		blt_next_frame();
	void		disp_frames_per_second();

	void		process_key(unsigned scanCode, unsigned skeyState);

	void		detect_letter_key(unsigned scanCode, unsigned skeyState);
	void		detect_function_key(unsigned scanCode, unsigned skeyState);
	void		detect_cheat_key(unsigned scanCode, unsigned skeyState);
	int			detect_debug_cheat_key(unsigned scanCode, unsigned skeyState);
	int 		detect_set_speed(unsigned scanCode, unsigned skeyState);

	int 		detect_key_str(int keyStrId, const char* keyStr);
};

extern Sys sys;
#ifdef DEBUG
extern char debug2_enable_flag;
extern File seedCompareFile;
//### begin alex 11/8 ###//
extern char debug_seed_status_flag;
//#### end alex 11/8 ####//
extern int	debug_sim_game_type;
#endif

//-------------------------------------//

#endif


