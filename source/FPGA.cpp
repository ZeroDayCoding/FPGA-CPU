#include "FPGA.hpp"

namespace ZDC
{
    namespace EMULATOR
    {
        struct FPGAInternal {
            int nGridWidth, nGridHeight;
            void* pLogicCells;

        };

        bool FPGA::setupLogicCellGrid(int width, int height) {
            return false;
        }
    } // namespace EMULATOR
} // namespace ZDC
