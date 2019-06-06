#include "primitive.hpp"
#include "cyobject.hpp"
#include "cystring.hpp"

#include <cstring>

Primitive Primitive::null = Primitive();

Primitive::Primitive() {
}

Primitive::~Primitive() {
    free_linked();
}

void Primitive::free_linked() {
    if (type == TypeCodes::Object) {
        CyObject* linked = unpack_value<CyObject*>();
        linked->remove_reference();
    }
    if (type == TypeCodes::String) {
        string* linked = unpack_value<string*>();
        delete linked;
    }
}

void Primitive::reassign(Primitive to) {
    free_linked();
    assign(to);
}

void Primitive::assign(Primitive to) {
    type = to.type;

    std::memcpy(data, to.data, 8);

    if (to.type == TypeCodes::Object) {
        CyObject* linked = unpack_value<CyObject*>();
        linked->add_reference();
    }
    if (to.type == TypeCodes::String) {
        string* linked = unpack_value<string*>();
        bind_value<string*>( new string(*linked) );
    }
}

Primitive& Primitive::operator =(const Primitive& p) {
    reassign(p);
    return *this;
}

Primitive::Primitive(const Primitive& p) {
    type = p.type;
    std::memcpy(data, p.data, 8);

    if (p.type == TypeCodes::Object) {
        CyObject* linked = unpack_value<CyObject*>();
        linked->add_reference();
    }
    if (p.type == TypeCodes::String) {
        string* linked = unpack_value<string*>();
        bind_value<string*>( new string(*linked) );
    }
}

Primitive create_int(int n) {
    Primitive p;
    p.bind_value<int>(n);
    p.type = TypeCodes::Integer;
    return p;
}

Primitive create_float(float n) {
    Primitive p;
    p.bind_value<float>(n);
    p.type = TypeCodes::Float;
    return p;
}




