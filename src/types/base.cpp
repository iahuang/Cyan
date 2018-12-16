#include "base.hpp"

namespace types {
    Object& CyFunc(CyMemory& loc, Fcall body) {
        Object& f = loc.allocate();
        f.nativeValue = body;
        return f;
    }
    namespace cystring {
        Object& string_tostring(Object& self, vector<Object*> args){return *args[0];}

    }
    
    Object& CyString(CyMemory& loc, string s) {
        Object& msg = loc.allocate();
        msg.value = true;
        msg.nativeValue = s;
        Object& f = CyFunc(loc, cystring::string_tostring);
        // msg.set("toString", f);
        return msg;
    }
    Object& CyNull(CyMemory& loc) { 
        Object& x = loc.allocate();
        x.value = true;
        return x;
    }
    namespace cyint {
        Object& int_tostring(Object& self, vector<Object*> args) {
            return CyString(*(self.source), to_string(any_cast<int>(self.nativeValue)));
        }
    }
    Object& CyInt(CyMemory& loc, int s) {
        Object& x = loc.allocate();
        x.value = true;
        x.nativeValue = s;
        Object& f = CyFunc(loc, cyint::int_tostring);
        x.set("toString", f);
        return x;
    }
}