#include "properties.hpp"

Object P_toString::toString() {
    return CyString("<Object at "+(int)(this)+">");
}