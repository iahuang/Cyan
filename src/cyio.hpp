#pragma once
#include <any>
#include "memory.hpp"
#include "types/base.hpp"

Object& cyPrint(vector<Object*> args);

namespace cyio {
    Object& c_init(CyMemory& loc);
}