#pragma once

#include <stdint.h>

#define MCP4_VERSION "0.1.0"

#define MCP4706 1
#define MCP4716 2
#define MCP4725 3
#define MCP4726 4
#define MCP4728 5
#define MCP47A1 6
#define MCP47DA1 7
#define MCP47FEB01 8
#define MCP47FEB02 9
#define MCP47FEB11 10
#define MCP47FEB12 11
#define MCP47FEB21 12
#define MCP47FEB22 13
#define MCP47FVB01 14
#define MCP47FVB02 15
#define MCP47FVB11 16
#define MCP47FVB12 17
#define MCP47FVB21 18
#define MCP47FVB22 19
#define MCP4801 20
#define MCP4802 21
#define MCP4811 22
#define MCP4812 23
#define MCP4821 24
#define MCP4822 25
#define MCP48FEB01 26
#define MCP48FEB02 27
#define MCP48FEB11 28
#define MCP48FEB12 29
#define MCP48FEB21 30
#define MCP48FEB22 31
#define MCP48FVB01 32
#define MCP48FVB02 33
#define MCP48FVB11 34
#define MCP48FVB12 35
#define MCP48FVB21 36
#define MCP48FVB22 37
#define MCP4901 38
#define MCP4902 39
#define MCP4911 40
#define MCP4912 41
#define MCP4921 42
#define MCP4922 43
#define TC1320 44
#define TC1321 45

class MCP4 {
public:
  // -= Constants =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// MCP48XX/MCP49XX
#if MCP4_DEVICE == MCP4801 || MCP4_DEVICE == MCP4811 || MCP4_DEVICE == MCP4821 || MCP4_DEVICE == MCP4802 || MCP4_DEVICE == MCP4812 || MCP4_DEVICE == MCP4822 || MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
  static const uint16_t DATA = 0xFFF;  // The 12-bit data bitmask

  // Configuration - These are stored as uint8_t to save space on any embedded systems
  static const uint8_t SHDN = 0x10;  // Output shutdown control bit (0: Shutdown mode, 1: Active mode)
  static const uint8_t GA   = 0x20;  // Output gain selection bit (0: 2x, 1: 1x)
#endif

// MCP48X1/MCP49X1
#if MCP4_DEVICE == MCP4801 || MCP4_DEVICE == MCP4811 || MCP4_DEVICE == MCP4821 || MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921
  static const uint8_t OFF = 0;
  static const uint8_t X1  = GA | SHDN;
  static const uint8_t X2  = SHDN;
#endif

// MCP48X2/MCP49X2
#if MCP4_DEVICE == MCP4802 || MCP4_DEVICE == MCP4812 || MCP4_DEVICE == MCP4822 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
  static const uint8_t AB = 0x80;  // Channel selection bit (0: A, 1: B)

  static const uint8_t A_OFF = 0;
  static const uint8_t A_X1  = GA | SHDN;
  static const uint8_t A_X2  = SHDN;

  static const uint8_t B_OFF = AB;
  static const uint8_t B_X1  = AB | GA | SHDN;
  static const uint8_t B_X2  = AB | SHDN;
#endif

// MCP49XX
#if MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
  static const uint8_t BUF = 0x40;  // Input buffer control bit (0: Unbuffered, 1: Buffered)
#endif

// MCP49X1
#if MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921
  static const uint8_t BUFFERED_X1 = BUF | GA | SHDN;
  static const uint8_t BUFFERED_X2 = BUF | SHDN;
#endif

// MCP49X2
#if MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
  static const uint8_t BUFFERED_A_X1 = BUF | GA | SHDN;
  static const uint8_t BUFFERED_A_X2 = BUF | SHDN;

  static const uint8_t BUFFERED_B_X1 = AB | BUF | GA | SHDN;
  static const uint8_t BUFFERED_B_X2 = AB | BUF | SHDN;
#endif

  // -= Functions =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  // NOTE: I know code shouldnt be in header files but I can't for the life of me figure out a better way to do this (with
  // single-device setup. Could easily implement per-device classes or a single class that accepts a DEVICE as a constructor argument)
  //
  // Also, code is not very dry to save cycles (maybe)?

  MCP4() {}

// MCP480X/MCP490X - 8-bit
#if MCP4_DEVICE == MCP4801 || MCP4_DEVICE == MCP4802 || MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4902

  //! Generate a write command.
  /*!
    \param config The configuration byte to write into the upper nibble of the upper byte.
    \param value  The value.
    \return The resulting command.
  */
  uint16_t write(uint8_t config, uint16_t value) {
    return (config << 8) | (value << 4);
  }

  //! Generate a write command.
  /*!
    \param config  The configuration byte to write into the upper nibble of the upper byte.
    \param value   The value.
    \param command The pointer to the location to set as the resulting command.
    \return The command.
  */
  void write(uint8_t config, uint16_t value, uint16_t &command) {
    command = (config << 8) | (value << 4);
  }

#endif

// MCP481X/MCP491X - 10-bit
#if MCP4_DEVICE == MCP4811 || MCP4_DEVICE == MCP4812 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4912

  //! Generate a write command.
  /*!
    \param config The configuration byte to write into the upper nibble of the upper byte.
    \param value  The value.
    \return The resulting command.
  */
  uint16_t write(uint8_t config, uint16_t value) {
    return (config << 8) | ((value << 2) & DATA);
  }

