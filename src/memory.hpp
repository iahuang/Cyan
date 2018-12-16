#pragma once
#include <any>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <list>

using namespace std;
class Object;
class CyMemory;
class Program;

typedef Object& (*Fcall)(Object& self, vector<Object*>);

class Object {
    public:
    int nativeType = 0;
    int debug = 20;
    unordered_map<string, Object*>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
    bool value;
    vector<CyMemory*> references;
    Object();
    CyMemory* source;

    Object& get(string name);
    void set(string name, Object& to);

    Object& call(string name, vector<Object*> args);
};


class CyMemory {
    public:
    int scope = 0;
    list<Object> pool;
    Object& allocate();
    int debug = 0;
    CyMemory (CyMemory& parent);
    CyMemory ();
    ~CyMemory (); // Clean up any stored variables
};
