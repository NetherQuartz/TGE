#include <iostream>
#include "tge.hpp"

#if defined(_WIN32) || defined(WIN32)

#include <windows.h>

namespace TGE {


};

#elif defined(__unix__)

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

namespace TGE {

    bool Controls::KBHit() const {
        int bytesWaiting = 0;
        ioctl(0, FIONREAD, &bytesWaiting);
        return bytesWaiting > 0;
    }

    void Controls::EchoOn() const {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::EchoOff() const {
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::BufferOn() const {
        auto cur_tio = old_tio;
        cur_tio.c_lflag &= ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::BufferOff() const {
        auto cur_tio = old_tio;
        cur_tio.c_lflag &= (~ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    char Controls::GetInput() const {
        if (KBHit()) {
            return getchar();
        }
        return '\0';
    }

    Controls::~Controls() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        tcflush(0, TCIFLUSH);
    }

    Controls::Controls() : new_tio(termios()), old_tio(termios()) {
        tcgetattr(STDIN_FILENO, &old_tio);
        new_tio = old_tio;
        new_tio.c_lflag &= (~ICANON & ~ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    }
};

#else
#error Unknown operating system! This code has been tested only on Windows and *nix systems!
#endif