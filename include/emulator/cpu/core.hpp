#pragma once
#include "registers.hpp"

namespace ZDC
{
    namespace Emulator
    {
        namespace CPU
        {

            class Core {
            private:
                int step;
                int instruction;

                Registers regs;
            };

        } // namespace CPU
    } // namespace Emulator
} // namespace ZDC