// tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/*
 *  below is use catch's main()  entry
 */

#define USE_CATCH_MAIN  0

#if USE_CATCH_MAIN

	#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
	#include "catch.hpp"

#else

	#define CATCH_CONFIG_RUNNER
	#include "catch.hpp"

	int main(int argc, char* const argv[])
	{
		// global setup...

		Catch::Session session; // There must be exactly once instance
								// writing to session.configData() here sets defaults
								// this is the preferred way to set them

		int returnCode = session.applyCommandLine(argc, argv);
		if (returnCode != 0) // Indicates a command line error
			return returnCode;

		// writing to session.configData() or session.Config() here
		// overrides command line args
		// only do this if you know you need to

		return session.run();
	}

#endif  //#if USE_CATCH_MAIN



unsigned int Factorial(unsigned int number) {
	return number > 1 ? Factorial(number - 1)*number : 1 ;
}


//  TEST_CAE(testName, testTag)> testName have to
TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(0) == 1);
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized", "[vector]") {

	std::vector<int> v(5);

	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() >= 5);

	// like stack, work flow is like: test_case=>section1.
	// then back to test_case=>section2. like stack.
	// this is avoid setup() and teardown() on gTest()
	// section1
	SECTION("resizing bigger changes size and capacity") {
		v.resize(10);

		REQUIRE(v.size() == 10);
		REQUIRE(v.capacity() >= 10);
	}

	// section2
	SECTION("resizing smaller changes size but not capacity") {
		v.resize(0);

		REQUIRE(v.size() == 0);
		REQUIRE(v.capacity() >= 5);
	}

	SECTION("reserving bigger changes capacity but not size") {
		v.reserve(10);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 10);

		SECTION("reserving smaller again does not change capacity") {
			v.reserve(7);

			REQUIRE(v.capacity() >= 10);
		}
	}

	SECTION("reserving smaller does not change size or capacity") {
		v.reserve(0);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 5);
	}
}


TEST_CASE("Assertion Macros")
{
	int i = 41;
	REQUIRE(i == 41/*42*/); // test will not continue if require fail
	std::string str = "string value";

	CHECK(str == "string value");
	bool testBool = true;
	CHECK(testBool);  //fail but test will continue.

	REQUIRE(i == 41); // test will not continue if require fail

	// false expression
	REQUIRE_FALSE(!testBool);
	CHECK_FALSE(0);

	// Floating point comparisons
	float testFloat = 2.1f;
	REQUIRE(testFloat == Approx(2.1));

	REQUIRE(22.0 / 7.0 == Approx(3.141).epsilon(0.01));  // will success

//	REQUIRE(22 / 7 == Approx(3.141).epsilon(0.01));  // will fail

	CHECK(true);

	/*! https://github.com/philsquared/Catch/blob/master/docs/assertions.md
	 * REQUIRE_THROWS( expression ) and
	 * CHECK_THROWS( expression )
	 * Expects that an exception (of any type) is be thrown during evaluation of the expression.
	 *
	 * REQUIRE_THROWS_AS( expression, exception type ) and
	 * CHECK_THROWS_AS( expression, exception type )
	 * Expects that an exception of the specified type is thrown during evaluation of the expression.
	 *
	 * REQUIRE_NOTHROW( expression ) and
	 * CHECK_NOTHROW( expression )
	 * Expects that no exception is thrown during evaluation of the expression.
	 *
	 * Matcher expressions
	 *
	 * To support Matchers a slightly different form is used. Matchers will be more fully documented elsewhere. Note that Matchers are still at early stage development and are subject to change.
	 *
	 * REQUIRE_THAT( lhs, matcher call ) and
	 * CHECK_THAT( lhs, matcher call )
	 *
	 */
}

TEST_CASE("testname-logger")
{
	int i = 9;
	INFO("The number is " << i);

	WARN("The number is " << i);

//	FAIL("this is fail log");    //test failed

	CHECK(true);  

	int theAnswer = 9;
	CAPTURE(theAnswer);

}