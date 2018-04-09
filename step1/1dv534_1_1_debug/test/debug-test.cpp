#include <debug.h>
#include <cstring>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Correct filtering", "[getAlphaNumerics]")
{
    // Arrange
    char str[] = "khff  &%/321";
    char newStr[strlen(str)] = "";

    // Act
    int whitespaces = getAlphaNumerics(str, newStr);

    // Assert
    REQUIRE(strcmp(newStr, "KHFF321") == 0);
    REQUIRE((strlen(str) - strlen(newStr)) == 5);
    REQUIRE(whitespaces == 2);
}

TEST_CASE("Correct sorting", "[sortString]")
{
    // Arrange
    char newStr[] = "KHFF321";

    // Act
    sortString(newStr);

    // Assert
    REQUIRE(strcmp(newStr, "123FFHK") == 0);
}
