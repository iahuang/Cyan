#pragma once
#include <any>
#include "memory.hpp"
#include "types/cyint.hpp"
void cyPrint(obj_ptr s) {
    std::cout << any_cast<string>(s.call("toString", NULL)->nativeValue)
              << endl;
}