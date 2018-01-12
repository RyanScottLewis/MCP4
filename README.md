# DAC MCP4

Command generator for the MCP4 series of Digital-to-Analog Converters (DAC).

> At the moment this library currently only supports the following product families:
>
> * MCP4801/MCP4811/MCP4821
> * MCP4802/MCP4812/MCP4822
> * MCP4901/MCP4911/MCP4921
> * MCP4902/MCP4912/MCP4922

This library only handles a single device type globally (you probably wouldn't mix multiple device types on a project)
and does not handle command transmission, only command generation.

## Usage

```c++
// Setup MPC4 library
#define MCP4_DEVICE MCP4922
#include <MCP4.h>

// Initialize the command generator
MCP4 mcp4 = MCP4();

// Write a buffered value to the B channel with 1x gain
int16_t command = mcp4.write( MCP4::BUFFERED_B_X1, 0x555 );

// Command is now the following: 1111 0101 0101 0101
// Transmit the command to the DAC here
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/RyanScottLewis/MCP4. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## Roadmap

- [ ] MCP4706
- [ ] MCP4716
- [ ] MCP4725
- [ ] MCP4726
- [ ] MCP4728
- [ ] MCP47A1
- [ ] MCP47DA1
- [ ] MCP47FEB01
- [ ] MCP47FEB02
- [ ] MCP47FEB11
- [ ] MCP47FEB12
- [ ] MCP47FEB21
- [ ] MCP47FEB22
- [ ] MCP47FVB01
- [ ] MCP47FVB02
- [ ] MCP47FVB11
- [ ] MCP47FVB12
- [ ] MCP47FVB21
- [ ] MCP47FVB22
- [x] MCP4801
- [x] MCP4802
- [x] MCP4811
- [x] MCP4812
- [x] MCP4821
- [x] MCP4822
- [ ] MCP48FEB01
- [ ] MCP48FEB02
- [ ] MCP48FEB11
- [ ] MCP48FEB12
- [ ] MCP48FEB21
- [ ] MCP48FEB22
- [ ] MCP48FVB01
- [ ] MCP48FVB02
- [ ] MCP48FVB11
- [ ] MCP48FVB12
- [ ] MCP48FVB21
- [ ] MCP48FVB22
- [x] MCP4901
- [x] MCP4902
- [x] MCP4911
- [x] MCP4912
- [x] MCP4921
- [x] MCP4922
- [ ] TC1320
- [ ] TC1321

## License

The gem is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).
