#include <iostream>
#include "tge.hpp"

#if defined(_WIN32) || defined(WIN32)

namespace TGE {
    void ClearScreen() {
        system("cls");
    }
};

#elif defined(__unix__) || defined(__APPLE__)

namespace TGE {
    void ClearScreen() {
        std::cout << "\033c";
        std::cout.flush();
    }
};

#endif