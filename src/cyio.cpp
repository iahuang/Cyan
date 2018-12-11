#include "cyio.hpp"

obj_ptr cyPrint(vector<obj_ptr> args) {
    obj_ptr s = args[1];
    std::cout << any_cast<string>(s.call("toString", {})->nativeValue)
              << endl;
    return s;
}

obj_ptr cyio::init(CyMemory& loc) {
    obj_ptr p = loc.allocate();
    p->properties["print"] = types::CyFunc(loc, cyPrint);
    return p;
}