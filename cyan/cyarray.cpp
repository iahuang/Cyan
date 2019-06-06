#include "cyarray.hpp"
#include "arithmetic.hpp"
#include <stdexcept>

#define MEMBER(obj, name) member<M_##name>(obj)
#define METHOD(obj, method) method<M_##method>(obj)->method

Primitive cy_array::get1(Primitive self, Primitive index) {
    int i = index.unpack_value<int>();
    if (i >= MEMBER(self, length).unpack_value<int>()) {
        throw out_of_range("Index out of range");
    }
    return data[i];
}

Primitive cy_array::append1(Primitive self, Primitive thing) {
    data.push_back(thing);
    MEMBER(self, length) = add(MEMBER(self, length), create_int(1));
    return Primitive::null;
}

Primitive cy_array::toString0(Primitive self) {
    return create_string("<Array>");
}