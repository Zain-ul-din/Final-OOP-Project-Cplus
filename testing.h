
#ifndef TESTING_H
#define TESTING_H


#include <iostream>
#include <assert.h>
#include <functional>
#include <vector>

/*
  Custom Event Like c#
  USAGE:
    Event<void(int)> event;
    event.Add([] (int i) {
      std::cout << i << std::endl;
    });
    event.Invoke(5);
    // Enjoy the output
*/
template <class RETURN_TYPE, class... ARGS>
class Event final {
  public:

   Event () { m_listeners.clear();}
   
   void operator += (std::function<RETURN_TYPE(ARGS...)> func) { m_functions.push_back(func); } // addds event to list of functions

    // remove event from list of funtions
    void operator -= (std::function<RETURN_TYPE(ARGS...)> func) {
      for (int i = 0; i < m_functions.size(); i++) {
         if (m_functions[i] == func) {
            m_functions.erase(m_functions.begin() + i);
         }
      }
    }
    
    // fire event
    void Invoke (ARGS... args) {
      for (int i = 0; i < m_functions.size(); i++) 
         m_functions[i](args...);
    }

    ~Event () { m_listeners.clear();}
  private:
    std::vector <std::function<RETURN_TYPE(ARGS...)>> m_listeners;
}

void DoTesting () {
    std::cout << "Testing..." << std::endl;
    assert(1 == 1);
    std::cout << "Success!" << std::endl;
}



#endif // TESTING_H