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

//Filename    : AM.CPP
//Description : Ambition Entry Program

#include <ALL.h>
#include <version.h>

#ifdef WIN32
#include <initguid.h>
#endif

#ifdef ENABLE_INTRO_VIDEO
#include <dshow.h>
#endif

#include <OANLINE.h>
#include <OAUDIO.h>
#include <OBATTLE.h>
#include <OBOX.h>
#include <OBULLET.h>
#include <OCONFIG.h>
#include <ODATE.h>
#include <OFIRM.h>
#include <OFLAME.h>
#include <OFONT.h>
#include <OGAMEMENU.h>
#include <OGAMECTL.h>
#include <OGAMEINFO.h>
#include <OGAMESET.h>
#include <OGFILE.h>
#include <OGODRES.h>
#include <OHELP.h>
#include <OHILLRES.h>
#include <OIMGRES.h>
#include <OINFO.h>
#include <OMONSRES.h>
#include <OMOUSE.h>
#include <OMOUSECR.h>
#include <ONATION.h>
#include <ONEWS.h>
#include <OPLANT.h>
#include <OPOWER.h>
#include <ORACERES.h>
#include <OREBEL.h>
#include <OREMOTE.h>
#include <OSPATH.h>
#include <OSITE.h>
#include <OSPREUSE.h>
#include <OSPY.h>
#include <OSYS.h>
#include <OTALKRES.h>
#include <OTECHRES.h>
#include <OTERRAIN.h>
#include <OTOWN.h>
#include <OTownNetwork.h>
#include <OUNIT.h>
#include <OVGA.h>
#include <vga_util.h>
#ifdef ENABLE_INTRO_VIDEO
#include <OVIDEO.h>
#endif
#include <OWALLRES.h>
#include <OWORLD.h>
#include <OWEATHER.h>
#include <OTORNADO.h>
#include <OTUTOR.h>
#include <OSE.h>
#include <OSERES.h>
#include <OSNOWRES.h>
#include <OSNOWG.h>
#include <OROCKRES.h>
#include <OROCK.h>
#include <OEFFECT.h>
#include <OEXPMASK.h>
#include <OREGION.h>
#include <OWARPT.h>
#include <multiplayer.h>
#ifdef HAVE_LIBCURL
#include <WebService.h>
#endif
#include <OERRCTRL.h>
#include <OMUSIC.h>
#include <OLOG.h>
#include <OLONGLOG.h>
//### begin alex 3/10 ###//
#include <OGRPSEL.h>
//#### end alex 3/10 ####//
#include <OFIRMDIE.h>
#include <OCRC_STO.h>
// ###### begin Gilbert 23/10 #######//
#include <OOPTMENU.h>
#include <OINGMENU.h>
// ###### end Gilbert 23/10 #######//
#include <dbglog.h>
#include <locale.h>
#include "gettext.h"

//#include <OGAMESTATE.h>

char 	new_config_dat_flag=0;

//-------- System class ----------//

DBGLOG_DEFAULT_CHANNEL(am);

//------- Define static functions --------//

static void extra_error_handler();

/* Override obstinate SDL hacks */
#ifdef __WINE__
# ifdef main
#   undef main
# endif
#endif

#if (WIN32 && !USE_SDL)
// Prototype main since the runtime does not do that for us
int main(int, char**);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return main(__argc, __argv);
}
#endif

//---------- Begin of function main ----------//
//
// Compilation constants:
//
// DEBUG  - normal debugging
// DEBUG2 - shortest path searching and unit action debugging
// DEBUG3 - debugging some functions (e.g. Location::get_loc()) which
//          will cause major slowdown.
//
// Command line paramters:
// -join <named or ip address>
//   Begin the program by attempting to connect to the specified address.
// -host
//   Begin the program by hosting a multiplayer match
// -name <player name>
//   Set the name you wish to be known as.
//
// You cannot specify -join or -host more than once.
//
int main(int argc, char **argv)
{
#ifdef ENABLE_NLS
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALE_PATH);
	textdomain(PACKAGE);
#endif

	const char *lobbyJoinCmdLine = "-join";
	const char *lobbyHostCmdLine = "-host";
	const char *lobbyNameCmdLine = "-name";
	const char *demoCmdLine = "-demo";
	const char *demoSpeedCmdLine = "-speed";
	char *join_host = NULL;
	int lobbied = 0;
	int demoSelection = 0;
	int demoSpeed = 99;

