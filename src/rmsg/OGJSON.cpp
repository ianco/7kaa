//Filename    : OGJSON.CPP
//Description : JSON utilities

//#include <OGAMESTATE.h>
#include <OCONFIG.h>
#include <OLOG.h>
#include <dbglog.h>
#include <OGJSON.h>
#include "gettext.h"
#include "string.h"

void to_json(json& j, const Config& c) {
	j = json{
		{"difficulty_rating", c.difficulty_rating},
		{"startup", {
			{"ai_nation_count", c.ai_nation_count},
			{"start_up_cash", c.start_up_cash},
		//	{"start_up_food", c.start_up_food},
			{"ai_start_up_cash", c.ai_start_up_cash},
		//	{"ai_start_up_food", c.ai_start_up_food},
			{"ai_aggressiveness", c.ai_aggressiveness},
			{"start_up_independent_town", c.start_up_independent_town},
			{"start_up_raw_site", c.start_up_raw_site},
			{"difficulty_level", c.difficulty_level}
		}}
	};
}

void from_json(const json& j, Config& c) {
	c.difficulty_rating = j["difficulty_rating"].get<short>();
	c.ai_nation_count = j["startup"]["ai_nation_count"].get<char>();
	c.start_up_cash = j["startup"]["start_up_cash"].get<short>();
//	c.start_up_food = j["startup"]["start_up_food"].get<short>();
	c.ai_start_up_cash = j["startup"]["ai_start_up_cash"].get<short>();
//	c.ai_start_up_food = j["startup"]["ai_start_up_food"].get<short>();
	c.ai_aggressiveness = j["startup"]["ai_aggressiveness"].get<char>();
	c.start_up_independent_town = j["startup"]["start_up_independent_town"].get<short>();
	c.start_up_raw_site = j["startup"]["start_up_raw_site"].get<short>();
	c.difficulty_level = j["startup"]["difficulty_level"].get<char>();
}

void to_json(json& j, const GameFile& g) {
	j = json{
        {"GAME_VERSION", GAME_VERSION},
		{"class_size", g.class_size},    // for version compare
		{"player_name", g.player_name},
		{"race_id", g.race_id},
		{"nation_color", g.nation_color},
		{"game_date", g.game_date},      // the game date of the saved game
		{"terrain_set", g.terrain_set}
    };
}

void from_json(const json& j, GameFile& g){
    // validate version #?
    // GAME_VERSION = j["GAME_VERSION"].get<int>();
    g.class_size = j["class_size"].get<int>();
	strncpy( g.player_name, j["player_name"].get<std::string>().c_str(), NationArray::HUMAN_NAME_LEN );
	g.player_name[NationArray::HUMAN_NAME_LEN] = '\0';
    g.race_id = j["race_id"].get<short>();
    g.nation_color = j["nation_color"].get<short>();
    g.game_date = j["game_date"].get<int>();
    g.terrain_set = j["terrain_set"].get<short>();
}

void to_json(json& j, const RaceRes& r) {
    j = json{};
	RaceInfo* raceInfo = r.race_info_array;
	j["race_info"]["count"] = race_res.race_count;
	for( int i=1 ; i<=race_res.race_count ; i++, raceInfo++ ) {
		j["race_info"][std::to_string(i)] = raceInfo->town_name_used_count;
	}
    j["name_info"]["count"] = r.name_count;
    for( int i=1 ; i<=r.name_count ; i++) {
        j["name_info"][std::to_string(i)] = r.name_used_array[i-1];
    }
}

void from_json(const json& j, RaceRes& r){
    
}
