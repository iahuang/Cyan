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
        any body = properties[name]->nativeValue;
        Fcall method = any_cast<Fcall>(body);
        return method(this, args);
    }
};

void cyPrint(Object *s) {
    std::cout<<any_cast<string>(s->call("toString", NULL).nativeValue)<<endl;
}
Object *cyFunc(Fcall body) {
    Object *f = new Object();
    f->nativeValue = body;
    return f;
}
Object toString(Object *self, Object *args) {
    return *cyString(to_string(any_cast<int>(self->nativeValue)));
}

Object *cyInt(int s) {
    Object *x = new Object();
    x->nativeValue = s;
    x->properties["toString"] = cyFunc(toString);;
    return x;
}
Object toString2(Object *self, Object *args) {
    return *self;
}
Object *cyString(string s) {
    Object *msg = new Object();
    msg->nativeValue = s;
    msg->properties["toString"] = cyFunc(toString2);
    return msg;
}

int main() {
    cyPrint(cyString("oof"));
    cyPrint(cyInt(1));
    return 0;
}