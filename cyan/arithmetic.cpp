#include "arithmetic.hpp"
#include <utility>
#include <stdexcept>

using namespace std;

template <int TypeCode, typename A, typename B>
Primitive _add(Primitive a, Primitive b) {
    Primitive p;
    // Resulting type is whatever c++ thinks it should be. Make sure TypeCode is set correctly
    p.bind_value((a.unpack_value<A>() + b.unpack_value<B>())); 
    p.type = TypeCode;
    return p;
}

Primitive _invalid_binary_operation(Primitive a, Primitive b) {
    // Stub function for when an type specification of an operation should be invalid
    throw invalid_argument("Cannot perform this operation on these types");
}

Primitive add(Primitive a, Primitive b) {
    // vtable[type of argument a][type of argument b] = pointer to a function that adds the two underlying c++ types

    Primitive (*vtable[][NUMTYPECODES])(Primitive, Primitive) = {
        { // int + ?
            _add<Integer, int, int>,
            _add<Integer, int, float>,
            _add<Integer, int, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        { // float + ?
            _add<Integer, float, int>,
            _add<Integer, float, float>,
            _add<Integer, float, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        { // bool + ?
            _add<Integer, bool, int>,
            _add<Integer, bool, float>,
            _add<Integer, bool, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        { // string + ?
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        { // object + ?
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        { // nulltype + ?
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        }
    };

    return vtable[a.type][b.type](a,b); // Call the correct function
}