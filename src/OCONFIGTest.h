#ifndef OCONFIGTEST_H
#define OCONFIGTEST_H

#include <cppunit/extensions/HelperMacros.h>
//#include "Money.h"

class OCONFIGTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OCONFIGTest );
  CPPUNIT_TEST( testInit );
  CPPUNIT_TEST( testLoad );
  CPPUNIT_TEST( testToJson );
  CPPUNIT_TEST( testFromJson );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testInit();
  void testLoad();
  void testToJson();
  void testFromJson();
};

#endif // OCONFIGTEST_H
