//#include "stdafx.h"
#include "OCONFIGTest.h"
//#include "Money.h"

#include <OCONFIG.h>
#include <OLOG.h>


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
OCONFIGTest::testConstructor()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testConstructor ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process

  // Check
}

void
OCONFIGTest::testEqual()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testEqual ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process & Check
  CPPUNIT_ASSERT_EQUAL( 1, 1 );
}

void 
OCONFIGTest::testAdd()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testAdd ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process

  // Check
}

void 
OCONFIGTest::testAddThrow()
{
#if defined(DEBUG) && defined(ENABLE_LOG)
	String logLine("OCONFIGTest::testAddThrow ");
	LOG_MSG(logLine);
	LOG_DUMP;
#endif
  // Set up

  // Process
}
