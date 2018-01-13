#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4901
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
  REQUIRE(dac.write(MCP4::OFF, 0xAB) == 0x0AB0);
  REQUIRE(dac.write(MCP4::X1, 0xAB) == 0x3AB0);
  REQUIRE(dac.write(MCP4::X2, 0xAB) == 0x1AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_X1, 0xAB) == 0x7AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_X2, 0xAB) == 0x5AB0);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::OFF, 0xAB, command);
  REQUIRE(command == 0x0AB0);

  dac.write(MCP4::X1, 0xAB, command);
  REQUIRE(command == 0x3AB0);

  dac.write(MCP4::X2, 0xAB, command);
  REQUIRE(command == 0x1AB0);

  dac.write(MCP4::BUFFERED_X1, 0xAB, command);
  REQUIRE(command == 0x7AB0);

  dac.write(MCP4::BUFFERED_X2, 0xAB, command);
  REQUIRE(command == 0x5AB0);
}
