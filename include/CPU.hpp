#ifndef __CPU_HPP__
#define __CPU_HPP__
#include "Common.hpp"
#include "Registers.hpp"
namespace ZDC
{
    namespace Emulator
    {
        enum class AddressingMode {
            // The addressing mode is undefined, can't be used.
            NONE = -1,
            // The addressing mode isn't defined as this is a prefix value, which modifies the actual instruction that follows this prefix.
            PREFIX = 0,
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
        };

        class CPU {
        protected:
            struct CPUState {
                uint32_t bClkHigh : 1;
                uint32_t nInstCycle : 3;
                uint32_t bIntPend : 1;
                uint32_t bNMIPend : 1;
            };

        private:
            union {
                Registers::GeneralPurpose GPR;
                uint32_t arrGPR[sizeof(Registers::GeneralPurpose) / sizeof(uint32_t)];
            };
            union {
                Registers::SpecialPurpose SPR;
                uint32_t arrSPR[sizeof(Registers::SpecialPurpose) / sizeof(uint32_t)];
            };
            union {
                Registers::HardwareConfiguration HCR;
                uint32_t arrHCR[sizeof(Registers::HardwareConfiguration) / sizeof(uint32_t)];
            };
            union {
                Registers::CPUFlags Flags;
                uint32_t nFlags = 0;
            };
            union {
                CPUState State;
                uint32_t nState = 0;
            };
            
        public:
            CPU() {};
            ~CPU() = default;

        public:
            // CPU(CPU&&) = delete;
            // CPU& operator=(CPU&&) = delete;
            // CPU(const CPU&) = delete;
            // CPU& operator=(const CPU&) = delete;

        public:
            inline void setClock(bool bEnabled) { State.bClkHigh = (uint32_t)bEnabled; };

        public:
            void reset();
            void emulate();
        };
    } // namespace Emulator 
} // namespace ZDC
#endif//__CPU_HPP__ GUARD