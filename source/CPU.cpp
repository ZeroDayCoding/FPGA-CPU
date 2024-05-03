#include "CPU.hpp"
namespace ZDC
{
    namespace Emulator
    {
        void CPU::reset() {
            this->Flags.nPermissionLvl = 0b11;
            this->Flags.reserved = 0;
            this->State.nInstCycle = 0;
            this->SPR.pc = 0;
        }

        void CPU::emulate() {
            if(State.bClkHigh) {

            }
        }
    } // namespace Emulator
} // namespace ZDC
