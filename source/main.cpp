#include "CPU.hpp"
#include "Bus.hpp"
#include "Clock.hpp"
#include <iostream>
#include <thread>

void test(void*) {
    std::cout << "I should be shown every line." << std::endl;
}

void testDivided(void*) {
    std::cout << "I should be shown every 4th line." << std::endl;
}

int main(int argc, const char* argv[]) {
    std::shared_ptr<ZDC::Emulator::MemoryBus> ptrMemoryBus = std::make_shared<ZDC::Emulator::MemoryBus>();
    std::shared_ptr<ZDC::Emulator::AddressBus> ptrAddressBus = std::make_shared<ZDC::Emulator::AddressBus>();

    std::shared_ptr<ZDC::Emulator::Clock> ptrClock = std::make_shared<ZDC::Emulator::Clock>();
    ptrClock->addClockTick(test, nullptr);

    std::shared_ptr<ZDC::Emulator::ClockDivider> ptrClockDivider = std::make_shared<ZDC::Emulator::ClockDivider>(4);
    ptrClockDivider->setParent(ptrClock);
    ptrClockDivider->addClockTick(testDivided, nullptr);

    while(true) {
        ptrClock->clock();
        std::this_thread::yield();
    }
    return 0;
}