#ifndef TGE_WIN_HPP
#define TGE_WIN_HPP

#include <iostream>
#include <windows.h>
#include "tge.hpp"

namespace TGE {

    inline void ColoredOutput(std::string text, TGE::Colors foreground, TGE::Colors background) {

        WORD attribs = 0;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        /* Save current attributes */
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        switch (foreground) {
            case Colors::Black:
            case Colors::Transparent:
                attribs |= 0;
                break;
            case Colors::Red:
                attribs |= FOREGROUND_RED;
                break;
            case Colors::Green:
                attribs |= FOREGROUND_GREEN;
                break;
            case Colors::Yellow:
                attribs |= FOREGROUND_RED | FOREGROUND_GREEN;
                break;
            case Colors::Blue:
                attribs |= FOREGROUND_BLUE;
                break;
            case Colors::Magenta:
                attribs |= FOREGROUND_RED | FOREGROUND_BLUE;
                break;
            case Colors::Cyan:
                attribs |= FOREGROUND_GREEN | FOREGROUND_BLUE;
                break;
            case Colors::White:
                attribs |= FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
                break;
        }
        switch (background) {
            case Colors::Black:
            case Colors::Transparent:
                attribs |= 0;
                break;
            case Colors::Red:
                attribs |= BACKGROUND_RED;
                break;
            case Colors::Green:
                attribs |= BACKGROUND_GREEN;
                break;
            case Colors::Yellow:
                attribs |= BACKGROUND_RED | BACKGROUND_GREEN;
                break;
            case Colors::Blue:
                attribs |= BACKGROUND_BLUE;
                break;
            case Colors::Magenta:
                attribs |= BACKGROUND_RED | BACKGROUND_BLUE;
                break;
            case Colors::Cyan:
                attribs |= BACKGROUND_GREEN | BACKGROUND_BLUE;
                break;
            case Colors::White:
                attribs |= BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
                break;
        }
        SetConsoleTextAttribute(hConsole, attribs);
        std::cout << text;
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }
};

#endif