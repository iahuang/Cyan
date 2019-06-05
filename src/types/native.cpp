#include "native.hpp"

Object& Function::call(Object& self, vector<Object*> args) {
    return body(self, args);
}
Function::Function (string name, CyMemory* source) : Object(name, source) {
    cout<<"called function constructor\n";
}