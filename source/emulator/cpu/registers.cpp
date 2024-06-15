#include "emulator/cpu/core.hpp"
#include <iostream>
#include <iomanip>

namespace ZDC
{
    namespace Emulator
    {
        namespace CPU
        {
            GPRegisters::GPRegisters() {
                for(size_t i = 0; i < sizeof(arrRegs) / sizeof(GPRegister); i++)
                    arrRegs[i] = 0;
            }

            GPRegister& GPRegisters::reg(size_t i) {
                if(i >= sizeof(arrRegs) / sizeof(GPRegister)) {
                    printf("FATAL: Attempted to access a General Purpose Register that was out of bounds, range = [0-%ld); index = %ld.\n",sizeof(arrRegs) / sizeof(GPRegister),i);
                    abort();
                }
                return arrRegs[i];
            }

            GPHalfRegister& GPRegisters::high(size_t i) {
                if(i >= sizeof(arrRegs) / sizeof(GPRegister)) {
                    printf("FATAL: Attempted to access a General Purpose Register that was out of bounds, range = [0-%ld); index = %ld.\n",sizeof(arrRegs) / sizeof(GPRegister),i);
                    abort();
                }
                return *((GPHalfRegister*)(&arrRegs[i]) + 1);
            }

            GPHalfRegister& GPRegisters::low(size_t i) {
                if(i >= sizeof(arrRegs) / sizeof(GPRegister)) {
                    printf("FATAL: Attempted to access a General Purpose Register that was out of bounds, range = [0-%ld); index = %ld.\n",sizeof(arrRegs) / sizeof(GPRegister),i);
                    abort();
                }
                return *(GPHalfRegister*)(&arrRegs[i]);
            }

            void GPRegisters::dump(std::ostream& stream) noexcept {
                stream << "GP Registers:" << std::endl;
                for(size_t i = 0; i < sizeof(arrRegs) / sizeof(GPRegister); i++) {
                    stream << "  r" << i << "  =  0x" << std::hex << std::setfill('0') << std::setw(8) << arrRegs[i];
                    if(i % 2 == 1) stream << std::endl; else stream << "  |";
                }
            }

            void FlagsRegister_u::dump(std::ostream& stream) noexcept {
                if(this->AsStruct.zf) stream << "zf";
            }

            void SPRegisters::dump(std::ostream& stream) noexcept {
                stream << "SP Registers:" << std::endl;
                stream << "  ip\t=  0x" << std::hex << std::setfill('0') << std::setw(16) << ip << std::endl;
                stream << "  flags\t:  "; flags.dump(stream); stream << std::endl;
            }

            void SPRegisters::reset() {
                ip = 0x0000000000000000;
                flags.AsNumber = 0x0000000000000000;
            }

            void Registers::dump(std::ostream& stream) noexcept {
                gp.dump(stream);
                sp.dump(stream);
            }
        } // namespace CPU
    } // namespace Emulator
} // namespace ZDC