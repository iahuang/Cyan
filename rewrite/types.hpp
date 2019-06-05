#include "object.hpp"
#include <string>

using namespace std;

class CyInt: public CyObject {
    public:
    int value;
    CyInt(int i);
    Object toString();
};

class CyString: public CyObject {
    public:
    string value;
    CyString(string s);
    Object toString();
};