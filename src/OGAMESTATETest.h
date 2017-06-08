#ifndef OGAMESTATETEST_H
#define OGAMESTATETEST_H

#include <cppunit/extensions/HelperMacros.h>

class OGAMESTATETest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OGAMESTATETest );
  CPPUNIT_TEST( testLoadGame );
  CPPUNIT_TEST( testSaveGame );
  CPPUNIT_TEST( testTransmitJsonGame );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testLoadGame();
  void testSaveGame();
  void testTransmitJsonGame();
};

#endif // OGAMESTATETEST_H
