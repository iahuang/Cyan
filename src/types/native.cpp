#include "native.hpp"

namespace types {
    obj_ptr CyFunc(CyMemory& loc, Fcall body) {
        obj_ptr f = loc.allocate();
        f->nativeValue = body;
        return f;
    }
    namespace cystring {
        obj_ptr toString(vector<obj_ptr> args) { return args[0]; }

    }
    
    obj_ptr CyString(CyMemory& loc, string s) {
        obj_ptr msg = loc.allocate();
        msg->nativeValue = s;
        obj_ptr f = CyFunc(loc, cystring::toString);
        msg->properties["toString"] = f;
        return msg;
    }
    obj_ptr CyNull(CyMemory& loc) {
        obj_ptr x = loc.allocate();
        return x;
    }
    namespace cyint {
        obj_ptr toString(vector<obj_ptr> args) {
            return CyString(*args[0].source, to_string(any_cast<int>(args[0]->nativeValue)));
        }
    }
    obj_ptr CyInt(CyMemory& loc, int s) {
        obj_ptr x = loc.allocate();
        x->nativeValue = s;
        obj_ptr f = CyFunc(loc, cyint::toString);
        x->properties["toString"] = f;
        return x;
    }
}