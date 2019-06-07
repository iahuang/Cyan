#include "cyobject.hpp"
#include "members.hpp"

struct cy_array: CyObject, M_length, M_get1, M_append1 {
    vector<Primitive> data; // the native c++ container
    Primitive get1(Primitive self, Primitive index); // equivalent to array[index]

    Primitive append1(Primitive self, Primitive thing); // the length of the array
    
    Primitive toString0(Primitive self); // overrides CyObject::M_toString::toString0
};