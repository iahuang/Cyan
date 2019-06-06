#pragma once

#include "primitive.hpp"
#include "members.hpp"

#include <stdexcept>

struct CyObject: M_toString0 {
    int references = 0;

    CyObject() {
        add_reference();
    }

    void add_reference();
    void remove_reference();
};

template <typename T>
Primitive create_obj() {
    Primitive p;
    CyObject* linked = new T();
    p.bind_value<CyObject*>(linked);
    p.type = TypeCodes::Object;
    return p;
}

Primitive from_obj(CyObject* obj);

CyObject* getobj(Primitive p);

template <typename T>
T* method(Primitive p) {
    CyObject* obj = getobj(p);
    T* ptr = dynamic_cast<T*>(obj);
    if (ptr == NULL) {
        throw std::invalid_argument("Class has no such member!");
    }
    return ptr;
}

template <typename T>
Primitive& member(Primitive p) {
    CyObject* obj = getobj(p);
    T* ptr = dynamic_cast<T*>(obj);
    if (ptr == NULL) {
        throw std::invalid_argument("Class has no such member!");
    }
    return ptr->value;
}
