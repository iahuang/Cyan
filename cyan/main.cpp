#include "primitive.hpp"
#include "cyobject.hpp"
#include "cystring.hpp"
#include "cyio.hpp"
#include <iostream>

using namespace std;

struct CustomStringConverted: CyObject { 
    Primitive tostring(Primitive p) {
        return create_string("My custom object");
    }
};

int main() {
    Primitive test = create_obj<CyObject>();
    cy_print(test);
    test = create_obj<CustomStringConverted>();
    cy_print(test);
    test = create_float(2.3);
    cy_print(test);
}