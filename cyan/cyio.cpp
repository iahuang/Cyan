#include "cyio.hpp"
#include "primitive.hpp"
#include "cyobject.hpp"
#include <string>


string _obj_tostring(Primitive p) {
    Primitive s = method<M_toString0>(p)->toString0(p);
    return *(s.unpack_value<string*>());
}
string _tostring_stub(Primitive p) {
    return "null";
}
string _str_tostring(Primitive p) {
    return *(p.unpack_value<string*>());
}

void cy_print(Primitive p) {
    string (*ts_callbacks[])(Primitive) = {
        _tostring<int>,
        _tostring<float>,
        _tostring<bool>,
        _str_tostring,
        _obj_tostring,
        _tostring_stub

    };
    cout<<ts_callbacks[p.type](p)<<endl;
}