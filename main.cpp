#include "tge.hpp"

#include <iostream>
#include <string>
#include <unistd.h>

int main() {
    //ColoredOutput("Hello world!", TGE::Colors::Red, TGE::Colors::Transparent);
    //std::cout << '\n';
    std::cin.tie(nullptr);
    //std::ios::sync_with_stdio(false);
    TGE::Grid grid(30, 30);
    int i = 0, j = 0;
    for (int k = 0; k < 10000; ++k) {
        std::cout << "\033c";
//        for (int i = 0; i < grid.width(); ++i) {
//            for (int j = 0; j < grid.height(); ++j) {
//                grid.Place(i, j, static_cast<TGE::Colors>(rand() % 8));
//            }
//        }
        grid.Place(i, j, TGE::Colors::Yellow);
        ++i;
        if (i > grid.width() - 1) {
            i = 0;
            j++;
        }
        if (j > grid.height() - 1) {
            break;
        }
        grid.Print();
        usleep(1e6 / 30);
        //std::cout << i << " " << j << '\n';
    }

}