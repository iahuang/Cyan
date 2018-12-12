/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

class Foo {
    public:
    int n = 0;
};

void overwrite(Foo& f) {
    Foo n;
    n.n = 4;
    memcpy(&f, &n, sizeof(f));
}

int main() {
    Foo a;
    overwrite(a);
    cout<<a.n<<"\n";
    return 0;
}
