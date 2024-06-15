#pragma once
#include <cstdlib>
#include <iostream>

namespace ZDC
{
    namespace Emulator
    {
        namespace CPU
        {

            typedef unsigned int GPRegister;
            typedef unsigned short GPHalfRegister;

            class GPRegisters {
            private:
                GPRegister arrRegs[8];

            public:
                GPRegisters();

            public:
                GPRegister& reg(size_t i);
                GPHalfRegister& high(size_t i);
                GPHalfRegister& low(size_t i);

            public:
                void dump(std::ostream& stream) noexcept;
            };

            typedef unsigned long long int SPRegister;

            union FlagsRegister_u {
            public:
                struct FlagsRegister_s {
                    SPRegister zf : 1;
                } AsStruct;
                SPRegister AsNumber;
            public:
                FlagsRegister_u() : AsNumber(0x0000000000000000) {};
                void dump(std::ostream& stream) noexcept;
            };

            class SPRegisters {
            public:
                SPRegister ip;
                FlagsRegister_u flags;

            public:
                inline SPRegisters() { reset(); };

            public:
                void reset();
                void dump(std::ostream& stream) noexcept;
            };

            typedef unsigned int Instruction_t;

            class InternalRegs {
            public:
                Instruction_t instruction;
                
            };

            class Registers {
            public:
                GPRegisters gp;
                SPRegisters sp;
                InternalRegs internal;

            public:
                void dump(std::ostream& stream) noexcept;
            };
            
        } // namespace CPU
    } // namespace Emulator
} // namespace ZDC