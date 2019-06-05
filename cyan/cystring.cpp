#include "cystring.hpp"

Primitive create_string (string source) {
    Primitive p;
    p.bind_value<string*>( new string(source) );
    p.type = TypeCodes::String;
    return p;
}