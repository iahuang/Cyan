#pragma once
#include "../memory.hpp"

namespace types {
    obj_ptr CyFunc(CyMemory& loc, Fcall body);
    namespace cystring {
        obj_ptr toString(vector<obj_ptr> args);

    }
    obj_ptr CyString(CyMemory& loc, string s);
    obj_ptr CyNull(CyMemory& loc);
    namespace cyint {
        obj_ptr toString(vector<obj_ptr> args);
    }
    obj_ptr CyInt(CyMemory& loc, int s);
}
