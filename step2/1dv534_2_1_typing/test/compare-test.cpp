#include <compare.h>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Two equal strings", "[equal]")
{
    // Arrange
    char first[] = "abc";
    char second[] = "abc";
    auto compare = new Compare();

    // Act
    auto result = compare->equal(first, second);

    // Assert
    REQUIRE(result);
}

TEST_CASE("Uppercase differ", "[equal]")
{
    // Arrange
    char first[] = "abc";
    char second[] = "ABC";
    auto compare = new Compare();

    // Act
    auto result = compare->equal(first, second);

    // Assert
    REQUIRE_FALSE(result);
}

TEST_CASE("Non null terminated first string differ", "[equal]")
{
    // Arrange
    char first[] = {'a', 'b', 'c', 'd'};
    char second[4] = "abc";
    auto compare = new Compare();

    // Act
    auto result = compare->equal(first, second);

    // Assert
    REQUIRE_FALSE(result);
}

TEST_CASE("Non null terminated second string differ", "[equal]")
{
    // Arrange
    char first[] = "abc";
    char second[4] = {'a', 'b', 'c', 'd'};
    auto compare = new Compare();

    // Act
    auto result = compare->equal(first, second);

    // Assert
    REQUIRE_FALSE(result);
}
