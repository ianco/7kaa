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

//Filename   : OAI_MAIN.CPP
//Description: AI - main functions

#include <OSYS.h>
#include <ONATION.h>
#include <OWORLD.h>
#include <OGAMEINFO.h>
#include <OSPY.h>
#include <OCONFIG.h>
#include <OUNIT.h>
#include <OFIRM.h>
#include <OTOWN.h>
#include <OTALKRES.h>
#include <OF_MINE.h>
#include <OINFO.h>
#include <OLOG.h>

//--------- Begin of function Nation::process_ai --------//
void Nation::process_ai()
{
	//-*********** simulate aat ************-//
#ifdef DEBUG
	if(debug_sim_game_type)
		return;
#endif
	//-*********** simulate aat ************-//

	if( config.disable_ai_flag || game_info.game_mode == GAME_TEST )
		return;

	//---- if the king has just been killed ----//

	int nationRecno = nation_recno;

	if( !king_unit_recno )
	{
		if( think_succeed_king() )
			return;

		if( think_surrender() )
			return;

		defeated();
		return;
	}

	//-------- process main AI actions ---------//

   process_ai_main();

	if( nation_array.is_deleted(nationRecno) )		// the nation can have surrendered 
		return;

	//------ process queued diplomatic messges first --------//

	// ##### begin Gilbert 4/10 ######//
   if( (info.game_date-nation_recno)%3 == 0 )
	{
		LOG_MSG("begin process_action(0,ACTION_AI_PROCESS_TALK_MSG)");
		process_action(0, ACTION_AI_PROCESS_TALK_MSG);
		LOG_MSG("end process_action(0,ACTION_AI_PROCESS_TALK_MSG)");
		LOG_MSG(misc.get_random_seed());

		if( nation_array.is_deleted(nationRecno) )		// the nation can have surrendered 
			return;
	}

	// ##### end Gilbert 4/10 ######//

   //--------- process queued actions ----------//

	// ##### begin Gilbert 4/10 ######//
   if( (info.game_date-nation_recno)%3 == 0 )
	{
		LOG_MSG("begin process_action()");
		process_action();
		LOG_MSG("end process_action()");
		LOG_MSG(misc.get_random_seed());

		if( nation_array.is_deleted(nationRecno) )		// the nation can have surrendered 
			return;
	}
	// ##### end Gilbert 4/10 ######//

	//--- process action that are on-going and need continous checking ---//

	process_on_going_action();

	//--------- cheat ---------//
	//
	// In tutorial mode only so that your opponent won't surrender
	// and you won't go to the end game screen.
	//
	//-------------------------//

	if( game_info.game_mode == GAME_TUTORIAL )
	{
		if( cash < 100 )
			add_cheat( (float)200+misc.random(500) );

		if( food < 100 )
			food += 1000;
	}

	//----- think about updating relationship with other nations -----//

	if( info.game_date%360 == nation_recno%360 )
		ai_improve_relation();

	//------ think about surrendering -------//

	if( info.game_date%60 == nation_recno%60 )
	{
		if( think_surrender() )		
			return;

		if( think_unite_against_big_enemy() )
			return;
	}
}
//---------- End of function Nation::process_ai --------//


//--------- Begin of function Nation::process_on_going_action --------//
//
// Process action that are on-going and need continous checking.
//
void Nation::process_on_going_action()
{
	//--- if the nation is in the process of trying to capture an enemy town ---//

	if( ai_capture_enemy_town_recno )
	{
		if( info.game_date%5 == nation_recno%5 )
			think_capturing_enemy_town();
	}

	//----- if the nation is in the process of attacking a target ----//

	if( attack_camp_count > 0 )
		ai_attack_target_execute(1);
}
//---------- End of function Nation::process_on_going_action --------//


//------- Begin of function Nation::process_ai_main --------//
//
void Nation::process_ai_main()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
   String debugStr;
   debugStr = "Nation ";
   debugStr += nation_recno;
#endif

	static short intervalDaysArray[] = { 90, 30, 15, 15 };

	int intervalDays = intervalDaysArray[config.ai_aggressiveness-OPTION_LOW];

	if( game_info.game_mode == GAME_TUTORIAL )
		intervalDays = 120;

	switch( (info.game_date-nation_recno*4) % intervalDays )
   {
      case 0:
#if defined(DEBUG) && defined(ENABLE_LOG)
         debugStr += " think_build_firm";
#endif
         think_build_firm();
         break;

      case 1:
#if defined(DEBUG) && defined(ENABLE_LOG)
         debugStr += " think_trading";
#endif
         think_trading();
         break;

      case 2:
#if defined(DEBUG) && defined(ENABLE_LOG)
         debugStr += " think_capture";
#endif
			think_capture();
			break;

		case 3:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_explore";
#endif
			think_explore();
			break;

		case 4:        // think about expanding its military force
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_military";
#endif
			think_military();
			break;

		case 5:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_secret_attack";
#endif
			think_secret_attack();
			break;

		case 6:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_attack_monster";
#endif
			think_attack_monster();
			break;

		case 7:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_diplomacy";
#endif
			think_diplomacy();
			break;

		case 8:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_marine";
#endif
			think_marine();
			break;

		case 9:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_grand_plan";
#endif
			think_grand_plan();
			break;

		case 10:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_reduce_expense";
#endif
			think_reduce_expense();
			break;

		case 11:
#if defined(DEBUG) && defined(ENABLE_LOG)
			debugStr += " think_town";
#endif
			think_town();
			break;
	}

	LOG_MSG(debugStr);
	LOG_MSG(misc.get_random_seed());
}
//---------- End of function Nation::process_ai_main --------//


