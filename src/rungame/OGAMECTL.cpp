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

//Filename   : OGAMCTL.CPP
//Description: In Game Control functions

#include <ALL.h>
#include <KEY.h>
#include <OVGA.h>
#include <vga_util.h>
#include <OSYS.h>
#include <OMOUSE.h>
#include <OMOUSECR.h>
#include <OPOWER.h>
#include <OBOX.h>
#include <OFONT.h>
#include <OIMGRES.h>
#include <OINFO.h>
#include <OGAMECTL.h>
#include <OGAMEINFO.h>
#include <ONATION.h>
#include <OCONFIG.h>
#include <ORACERES.h>
#include <OBUTT3D.h>
#include <OBUTTCUS.h>
#include <OCOLTBL.h>
#include <OMUSIC.h>
#include <OSLIDCUS.h>
#include <OAUDIO.h>
#include <OREMOTE.h>
#include <OTUTOR.h>
#include <OOPTMENU.h>
#include <COLCODE.h>
#include <OFONT.h>
#include <OBUTTON.h>
#include <OUNITALL.h>
#include <OBULLET.h>
#include <OTERRAIN.h>
#include <OPLANT.h>
#include <OWORLD.h>
#include <OPOWER.h>
#include <OSITE.h>
#include <ORACERES.h>
#include <OWALLRES.h>
#include <OTECHRES.h>
#include <OGODRES.h>
#include <OMONSRES.h>
#include <OTOWN.h>
#include <OTownNetwork.h>
#include <ONATION.h>
#include <OFIRM.h>
#include <OSPRITE.h>
#include <OGAMESET.h>
#include <OGAMEINFO.h>
#include <OREBEL.h>
#include <OSPY.h>
#include <OBATTLE.h>
#include <ONEWS.h>
#include <OWEATHER.h>
#include <OHILLRES.h>
#include <OTALKRES.h>
#include <OSNOWRES.h>
#include <OSNOWG.h>
#include <OEXPMASK.h>
#include <OSE.h>
#include <OSERES.h>
#include <OROCKRES.h>
#include <OROCK.h>
#include <OEFFECT.h>
#include <OAUDIO.h>
#include <OMUSIC.h>
#include <OTORNADO.h>
#include <OWARPT.h>
// ##### begin Gilbert 2/10 #######//
#include <OFIRMDIE.h>
// ##### end Gilbert 2/10 #######//


//-------- Begin of function GameCtl::GameCtl --------//
//
GameCtl::GameCtl()
{
	// t.b.d. nothing for now
}
//--------- End of function GameCtl::GameCtl ---------//


//-------- Begin of function GameCtl::init --------//
//
// Note: all functions called in this function cannot call
//			misc.random(). Otherwise, it will cause random seed
//		   sync error.
//
// [int] loadGameCall - weather this function is called
//                      when a game is being loaded
//                      (default: 0)
//
int GameCtl::init(int loadGameCall)
{
   if( game_info.init_flag )
		deinit();

	music.stop();

	// ----- set waiting cursor -------- //
	int oldCursor = mouse_cursor.get_icon();
	mouse_cursor.set_icon(CURSOR_WAITING);

	int iret = init_internal(loadGameCall);

	// ----- restore from waiting cursor -------- //

	mouse_cursor.restore_icon(oldCursor);

	game_info.game_has_ended = 0;

	game_info.init_flag=1;

	return iret;
}
//--------- End of function GameCtl::init ---------//

int GameCtl::init_internal(int loadGameCall)
{
	int originalRandomSeed = misc.get_random_seed();

	//------- init game data class ---------//

	game_set.open_set(1);             // open the default game set

	char tpictFile[] = DIR_RES"I_TPICT?.RES";
	*(strstr( tpictFile, "?")) = '0' + config.terrain_set;
	image_tpict.init(tpictFile,1,0);		// config.terrain_set dependent, must load before town_res.init and terrain_res.init
	terrain_res.init();
	plant_res.init();
	tech_res.init();
	god_res.init();

	sprite_res.init();                              // sprite resource object must been initialized after game_set as it relies on game_set for info.
	sprite_frame_res.init();
	unit_res.init();
   monster_res.init();

	raw_res.init();
	race_res.init();
	firm_res.init();
	// ##### begin Gilbert 2/10 #######//
	firm_die_res.init();
	// ##### end Gilbert 2/10 #######//
	town_res.init();
	hill_res.init();
	snow_res.init();
	rock_res.init();
	explored_mask.init(vga.vga_color_table);
   se_res.init1();
	se_res.init2(&se_ctrl);
	talk_res.init();

	//------- init game data class ---------//

	nation_array.init();
	firm_array.init();
	// ##### begin Gilbert 2/10 #######//
	firm_die_array.init();
	// ##### end Gilbert 2/10 #######//
	town_array.init();
	town_network_array.init();
	unit_array.init();
	bullet_array.init();
	rebel_array.init();
	spy_array.init();
	site_array.init();
	rock_array.init();
	dirt_array.init();
	effect_array.init();
	tornado_array.init();
	war_point_array.init();

   //------ init game surface class ----------//

	power.init();
   world.init();
   battle.init();
   news_array.init();

	if( !loadGameCall )
		info.init();   // it reads in the panel texture and copy it to vga_back's buffer

   //---------------------------------------------//

	int quakeFreq;

	if( config.random_event_frequency )
	{
		quakeFreq = 2000 - config.random_event_frequency * 400
						+ info.random_seed%300;
	}
	else
	{
		quakeFreq = 0x0fffffff;
	}

	weather.init_date(info.game_year, info.game_month, info.game_day, config.latitude, quakeFreq);

	//---------------------------------------------//

	weather_forecast[0] = weather;
   weather_forecast[0].next_day();

   for(int foreDay=1; foreDay < MAX_WEATHER_FORECAST; ++foreDay)
   {
      weather_forecast[foreDay] = weather_forecast[foreDay-1];
      weather_forecast[foreDay].next_day();
	}

	snow_ground_array.init(weather.snow_scale(), info.game_year);

	//------------ run demo ------------//

	err_when( originalRandomSeed != misc.get_random_seed() );

	return TRUE;
}
//--------- End of function GameCtl::init_internal ---------//


