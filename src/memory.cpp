#include "memory.hpp"

using namespace std;

void println(string s) { cout << s << endl; }

Object& Object::get(string name) {
    auto got = properties.find(name);
    if (got == properties.end()) {
        cerr << "Error: Object has no property " << name << "\n";
        abort();
    }
    return *properties[name];
}
void Object::set(string name, Object& to) {
    if (properties.find(name) != properties.end()) { // Is the reference overriding something?
        properties[name]->unlink(
            *this);  // Removed tracked reference to this object from the replaced object
    }
    properties[name] = &to;
    to.name = name;
    to.references.emplace_back(this, name);  // Track reference to this object
}

Object& Object::call(Object& self, vector<Object*> args) {
    cerr << "Error: Object "<<name<<" is not callable\n";
    abort();
}
Object& Object::call_func(string name, vector<Object*> args) {
    return get(name).call(*this,args);
}

void Object::unlink(Object& o) {  // Remove tracked references from Object o
    // WARNING: No checking here, may segfault
    typedef list<Link>::iterator iter;
    iter rem;
    for (iter link = references.begin(); link != references.end(); ++link) {
        if (link->from == &o) {
            rem = link;
        }
    }
    references.erase(rem);
}

Object& CyMemory::allocate(string name) {
    pool.emplace_back(name, this);
    return pool.back();
}

Object::Object() {

}
Object::Object(string name, CyMemory* source) {
    this->name = name;
    this->source = source;
}

Object& Object::copy(CyMemory* to) {
    if (to->scope > source->scope) {
        return *this;
    }
    Object& copy = to->allocate();
    copy.nativeValue = nativeValue;

    for (const auto& [name, prop] : properties) {
        copy.set(name, prop->copy(to));
        prop->unlink(*this);
    }
    return copy;
}

Object::~Object() {  // Object deconstructor
    if (!references.empty()) {  // Reallocate object if it is being referenced
                                // by something else
        Link bottom = references.front();  // Lowest scope
        for (Link link : references) {
            if (link.source->scope < bottom.source->scope) {
                bottom = link;
            }
        }
        CyMemory* newloc = bottom.source;  // Location to which to reallocate
        Object& copied = copy(newloc);     // Recursive copy memory
        for (Link link : references) {     // Relink all other objects which reference this object
            link.from->properties[link.as] = &copied;
        }
    }
    // Goodbye :(
}

CyMemory::CyMemory() {}

CyMemory::CyMemory(CyMemory& parent) { scope = parent.scope + 1; }

CyMemory::~CyMemory() {  // Clean up stack variables
}

class CyFunction : Object {
    // An Object subclass with its own dedicated CyMemory for local variables
   public:
    CyMemory local;
};

Link::Link(Object* from, string as) {
    this->from = from;
    this->as = as;
    source = from->source;
}
