#ifndef TGE_HPP
#define TGE_HPP

#if !defined(__unix__) && !(defined(_WIN32) || defined(WIN32))
#error Unknown operating system! This code has been tested only on Windows and *nix systems!
#endif

#include <vector>
#include <string>

#ifdef __unix__
#include <termios.h>
#endif

namespace TGE {

    struct Point final {
        unsigned x;
        unsigned y;
    };

    enum class Colors {
        Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Transparent
    };

    class GameObject {
    public:

        explicit GameObject(Point);
        GameObject(unsigned, unsigned);

        virtual ~GameObject();

        Point position() const;

    protected:
        
        Point position_;
    };

    class Grid {
    public:

        Grid(unsigned width, unsigned height);
        ~Grid();

        void Print() const;

        void Place(unsigned x, unsigned y, Colors color);
        void Place(Point position, Colors color);
        void Place(const GameObject & gameObject);

        unsigned width() const;
        unsigned height() const;

    private:

        std::vector<std::vector<Colors>> grid_;
        unsigned width_;
        unsigned height_;
    };

    class Controls final {
    public:

        bool KBHit() const;
        void EchoOn();
        void EchoOff();
        void BufferOn();
        void BufferOff();
        char GetInput() const;
        ~Controls();

        static Controls & Instance() {
            static Controls instance;
            return instance;
        }

        Controls(Controls const &) = delete;
        Controls(Controls &&) = delete;
        Controls &operator=(Controls const &) = delete;
        Controls &operator=(Controls &&) = delete;

    private:

        Controls();

#ifdef __unix__
        bool buffer_on = true;
        bool echo_on = true;
        termios old_tio;
#endif
    };

    class Game {
    public:

        Game(unsigned, unsigned);
        virtual ~Game();
    
    protected:

        Grid grid_;

    private:

        Game();
        Game operator=(const Game &);

    };

    void ColoredOutput(std::string text, Colors foreground, Colors background = Colors::Transparent);
};

#endif