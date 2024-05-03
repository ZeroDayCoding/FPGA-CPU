#ifndef __CPU_HPP__
#define __CPU_HPP__
#include "Common.hpp"
namespace ZDC
{
    namespace Emulator
    {
        enum class AddressingMode {
            // The addressing mode is undefined, can't be used.
            NONE = -1,
            // The addressing mode is implied, instruction encodes the register or nothing.
            IMPLIED = 0,
            // The addressing mode is immediate, either an 8/16/32 bit immediate follows the instruction.
            IMMEDIATE,
            // The addressing mode is direct, a 32 bit immediate memory address follows the instruction.
            DIRECT,
            // The addressing mode is indirect, a 32 bit immediate memory address follows the instruction and encodes the actual memory address to be used.
            INDIRECT,
            // The addressing mode is direct indexed, a 32 bit immediate memory address follows the instruction and a register is used to offset this.
            DIRECT_INDEXED,
            // The addressing mode is indirect indexed, a 32 bit immediate memory address follows the instruction and encodes the actual memory address to be used; offset'ed by a register.
            INDIRECT_INDEXED,
            // The addressing mode uses InputOutput ports, a 8/16/32 bit immediate follows the instruction and indicates the port number to use.
            IO,
            // The addressing mode isn't defined as this is a prefix value, which modifies the actual instruction that follows this prefix.
            PREFIX,
        };

        struct GeneralPurposeRegisters {
            // Register #0
            uint32_t r0 = 0;
            // Register #1
            uint32_t r1 = 0;
            // Register #2
            uint32_t r2 = 0;
            // Register #3
            uint32_t r3 = 0;
            // Register #4
            uint32_t r4 = 0;
            // Register #5
            uint32_t r5 = 0;
            // Register #6
            uint32_t r6 = 0;
            // Register #7
            uint32_t r7 = 0;
            // Register #8
            uint32_t r8 = 0;
            // Register #9
            uint32_t r9 = 0;
            // Register #10
            uint32_t r10 = 0;
            // Register #11
            uint32_t r11 = 0;
            // Register #12
            uint32_t r12 = 0;
            // Register #13
            uint32_t r13 = 0;
            // Register #14
            uint32_t r14 = 0;
            // Register #15
            uint32_t r15 = 0;
        };

        struct SpecialPurposeRegisters {
            // Program Counter, points to the next instruction to be executed.
            uint32_t pc = 0;
            // Stack Pointer, points to the current head of the stack.
            uint32_t sp = 0;
            // Stack Base Pointer, points to the current stack base (otherwise known as the stack frame).
            uint32_t bp = 0;
            // Quick Return, points to the return address for the current function.
            uint32_t qr = 0;
        };

        struct HardwareConfigurationRegisters {
            // The current permission level that the CPU is currently in.
            uint32_t rPERMLVL = 0;
        };

        class CPU {
        private:
            union {
                GeneralPurposeRegisters GPR;
                uint32_t arrGPR[sizeof(GeneralPurposeRegisters) / sizeof(uint32_t)];
            };
            union {
                SpecialPurposeRegisters SPR;
                uint32_t arrSPR[sizeof(SpecialPurposeRegisters) / sizeof(uint32_t)];
            };
            union {
                HardwareConfigurationRegisters HCR;
                uint32_t arrHCR[sizeof(HardwareConfigurationRegisters) / sizeof(uint32_t)];
            };
        public:
            CPU() = default;
        };
    } // namespace Emulator 
} // namespace ZDC
#endif//__CPU_HPP__ GUARD