#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define MCP4_DEVICE MCP4812
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

  REQUIRE(MCP4::B_OFF == 0x80);
  REQUIRE(MCP4::B_X1 == 0xB0);
  REQUIRE(MCP4::B_X2 == 0x90);
}

TEST_CASE("MCP4::write(config, value)", "[func]") {
  REQUIRE(dac.write(MCP4::A_OFF, 0xABCD) == 0x0F34);
  REQUIRE(dac.write(MCP4::A_X1, 0xABCD) == 0x3F34);
  REQUIRE(dac.write(MCP4::A_X2, 0xABCD) == 0x1F34);

  REQUIRE(dac.write(MCP4::B_OFF, 0xABCD) == 0x8F34);
  REQUIRE(dac.write(MCP4::B_X1, 0xABCD) == 0xBF34);
  REQUIRE(dac.write(MCP4::B_X2, 0xABCD) == 0x9F34);
}

TEST_CASE("MCP4::write(config, value, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::A_OFF, 0xABCD, command);
  REQUIRE(command == 0x0F34);

  dac.write(MCP4::A_X1, 0xABCD, command);
  REQUIRE(command == 0x3F34);

  dac.write(MCP4::A_X2, 0xABCD, command);
  REQUIRE(command == 0x1F34);

  dac.write(MCP4::B_OFF, 0xABCD, command);
  REQUIRE(command == 0x8F34);

  dac.write(MCP4::B_X1, 0xABCD, command);
  REQUIRE(command == 0xBF34);

  dac.write(MCP4::B_X2, 0xABCD, command);
  REQUIRE(command == 0x9F34);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower)", "[func]") {
  REQUIRE(dac.write(MCP4::A_OFF, 0xAB, 0xCD) == 0x0F34);
  REQUIRE(dac.write(MCP4::A_X1, 0xAB, 0xCD) == 0x3F34);
  REQUIRE(dac.write(MCP4::A_X2, 0xAB, 0xCD) == 0x1F34);

  REQUIRE(dac.write(MCP4::B_OFF, 0xAB, 0xCD) == 0x8F34);
  REQUIRE(dac.write(MCP4::B_X1, 0xAB, 0xCD) == 0xBF34);
  REQUIRE(dac.write(MCP4::B_X2, 0xAB, 0xCD) == 0x9F34);
}

TEST_CASE("MCP4::write(config, valueUpper, valueLower, *command)", "[func]") {
  uint16_t command = 0;

  dac.write(MCP4::A_OFF, 0xAB, 0xCD, command);
  REQUIRE(command == 0x0F34);

  dac.write(MCP4::A_X1, 0xAB, 0xCD, command);
  REQUIRE(command == 0x3F34);

  dac.write(MCP4::A_X2, 0xAB, 0xCD, command);
  REQUIRE(command == 0x1F34);

  dac.write(MCP4::B_OFF, 0xAB, 0xCD, command);
  REQUIRE(command == 0x8F34);

  dac.write(MCP4::B_X1, 0xAB, 0xCD, command);
  REQUIRE(command == 0xBF34);

  dac.write(MCP4::B_X2, 0xAB, 0xCD, command);
  REQUIRE(command == 0x9F34);
}
