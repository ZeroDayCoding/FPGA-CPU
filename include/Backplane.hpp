#ifndef __BACKPLANE_HPP__
#define __BACKPLANE_HPP__
#include "Common.hpp"
#include "Bus.hpp"
namespace ZDC
{
    namespace Emulator
    {
        namespace Backplane {
            
            class MMU : Emulated {
            public:
                virtual void ClockTick() = 0;
            };

            /**
             * The MainBoard is used to connect the bus's between the IO and Memory using the MMU.
             */
            class MainBoard {
            public:
                // This control bus is connected directly to the CPU's and the MMU.
                ZDC::Emulator::CtrlBus oCtrlBusCPU;
                // This data bus is connected directly to the CPU's and the MMU.
                ZDC::Emulator::DataBus oDataBusCPU;
                // This address bus is connected directly to the CPU's and the MMU.
                ZDC::Emulator::AddrBus oAddrBusCPU;

            public:
                // This control bus is connected directly to the MMU and the IO and/or memory.
                ZDC::Emulator::CtrlBus oCtrlBusMMU;
                // This data bus is connected directly to the MMU and the IO and/or memory.
                ZDC::Emulator::DataBus oDataBusMMU;
                // This address bus is connected directly to the MMU and the IO and/or memory.
                ZDC::Emulator::AddrBus oAddrBusMMU;

            public:

            };
            

        } // namespace Backplane
    } // namespace Emulator
} // namespace ZDC
#endif//__BACKPLANE_HPP__ GUARD