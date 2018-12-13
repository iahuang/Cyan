#pragma once
#include <any>
#include "memory.hpp"
#include "types/base.hpp"

obj_ptr cyPrint(vector<obj_ptr> args);

namespace cyio {
    obj_ptr init(CyMemory& loc);
}