
#ifndef TESTING_H
#define TESTING_H


#include <iostream>
#include <assert>

void DoTesting () {
    std::cout << "Testing..." << std::endl;
    assert(1 == 1);
    std::cout << "Success!" << std::endl;
}

#endif // TESTING_H