#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "types/base.hpp"
#include "cyio.hpp"
#include "memory.hpp"

using namespace std;

CyMemory root; // The root stack. Stores all imported modules, global variables, etc.

// TODO: On reallocation, objects should not be allowed to copy to a higher scope.

namespace main_def { // Define properties associated with _this_ module
    Object& init (CyMemory& loc) {
        Object& p = loc.allocate("main_module");
        return p;
    }
}

int main() {
    types::base_static::base_init(root);
    Object& prg_main = main_def::init(root); // Initialize this module
    Object& prg_cyio = cyio::c_init(root); // Initialize Cyan's stdio module
    CyMemory* sub = new CyMemory(root);
    Object& test_variable = types::CyInt(*sub, 90);
    Object& b = types::CyInt(*sub, 80);
    prg_main.set("test_variable", test_variable); // int test_variable = 12
    test_variable.set("b", b);
    delete sub;
    prg_cyio.call("print", {&prg_main.get("test_variable")}); // Print test_variable
    prg_cyio.call("print", {&prg_main.get("test_variable").get("b")}); // Print test_variable
    return 0; // End C++ routine
}