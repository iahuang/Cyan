#include "../memory.hpp"

class Program : public Object {
    public:
    CyMemory scope;
};

class Function : public Object {
    public:
    Fcall body;
    Object& call(Object& self, vector<Object*> args);
    //using Object::Object;
    Function (string name, CyMemory* source);
};

class TypedMethod : public Object {
    public:
    unordered_map<int, Fcall> variants;

};