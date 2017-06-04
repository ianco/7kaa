#ifndef OCONFIGTEST_H
#define OCONFIGTEST_H

#include <cppunit/extensions/HelperMacros.h>
//#include "Money.h"

class OCONFIGTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OCONFIGTest );
  CPPUNIT_TEST( testInit );
  CPPUNIT_TEST( testLoad );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testInit();
  void testLoad();
};

#endif // OCONFIGTEST_H
