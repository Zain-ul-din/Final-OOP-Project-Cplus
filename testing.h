
#ifndef TESTING_H
#define TESTING_H


#include <iostream>
#include <assert.h>

void DoTesting () {
    std::cout << "Testing..." << std::endl;
    assert(1 == 1);
    std::cout << "Success!" << std::endl;
}

template <class CallBack>
class TestingLib {
public:
    // do test here
    private :
    vector<CallBack> callbacks;
};


#endif // TESTING_H
