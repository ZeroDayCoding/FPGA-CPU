#ifndef __COMMON_HPP__
#define __COMMON_HPP__
namespace ZDC
{
    
    typedef char      sint8_t;
    typedef short     sint16_t;
    typedef int       sint32_t;
    typedef long long sint64_t;

    typedef unsigned char      uint8_t;
    typedef unsigned short     uint16_t;
    typedef unsigned int       uint32_t;
    typedef unsigned long long uint64_t;

    namespace Emulator
    {
        
        /// @brief A single analog wire signal, can be: high, low or transitioning between.
        class SingleWire {
        public:
            /// @brief Called when the wire is going from high to low.
            virtual void goingLow() = 0;
            /// @brief Called when the wire is low.
            virtual void beingLow() = 0;
            /// @brief Called when the wire is going from low to high.
            virtual void goingHigh() = 0;
            /// @brief Called when the wire is high.
            virtual void beingHigh() = 0;
            /// @brief Called when the wire is disconnected, or at startup before the wire is connected.
            virtual void disconnect() = 0;
        };

        class Emulated {
        public:
            Emulated();
            virtual ~Emulated();

        public:
            /// @brief Called once per emulator tick, before any clocks are ticked this cycle.
            /// @param delta The amount of emulated time that has passed since last tick.
            virtual void EmulatorTick(float delta) {};
        };

        extern void TickEmulator(float delta);

    } // namespace Emulator
} // namespace ZDC
#endif//__COMMON_HPP__ GUARD