  //! Generate a write command.
  /*!
    \param config  The configuration byte to write into the upper nibble of the upper byte.
    \param value   The value.
    \param command The pointer to the location to set as the resulting command.
    \return The command.
  */
  void write(uint8_t config, uint16_t value, uint16_t &command) {
    command = (config << 8) | ((value << 2) & DATA);
  }

  //! Generate a write command.
  /*!
    \param config     The configuration byte to write into the upper nibble of the upper byte.
    \param valueUpper The value's upper byte (MSB).
    \param valueLower The value's lower byte (LSB).
    \return The resulting command.
  */
  uint16_t write(uint8_t config, uint8_t valueUpper, uint8_t valueLower) {
    return (config << 8) | ((((valueUpper << 8) | valueLower) << 2) & DATA);
  }

  //! Generate a write command.
  /*!
    \param config     The configuration byte to write into the upper nibble of the upper byte.
    \param valueUpper The value's upper byte (MSB).
    \param valueLower The value's lower byte (LSB).
    \param command    The pointer to the location to set as the resulting command.
    \return The resulting command.
  */
  void write(uint8_t config, uint8_t valueUpper, uint8_t valueLower, uint16_t &command) {
    command = (config << 8) | ((((valueUpper << 8) | valueLower) << 2) & DATA);
  }

#endif

// MCP482X/MCP492X - 12-bit
#if MCP4_DEVICE == MCP4821 || MCP4_DEVICE == MCP4822 || MCP4_DEVICE == MCP4921 || MCP4_DEVICE == MCP4922

  //! Generate a write command.
  /*!
    \param config The configuration byte to write into the upper nibble of the upper byte.
    \param value  The value.
    \return The resulting command.
  */
  uint16_t write(uint8_t config, uint16_t value) {
    return (config << 8) | (value & DATA);
  }

  //! Generate a write command.
  /*!
    \param config  The configuration byte to write into the upper nibble of the upper byte.
    \param value   The value.
    \param command The pointer to the location to set as the resulting command.
    \return The command.
  */
  void write(uint8_t config, uint16_t value, uint16_t &command) {
    command = (config << 8) | (value & DATA);
  }

  //! Generate a write command.
  /*!
    \param config     The configuration byte to write into the upper nibble of the upper byte.
    \param valueUpper The value's upper byte (MSB).
    \param valueLower The value's lower byte (LSB).
    \return The resulting command.
  */
  uint16_t write(uint8_t config, uint8_t valueUpper, uint8_t valueLower) {
    return (config << 8) | (((valueUpper << 8) | valueLower) & DATA);
  }

  //! Generate a write command.
  /*!
    \param config     The configuration byte to write into the upper nibble of the upper byte.
    \param valueUpper The value's upper byte (MSB).
    \param valueLower The value's lower byte (LSB).
    \param command    The pointer to the location to set as the resulting command.
    \return The resulting command.
  */
  void write(uint8_t config, uint8_t valueUpper, uint8_t valueLower, uint16_t &command) {
    command = (config << 8) | (((valueUpper << 8) | valueLower) & DATA);
  }

#endif
};

// MCP48XX/MCP49XX
#if MCP4_DEVICE == MCP4801 || MCP4_DEVICE == MCP4811 || MCP4_DEVICE == MCP4821 || MCP4_DEVICE == MCP4802 || MCP4_DEVICE == MCP4812 || MCP4_DEVICE == MCP4822 || MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
const uint16_t MCP4::DATA;
const uint8_t  MCP4::SHDN;
const uint8_t  MCP4::GA;
#endif

// MCP48X1/MCP49X1
#if MCP4_DEVICE == MCP4801 || MCP4_DEVICE == MCP4811 || MCP4_DEVICE == MCP4821 || MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921
const uint8_t MCP4::OFF;
const uint8_t MCP4::X1;
const uint8_t MCP4::X2;
#endif

// MCP48X2/MCP49X2
#if MCP4_DEVICE == MCP4802 || MCP4_DEVICE == MCP4812 || MCP4_DEVICE == MCP4822 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
const uint8_t MCP4::AB;

const uint8_t MCP4::A_OFF;
const uint8_t MCP4::A_X1;
const uint8_t MCP4::A_X2;

const uint8_t MCP4::B_OFF;
const uint8_t MCP4::B_X1;
const uint8_t MCP4::B_X2;
#endif

// MCP49XX
#if MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921 || MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
const uint8_t MCP4::BUF;
#endif

// MCP49X1
#if MCP4_DEVICE == MCP4901 || MCP4_DEVICE == MCP4911 || MCP4_DEVICE == MCP4921
const uint8_t MCP4::BUFFERED_X1;
const uint8_t MCP4::BUFFERED_X2;
#endif

// MCP49X2
#if MCP4_DEVICE == MCP4902 || MCP4_DEVICE == MCP4912 || MCP4_DEVICE == MCP4922
const uint8_t MCP4::BUFFERED_A_X1;
const uint8_t MCP4::BUFFERED_A_X2;

const uint8_t MCP4::BUFFERED_B_X1;
const uint8_t MCP4::BUFFERED_B_X2;
#endif
