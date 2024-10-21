module;

#include <cstdint>
#include <iostream>

// NES has a built in 2K memory, plus the cartridge, which may have any of a number of mappings.
// $0000 to $07FF is built in memory.

// PPU is $2000 to $2007. Also has its own bus, 16K addressable range: Graphics on cartridge 8 kb from $0600 to $1FFF. VRAM 2K - $2000 to $27FF. Palettes $3F00 to $3FFF. 
// PPU also has Object Attribute Memory not on bus, to store sprites. 
// PPU clocked at 3x CPU clock.
// APU for sound is $4000 to $4017.

// Cartridge is roughly $4020 to $FFFF.

export module bus;

namespace bus
{
    void write_u8(uint16_t address, uint8_t value)
    {
        std::cout << "Stub: Write" << value << " to " << address << "\n";
    }
}