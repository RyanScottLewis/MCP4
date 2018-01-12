#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4821
#include <MCP4.hpp>

MCP4 dac = MCP4();

TEST_CASE("Constants are correct", "[const]") {
  REQUIRE(MCP4::DATA == (uint16_t)0xFFF);
  REQUIRE(MCP4::SHDN == (uint8_t)0x10);
  REQUIRE(MCP4::GA == (uint8_t)0x20);

  REQUIRE(MCP4::OFF == (uint8_t)0x00);
  REQUIRE(MCP4::X1 == (uint8_t)0x30);
  REQUIRE(MCP4::X2 == (uint8_t)0x10);
}

TEST_CASE("MCP4::write(config, value)", "[func]") {
  REQUIRE(dac.write(MCP4::OFF, 0xABCD) == (uint16_t)0x0BCD);
  REQUIRE(dac.write(MCP4::X1, 0xABCD) == (uint16_t)0x3BCD);
  REQUIRE(dac.write(MCP4::X2, 0xABCD) == (uint16_t)0x1BCD);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::OFF, 0xABCD, command);
  REQUIRE(command == (uint16_t)0x0BCD);

  dac.write(MCP4::X1, 0xABCD, command);
  REQUIRE(command == (uint16_t)0x3BCD);

  dac.write(MCP4::X2, 0xABCD, command);
  REQUIRE(command == (uint16_t)0x1BCD);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower)", "[func]") {
  REQUIRE(dac.write(MCP4::OFF, 0xAB, 0xCD) == (uint16_t)0x0BCD);
  REQUIRE(dac.write(MCP4::X1, 0xAB, 0xCD) == (uint16_t)0x3BCD);
  REQUIRE(dac.write(MCP4::X2, 0xAB, 0xCD) == (uint16_t)0x1BCD);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::OFF, 0xAB, 0xCD, command);
  REQUIRE(command == (uint16_t)0x0BCD);

  dac.write(MCP4::X1, 0xAB, 0xCD, command);
  REQUIRE(command == (uint16_t)0x3BCD);

  dac.write(MCP4::X2, 0xAB, 0xCD, command);
  REQUIRE(command == (uint16_t)0x1BCD);
}
