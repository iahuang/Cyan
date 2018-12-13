#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "types/base.hpp"
#include "cyio.hpp"

CyMemory root; // The root stack. Stores all imported modules, global variables, etc.

namespace main_def { // Define properties associated with _this_ module
    obj_ptr init (CyMemory& loc) {
        obj_ptr p  = loc.allocate();
        p->properties["test_variable"] = types::CyInt(loc, 12); // int test_variable = 12;
        return p;
    }
}

obj_ptr prg_main = main_def::init(root); // Initialize this module
obj_ptr prg_cyio = cyio::init(root); // Initialize Cyan's stdio module

int main() {
    prg_cyio.call("print", {prg_main.get("test_variable")}); // Print test_variable
    return 0; // End C++ routine
}