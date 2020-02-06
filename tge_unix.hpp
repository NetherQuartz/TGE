#ifndef TGE_UNIX_HPP
#define TGE_UNIX_HPP

#include <iostream>
#include "tge.hpp"

namespace TGE {
    inline void ColoredOutput(std::string text, Colors foreground, Colors background) {
        std::string prefix = "\033[";
        switch (foreground) {
            case Colors::Black:
                prefix += "30";
                break;
            case Colors::Red:
                prefix += "31";
                break;
            case Colors::Green:
                prefix += "32";
                break;
            case Colors::Yellow:
                prefix += "33";
                break;
            case Colors::Blue:
                prefix += "34";
                break;
            case Colors::Magenta:
                prefix += "35";
                break;
            case Colors::Cyan:
                prefix += "36";
                break;
            case Colors::White:
                prefix += "37";
                break;
            case Colors::Transparent:
                break;
        }
        if (background != Colors::Transparent && foreground != Colors::Transparent) {
            prefix += ";";
        }
        switch (background) {
            case Colors::Black:
                prefix += "40";
                break;
            case Colors::Red:
                prefix += "41";
                break;
            case Colors::Green:
                prefix += "42";
                break;
            case Colors::Yellow:
                prefix += "43";
                break;
            case Colors::Blue:
                prefix += "44";
                break;
            case Colors::Magenta:
                prefix += "45";
                break;
            case Colors::Cyan:
                prefix += "46";
                break;
            case Colors::White:
                prefix += "47";
                break;
            case Colors::Transparent:
                break;
        }
        prefix += "m";
        std::cout << prefix << text << "\033[0m";
    }
};

#endif