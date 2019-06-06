#include "primitive.hpp"
#include "cyobject.hpp"
#include "cystring.hpp"
#include "cyio.hpp"
#include "cyarray.hpp"
#include <iostream>

#define MEMBER(obj, name) member<M_##name>(obj)
#define METHOD(obj, name) method<M_##name>(obj)->name

using namespace std;

struct CustomStringConverted: CyObject { 
    Primitive toString0(Primitive p) {
        return create_string("My custom object");
    }
};

int main() {
    Primitive test = create_obj<cy_array>();
    cy_print(test);
    METHOD(test, append1)(test, create_int(2));
    cy_print(METHOD(test, get1)(test, create_int(0)));
    cy_print(member<M_length>(test));
    test = create_obj<CustomStringConverted>();
    cy_print(test);
    test = create_float(4.3);
    cy_print(test);
}