#pragma once
#include "../cyan.hpp"

namespace types {
    obj_ptr CyFunc(CyMemory& loc, Fcall body) {
        obj_ptr f = loc.allocate();
        f->nativeValue = body;
        return f;
    }
}
