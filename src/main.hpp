#pragma once
using namespace std;

class Object;
class CyMemory;

class obj_ptr {
    public:
    int index;
    CyMemory* source;
    obj_ptr(int i, CyMemory* source);
    obj_ptr();
    Object* getLinked() const;
    Object* operator->() const;
    obj_ptr call(string name, obj_ptr* args);
};

class Object {
    public:
    int nativeType = 0;
    int debug = 20;
    unordered_map<string, obj_ptr>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
};

class CyMemory {
    public:
    vector<Object> pool;
    obj_ptr allocate();
    obj_ptr push(Object o);
    int debug = 0;
};

typedef obj_ptr (*Fcall)(obj_ptr, obj_ptr*);