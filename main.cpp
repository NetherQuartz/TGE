#include "tge.hpp"

#include <iostream>
#include <string>

int main() {
    //ColoredOutput("Hello world!", TGE::Colors::Red, TGE::Colors::Transparent);
    //std::cout << '\n';
    TGE::Grid grid(20, 10);
    for (int i = 0; i < grid.width(); ++i) {
        for (int j = 0; j < grid.height(); ++j) {
            grid.Place(i, j, static_cast<TGE::Colors>(rand() % 8));
        }
    }
    grid.Print();
}