#if defined(DEBUG) && defined(ENABLE_LOG)
	//String logLine("startup 7kaa ... ");
	LOG_MSG("AM::startup 7kaa ...");
	LOG_DUMP;
#endif

	sys.set_config_dir();

	//try to read from CONFIG.DAT, moved to AM.CPP

	if( !config.load("CONFIG.DAT") )
	{
		new_config_dat_flag = 1;
		config.init();
		config.save("CONFIG.DAT");
	}

	//----- read command line arguments -----//

	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], lobbyJoinCmdLine)) {
			if (lobbied) {
				sys.show_error_dialog(_("You cannot specify multiple -host or -join options."));
				return 1;
			}
			if (i >= argc - 1) {
				sys.show_error_dialog(_("Expected argument after %s."), lobbyJoinCmdLine);
				return 1;
			}
			lobbied = 1;
			join_host = argv[i+1];
			i++;
		} else if (!strcmp(argv[i], lobbyHostCmdLine)) {
			if (lobbied) {
				sys.show_error_dialog(_("You cannot specify multiple -host or -join options."));
				return 1;
			}
			lobbied = 1;
		} else if (!strcmp(argv[i], lobbyNameCmdLine)) {
			if (i >= argc - 1) {
				sys.show_error_dialog(_("Expected argument after %s."), lobbyNameCmdLine);
				return 1;
			}
			strncpy(config.player_name, argv[i+1], config.PLAYER_NAME_LEN);
			config.player_name[config.PLAYER_NAME_LEN] = 0;
			i++;
		} else if (!strcmp(argv[i], demoCmdLine)) {
			demoSelection = 1;
		} else if (!strcmp(argv[i], demoSpeedCmdLine)) {
			if (i >= argc - 1) {
				sys.show_error_dialog(_("Expected argument after %s."), demoSpeedCmdLine);
				return 1;
			}
			demoSpeed = atoi(argv[i+1]);
			i++;
		}
	}

#ifdef ENABLE_INTRO_VIDEO
	//----------- play movie ---------------//

	if (!sys.set_game_dir())
		return 1;

	if (!lobbied && !demoSelection)
	{
		String movieFileStr;
		movieFileStr = DIR_MOVIE;
		movieFileStr += "INTRO.AVI";

		video.set_skip_on_fail();

		// ###### begin Gilbert 29/10 #####//
		if( !misc.is_file_exist("SKIPAVI.SYS") && misc.is_file_exist(movieFileStr) )
		// ###### end Gilbert 29/10 #####//
		{
			//---------- play the movie now ---------//

			video.init();

			if( video.init_success )
			{
				video.play_until_end( movieFileStr, hInstance, 60 );
			}
			else
			{
				// display a message box (note:sys.main_hwnd is not valid)
				// MessageBox( NULL, "Cannot initialize ActiveMovie",
				//   "Seven Kingdoms", MB_OK | MB_ICONWARNING | MB_DEFBUTTON1 | MB_TASKMODAL );
			}

			video.deinit();
		}
	}
#endif // ENABLE_INTRO_VIDEO

	if( !sys.init() )
		return 1;

	err.set_extra_handler( extra_error_handler );   // set extra error handler, save the game when a error happens

	if (!lobbied && !demoSelection)
		game_menu.main_menu();
#ifndef DISABLE_MULTI_PLAYER
	else if (!demoSelection)
		game_menu.multi_player_menu(lobbied, join_host);
#endif // DISABLE_MULTI_PLAYER
	else if (!lobbied)
	{
		mouse_cursor.set_icon(CURSOR_NORMAL);
		sys.set_speed(demoSpeed);
		sys.disp_fps_flag = 1;
		config.help_mode = NO_HELP;
		game_info.game_mode = GAME_DEMO;
		game_ctl.init();
#ifdef HEADLESS_SIM
		info.init_random_seed(0);
		battle.run(0);
#else
		battle.run_test();
#endif
		game_ctl.deinit();
	}

	sys.deinit();

	return 0;
}
//---------- End of function main ----------//


//------- Begin of function extra_error_handler -----------//

static void extra_error_handler()
{
	if( game_info.game_mode != GAME_SINGLE_PLAYER )
		return;

	game_file_array.save_new_game("ERROR.SAV");  // save a new game immediately without prompting menu

	box.msg( "Error encountered. The game has been saved to ERROR.SAV" );
}
//----------- End of function extra_error_handler -------------//
