#ifndef __REGISTERS_HPP__
#define __REGISTERS_HPP__
#include "Common.hpp"
namespace ZDC
{
    namespace Emulator
    {
        namespace Registers
        {
#pragma pack(push, 1)
            // General Purpose Registers, useable by the CPU internals including ALU.
            struct GeneralPurpose {
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

            // Special Purpose Registers, used for specific purposes, useable by the CPU internals and ALU.
            struct SpecialPurpose {
                // Program Counter, points to the next instruction to be executed.
                uint32_t pc = 0;
                // Stack Pointer, points to the current head of the stack.
                uint32_t sp = 0;
                // Stack Base Pointer, points to the current stack base (otherwise known as the stack frame).
                uint32_t bp = 0;
                // Quick Return, points to the return address for the current function.
                uint32_t qr = 0;
            };

            // Hardware Configuration Registers, used internally by the CPU but can't be manipulated by the ALU.
            struct HardwareConfiguration {
                // The current permission level that the CPU is currently in.
                uint32_t rPERMLVL = 0;
            };

            // Flags register, used internally by the CPU and the ALU.
            struct CPUFlags {
                // Set when the ALU's result had resulted in a carry.
                uint32_t nCarry : 1;
                // Set when the ALU's parity is even.
                uint32_t nParity : 1;
                // Set when the ALU's result is zero.
                uint32_t nZero : 1;
                // Set when the ALU's result is negative.
                uint32_t nSign : 1;
                // Set when the ALU performs an operation and overflows.
                uint32_t nOverflow : 1;
                // Trap flag, when set will single step the processor.
                uint32_t nTrap : 1;
                // Maskable Interrupt Enable flag, prevents interrupts that can be masked from having any effect.
                uint32_t nIntEnable : 1;
                // The current permission level that the CPU is currently in (0-3).
                uint32_t nPermissionLvl : 2;
                
                // Reserved Flags - Keep as Zero.
                uint32_t reserved : 23;
            };
#pragma pack(pop)    
        } // namespace Registers
    }
}
#endif//__REGISTERS_HPP__ GUARD