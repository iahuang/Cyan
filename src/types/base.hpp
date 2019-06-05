#pragma once
#include "../memory.hpp"
#include "native.hpp"

namespace types {
    namespace base_static {
        void base_init(CyMemory& root);
    }
    Object& CyFunc(CyMemory& loc, Fcall body);
    Object& CyString(CyMemory& loc, string s);
    Object& CyNull(CyMemory& loc);
    Object& CyInt(CyMemory& loc, int s);
}
