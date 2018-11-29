#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include "cyan.hpp"

using namespace std;

void println(string s) { cout << s << endl; }

class Object {
    public:
    int nativeType = 0;
    int debug = 0;
    unordered_map<string, obj_ptr>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
};

class CyMemory {
    // Stores all Cyan variables
   public:
    vector<Object> pool;
    obj_ptr allocate() {
        pool.push_back(Object());
        return obj_ptr(static_cast<int>(pool.size()) - 1, this);
    }
};

class CyFunction:Object {
    // An Object subclass with its own dedicated CyMemory for local variables
    public:
    CyMemory local;
};

CyMemory global;

obj_ptr::obj_ptr(int i, CyMemory* source) {
    index = i;
    this->source = source;
}
obj_ptr::obj_ptr() {} // Default constructor

Object* obj_ptr::getLinked() const {
    if (!&CyMemory::pool[index]) {
        return (Object*)0;
    }
    return &CyMemory::pool[index];
}

Object* obj_ptr::operator->() const { return this->getLinked(); }

obj_ptr obj_ptr::call(string name, obj_ptr* args) {
    any body = getLinked()->properties[name]->nativeValue;
    Fcall method = any_cast<Fcall>(body);
    return method(*this, args);
}

void cyPrint(obj_ptr s) {
    std::cout << any_cast<string>(s.call("toString", NULL)->nativeValue)
              << endl;
}

obj_ptr cyFunc(Fcall body) {
    obj_ptr f = CyMemory::allocate();
    f->nativeValue = body;
    return f;
}

obj_ptr toString(obj_ptr self, obj_ptr* args) {
    return cyString(to_string(any_cast<int>(self->nativeValue)));
}

obj_ptr cyInt(int s) {
    obj_ptr x = CyMemory::allocate();
    x->nativeValue = s;
    obj_ptr f = cyFunc(toString);
    x->properties["toString"] = f;
    return x;
}

obj_ptr toString2(obj_ptr self, obj_ptr* args) { return self; }

obj_ptr cyString(string s) {
    obj_ptr msg = CyMemory::allocate();
    msg->nativeValue = s;
    obj_ptr f = cyFunc(toString2);
    msg->properties["toString"] = f;
    return msg;
}

int main() {
    cyPrint(cyString("oof"));
    cyPrint(cyInt(1));
    return 0;
}