//-------- Begin of function GameCtl::deinit --------//
//
// [int] loadGameCall - weather this function is called
//                      when a game is being loaded
//                      (default: 0)
//
void GameCtl::deinit(int loadGameCall)
{
	if( !game_info.init_flag )
		return;

	power.disable();     // disable power, which handle mouse inputs

	music.stop();
	audio.stop_wav();

	//----- set waiting cursor -------- //

	int oldCursor = mouse_cursor.get_icon();
	mouse_cursor.set_icon(CURSOR_WAITING);

	//------- deinit game data class ---------//

	nation_array.deinit();
	firm_array.deinit();
	// ##### begin Gilbert 2/10 #######//
	firm_die_array.deinit();
	// ##### end Gilbert 2/10 #######//
	town_network_array.deinit();
	town_array.deinit();
	unit_array.deinit();
	bullet_array.deinit();
	rebel_array.deinit();
	spy_array.deinit();
	region_array.deinit();
	site_array.deinit();
	rock_array.deinit();
	dirt_array.deinit();
	effect_array.deinit();
	tornado_array.deinit();
	war_point_array.deinit();

	//------ deinit game surface class -------//

	world.deinit();
	battle.deinit();
	news_array.deinit();

	if( !loadGameCall )
		info.deinit();

	//------- deinit game data class ---------//

	image_tpict.deinit();
	terrain_res.deinit();
	plant_res.deinit();
	tech_res.deinit();
	god_res.deinit();
	monster_res.deinit();

	sprite_res.deinit();
	sprite_frame_res.deinit();
	unit_res.deinit();

	raw_res.deinit();
	race_res.deinit();
	firm_res.deinit();
	// ##### begin Gilbert 2/10 #######//
	firm_die_res.deinit();
	// ##### end Gilbert 2/10 #######//
	town_res.deinit();
	hill_res.deinit();
	snow_res.deinit();
	rock_res.deinit();
	explored_mask.deinit();
	se_res.deinit();
	talk_res.deinit();

	game_set.close_set();           // close the game set

	//----- restore from waiting cursor -------- //

	mouse_cursor.restore_icon(oldCursor);

	game_info.init_flag=0;
}
//--------- End of function GameCtl::deinit ---------//


//-------- Begin of function GameCtl::mp_broadcast_setting --------//
//
// Broadcast the latest game settings from the host to all clients.
// This function should be called by the host only
//
// see also to RemoteMsg::update_game_setting
//
void GameCtl::mp_broadcast_setting()
{
	// send (long) random seed
	// send (short) no. of nations
	// for each nation, send :
	//	(short) nation recno
	// (DWORD) directPlay player id
	// (short) color scheme
	// (short) race id
	//
	short i;
	int msgSize = sizeof(long)	+sizeof(short) + 
		nation_array.size()*(3*sizeof(short)+sizeof(PID_TYPE));
	RemoteMsg *remoteMsg = remote.new_msg( MSG_UPDATE_GAME_SETTING, msgSize );

	char* dataPtr = remoteMsg->data_buf;

	*(long*)dataPtr   = misc.get_random_seed();
	dataPtr 		      += sizeof(long);

	*(short*)dataPtr  = nation_array.size();
	dataPtr           += sizeof(short);

	for( i=1 ; i<=nation_array.size() ; i++)
	{
		*(short *)dataPtr = i;
		dataPtr += sizeof(short);
		*(PID_TYPE *)dataPtr = nation_array[i]->player_id;
		dataPtr += sizeof(PID_TYPE);
		*(short *)dataPtr = nation_array[i]->color_scheme_id;
		dataPtr += sizeof(short);
		*(short *)dataPtr = nation_array[i]->race_id;
		dataPtr += sizeof(short);
	}

	err_when(dataPtr - remoteMsg->data_buf > msgSize);

	remote.send_free_msg(remoteMsg);		// send out the message and free it after finishing sending
}
//--------- End of function GameCtl::mp_broadcast_setting ---------//


