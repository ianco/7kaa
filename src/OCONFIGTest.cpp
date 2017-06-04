//#include "stdafx.h"
#include "OCONFIGTest.h"
//#include "Money.h"

//#include <OGAMESTATE.h>
#include <OCONFIG.h>
#include <OLOG.h>
#include <OSYS.h>
#include "json.hpp"

using json = nlohmann::json;


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( OCONFIGTest );


void 
OCONFIGTest::setUp()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::setUp ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}

void 
OCONFIGTest::tearDown()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::tearDown ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}

void
OCONFIGTest::testInit()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testInit ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char 	new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();

  	// Process & Check
	char expected_count = 2;
  	CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );

	config.change_difficulty(OPTION_HIGH);
	expected_count = 6;
  	CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}

void
OCONFIGTest::testLoad()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testLoad ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char 	new_config_dat_flag=0;
	sys.set_config_dir();

	if( !config.load("CONFIG.DAT") ) {
		CPPUNIT_FAIL("Unable to read configuration file");
	}

  	// Process & Check
	char expected_count = 1;
  	CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}

void 
OCONFIGTest::testToJson()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testToJson ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();

  	// Process & Check
	std::string s = config.convert_to_json();
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(s.c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
	json jc = json::parse(s);
	char expected_count = 2;
  	CPPUNIT_ASSERT_EQUAL( jc["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}

void 
OCONFIGTest::testFromJson()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testFromJson ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();
	std::string s = config.convert_to_json();
	json jc = json::parse(s);
	jc["startup"]["ai_nation_count"] = 1;
	config.change_from_json(jc.dump());

  	// Process & Check
	s = config.convert_to_json();
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(s.c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
	jc = json::parse(s);
	char expected_count = 1;
  	CPPUNIT_ASSERT_EQUAL( jc["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}


