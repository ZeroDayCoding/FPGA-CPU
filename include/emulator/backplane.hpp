#pragma once
#include "common.hpp"
#include <vector>
namespace ZDC
{
    namespace Backplane
    {
        template<typename SlotType>
        class Slots;

        template<typename SlotType>
        class SlotBuses;

        template<typename SlotType>
        class SlotBackplane;

        /// @brief A main slot of the backplane, usually reserved for CPU's.
        class MainSlot {
            friend class Slots<MainSlot>;
        public:
            union ControlLines {
                #pragma pack(push, 1)
                struct Flags {
                    /// @brief When set the current memory operation will be a write.
                    uint16_t write : 1;
                    /// @brief When set the processor is currently attempting a memory operation.
                    uint16_t memory_enable : 1;
                    /// @brief When set the processor is currently attempting an I/O operation.
                    uint16_t io_enable : 1;
                    /// @brief The current privilege level that the current operation is being performed in. 
                    uint16_t privilege_level : 2;
                } AsStruct;
                #pragma pack(pop)
                uint16_t AsNumber;
            public:
                ControlLines(uint16_t nValue) : AsNumber(nValue) {}
            };

        public:
            using CtrlBus = ControlLines;
            using IOPortBus = uint16_t;
            using MemoryBus = uint32_t;
            using AddressBus = uint32_t;

        private:
            SlotBuses<MainSlot>* ptrBuses;
            SlotBackplane<MainSlot>* ptrSlotConnection;

        public:
            SlotBuses<MainSlot>& buses() { return *ptrBuses; }
            const SlotBuses<MainSlot>& buses() const { return *ptrBuses; }
            bool hasConnection() const { return ptrSlotConnection != 0; }
            SlotBackplane<MainSlot>& connection() { return *ptrSlotConnection; }
            void connect(SlotBackplane<MainSlot>* ptrConnection) { this->disconnect(); ptrSlotConnection = ptrConnection; if(ptrConnection) ptrConnection->ptrSlotType = this; }
            void disconnect() { if(ptrSlotConnection) ptrSlotConnection->ptrSlotType = 0; ptrSlotConnection = 0; }

        public:
            MainSlot() {};
        };

        /// @brief A sub slot of the backplane, used by I/O, memory and other chips.
        class SubSlot {
            friend class Slots<SubSlot>;
        public:
            using CtrlBus = uint16_t;
            using MemoryBus = uint32_t;
            using AddressBus = uint32_t;
            using IOPortBus = uint16_t;

        private:
            SlotBuses<SubSlot>* ptrBuses;
            SlotBackplane<SubSlot>* ptrSlotConnection;

        public:
            SlotBuses<SubSlot>& buses() { return *ptrBuses; }
            const SlotBuses<SubSlot>& buses() const { return *ptrBuses; }
            bool hasConnection() const { return ptrSlotConnection != 0; }
            SlotBackplane<SubSlot>& connection() { return *ptrSlotConnection; }
            void connect(SlotBackplane<SubSlot>* ptrConnection) { this->disconnect(); ptrSlotConnection = ptrConnection; if(ptrConnection) ptrConnection->ptrSlotType = this; }
            void disconnect() { if(ptrSlotConnection) ptrSlotConnection->ptrSlotType = 0; ptrSlotConnection = 0; }

        public:
            SubSlot() {};
        };

        template<typename SlotType>
        class SlotBackplane {
            friend class SlotType;
        private:
            SlotType* ptrSlotType;

        public:
            bool isConnected() const { return ptrSlotType != 0; }
            SlotType& slot() { return *ptrSlotType; }
            const SlotType& slot() const { return *ptrSlotType; }

        public:
            virtual void ClkTick() = 0;
        };

        template<typename BusLanes, uint64_t BusMask=((uint64_t)~0)>
        class Bus {
        private:
            /// @brief The bus asserted value.
            BusLanes _lanes = (BusLanes)0;
            /// @brief A pointer to the asserter that is currently asserting on this bus.
            void* _asserter = 0;

        public:
            /// @return True if, and only if, no out of bounds bus lanes are asserted; otherwise, false.
            inline bool isValid() const { return (_lanes & (BusLanes)BusMask); }
            /// @return A reference to the bus's lanes.
            inline BusLanes& lanes() { return _lanes; }
            /// @return A constant reference to the bus's lanes.
            inline const BusLanes& lanes() const { return _lanes; }
            /// @return True if, and only if, the bus currently has an asserter; otherwise, false.
            inline void* asserter() const { return _asserter; }
            /// @brief Claims the bus for a specific asserter, shouldn't be unclaimed unless by that asserter.
            inline void asserter(void* asserter) { _asserter = asserter; }

        public:
            Bus() = default;
        };

        template<typename SlotType>
        class SlotBuses {
        public:
            /// @brief The control bus, used by the slots in this group to assert control lines.
            Bus<typename SlotType::CtrlBus> oCtrlBus;
            /// @brief An IO port bus, used by the slots in this group to assert an IO port value.
            Bus<typename SlotType::IOPortBus> oIOPortBus;
            /// @brief A memory bus, used by the slots in this group to assert a memory value.
            Bus<typename SlotType::MemoryBus> oMemoryBus;
            /// @brief An address bus, used by the slots in this group to assert an address value.
            Bus<typename SlotType::AddressBus> oAddressBus;
        };

        template<typename SlotType>
        class Slots {
        public:
            SlotBuses<SlotType> oBuses;
            /// @brief An array of four slots, initially unpopulated but later connected.
            SlotType arrSlots[4];

        public:
            Slots() {
                for(size_t i = 0; i < sizeof(arrSlots) / sizeof(arrSlots[0]); i++)
                    arrSlots[i].ptrBuses = &oBuses;
            }
            ~Slots() = default;

        public:
            void ClcTick();
        };

        /// @brief The backplane of our system, composed of main/sub slots and an FPGA MMU.
        class Backplane {
        public:
            Slots<MainSlot> mainSlots;
            Slots<SubSlot> subSlots;
        };

    } // namespace Backplane
} // namespace ZDC
