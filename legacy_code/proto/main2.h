using namespace std;
class Object;
typedef Object (*Fcall)(Object&, Object*);
void cyFunc(Object &parent, Fcall body);
void cyInt(Object &parent, int s);
void cyString(Object &parent, string s);