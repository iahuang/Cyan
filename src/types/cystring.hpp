#pragma once
#include "../main.hpp"
#include "cyfunc.hpp"

namespace types {
    obj_ptr toString2(obj_ptr self, obj_ptr* args) { return self; }

    obj_ptr CyString(CyMemory& loc, string s) {
        obj_ptr msg = loc.allocate();
        msg->nativeValue = s;
        obj_ptr f = CyFunc(loc, toString2);
        msg->properties["toString"] = f;
        return msg;
    }
}  // namespace types
