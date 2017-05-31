#ifndef OGAMESTATETEST_H
#define OGAMESTATETEST_H

#include <cppunit/extensions/HelperMacros.h>
//#include "Money.h"

class OGAMESTATETest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OGAMESTATETest );
  CPPUNIT_TEST( testConstructor );
  CPPUNIT_TEST( testEqual );
  CPPUNIT_TEST( testAdd );
  //CPPUNIT_TEST_EXCEPTION( testAddThrow, IncompatibleMoneyError );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testEqual();
  void testAdd();
  void testAddThrow();
};

#endif // OGAMESTATETEST_H
