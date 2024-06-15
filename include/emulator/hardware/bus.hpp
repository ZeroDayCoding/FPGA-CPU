#pragma once
#include "common.hpp"
#include <list>

namespace ZDC
{
    namespace Emulator
    {
        namespace Hardware
        {
            
            typedef unsigned long long int AddressBus;
            typedef unsigned int DataBus;

            class BusConnection;

            template<typename Lines>
            class Bus {
                DISABLE_COPY_CONSTRUCTOR(Bus<Lines>);
                DISABLE_MOVE_CONSTRUCTOR(Bus<Lines>);
            private:
                Lines _lines = 0;
                std::list<BusConnection&> listConnections;

            public:
                Bus() = default;
                ~Bus() = default;

            public:
                inline Lines& lines() { return _lines; };

            public:
                void connect(BusConnection& connection);
                void disconnect(BusConnection& connection);
            };
            
            class BusConnection {
                template<typename Lines> friend class Bus;
            protected:
                virtual void OnBusConnect(void* bus) {};
                virtual void OnBusDisconnect(void* bus) {};
            };

        } // namespace Hardware
    } // namespace Emulator
} // namespace ZDC
