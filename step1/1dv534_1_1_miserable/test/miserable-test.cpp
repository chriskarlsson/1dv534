#include <miserable.h>
#include <measurements-mock.h>
#include <string>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Get 2 measurements", "[getMeasurements]")
{
    // Arrange
    const int MEASUREMENTS_PER_ROW = 6;
    const int NUMBER_OF_MEASUREMENTS = 2;
    const double MEASUREMENTS[] = { 1.234, 5.678, 9.123 };
    const int SIZE = 3;
    auto measurementsMock = new MeasurementsMock(MEASUREMENTS, SIZE);
    auto miserable = new Miserable(measurementsMock);

    // Act
    auto result = miserable->getMeasurements(MEASUREMENTS_PER_ROW, NUMBER_OF_MEASUREMENTS);

    // Assert
    REQUIRE(result.find("1.23") != std::string::npos);
    REQUIRE(result.find("1.234") == std::string::npos);
    REQUIRE(result.find("5.68") != std::string::npos); // Round
    REQUIRE(result.find("9.12") == std::string::npos);
}

TEST_CASE("Get warning on too few measurements", "[getMeasurements]")
{
    // Arrange
    const int MEASUREMENTS_PER_ROW = 6;
    const int NUMBER_OF_MEASUREMENTS = 4;
    const double MEASUREMENTS[] = { 1.234, 5.678, 9.123 };
    const int SIZE = 3;
    auto measurementsMock = new MeasurementsMock(MEASUREMENTS, SIZE);
    auto miserable = new Miserable(measurementsMock);

    // Act
    auto result = miserable->getMeasurements(MEASUREMENTS_PER_ROW, NUMBER_OF_MEASUREMENTS);

    // Assert
    REQUIRE(result.find("too few measurements") != std::string::npos);
}

TEST_CASE("Get max and min", "[getMaxMin]")
{
    // Arrange
    const double MEASUREMENTS[] = { 5.678, 1.234, 9.123 };
    const int SIZE = 3;
    auto measurementsMock = new MeasurementsMock(MEASUREMENTS, SIZE);
    auto miserable = new Miserable(measurementsMock);

    // Act
    auto result = miserable->getMaxMin();

    // Assert
    REQUIRE(result.find("1.23") != std::string::npos);
    REQUIRE(result.find("1.234") == std::string::npos);
    REQUIRE(result.find("5.68") == std::string::npos);
    REQUIRE(result.find("5.678") == std::string::npos);
    REQUIRE(result.find("9.12") != std::string::npos);
}

TEST_CASE("Get average", "[getAverage]")
{
    // Arrange
    const double MEASUREMENTS[] = { 1.0, 2.0 };
    const int SIZE = 2;
    auto measurementsMock = new MeasurementsMock(MEASUREMENTS, SIZE);
    auto miserable = new Miserable(measurementsMock);

    // Act
    auto result = miserable->getAverage();

    // Assert
    REQUIRE(result.find("1.50") != std::string::npos);
}
