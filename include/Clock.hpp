#ifndef __CLOCK_HPP__
#define __CLOCK_HPP__
#include <vector>
#include <memory>
#include <iostream>
namespace ZDC
{
    namespace Emulator
    {
        // A clock "tick" callback function, called once every clock tick.
        typedef void(*FnClockTick)(void* lpParam);

        class ClockDivider : public std::enable_shared_from_this<ClockDivider> {
        public:
            // A potential parent for this clock divider.
            std::weak_ptr<ClockDivider> ptrParent;
            // The number of cycles that must occur before this clock divider ticks.
            const size_t nTargetCyclesTillTick;
            // The number of cycles that must occur before this clock divider ticks.
            size_t nCyclesTillTick = 0;
            // A vector of clock functions that will be ticked when this divider is ticked.
            std::vector<std::pair<FnClockTick, void*>> vectCallbacks;
            // A vector of clock dividers that will be ticked when this divider is ticked.
            std::vector<std::weak_ptr<ClockDivider>> vectDividers;

        public:
            ClockDivider(size_t nTargetCyclesTillTick) : nTargetCyclesTillTick(nTargetCyclesTillTick) {};
            ~ClockDivider() = default;
            ClockDivider(ClockDivider&&) = delete;
            ClockDivider& operator=(ClockDivider&&) = delete;
            ClockDivider(const ClockDivider&) = delete;
            ClockDivider& operator=(const ClockDivider&) = delete;

        public:
            void setParent(std::shared_ptr<ClockDivider> ptrParent) {
                // Remove us from our old parent.
                auto oldParent = this->ptrParent.lock();
                if(oldParent) oldParent->removeDivider(this->shared_from_this());
                // If we have a new parent then we can set it with ease.
                if(ptrParent) {
                    this->ptrParent = ptrParent;
                    ptrParent->vectDividers.push_back(this->weak_from_this());
                }
            }
            void removeDivider(std::shared_ptr<ClockDivider> ptrClockDivider) {
                // Attempt to find the divider and remove it from the list.
                for(auto it = vectDividers.begin(); it != vectDividers.end(); it++) {
                    if((*it).lock() == ptrClockDivider) {
                        ptrClockDivider->ptrParent.reset();
                        vectDividers.erase(it);
                        break;
                    }
                }
            }

        public:
            void addClockTick(FnClockTick fnTick, void* lpParam) {
                this->vectCallbacks.push_back({fnTick, lpParam});
            }

        public:
            void clock() {
                if((++this->nCyclesTillTick) >= this->nTargetCyclesTillTick) {
                    this->nCyclesTillTick = 0;
                    for(auto _divider : vectDividers){
                        auto divider = _divider.lock();
                        if(divider)
                            divider->clock();
                    }
                    for(auto paired : vectCallbacks)
                        paired.first(paired.second);
                }
            }

        public:
            static void clock(void* lpParam) { ((ClockDivider*)lpParam)->clock(); }
        };

        class Clock : public ClockDivider {
        public:
            Clock() : ClockDivider(1) {};
        };

        

    } // namespace Emulator
} // namespace ZDC
#endif//__CLOCK_HPP__ GUARD