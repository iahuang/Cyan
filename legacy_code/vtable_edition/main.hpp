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
typedef obj_ptr (*Fcall)(obj_ptr, obj_ptr*);
obj_ptr cyFunc(Fcall body);
obj_ptr cyInt(int s);
obj_ptr cyString(string s);
