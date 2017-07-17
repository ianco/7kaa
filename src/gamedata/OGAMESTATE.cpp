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

//Filename    : OGAMESTATE.CPP
//Description : Global Variables
//Owner		  : Ian

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
#include <OGAME.h>
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

#include <OGAMESTATE.h>

// -------- Define constant ---------//


// -------- Define methods ---------//

