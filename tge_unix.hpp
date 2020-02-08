#ifndef TGE_UNIX_HPP
#define TGE_UNIX_HPP

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

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

    class Controls final {
    public:

        bool KBHit() const {
            int bytesWaiting = 0;
            ioctl(0, FIONREAD, &bytesWaiting);
            return bytesWaiting > 0;
        }

        void EchoOn() const {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
            tcflush(0, TCIFLUSH);
        }

        void EchoOff() const {
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
            tcflush(0, TCIFLUSH);
        }

        void BufferOn() const {
            auto cur_tio = old_tio;
            cur_tio.c_lflag &= ICANON;
            tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
            tcflush(0, TCIFLUSH);
        }

        void BufferOff() const {
            auto cur_tio = old_tio;
            cur_tio.c_lflag &= (~ICANON);
            tcsetattr(STDIN_FILENO, TCSANOW, &cur_tio);
            tcflush(0, TCIFLUSH);
        }

        char GetInput() const {
            if (KBHit()) {
                return getchar();
            }
            return '\0';
        }

        ~Controls() {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
            tcflush(0, TCIFLUSH);
        }

        static Controls & Instance() {
            static Controls instance;
            return instance;
        }

        Controls(Controls const &) = delete;
        Controls(Controls &&) = delete;
        Controls &operator=(Controls const &) = delete;
        Controls &operator=(Controls &&) = delete;

    private:

        Controls() : new_tio(termios()), old_tio(termios()) {
            tcgetattr(STDIN_FILENO, &old_tio);
            new_tio = old_tio;
            new_tio.c_lflag &= (~ICANON & ~ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        }

        termios old_tio;
        termios new_tio;
    };
};

#endif