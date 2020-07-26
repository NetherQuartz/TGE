#ifndef TGE_HPP
#define TGE_HPP

#if !(defined(__unix__) || defined(__APPLE__)) && !(defined(_WIN32) || defined(WIN32))
#error Unknown operating system! This code has been tested only on Windows and *nix systems!
#endif

#include <vector>
#include <string>
#include <set>

#if defined(__unix__) || defined(__APPLE__)
#include <termios.h>
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

namespace TGE {

    struct Point final {
        int x;
        int y;
        int z;
    };

    enum class Colors {
        Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Transparent
    };

    class GameObject {
    public:

        explicit GameObject(Point, std::vector<std::vector<Colors>>);

        virtual ~GameObject();

        Point getPosition() const;
        void setPosition(Point);
        void move(Point);

        std::vector<std::vector<Colors>> & body();
        const std::vector<std::vector<Colors>> & body() const;

        static bool compareByZ(const GameObject *, const GameObject *);

    protected:
        
        Point position_;
        std::vector<std::vector<Colors>> body_;
    };

    class Grid {
    public:

        Grid(unsigned width, unsigned height, Colors fill = Colors::Transparent);
        ~Grid();

        void Draw();

        void Place(const GameObject & gameObject);

        unsigned width() const;
        unsigned height() const;

    private:

        std::vector<std::vector<Colors>> grid_;
        std::set<const GameObject*, decltype(GameObject::compareByZ)*> gameObjects_;
        unsigned width_;
        unsigned height_;
    };

    class Controls final {
    public:

        bool KBHit() const;
        char GetInput() const;
        void SetInputVisibility(bool);
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

        void EchoOn();
        void EchoOff();
        void BufferOn();
        void BufferOff();

        bool buffer_on = true;
        bool echo_on = true;

#if defined(__unix__) || defined(__APPLE__)
        termios old_tio;
#elif defined(_WIN32) || defined(WIN32)
        HANDLE console;
        DWORD old_mode;
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

    void ColoredOutput(const std::string & text, Colors foreground, Colors background = Colors::Transparent);
    void ClearScreen();
};

#endif