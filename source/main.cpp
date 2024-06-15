#include <iostream>
#include <math.h>
#include "emulator/cpu/core.hpp"

int main(int argc, const char* argv[]) {
    Registers regs;
    regs.gp.reg(0) = 0xDEADC0DE;
    regs.gp.high(1) = 0xBEEF;
    regs.gp.high(2) = 0xDECE;
    regs.gp.low(2) = 0xA5ED;
    regs.dump(std::cout);
    return 0;
}