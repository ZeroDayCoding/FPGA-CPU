#ifndef __BUS_HPP__
#define __BUS_HPP__
#include "Common.hpp"
namespace ZDC
{
    namespace Emulator
    {
        union Bus8 {
            struct Lines {
                uint8_t d0 : 1;
                uint8_t d1 : 1;
                uint8_t d2 : 1;
                uint8_t d3 : 1;
                uint8_t d4 : 1;
                uint8_t d5 : 1;
                uint8_t d6 : 1;
                uint8_t d7 : 1;
            } AsLines;
            struct Nibbles {
                uint8_t Low : 4;
                uint8_t High : 4;
            } AsNibbles;
            uint8_t AsNumber = 0;

        public:
            Bus8() {};
        };

        union Bus16 {
            struct Lines {
                uint16_t  d0 : 1;
                uint16_t  d1 : 1;
                uint16_t  d2 : 1;
                uint16_t  d3 : 1;
                uint16_t  d4 : 1;
                uint16_t  d5 : 1;
                uint16_t  d6 : 1;
                uint16_t  d7 : 1;
                uint16_t  d8 : 1;
                uint16_t  d9 : 1;
                uint16_t d10 : 1;
                uint16_t d11 : 1;
                uint16_t d12 : 1;
                uint16_t d13 : 1;
                uint16_t d14 : 1;
                uint16_t d15 : 1;
            } AsLines;
            struct HalfWord {
                uint16_t Low : 8;
                uint16_t High : 8;
            } AsHalfWord;
            Bus8 AsBus8;
            uint16_t AsNumber = 0;

        public:
            Bus16() {};
        };
        
        union Bus32 {
            struct Lines {
                uint32_t  d0 : 1;
                uint32_t  d1 : 1;
                uint32_t  d2 : 1;
                uint32_t  d3 : 1;
                uint32_t  d4 : 1;
                uint32_t  d5 : 1;
                uint32_t  d6 : 1;
                uint32_t  d7 : 1;
                uint32_t  d8 : 1;
                uint32_t  d9 : 1;
                uint32_t d10 : 1;
                uint32_t d11 : 1;
                uint32_t d12 : 1;
                uint32_t d13 : 1;
                uint32_t d14 : 1;
                uint32_t d15 : 1;
                uint32_t d16 : 1;
                uint32_t d17 : 1;
                uint32_t d18 : 1;
                uint32_t d19 : 1;
                uint32_t d20 : 1;
                uint32_t d21 : 1;
                uint32_t d22 : 1;
                uint32_t d23 : 1;
                uint32_t d24 : 1;
                uint32_t d25 : 1;
                uint32_t d26 : 1;
                uint32_t d27 : 1;
                uint32_t d28 : 1;
                uint32_t d29 : 1;
                uint32_t d30 : 1;
                uint32_t d31 : 1;
            } AsLines;
            struct Word {
                uint32_t Low  : 16;
                uint32_t High : 16;
            } AsWord;
            Bus16 AsBus16;
            uint32_t AsNumber = 0;

        public:
            Bus32() {};
        };

        union Bus64 {
            struct Lines {
                uint64_t  d0 : 1;
                uint64_t  d1 : 1;
                uint64_t  d2 : 1;
                uint64_t  d3 : 1;
                uint64_t  d4 : 1;
                uint64_t  d5 : 1;
                uint64_t  d6 : 1;
                uint64_t  d7 : 1;
                uint64_t  d8 : 1;
                uint64_t  d9 : 1;
                uint64_t d10 : 1;
                uint64_t d11 : 1;
                uint64_t d12 : 1;
                uint64_t d13 : 1;
                uint64_t d14 : 1;
                uint64_t d15 : 1;
                uint64_t d16 : 1;
                uint64_t d17 : 1;
                uint64_t d18 : 1;
                uint64_t d19 : 1;
                uint64_t d20 : 1;
                uint64_t d21 : 1;
                uint64_t d22 : 1;
                uint64_t d23 : 1;
                uint64_t d24 : 1;
                uint64_t d25 : 1;
                uint64_t d26 : 1;
                uint64_t d27 : 1;
                uint64_t d28 : 1;
                uint64_t d29 : 1;
                uint64_t d30 : 1;
                uint64_t d31 : 1;
                uint64_t d32 : 1;
                uint64_t d33 : 1;
                uint64_t d34 : 1;
                uint64_t d35 : 1;
                uint64_t d36 : 1;
                uint64_t d37 : 1;
                uint64_t d38 : 1;
                uint64_t d39 : 1;
                uint64_t d40 : 1;
                uint64_t d41 : 1;
                uint64_t d42 : 1;
                uint64_t d43 : 1;
                uint64_t d44 : 1;
                uint64_t d45 : 1;
                uint64_t d46 : 1;
                uint64_t d47 : 1;
                uint64_t d48 : 1;
                uint64_t d49 : 1;
                uint64_t d50 : 1;
                uint64_t d51 : 1;
                uint64_t d52 : 1;
                uint64_t d53 : 1;
                uint64_t d54 : 1;
                uint64_t d55 : 1;
                uint64_t d56 : 1;
                uint64_t d57 : 1;
                uint64_t d58 : 1;
                uint64_t d59 : 1;
                uint64_t d60 : 1;
                uint64_t d61 : 1;
                uint64_t d62 : 1;
                uint64_t d63 : 1;
            } AsLines;
            struct DoubleWord {
                uint64_t Low  : 32;
                uint64_t High : 32;
            } AsDoubleWord;
            Bus32 AsBus32;
            uint64_t AsNumber = 0;

        public:
            Bus64() {};
        };

        using DataBus = Bus64;
        using AddrBus = Bus64;
        using CtrlBus = Bus16;

    } // namespace Emulator
} // namespace ZDC
#endif//__BUS_HPP__ GUARD