#include "cyio.hpp"

Object& cyPrint(Object& self, vector<Object*> args) {
    Object& s = *args[0];
    std::cout << any_cast<string>(s.call_func("toString", {}).nativeValue)
              << endl;
    return s;
}

Object& cyio::c_init(CyMemory& loc) {
    Object& p = loc.allocate("cyio_module");
    Object& f = types::CyFunc(loc, cyPrint);
    p.set("print", f);
    return p;
}