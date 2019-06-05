#include "cyobject.hpp"

void CyObject::add_reference() {
    references++;
}

void CyObject::remove_reference() {
    references--;
    if (references == 0) {
        delete this; // yeetus fetus
    }
}

Primitive from_obj(CyObject* obj) {
    Primitive p;
    p.bind_value<CyObject*>(obj);
    p.type = TypeCodes::Object;
    return p;
}

CyObject* getobj(Primitive p) {
    if (p.type != TypeCodes::Object) {
        throw std::invalid_argument("Argument is not an Object!");
    }
    return p.unpack_value<CyObject*>();
}