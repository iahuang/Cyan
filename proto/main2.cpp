#include <any>
#include <iostream>
#include <unordered_map>
#include "main2.h"
using namespace std;

class Object {
    public:
    int nativeType = 0;
    unordered_map<string, Object*> properties; // Class methods are properties, like in Python
    any nativeValue;
    Object call(string name, Object args[]) {
        cout<<"internal explicit check, address: "<<properties["toString"]<<endl;
        cout<<"calling "<<name<<endl;
        cout<<"getting property"<<endl;
        Object *prop = properties[name];
        cout<<"getting function body"<<endl;
        if (!prop) {
            cout<<"oh no"<<endl;
        } else {
            cout<<"property is not NULL"<<endl;
        }
        cout<<"retrieved function, address: "<<prop<<endl;
        cout<<"debug: "<<prop->debug<<endl;
        any body = prop->nativeValue;
        cout<<"getting function"<<endl;
        Fcall method = any_cast<Fcall>(body);
        cout<<"running method"<<endl;
        return method(*this, args);
    }
    int debug = 0;
};

void cyPrint(Object *s) {
    cout<<"explicit check, address: "<<s->properties["toString"]<<endl;
    cout<<"printing"<<endl;
    Object cast = s->call("toString", NULL);
    cout<<"casting any"<<endl;
    std::cout<<any_cast<string>(cast.nativeValue)<<endl;
}
void cyFunc(Object &f, Fcall body) {
    f.nativeValue = body;
    f.debug = 2;
}
Object toString(Object &self, Object *args) {
    Object s;
    cyString(s,to_string(any_cast<int>(self.nativeValue)));
    return s;
    
}

void cyInt(Object &x, int s) {
    x.nativeValue = s;
    Object f;
    cyFunc(f, toString);
    x.properties["toString"] = &f;
}
Object toString2(Object &self, Object *args) {
    return self;
}
void cyString(Object &msg,string s) {
    msg.debug = 1;
    msg.nativeValue = s;
    Object f;
    cout<<"created function, address: "<<&f<<endl;
    cyFunc(f, toString2);
    cout<<"initialized function, address: "<<&f<<endl;
    cout<<"debug: "<<f.debug<<endl;
    msg.properties["toString"] = &f;
    cout<<"redundant confirmation, address: "<<msg.properties["toString"]<<endl;
}

int main() {
    Object s;
    cyString(s,"oof");
    cout<<"global check, address: "<<s.properties["toString"]<<endl;
    cout<<"global check, debug: "<<s.properties["toString"]->debug<<endl;
    cyPrint(&s);
    // cyPrint(cyInt(1));
    return 0;
}