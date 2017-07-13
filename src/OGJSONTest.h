#ifndef OGJSONTEST_H
#define OGJSONTEST_H

#include <cppunit/extensions/HelperMacros.h>

class OGJSONTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( OGJSONTest );
  CPPUNIT_TEST( testToJson );
//  CPPUNIT_TEST( testFromJson );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testToJson();
//  void testFromJson();
};

#endif // OGJSONTEST_H
