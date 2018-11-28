#pragma once
#include "../main.hpp"

namespace types {
    obj_ptr CyFunc(CyMemory& loc, Fcall body) {
        obj_ptr f = loc.allocate();
        f->nativeValue = body;
        return f;
    }
}
