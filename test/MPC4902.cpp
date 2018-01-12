#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4902
#include <MCP4.hpp>

MCP4 dac = MCP4();

TEST_CASE("Constants are correct", "[const]") {
  REQUIRE(MCP4::DATA == (uint16_t)0xFFF);
  REQUIRE(MCP4::SHDN == (uint8_t)0x10);
  REQUIRE(MCP4::GA == (uint8_t)0x20);
  REQUIRE(MCP4::AB == (uint8_t)0x80);

  REQUIRE(MCP4::A_OFF == (uint8_t)0x00);
  REQUIRE(MCP4::A_X1 == (uint8_t)0x30);
  REQUIRE(MCP4::A_X2 == (uint8_t)0x10);
  REQUIRE(MCP4::BUFFERED_A_X1 == (uint8_t)0x70);
  REQUIRE(MCP4::BUFFERED_A_X2 == (uint8_t)0x50);

  REQUIRE(MCP4::B_OFF == (uint8_t)0x80);
  REQUIRE(MCP4::B_X1 == (uint8_t)0xB0);
  REQUIRE(MCP4::B_X2 == (uint8_t)0x90);
  REQUIRE(MCP4::BUFFERED_B_X1 == (uint8_t)0xF0);
  REQUIRE(MCP4::BUFFERED_B_X2 == (uint8_t)0xD0);
}

TEST_CASE("MCP4::write(config, value)", "[func]") {
  REQUIRE(dac.write(MCP4::A_OFF, 0xAB) == (uint16_t)0x0AB0);
  REQUIRE(dac.write(MCP4::A_X1, 0xAB) == (uint16_t)0x3AB0);
  REQUIRE(dac.write(MCP4::A_X2, 0xAB) == (uint16_t)0x1AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_A_X1, 0xAB) == (uint16_t)0x7AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_A_X2, 0xAB) == (uint16_t)0x5AB0);

  REQUIRE(dac.write(MCP4::B_OFF, 0xAB) == (uint16_t)0x8AB0);
  REQUIRE(dac.write(MCP4::B_X1, 0xAB) == (uint16_t)0xBAB0);
  REQUIRE(dac.write(MCP4::B_X2, 0xAB) == (uint16_t)0x9AB0);
  REQUIRE(dac.write(MCP4::BUFFERED_B_X1, 0xAB) == (uint16_t)0xFAB0);
  REQUIRE(dac.write(MCP4::BUFFERED_B_X2, 0xAB) == (uint16_t)0xDAB0);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::A_OFF, 0xAB, command);
  REQUIRE(command == (uint16_t)0x0AB0);

  dac.write(MCP4::A_X1, 0xAB, command);
  REQUIRE(command == (uint16_t)0x3AB0);

  dac.write(MCP4::A_X2, 0xAB, command);
  REQUIRE(command == (uint16_t)0x1AB0);

  dac.write(MCP4::BUFFERED_A_X1, 0xAB, command);
  REQUIRE(command == (uint16_t)0x7AB0);

  dac.write(MCP4::BUFFERED_A_X2, 0xAB, command);
  REQUIRE(command == (uint16_t)0x5AB0);

  dac.write(MCP4::B_OFF, 0xAB, command);
  REQUIRE(command == (uint16_t)0x8AB0);

  dac.write(MCP4::B_X1, 0xAB, command);
  REQUIRE(command == (uint16_t)0xBAB0);

  dac.write(MCP4::B_X2, 0xAB, command);
  REQUIRE(command == (uint16_t)0x9AB0);

  dac.write(MCP4::BUFFERED_B_X1, 0xAB, command);
  REQUIRE(command == (uint16_t)0xFAB0);

  dac.write(MCP4::BUFFERED_B_X2, 0xAB, command);
  REQUIRE(command == (uint16_t)0xDAB0);
}
