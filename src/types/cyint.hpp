#pragma once
#include "../cyan.hpp"
#include "cystring.hpp"

namespace types {
    obj_ptr toString(obj_ptr self, obj_ptr* args) {
        return CyString(*self.source, to_string(any_cast<int>(self->nativeValue)));
    }

    obj_ptr CyInt(CyMemory& loc, int s) {
        obj_ptr x = loc.allocate();
        x->nativeValue = s;
        obj_ptr f = CyFunc(loc, toString);
        x->properties["toString"] = f;
        return x;
    }
}
