#pragma once
#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;
class Object;
class CyMemory;
class Program;



class obj_ptr {
    public:
    int index;
    CyMemory* source;
    obj_ptr(int i, CyMemory* source);
    obj_ptr();
    Object* getLinked() const;
    Object* operator->() const;
    obj_ptr call(string name, vector<obj_ptr> args);
    obj_ptr get(string name);
};

typedef obj_ptr (*Fcall)(vector<obj_ptr>);

class Object {
    public:
    int nativeType = 0;
    int debug = 20;
    unordered_map<string, obj_ptr>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
    obj_ptr get(string name);
};


class CyMemory {
    public:
    vector<Object> pool;
    obj_ptr allocate();
    obj_ptr push(Object o);
    int debug = 0;
};

class Program : public Object {
    public:
    CyMemory scope;
};
