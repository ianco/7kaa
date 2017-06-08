
#include <ALL.h>
#include <version.h>

#include <OGFILE.h>
#include <OSYS.h>
//#include <OGAMESTATE.h>
#include <OLOG.h>

#include "OGAMESTATETest.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( OGAMESTATETest );

void 
OGAMESTATETest::setUp()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGAMESTATETest::setUp ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}


void 
OGAMESTATETest::tearDown()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGAMESTATETest::tearDown ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
}


void 
OGAMESTATETest::testLoadGame()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGAMESTATETest::testLoadGame ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up
  game_file_array.init("*.SAV");
  GameFile* gameFile = game_file_array[0];
  //int res = gameFile->load_game((const char*)sys.dir_config, NULL);

  // Process
#if defined(DEBUG) && defined(ENABLE_LOG)
  //String logLine2(gameFile->file_name);
  //LOG_MSG(logLine);
  //LOG_DUMP;
#endif
  //CPPUNIT_ASSERT_EQUAL( res, 0 );

  // Check
}

void
OGAMESTATETest::testSaveGame()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGAMESTATETest::testSaveGame ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process & Check
}

void 
OGAMESTATETest::testTransmitJsonGame()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OGAMESTATETest::testTransmitJsonGame ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process

  // Check
}


