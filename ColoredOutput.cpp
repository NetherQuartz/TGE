#include <iostream>
#include "tge.hpp"

#if defined(_WIN32) || defined(WIN32)

#include <windows.h>

namespace TGE {

    void ColoredOutput(std::string text, TGE::Colors foreground, TGE::Colors background) {

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

#elif defined(__unix__)

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

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

#else
#error Unknown operating system! This code has been tested only on Windows and *nix systems!
#endif