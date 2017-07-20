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

//Filename    : OGAMEINFO.CPP
//Description : Main Game Object (re-factored from GameMenu)

#include <ALL.h>
#include <COLCODE.h>
#include <OSYS.h>
#include <OSYSINFO.h>
#include <OVGA.h>
#include <OFONT.h>
#include <OMOUSE.h>
#include <OMOUSECR.h>
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
#include <OIMGRES.h>
#include <OINFO.h>
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

//---------------- DETECT_SPREAD ----------------//
//
// Spread out 2 tiles on all direction when detecting sprite.
// A bigger value is required for bigger sprite.
// this should be a number big enough to cover the biggest
// sprite in the game.
//
// It would be equal to the size of the biggest
// sprite in the game + 1 (+1 for the difference
// between (next_x & cur_x).
//
//-----------------------------------------------//

//-------- Begin of function GameInfo::GameInfo --------//
//
GameInfo::GameInfo()
{
   init_flag = 0;
   game_mode = GAME_PREGAME;

	init_remap_table();        // initialize color remap table
}
//--------- End of function GameInfo::GameInfo ---------//


//--------- Begin of function GameInfo::init_remap_table --------//

void GameInfo::init_remap_table()
{
	//------------- Define constant ------------//

	#define FIRST_REMAP_KEY       0xE0        // the source color code of the colors to be remapped
	#define REMAP_KEY_COUNT       8

	//-------- define color remap scheme -------//

	static ColorRemapMethod remap_method_array[] =
	{
      { 0xBC, 0xDC },   // the first remap table is for independent units
      { 0xA0, 0xC0 },   // following are eight remap table for each color code
      { 0xA4, 0xC4 },
      { 0xA8, 0xC8 },
      { 0xAC, 0xCC },
      { 0xB0, 0xD0 },
		{ 0xB4, 0xD4 },
      { 0xB8, 0xD8 },
      { 0xBC, 0xDC },
   };

   //---- define the main color code for each color scheme ----//

   static int main_color_array[] =
   {
      0xDC,
      0xC0,
      0xC4,
      0xC8,
      0xCC,
      0xD0,
      0xD4,
      0xD8,
	};

	//-------- initialize color remap table -------//

	int         i, j;
	ColorRemap *colorRemap = color_remap_array;

	for( i=0 ; i<MAX_COLOR_SCHEME+1 ; i++, colorRemap++ )    // MAX_COLOR_SCHEME+1, +1 for independent units
	{
      colorRemap->main_color = main_color_array[i];

      for( j=0 ; j<256 ; j++ )
         colorRemap->color_table[j] = j;

      for( j=0 ; j<4 ; j++ )
         colorRemap->color_table[FIRST_REMAP_KEY+j] = (char) (remap_method_array[i].primary_color+j);

      for( j=0 ; j<4 ; j++ )
         colorRemap->color_table[FIRST_REMAP_KEY+4+j] = (char) (remap_method_array[i].secondary_color+j);

//    for( j=0 ; j<4 ; j++ )
//       colorRemap->color_table[FIRST_REMAP_KEY+j] = (char) (remap_method_array[i].secondary_color+j);
   }
}
//---------- End of function GameInfo::init_remap_table --------//


//--------- Begin of function GameInfo::get_color_remap_table --------//
//
// <int> nationRecno  - 0 for independent nation
// <int> selectedFlag - whether display outline around the bitmap
//
char* GameInfo::get_color_remap_table(int nationRecno, int selectedFlag)
{
   ColorRemap* colorRemap;
   char* colorRemapTable;

	// ###### begin Gilbert 1/10 ######//
   if( nationRecno==0 || nation_array.is_deleted(nationRecno) )    // independent units
	// ###### end Gilbert 1/10 ######//
      colorRemap = color_remap_array;
   else
      colorRemap = color_remap_array+nation_array[nationRecno]->color_scheme_id;

   colorRemapTable = colorRemap->color_table;

   //--------- set outline color ---------//

	#define FIRST_CYCLE_COLOR     0xEF
	#define CYCLE_COLOR_COUNT     1
   #define CYCLE_FRAME_INTERVAL  3

   if( selectedFlag )
   {
      int cycleId=0;
/*
      if( CYCLE_COLOR_COUNT==1 )
      {
         cycleId = 0;
      }
      else
      {
         cycleId = sys_info.frame_count / CYCLE_FRAME_INTERVAL % (CYCLE_COLOR_COUNT*2-2);

         if( cycleId >= CYCLE_COLOR_COUNT )              // cycle in reserved order
            cycleId = CYCLE_COLOR_COUNT*2-2 - cycleId;
      }
*/
      colorRemapTable[OUTLINE_CODE]        = FIRST_CYCLE_COLOR + cycleId;
      colorRemapTable[OUTLINE_SHADOW_CODE] = FIRST_CYCLE_COLOR + cycleId;
   }
   else
   {
      colorRemapTable[OUTLINE_CODE] = (char) TRANSPARENT_CODE;
      colorRemapTable[OUTLINE_SHADOW_CODE] = (char) SHADOW_CODE;
   }

   return colorRemapTable;
}
//--------- End of function GameInfo::get_color_remap_table --------//


void GameInfo::disp_gen_map_status( int curStep, int maxStep, int section )
{
	const int POPUP_WINDOW_WIDTH = 266;
	const int POPUP_WINDOW_HEIGHT = 149;
	const int POPUP_WINDOW_X1 = (vga_front.buf_width() - POPUP_WINDOW_WIDTH) / 2;
	const int POPUP_WINDOW_Y1 = (vga_front.buf_height() - POPUP_WINDOW_HEIGHT) / 2;

	const int BAR_X1 = POPUP_WINDOW_X1 + 46;
	// ###### begin Gilbert 29/10 ######//
	const int BAR_Y1 = POPUP_WINDOW_Y1 + 106;
	// ###### end Gilbert 29/10 ######//

	const int MAX_SECTION = 2;		// section 0 for world.genmap, section 1 for battle.run
	static int accSectionWeight[MAX_SECTION+1] = { 0, 60, 100 };

	if( section == 0 && curStep == 0)
	{
		image_menu.put_front(POPUP_WINDOW_X1, POPUP_WINDOW_Y1, "NEWWORLD");
	}

	err_when( section < 0 || section >= MAX_SECTION );
	err_when( curStep < 0 || curStep > maxStep );
	if( curStep >= 0 && curStep <= maxStep)
	{
		float r = float(accSectionWeight[section]) + 
			float((accSectionWeight[section+1]-accSectionWeight[section]) * curStep) / maxStep;
		vga_front.indicator(4, BAR_X1, BAR_Y1, r, (float)accSectionWeight[MAX_SECTION], 0);
	}

	sys.blt_virtual_buf();
}
