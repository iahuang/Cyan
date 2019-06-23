#pragma once

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

enum TypeCodes {
    Null,
    Integer,
    Float,
    Boolean,
    String,
    Object,
    NUMTYPECODES
};


struct Primitive {
    int type = TypeCodes::Null;
    byte data[8];

    static Primitive null;

    ~Primitive();
    Primitive();

    // ARC method to unreference the object that was potentially stored in this Primitive on reassignment
    void free_linked();

    // Write a c++ type into the data buffer 
    template <typename T>
    void bind_value(T value) {
        *(T*)(data) = value;
    }

    // Read the c++ type from the data buffer
    template <typename T>
    T unpack_value() const {
        return *(T*)(data);
    }

    void assign(Primitive to);      // var thing = to
    void reassign(Primitive to);    // thing = to

    Primitive(const Primitive&);
    Primitive& operator =(const Primitive&);
};

Primitive create_int(int);      // Constructors for primitive datatypes
Primitive create_float(float);