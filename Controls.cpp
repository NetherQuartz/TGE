#include <iostream>
#include "tge.hpp"

namespace TGE {
    void Controls::SetInputVisibility(bool isVisible) {
        if (isVisible) {
            EchoOn();
        } else {
            EchoOff();
        }
    }
};

#if defined(_WIN32) || defined(WIN32)

#include <windows.h>
#include <conio.h>

namespace TGE {

    bool Controls::KBHit() const {
        return _kbhit();
    }

    void Controls::EchoOn() {
        DWORD mode = old_mode;
        if (echo_on) {
            return;
        } else {
            if (buffer_on) {
                mode = old_mode;
            } else {
                mode &= ~ENABLE_LINE_INPUT;
            }
            echo_on = true;
        }
        SetConsoleMode(console, mode);
    }

    void Controls::EchoOff() {
        DWORD mode = old_mode;
        if (!echo_on) {
            return;
        } else {
            if (buffer_on) {
                mode &= ~ENABLE_ECHO_INPUT;
            } else {
                mode &= (~ENABLE_ECHO_INPUT & ~ENABLE_LINE_INPUT);
            }
            echo_on = false;
        }
        SetConsoleMode(console, mode);
    }

    void Controls::BufferOn() {
        DWORD mode = old_mode;
        if (buffer_on) {
            return;
        } else {
            if (echo_on) {
                mode = old_mode;
            } else {
                mode &= ~ENABLE_ECHO_INPUT;
            }
            buffer_on = true;
        }
        SetConsoleMode(console, mode);
    }

    void Controls::BufferOff() {
        DWORD mode = old_mode;
        if (!buffer_on) {
            return;
        } else {
            if (echo_on) {
                mode &= ~ENABLE_LINE_INPUT;
            } else {
                mode &= (~ENABLE_ECHO_INPUT & ~ENABLE_LINE_INPUT);
            }
            buffer_on = false;
        }
        SetConsoleMode(console, mode);
    }

    char Controls::GetInput() const {
        if (KBHit()) {
            if (echo_on) {
                return (char)_getche();
            } else {
                return (char)_getch();
            }
        }
        return '\0';
    }

    Controls::~Controls() {
        SetConsoleMode(console, old_mode);
    }

    Controls::Controls() {
        DWORD mode;
        console = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(console, &mode);
        old_mode = mode;
        BufferOff();
    }
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

    void Controls::EchoOn() {
        termios cur_tio = old_tio;
        if (echo_on) {
            return;
        } else {
            if (buffer_on) {
                cur_tio = old_tio;
            } else {
                cur_tio.c_lflag &= ~ICANON;
            }
            echo_on = true;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::EchoOff() {
        termios cur_tio = old_tio;
        if (!echo_on) {
            return;
        } else {
            if (buffer_on) {
                cur_tio.c_lflag &= ~ECHO ;
            } else {
                cur_tio.c_lflag &= (~ECHO & ~ICANON);
            }
            echo_on = false;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::BufferOn() {
        termios cur_tio = old_tio;
        if (buffer_on) {
            return;
        } else {
            if (echo_on) {
                cur_tio = old_tio;
            } else {
                cur_tio.c_lflag &= ~ECHO;
            }
            buffer_on = true;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    void Controls::BufferOff() {
        termios cur_tio = old_tio;
        if (!buffer_on) {
            return;
        } else {
            if (echo_on) {
                cur_tio.c_lflag &= ~ICANON;
            } else {
                cur_tio.c_lflag &= (~ECHO & ~ICANON);
            }
            buffer_on = false;
        }
        tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
        tcflush(0, TCIFLUSH);
    }

    char Controls::GetInput() const {
        if (KBHit()) {
            return (char)getchar();
        }
        return '\0';
    }

    Controls::~Controls() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        tcflush(0, TCIFLUSH);
    }

    Controls::Controls() : old_tio(termios()) {
        tcgetattr(STDIN_FILENO, &old_tio);
    }
};

#endif