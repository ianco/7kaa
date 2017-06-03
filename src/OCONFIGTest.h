#ifndef OCONFIGTEST_H
#define OCONFIGTEST_H

#include <cppunit/extensions/HelperMacros.h>
//#include "Money.h"

class OCONFIGTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OCONFIGTest );
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

#endif // OCONFIGTEST_H
