//Filename	  : OGJSON.H
//Description : Header file for JSON utilities class

#ifndef __OGJSON_H
#define __OGJSON_H

#include <string>

#include "json.hpp"

using json = nlohmann::json;

void to_json(json& j, const Config& c);
void from_json(const json& j, Config& c);

#endif
