#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4902
#include <MCP4.hpp>

MCP4 dac = MCP4();

TEST_CASE("Constants are correct", "[const]") {
  REQUIRE(MCP4::DATA == 0xFFF);
  REQUIRE(MCP4::SHDN == 0x10);
  REQUIRE(MCP4::GA == 0x20);
  REQUIRE(MCP4::AB == 0x80);

  REQUIRE(MCP4::A_OFF == 0x00);
  REQUIRE(MCP4::A_X1 == 0x30);
  REQUIRE(MCP4::A_X2 == 0x10);
  REQUIRE(MCP4::BUFFERED_A_X1 == 0x70);
  REQUIRE(MCP4::BUFFERED_A_X2 == 0x50);

  REQUIRE(MCP4::B_OFF == 0x80);
  REQUIRE(MCP4::B_X1 == 0xB0);
  REQUIRE(MCP4::B_X2 == 0x90);
  REQUIRE(MCP4::BUFFERED_B_X1 == 0xF0);
  REQUIRE(MCP4::BUFFERED_B_X2 == 0xD0);
}

TEST_CASE("MCP4::write(config, value)", "[func]") {
  REQUIRE(dac.write(MCP4::A_OFF, 0xAB) == 0x0AB0);
  REQUIRE(dac.write(MCP4::A_X1, 0xAB) == 0x3AB0);
  REQUIRE(dac.write(MCP4::A_X2, 0xAB) == 0x1AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_A_X1, 0xAB) == 0x7AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_A_X2, 0xAB) == 0x5AB0);

  REQUIRE(dac.write(MCP4::B_OFF, 0xAB) == 0x8AB0);
  REQUIRE(dac.write(MCP4::B_X1, 0xAB) == 0xBAB0);
  REQUIRE(dac.write(MCP4::B_X2, 0xAB) == 0x9AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_B_X1, 0xAB) == 0xFAB0);
  REQUIRE(dac.write(MCP4::BUFFERED_B_X2, 0xAB) == 0xDAB0);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::A_OFF, 0xAB, command);
  REQUIRE(command == 0x0AB0);

  dac.write(MCP4::A_X1, 0xAB, command);
  REQUIRE(command == 0x3AB0);

  dac.write(MCP4::A_X2, 0xAB, command);
  REQUIRE(command == 0x1AB0);

  dac.write(MCP4::BUFFERED_A_X1, 0xAB, command);
  REQUIRE(command == 0x7AB0);

  dac.write(MCP4::BUFFERED_A_X2, 0xAB, command);
  REQUIRE(command == 0x5AB0);

  dac.write(MCP4::B_OFF, 0xAB, command);
  REQUIRE(command == 0x8AB0);

  dac.write(MCP4::B_X1, 0xAB, command);
  REQUIRE(command == 0xBAB0);

  dac.write(MCP4::B_X2, 0xAB, command);
  REQUIRE(command == 0x9AB0);

  dac.write(MCP4::BUFFERED_B_X1, 0xAB, command);
  REQUIRE(command == 0xFAB0);

  dac.write(MCP4::BUFFERED_B_X2, 0xAB, command);
  REQUIRE(command == 0xDAB0);
}
