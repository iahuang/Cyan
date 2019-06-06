#include "arithmetic.hpp"
#include <utility>
#include <stdexcept>

using namespace std;

template <int TypeCode, typename A, typename B>
Primitive _add(Primitive a, Primitive b) {
    Primitive p;
    p.bind_value((a.unpack_value<A>() + b.unpack_value<B>()));
    p.type = TypeCode;
    return p;
}

Primitive _invalid_binary_operation(Primitive a, Primitive b) {
    throw invalid_argument("Cannot perform this operation on these types");
}

Primitive add(Primitive a, Primitive b) {
    Primitive (*vtable[][NUMTYPECODES])(Primitive, Primitive) = {
        {
            _add<Integer, int, int>,
            _add<Integer, int, float>,
            _add<Integer, int, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        {
            _add<Integer, float, int>,
            _add<Integer, float, float>,
            _add<Integer, float, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        {
            _add<Integer, bool, int>,
            _add<Integer, bool, float>,
            _add<Integer, bool, bool>,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        {
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        {
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        },
        {
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation,
            _invalid_binary_operation
        }
    };

    return vtable[a.type][b.type](a,b);
}