#include "members.hpp"
#include "cyobject.hpp"
#include "cyio.hpp"
#include <sstream>

Primitive M_toString0::toString0(Primitive self) {
    std::stringstream sstream;
    sstream << std::hex << self.unpack_value<unsigned long long>();
    std::string result = sstream.str();
    Primitive output = create_string("<Object at 0x"+result+">");
    return output;
}