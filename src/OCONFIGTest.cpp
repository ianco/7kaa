//#include "stdafx.h"
#include "OCONFIGTest.h"
//#include "Money.h"

//#include <OGAMESTATE.h>
#include <OCONFIG.h>
#include <OLOG.h>
#include <OSYS.h>
#include "json.hpp"
#include "restclient-cpp/restclient.h"


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
	json jc = config;
	std::string s = jc.dump();
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(s.c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
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

void 
OCONFIGTest::testJsonToWebService()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testJsonToWebService ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();
	json jc = config;
	jc["startup"]["ai_nation_count"] = 7;
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine4(jc.dump().c_str());
	LOG_MSG("Sent:");
	LOG_MSG(logLine4);
	LOG_DUMP;
#endif
	RestClient::Response r = RestClient::post("http://localhost:8080/config", "text/json", jc.dump().c_str());
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine3(r.body.c_str());
	LOG_MSG("Received:");
	LOG_MSG(logLine3);
	LOG_DUMP;
#endif
	json jc2 = json::parse(r.body);
	
  	// Process & Check
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(jc2.dump().c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
	char expected_count = 7;
  	CPPUNIT_ASSERT_EQUAL( jc2["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}

void 
OCONFIGTest::testJsonFromWebService()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testJsonFromWebService ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  	// Set up
  	// Set up
	char new_config_dat_flag=0;
	sys.set_config_dir();

	new_config_dat_flag = 1;
	config.init();
	json jc = config;
	std::string s = jc.dump();
	RestClient::Response r = RestClient::get("http://localhost:8080/config");
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine3(r.body.c_str());
	LOG_MSG("Received:");
	LOG_MSG(logLine3);
	LOG_DUMP;
#endif
	json jc2 = json::parse(r.body);
	
  	// Process & Check
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine2(jc2.dump().c_str());
	LOG_MSG(logLine2);
	LOG_DUMP;
#endif
	char expected_count = 7;
  	CPPUNIT_ASSERT_EQUAL( jc2["startup"]["ai_nation_count"].get<char>(), expected_count );

	//config.change_difficulty(OPTION_HIGH);
	//expected_count = 6;
  	//CPPUNIT_ASSERT_EQUAL( config.ai_nation_count, expected_count );
}


