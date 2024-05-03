#ifndef __FPGA_HPP__
#define __FPGA_HPP__
#include <map>

namespace ZDC
{
    namespace EMULATOR
    {
        class FPGA {
        private:
            // A map of the setup hints that are in use during the FPGA setup process.
            std::map<int, int> mapHints;
            // A pointer to the constructed internal FPGA structure.
            void* pIFPGA;

        public:
            /// @brief Gets the hint for the identifier, defaults to the given value if not found.
            /// @param nIdentifier The identifier for the hint to be used.
            /// @param nDefaultValue The default value for the hint if not found.
            /// @return The value that the hint is using, will be the default value if not found.
            inline int getSetupHint(int nIdentifier, int nDefaultValue) {
                decltype(mapHints)::iterator found = mapHints.find(nIdentifier);
                if(found == mapHints.end()) return nDefaultValue;
                return found->second;
            }
            
            /// @brief During setup some information is implied but can be specified using hints.
            /// @param nIdentifier The hint's identifier, see FPGA_HINT_{x} macros (where X is the name of the hint).
            /// @param nValue The hint's value, see FPGA_HINT_{x}_{y} macros (where X is the name of the hint, Y is the specifc value).
            inline void setSetupHint(int nIdentifier, int nValue) { mapHints[nIdentifier] = nValue; }

            /// @brief Sets up the Logic Cell grid using the width/height as the grid's dimensions.
            /// @param width The width of the FPGA Logic Cell grid.
            /// @param height The height of the FPGA Logic Cell grid.
            /// @return True if the grid was successfully created, otherwise false (see errno for more info).
            bool setupLogicCellGrid(int width, int height);
        };
    } // namespace EMULATOR
} // namespace ZDC
#endif//__FPGA_HPP__ GUARD