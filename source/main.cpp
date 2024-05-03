#include "Bus.hpp"
#include "Backplane.hpp"
#include <iostream>
#include <thread>
#include <assert.h>

int main(int argc, const char* argv[]) {

    float clockrate = 1 / 1000;

    while(true) {
        ZDC::Emulator::TickEmulator(clockrate);
        std::this_thread::yield();
    }
    return 0;
}