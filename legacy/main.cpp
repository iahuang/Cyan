#include <string>
#include <stdio.h>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

class Object {
    public:
    typedef Object& (*fcall)(Object&, Object*);//function<Object&(Object&, Object*)> fcall;
    static Object Null;
    map<string, Object> objects;
    unordered_map<string, fcall> methods;

    Object() {
        
    }
    Object &call(string name, Object args[]) {
        Object& n = methods[name](*this,args);
        return n;
    }

};



class Native: public Object {
    public:
    int type;
};

class Int: public Native {
    public:
    int value;
    Int(int value) {
        this->value = value;
        type = 0;
    }

};

class String: public Native {
    public:
    string value;

    static Object &toString(Object &what, Object *args) {
        return what;
    }
    
    String(string value) {
        this->value = value;
        type = 1;
        
        methods["toString"] = toString;
    }
};

Object Object::Null = Object();

void print(Object &s) {
    Object *obj = &s.call("toString", {});
    String *sObj = (String*)obj;
    std::cout << sObj->value << "\n"; 
}

int main() {
    String hello = String("Hello World!");

    print(hello);
    return 0;
}