#include "types.hpp"

CyInt::CyInt (int i) {
    value = i;
}
Object CyInt::toString () {
    return CyString(to_string(value));
}

CyString::CyString (string s) {
    value = s;
}
Object CyString::toString() {
    return *this;
}