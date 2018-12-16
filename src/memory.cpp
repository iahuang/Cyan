#include "memory.hpp"

using namespace std;

void println(string s) { cout << s << endl; }

Object& Object::get(string name) {
    auto got = properties.find(name);
    if (got == properties.end()) {
        cerr<<"Error: Object has no property "<<name<<"\n";
        abort();
    }
    return *properties[name];
}
void Object::set(string name, Object& to) {
    properties[name] = &to;
    if (!to.value) {
        to.references.push_back(source);
    }
}

Object& Object::call(string name, vector<Object*> args) {
    auto f = any_cast<Fcall>(get(name).nativeValue);
    return f(*this, args);
}

Object& CyMemory::allocate() {
    auto o = Object();
    o.source = this;
    pool.push_back(o);
    return pool.back();
}

Object::Object() {}

CyMemory::CyMemory() {
    
}

CyMemory::CyMemory(CyMemory& parent) {
    scope = parent.scope+1;
}

CyMemory::~CyMemory() { // Clean up stack variables
    
}

class CyFunction : Object {
    // An Object subclass with its own dedicated CyMemory for local variables
   public:
    CyMemory local;
};

