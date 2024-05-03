#include "Common.hpp"
#include <mutex>
#include <memory>
#include <vector>
namespace ZDC
{
    namespace Emulator
    {
        /**
         * A mutex to prevent the modification of the vectEmulated static variable, 
         * especially as we are iterating through it.
         */
        static std::mutex mutexVectEmulated;
        
        /**
         * A vector of Emulated object's, via their pointer, automatically 
         * added/removed when they are created or destroyed.
         */
        static std::vector<Emulated*> vectEmulated;

        Emulated::Emulated() {
            std::lock_guard guard(mutexVectEmulated);
            vectEmulated.push_back(this);
        }

        Emulated::~Emulated() {
            std::lock_guard guard(mutexVectEmulated);
            for(auto it = vectEmulated.begin(); it != vectEmulated.end(); it++){
                if((*it) == this) {
                    vectEmulated.erase(it);
                    break;
                }
            }
        }

        void TickEmulator(float delta) {
            std::lock_guard guard(mutexVectEmulated);
            for(auto it : vectEmulated)
                it->EmulatorTick(delta);
        }
    } // namespace Emulator
} // namespace ZDC
