#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include "cyan.hpp"

using namespace std;

void println(string s) { cout << s << endl; }

obj_ptr CyMemory::allocate()  {
    pool.push_back(Object());
    return obj_ptr(static_cast<int>(pool.size()) - 1, this);
}
obj_ptr CyMemory::push(Object o) {
    pool.push_back(o);
    return obj_ptr(static_cast<int>(pool.size()) - 1, this);
}

class CyFunction : Object {
    // An Object subclass with its own dedicated CyMemory for local variables
   public:
    CyMemory local;
};


obj_ptr::obj_ptr(int i, CyMemory* source) {
    index = i;
    this->source = source;
}
obj_ptr::obj_ptr() {}  // Default constructor

Object* obj_ptr::getLinked() const {
    return &source->pool[index];
}

Object* obj_ptr::operator->() const { return this->getLinked(); }

obj_ptr obj_ptr::call(string name, obj_ptr* args) {
    Object* linked = getLinked();
    any body = linked->properties[name]->nativeValue;
    Fcall method = any_cast<Fcall>(body);
    return method(*this, args);
}
