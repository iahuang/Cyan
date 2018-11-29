#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "cyan.hpp"

#include "types/cyint.hpp"
#include "cyio.hpp"

CyMemory global;

int main() {
    obj_ptr o = types::CyInt(global, 1);
    cyPrint(o);
    return 0;
}