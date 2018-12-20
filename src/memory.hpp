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

class Link {
    public:
    Object* from;
    string as;
    CyMemory* source;

    Link(Object* from, string as);
    Link();
};

class Object {
    public:
    int nativeType = 0;
    int debug = 20;
    unordered_map<string, Object*>
        properties;  // Class methods are properties, like in Python
    any nativeValue;
    bool value;
    list<Link> references;
    CyMemory* source;
    string name;

    Object();
    Object(string name, CyMemory* source);
    ~Object();
    Object& copy(CyMemory* to);
    
    Object& get(string name);
    void set(string name, Object& to);
    Object& call(string name, vector<Object*> args);
    void unlink(Object& o);

};

class CyMemory {
    public:
    string name = "undefined";
    int scope = 0;
    list<Object> pool;
    Object& allocate(string name="");
    int debug = 0;
    CyMemory (CyMemory& parent);
    CyMemory ();
    ~CyMemory (); // Clean up any stored variables
};
