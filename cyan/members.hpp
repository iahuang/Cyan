#pragma once

#include "primitive.hpp"
#include "cystring.hpp"

struct M_toString {
    virtual Primitive tostring(Primitive self);
};
