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

typedef Object (*Fcall)(vector<Object>);

class Object {
    public:
    Object(CyMemory& loc);
    int nativeType = 0;
    int debug = 20;
    int index;
    CyMemory source;
    unordered_map<string, Object>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
    Object get(string name);
    Object call(string name, vector<Object> args);
};


class CyMemory {
    public:
    vector<Object> pool;
    int debug = 0;
    void allocate(Object& o);
};

class Program : public Object {
    public:
    CyMemory scope;
};
