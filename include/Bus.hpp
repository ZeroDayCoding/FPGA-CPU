#ifndef __BUS_HPP__
#define __BUS_HPP__
#include "Common.hpp"
#include <bitset>
#include <memory>
namespace ZDC
{
    namespace Emulator
    {
        
        template<size_t Lines>
        using Bus = std::bitset<Lines>;

        using MemoryBus = Bus<32>;
        using AddressBus = Bus<32>;
        using IOAddrBus = Bus<16>;
        using IOMemBus = Bus<8>;

        template<size_t Lines>
        class BusConnector {
        private:
            std::shared_ptr<Bus<Lines>> ptrBus;

        public:
            // Gets the underlying bus, if nullptr then bus isn't connected.
            inline Bus<Lines>* get() { return ptrBus.get(); };

        public:
            BusConnector() = default;
            ~BusConnector() = default;

        public:
            BusConnector(BusConnector&& o) : ptrBus(std::move(o.ptrBus)) {};
            BusConnector& operator=(BusConnector&& o) { ptrBus = std::move(o.ptrBus); return *this; };
            BusConnector(const BusConnector& o) : ptrBus(o.ptrBus) {};
            BusConnector& operator=(const BusConnector& o) { ptrBus = o.ptrBus; return *this; };
        };

    } // namespace Emulator
} // namespace ZDC
#endif//__BUS_HPP__ GUARD