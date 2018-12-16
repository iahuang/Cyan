#include "cyio.hpp"

Object& cyPrint(Object& self, vector<Object*> args) {
    Object& s = *args[0];
    std::cout << any_cast<string>(s.call("toString", {}).nativeValue)
              << endl;
    return s;
}

Object& cyio::c_init(CyMemory& loc) {
    Object& p = loc.allocate();
    p.set("print", types::CyFunc(loc, cyPrint));
    return p;
}