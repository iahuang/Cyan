#include "cyobject.hpp"
#include "members.hpp"

struct cy_array: CyObject, M_length, M_get1, M_append1 {
    vector<Primitive> data;
    Primitive get1(Primitive self, Primitive index);

    Primitive append1(Primitive self, Primitive thing);
    
    Primitive toString0(Primitive self);
};