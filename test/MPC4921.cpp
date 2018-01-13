#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4921
#include <MCP4.hpp>

MCP4 dac = MCP4();

TEST_CASE("Constants are correct", "[const]") {
  REQUIRE(MCP4::DATA == 0xFFF);
  REQUIRE(MCP4::SHDN == 0x10);
  REQUIRE(MCP4::GA == 0x20);

  REQUIRE(MCP4::OFF == 0x00);
  REQUIRE(MCP4::X1 == 0x30);
  REQUIRE(MCP4::X2 == 0x10);
  REQUIRE(MCP4::BUFFERED_X1 == 0x70);
  REQUIRE(MCP4::BUFFERED_X2 == 0x50);
}

TEST_CASE("MCP4::write(config, value)", "[func]") {
  REQUIRE(dac.write(MCP4::OFF, 0xABCD) == 0x0BCD);
  REQUIRE(dac.write(MCP4::X1, 0xABCD) == 0x3BCD);
  REQUIRE(dac.write(MCP4::X2, 0xABCD) == 0x1BCD);
  REQUIRE(dac.write(MCP4::BUFFERED_X1, 0xABCD) == 0x7BCD);
  REQUIRE(dac.write(MCP4::BUFFERED_X2, 0xABCD) == 0x5BCD);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::OFF, 0xABCD, command);
  REQUIRE(command == 0x0BCD);

  dac.write(MCP4::X1, 0xABCD, command);
  REQUIRE(command == 0x3BCD);

  dac.write(MCP4::X2, 0xABCD, command);
  REQUIRE(command == 0x1BCD);

  dac.write(MCP4::BUFFERED_X1, 0xABCD, command);
  REQUIRE(command == 0x7BCD);

  dac.write(MCP4::BUFFERED_X2, 0xABCD, command);
  REQUIRE(command == 0x5BCD);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower)", "[func]") {
  REQUIRE(dac.write(MCP4::OFF, 0xAB, 0xCD) == 0x0BCD);
  REQUIRE(dac.write(MCP4::X1, 0xAB, 0xCD) == 0x3BCD);
  REQUIRE(dac.write(MCP4::X2, 0xAB, 0xCD) == 0x1BCD);
  REQUIRE(dac.write(MCP4::BUFFERED_X1, 0xAB, 0xCD) == 0x7BCD);
  REQUIRE(dac.write(MCP4::BUFFERED_X2, 0xAB, 0xCD) == 0x5BCD);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::OFF, 0xAB, 0xCD, command);
  REQUIRE(command == 0x0BCD);

  dac.write(MCP4::X1, 0xAB, 0xCD, command);
  REQUIRE(command == 0x3BCD);

  dac.write(MCP4::X2, 0xAB, 0xCD, command);
  REQUIRE(command == 0x1BCD);

  dac.write(MCP4::BUFFERED_X1, 0xAB, 0xCD, command);
  REQUIRE(command == 0x7BCD);

  dac.write(MCP4::BUFFERED_X2, 0xAB, 0xCD, command);
  REQUIRE(command == 0x5BCD);
}
