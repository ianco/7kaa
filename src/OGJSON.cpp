//Filename    : OGJSON.CPP
//Description : JSON utilities

#include <OCONFIG.h>
#include <OLOG.h>
#include <dbglog.h>
#include <OGJSON.h>
#include "gettext.h"

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
