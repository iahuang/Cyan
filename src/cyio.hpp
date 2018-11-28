void cyPrint(obj_ptr s) {
    std::cout << any_cast<string>(s.call("toString", NULL)->nativeValue)
              << endl;
}