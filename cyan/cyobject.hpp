#pragma once

#include "primitive.hpp"
#include "members.hpp"

#include <stdexcept>

struct CyObject: M_toString0 {
    int references = 0;

    CyObject() {
        add_reference();
    }

    void add_reference(); // ARC add reference
    void remove_reference(); // ARC remove reference
};

template <typename T>
Primitive create_obj() { // Create Primitive linked to a new CyObject
    Primitive p;
    CyObject* linked = new T();
    p.bind_value<CyObject*>(linked);
    p.type = TypeCodes::Object;
    return p;
}

Primitive from_obj(CyObject* obj); // Create a CyObject Primitive from an existing CyObject

CyObject* getobj(Primitive p); // Shorthand for p.unpack_value<CyObject*>

template <typename T>
T* method(Primitive p) { // Returns the method class T for the object
    CyObject* obj = getobj(p);
    T* ptr = dynamic_cast<T*>(obj);
    if (ptr == NULL) {
        throw std::invalid_argument("Class has no such member!");
    }
    return ptr;
}

template <typename T>
Primitive& member(Primitive p) { // Returns the member of an object from the member class T
    CyObject* obj = getobj(p);
    T* ptr = dynamic_cast<T*>(obj);
    if (ptr == NULL) {
        throw std::invalid_argument("Class has no such member!");
    }
    return ptr->value;
}
