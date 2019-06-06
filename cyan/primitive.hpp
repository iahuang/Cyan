#pragma once

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum TypeCodes {
    Integer,
    Float,
    Boolean,
    String,
    Object,
    Null,
    NUMTYPECODES
};


struct Primitive {
    int type = TypeCodes::Null;
    byte data[8];

    static Primitive null;

    ~Primitive();
    Primitive();

    void free_linked();

    template <typename T>
    void bind_value(T value) {
        *(T*)(data) = value;
    }

    template <typename T>
    T unpack_value() const {
        return *(T*)(data);
    }

    void assign(Primitive to);
    void reassign(Primitive to);

    Primitive(const Primitive&);
    Primitive& operator =(const Primitive&);
};

Primitive create_int(int);
Primitive create_float(float);