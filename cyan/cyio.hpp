#pragma once

#include "primitive.hpp"
#include "cyobject.hpp"
#include <string>


template <typename T>
string _tostring(Primitive p) {
    return to_string(p.unpack_value<T>()); // native to_string defined in <string>
}

string _obj_tostring(Primitive p);
string _tostring_stub(Primitive p);
string _str_tostring(Primitive p);

void cy_print(Primitive p);