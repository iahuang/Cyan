#include "memory.hpp"

using namespace std;

Object::Object (CyMemory& loc) {
    source = loc;
    loc.allocate(*this);
}

Object Object::get (string name) {
    return properties[name];
}

Object Object::call (string name, vector<Object> args) {
    Fcall method = any_cast<Fcall>(properties[name].nativeValue);
    args.insert(args.begin(), *this);
    return method(args);
}

void CyMemory::allocate (Object& o) {
    o.index = pool.size();
    pool.push_back(Object(o));
    return obj_ptr(static_cast<int>(pool.size()) - 1, this);
}