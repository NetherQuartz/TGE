#include "tge.hpp"
#include <iostream>
#include <string>

int main() {
    TGE::ColoredOutput("L", TGE::Colors::White, TGE::Colors::Red);
    TGE::ColoredOutput("G", TGE::Colors::White, TGE::Colors::Yellow);
    TGE::ColoredOutput("B", TGE::Colors::White, TGE::Colors::Green);
    TGE::ColoredOutput("T", TGE::Colors::White, TGE::Colors::Cyan);
    TGE::ColoredOutput("Q", TGE::Colors::White, TGE::Colors::Blue);
    TGE::ColoredOutput("+", TGE::Colors::White, TGE::Colors::Magenta);
    std::cout << '\n';
}