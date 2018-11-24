using namespace std;
class Object;
typedef Object (*Fcall)(Object*, Object*);
Object *cyFunc(Fcall body, int args);
Object *cyInt(int s);
Object *cyString(string s);