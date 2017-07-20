//#include "stdafx.h"
#include "OGJSONTest.h"

#include <OLOG.h>
#include <OSYS.h>
#include <OGAMESET.h>
#include <ORACERES.h>
#include <OGJSON.h>
#include "restclient-cpp/restclient.h"


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( OGJSONTest );


void 
OGJSONTest::setUp()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGJSONTest::setUp ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}

void 
OGJSONTest::tearDown()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGJSONTest::tearDown ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}

void 
OGJSONTest::testToJson()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGJSONTest::testToJson ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();
	sys.set_game_dir();
	sys.init_objects();
	sys.init_directx_internal();

	new_config_dat_flag = 1;
	config.init();
	game_set.init();
	game_info.init_internal(FALSE);

  	// Process & Check
	json jc = race_res;
	std::string s = jc.dump();
#if defined(DEBUG) && defined(ENABLE_LOG)
	//String logLine2(jc.dump());
	LOG_MSG(s);
	LOG_DUMP;
#endif
	//char expected_count = 2;
  	//CPPUNIT_ASSERT_EQUAL( jc["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}
/*
void 
OGJSONTest::testFromJson()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGJSONTest::testFromJson ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();
	json jc = config;
	jc["startup"]["ai_nation_count"] = 1;
	config = jc;

  	// Process & Check
	jc = config;
	std::string s = jc.dump();
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(s.c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
	char expected_count = 1;
  	CPPUNIT_ASSERT_EQUAL( jc["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}
*/

