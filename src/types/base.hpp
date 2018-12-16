#pragma once
#include "../memory.hpp"

namespace types {
    Object& CyFunc(CyMemory& loc, Fcall body);
    namespace cystring {
        Object& tostring(vector<Object*> args);

    }
    Object& CyString(CyMemory& loc, string s);
    Object& CyNull(CyMemory& loc);
    namespace cyint {
        Object& tostring(vector<Object*> args);
    }
    Object& CyInt(CyMemory& loc, int s);
}
