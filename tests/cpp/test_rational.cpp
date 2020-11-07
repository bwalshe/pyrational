#define CATCH_CONFIG_MAIN  
#include <catch2/catch.hpp>
#include <vector>
#include "rational.h"


TEST_CASE("Denominator is always positive, numerator has correct sign", "[rational]"){
    auto r  = GENERATE(as<rational>{},rational(-1, 2), rational(1,-2));
    REQUIRE( r.numerator == -1);
    REQUIRE( r.denominator == 2);
}

TEST_CASE("numerator and denominator are coprime when numerator < denominator", 
          "[rational]") {
    rational r(2, 4);
    REQUIRE(r.numerator == 1);
    REQUIRE(r.denominator == 2);
}

TEST_CASE("numerator and denominator are coprime when numerator > denominator", 
          "[rational]") {
    rational r(4, 2);
    REQUIRE(r.numerator == 2);
    REQUIRE(r.denominator == 1);
}

TEST_CASE("equality rational == rational", "[rational]") {
    REQUIRE(rational(3, 7) == rational(6, 14));
    REQUIRE(rational(3, 7) != rational(4, 7));
    REQUIRE(rational(3, 7) != rational(3, 8));
}

TEST_CASE("equality rational == int", "[rational]") {
    REQUIRE(rational(3, 1) == 3);
    REQUIRE(rational(2, 1) != 3);
    REQUIRE(rational(3, 2) != 3);
}

TEST_CASE("Adding rational + rational", "[rational]") {
    REQUIRE(rational(1,2) + rational(1, 4) == rational(3, 4) );
}

TEST_CASE("Adding rational + int", "[rational]") {
    REQUIRE(rational(1,2) + 1 == rational(3, 2) );
}

TEST_CASE("Multiply rational * rational", "[rational]") {
    REQUIRE(rational(2, 3) * rational(3, 4) == rational(1, 2) );
}

TEST_CASE("Multiply rational * int", "[rational]") {
    REQUIRE(rational(1,3) * 2 == rational(2, 3) );
}

TEST_CASE("Cast to string", "[rational]") {
    REQUIRE(static_cast<std::string>(rational(2, 3)) == "2/3");
}

TEST_CASE("Cast to float", "[rational]") {
    REQUIRE(static_cast<float>(rational(2, 3)) == Approx(2.0 / 3.0));
}