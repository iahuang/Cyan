#include "base.hpp"

namespace types {
    namespace base_static {
        Object& f_i2s(Object& self, vector<Object*> args) {
            return CyString(*(self.source), to_string(any_cast<int>(self.nativeValue)));
        }
        Object& f_s2s(Object& self, vector<Object*> args){return *args[0];}

        Object* i2string;
        Object* s2string;

        void base_init(CyMemory& root) {
            i2string = &CyFunc(root, f_i2s);
            s2string = &CyFunc(root, f_s2s);
        }
    }
    using namespace base_static;
    Object& CyFunc(CyMemory& loc, Fcall body) {
        Object& f = loc.allocate("<function>");
        f.nativeValue = body;
        return f;
    }
    
    Object& CyString(CyMemory& loc, string s) {
        Object& msg = loc.allocate("<string>");
        msg.value = true;
        msg.nativeValue = s;
        Object& f = *s2string;
        // msg.set("toString", f);
        return msg;
    }
    Object& CyNull(CyMemory& loc) { 
        Object& x = loc.allocate("<null>");
        x.value = true;
        return x;
    }
    Object& CyInt(CyMemory& loc, int s) {
        Object& x = loc.allocate("<int>");
        x.value = true;
        x.nativeValue = s;
        Object& f = *i2string;
        x.set("toString", f);
        return x;
    }
}