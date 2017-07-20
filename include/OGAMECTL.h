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

//Filename	  : OGAMECTL.H
//Description : Header file for Game Control class

#ifndef __OGAMECTL_H
#define __OGAMECTL_H

#include <ALL.h>
#include <OCONFIG.h>
#include <OGAMEINFO.h>

#pragma pack(1)
class GameCtl
{
public:
	GameCtl();

	int			init(int loadGameCall=0);
	int 		init_internal(int loadGameCall);
	void		deinit(int loadGameCall=0);

	void 		mp_broadcast_setting();

};
#pragma pack()

extern GameInfo game_info;
extern GameCtl game_ctl;
extern char game_demo_mode, game_design_mode;

//-------------------------------------//

#endif


