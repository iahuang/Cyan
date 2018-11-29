#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "memory.hpp"
#include "program.hpp"

#include "types/cyint.hpp"
#include "cyio.hpp"

Program prg;

int main() {
    obj_ptr o = types::CyInt(prg.scope, 1);
    cyPrint(o);
    return 0;
}