//--------- Begin of function Nation::think_explore --------//

void Nation::think_explore()
{
}
//---------- End of function Nation::think_explore --------//


//-------- Begin of function Nation::think_succeed_king --------//
//
// return: <int> 1 - a unit succeed the king
//               0 - no unit available for succeeding the king,
//                   the nation is defeated.
//
int Nation::think_succeed_king()
{
   int  i, curRating, bestRating=0;
   Unit *unitPtr, *bestUnitPtr=NULL;
   Firm *firmPtr, *bestFirmPtr=NULL;
   int  bestWorkerId=0;

   //---- try to find the best successor from mobile units ----//

   for( i=unit_array.size() ; i>0 ; i-- )
   {
      if( unit_array.is_deleted(i) )
         continue;

      unitPtr = unit_array[i];

      if( unitPtr->nation_recno != nation_recno || !unitPtr->race_id )
         continue;

      if( !unitPtr->is_visible() && unitPtr->unit_mode != UNIT_MODE_OVERSEE )
         continue;

      err_when( unitPtr->skill.combat_level<= 0 );

      curRating = 0;

		if( unitPtr->race_id == race_id )
			curRating += 50;

      if( unitPtr->rank_id == RANK_GENERAL )
         curRating += 50;

		if( unitPtr->skill.skill_id == SKILL_LEADING )
         curRating += unitPtr->skill.skill_level;

      if( curRating > bestRating )
      {
         bestRating  = curRating;
         bestUnitPtr = unitPtr;
      }
   }

   //---- try to find the best successor from military camps ----//

   for( i=firm_array.size() ; i>0 ; i-- )
   {
      if( firm_array.is_deleted(i) )
         continue;

      firmPtr = firm_array[i];

      if( firmPtr->nation_recno != nation_recno )
         continue;

      //------ only military camps -------//

      if( firmPtr->firm_id == FIRM_CAMP )
      {
         Worker* workerPtr = firmPtr->worker_array;

         for(int j=1 ; j<=firmPtr->worker_count ; j++, workerPtr++ )
         {
            if( !workerPtr->race_id )
               continue;

            curRating = 0;

            if( workerPtr->race_id == race_id )
               curRating += 50;

				if( workerPtr->rank_id == RANK_GENERAL )
               curRating += 50;

            if( workerPtr->skill_id == SKILL_LEADING )
               curRating += workerPtr->skill_level;

            if( curRating > bestRating )
            {
               bestRating   = curRating;
               bestUnitPtr  = NULL;
               bestFirmPtr  = firmPtr;
               bestWorkerId = j;
            }
         }
      }
   }

   //------- if the best successor is a mobile unit -------//

   if( bestUnitPtr )
   {
      //-- if the unit is in a command base or seat of power, mobilize it --//

      if( !bestUnitPtr->is_visible() )
      {
         err_when( bestUnitPtr->unit_mode != UNIT_MODE_OVERSEE );

         firm_array[bestUnitPtr->unit_mode_para]->mobilize_overseer();

         err_when( bestUnitPtr->skill.combat_level<= 0 );
      }

      //---------- succeed the king -------------//

      if( bestUnitPtr->is_visible() )     // it may still be not visible if there is no space for the unit to be mobilized
      {
         if( bestUnitPtr->spy_recno && bestUnitPtr->true_nation_recno() == nation_recno )    // if this is a spy and he's our spy
            spy_array[bestUnitPtr->spy_recno]->drop_spy_identity();                          // revert the spy to a normal unit

         succeed_king( bestUnitPtr->sprite_recno );
         return 1;
      }
   }

   //------- if the best successor is a soldier in a camp -------//

   if( bestFirmPtr )
   {
		int unitRecno = bestFirmPtr->mobilize_worker(bestWorkerId, COMMAND_AI);

      if( unitRecno )
      {
         succeed_king( unitRecno );
         return 1;
      }
   }

   //--- if stil not found here, then try to locate the sucessor from villages ---//

   Town* townPtr;

   for( i=town_array.size() ; i>0 ; i-- )
   {
		if( town_array.is_deleted(i) )
         continue;

      townPtr = town_array[i];

      if( townPtr->nation_recno != nation_recno )
         continue;

      if( townPtr->recruitable_race_pop(race_id, 0) > 0 )   // if this town has people with the same race as the original king
      {
         int unitRecno = townPtr->mobilize_town_people(race_id, 1, 0);     // 1-dec pop, 0-don't mobilize spies

			if( unitRecno )
			{
				succeed_king( unitRecno );
				return 1;
			}
		}
	}

	return 0;
}
//---------- End of function Nation::think_succeed_king ---------//


//--------- Begin of function Nation::ai_improve_relation --------//
//
// This function is called once every year.
//
void Nation::ai_improve_relation()
{
	NationRelation* nationRelation;

	for( int i=nation_array.size() ; i>0 ; i-- )
	{
		if( nation_array.is_deleted(i) )
			continue;

		nationRelation = get_relation(i);

		if( nationRelation->status == NATION_HOSTILE )
			continue;

		//--- It improves the AI relation with nations that have trade with us. ---//

		change_ai_relation_level( i, trade_rating(i) / 10 );

		//--- decrease the started_war_on_us_count once per year, gradually forgiving other nations' wrong doing ---//

		if( nationRelation->started_war_on_us_count > 0
			 && misc.random(5-pref_forgiveness/20) > 0 )
		{
			nationRelation->started_war_on_us_count--;
		}
	}
}
//---------- End of function Nation::ai_improve_relation --------//


