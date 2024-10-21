module;

#include <cstdint>
#include <format>
#include <string>
#include <iostream>

export module cpu;

// Reference: https://www.masswerk.at/6502/6502_instruction_set.html

namespace cpu
{
    struct _registers
    {
        uint16_t PC = 0; // Program Counter
        uint8_t AC = 0; // Accumulator / A
        uint8_t X = 0; // XR
        uint8_t Y = 0; // YR
        uint8_t SR = 0; // Status Register [NV-BDIZC] / P
        uint8_t SP = 0; // Stack Pointer / S
    };
    export _registers reg;

    struct _flags
    {
        // bit 7 to bit 0
        bool N = false; // Negative - a set sign bit in bit position 7.
        bool V = false; // Overflow - An overflow with signed binary arthmetic. -128 to +127
        bool Unused = false; // Just in case
        bool B = false; // Break - The break flag will be inserted, whenever the status register is transferred to the stack by software (BRK or PHP), and will be zero, when transferred by hardware.
        bool D = false; // Decimal (Use BCD for arithmetic)
        bool I = false; // Interrupt (IRQ Disable)
        bool Z = false; // Zero - All zero bits
        bool C = false; // Carry - A buffer and borrow in arthmetic. Comparisons will update this and Z/N, as will shift & rotate.
    };

    export _flags flag;

    export void print_regs()
    {
        std::string reg_status = std::format("PC: {} AC: {} X: {} Y: {} SR: {} SP: {}", reg.PC, reg.AC, reg.X, reg.Y, reg.SR, reg.SP);
        std::cout << reg_status << "\n";
    }

    export void init()
    {
        std::cout << "cpu:init" << "\n";
        print_regs();
    };
} // namespace name
